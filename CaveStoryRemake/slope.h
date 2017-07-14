/*************************************************************************
File name:		slope.h
Description:	handles the slopes(hypotenuse line between 2 points)
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef SLOPE_H
#define SLOPE_H

//includes
#include "globals.h"
#include <cmath>
#include "rectangle.h"

//declarations

//Class definition
class Slope {
public:
	Slope() {}	// default constructor

	Slope(Vector2 p1, Vector2 p2) :
		_v2P1(p1),
		_v2P2(p2)
	{
		_fSlope = CalculateSlope(p1, p2);
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
	//Determines if the object intersects the slope
	const bool CollidesWith(const Rectangle &other) const {
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
				other.GetBottom() >= this->_v2P1.y);
	}
private:
	Vector2 _v2P1, _v2P2;	//points on the slope
	float _fSlope;
};
#endif	//end of #include guard