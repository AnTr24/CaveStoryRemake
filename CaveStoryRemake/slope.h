/*************************************************************************
File name:		slope.h
Description:	handles the slopes(hypotenuse line between 2 points)
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef SLOPE_H
#define SLOPE_H

//includes
#include "globals.h"
#include "rectangle.h"

#include <cmath>
#include <algorithm>

//declarations

//Class definition
class Slope {
public:
	enum SlopeType {
		Ceiling,
		Ground
	};

	SlopeType Type;

	Slope() {}	// default constructor

	Slope(Vector2 p1, Vector2 p2, SlopeType slopeType) :
		_v2P1(p1),
		_v2P2(p2),
		Type(slopeType)
	{
		_fSlope = CalculateSlope(p1, p2);
		SetBoundingBox(p1, p2);
	}

	//static float CalculateLength
	//calculates the distance between 2 points
	static float CalculateSlope(Vector2 p1, Vector2 p2) {

		return (p2.x - p1.x) == 0 ? 0 : ((float)p2.y - (float)p1.y) / ((float)p2.x - (float)p1.x);
	}

	//const inline Vector2 GetP1
	//returns first point of slope
	const inline Vector2 GetP1() const {
		return this->_v2P1;
	}

	//const inline Vector2 GetP2
	//returns 2nd point of slope
	const inline Vector2 GetP2() const {
		return this->_v2P2;
	}

	//const inline float GetSlope
	//returns length of slope
	const inline float GetSlope() const {
		return this->_fSlope;
	}

	//const bool CollidesWith
	//Determines if the rectangle intersects the slope
	const bool CollidesWith(const Rectangle &other) const {
		/*
		//Note: this collision only checks if 'other' is within the bounding rectangle of the slopes....
		return
			(// [/] slope, p2 on left
				other.GetRight() >= this->_v2P2.x &&
				other.GetLeft() <= this->_v2P1.x&&
				other.GetTop() <= this->_v2P2.y &&
				other.GetBottom() >= this->_v2P1.y) ||

			(// [/] slope, p1 on left
				other.GetRight() >= this->_v2P1.x &&
				other.GetLeft() <= this->_v2P2.x&&
				other.GetTop() <= this->_v2P1.y &&
				other.GetBottom() >= this->_v2P2.y) ||
			(// [\] slope, p2 on left
				other.GetRight() >= this->_v2P2.x &&
				other.GetLeft() <= this->_v2P1.x&&
				other.GetTop() <= this->_v2P1.y &&
				other.GetBottom() >= this->_v2P2.y) ||
			(// [\] slope, p1 on left
				other.GetRight() >= this->_v2P1.x &&
				other.GetLeft() <= this->_v2P2.x&&
				other.GetTop() <= this->_v2P2.y &&
				other.GetBottom() >= this->_v2P1.y);*/

		//Initial check: if collision occurs in bounding boxes
		if (!this->_rBoundingBox.CollidesWith(other))
			return false;

		//Within bounding box, further collision checking below:

		//Refinement: check if any of the 4 lines of the rectangle intersect with the slope
		//Using intersection of 2 line segments for slope collision detection:
		//http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
		//Two segments ab and cd intersect if
		//• the endpoints a and b are on opposite sides of the line ←→cd, and
		//• the endpoints c and d are on opposite sides of the line ←→ab.
		//the lines are colinear(same slope) and intersect in x and y ranges/projections

		//ensure p is leftmost point and q is rightmost
		Vector2 p1;
		Vector2 q1;

		if (this->_v2P1.x < this->_v2P2.x)
		{
			p1 = this->_v2P1;
			q1 = this->_v2P2;
		}
		else
		{
			p1 = this->_v2P2;
			q1 = this->_v2P1;
		}

		Vector2 pTL = other.GetTopLeft();
		Vector2 qTR = other.GetTopRight();
		Vector2 pBL = other.GetBottomLeft();
		Vector2 qBR = other.GetBottomRight();

		//Check itnersection on each side of rectangle
		return 
		LineSegmentIntersection(p1, q1, pTL, qTR) ||	//top-side itnersection
		LineSegmentIntersection(p1, q1, pBL, qBR) ||	//bottom-side itnersection
		LineSegmentIntersection(p1, q1, pTL, pBL) ||	//left-side itnersection
		LineSegmentIntersection(p1, q1, qTR, qBR);		//right-side itnersection
	}

	//const bool LineSegmentIntersection
	//using angle orientation of 2 linesegments, determine if ther intersect
	const bool LineSegmentIntersection(Vector2 p1, Vector2 q1, Vector2 p2, Vector2 q2) const{
		int o1, o2, o3, o4;	//orientation values
		
		o1 = Orientation(p1, q1, p2);
		o2 = Orientation(p1, q1, q2);

		o3 = Orientation(p2, q2, p1);
		o4 = Orientation(p2, q2, q1);

		//General case: Check if orientations are different
		if (o1 != o2 && o3 != o4)
			return true;

		//Special Cases: dealing with the colinear:
		// p1, q1 and p2 are colinear and p2 lies on segment p1q1
		if (o1 == 0 && OnSegment(p1, p2, q1)) return true;

		// p1, q1 and p2 are colinear and q2 lies on segment p1q1
		if (o2 == 0 && OnSegment(p1, q2, q1)) return true;

		// p2, q2 and p1 are colinear and p1 lies on segment p2q2
		if (o3 == 0 && OnSegment(p2, p1, q2)) return true;

		// p2, q2 and q1 are colinear and q1 lies on segment p2q2
		if (o4 == 0 && OnSegment(p2, q1, q2)) return true;

		return false; // Doesn't fall in any of the above cases
	}

	//const int Orientation
	//Determines the direction of rotation
	//returns:
	//0 ->a,b,c are colinear
	//1-> clockwise
	//2->counter-clockwise
	const int Orientation(Vector2 p, Vector2 q, Vector2 r) const {
		// See http://www.geeksforgeeks.org/orientation-3-ordered-points/

		//TL;DR: given 3 ordered points, we can create two triangles(see link for diagram)
		//using the slopes(m and n) between the points, we can determine the orientation: 
		/*If  m < n, the orientation is counterclockwise (left turn)
		  If  m = n, the orientation is collinear
		  If  m > n, the orientation is clockwise (right turn)*/

		//slope m
		//m = (q.y - p.y) / (q.x - p.y)

		//slope n
		//n = (r.y - q.y) / (r.x - q.y)

		//val = m - n

		//simplified
		int val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

		if (val == 0) return 0;  // colinear

		return (val > 0) ? 1 : 2; // clock or counterclock wise
	}

	// Given three colinear points p, q, r, the function checks if
	// point q lies on line segment 'pr'
	const bool OnSegment(Vector2 p, Vector2 q, Vector2 r) const
	{
		//check if point q is within the x and y ranges of linesegment 'pr'
		if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
			q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
			return true;

		return false;
	}

private:
	Vector2 _v2P1, _v2P2;	//points on the slope
	float _fSlope;
	Rectangle _rBoundingBox;

	void SetBoundingBox(Vector2 p1, Vector2 p2) {
		int x = std::min(_v2P1.x, _v2P2.x);
		int y = std::min(_v2P1.y, _v2P2.y);
		int w = std::abs(_v2P1.x - _v2P2.x);
		int h = std::abs(_v2P1.y - _v2P2.y);

		this->_rBoundingBox = Rectangle(x, y, w, h);
	}
};
#endif	//end of #include guard