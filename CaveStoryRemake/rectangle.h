/*************************************************************************
File name:		rectangle.h
Description:	Header file for rectangle class. Rectangle is used for collisions
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef RECTANGLE_H
#define RECTANGLE_H

//includes
#include "globals.h"
//declarations

//Class definition
class Rectangle {
public:
	Rectangle() {}	// default constructor

	Rectangle(int x, int y, int width, int height) :
		_x(x),
		_y(y),
		_width(width),
		_height(height)
	{}

	//GetCenter[X/Y] Functions: retrieves center value for the rectangle 
	const int GetCenterX()const { return this->_x + this->_width / 2; }
	const int GetCenterY()const { return this->_y + this->_height / 2; }

	//GetLeft : Retrieves the left side of the reactangle
	const int GetLeft() const { return this->_x; }

	//GetRight : Retrieves the right side of the reactangle
	const int GetRight() const { return this->_x + this->_width; }

	//GetTop : Retrieves the top side of the reactangle
	const int GetTop() const { return this->_y; }

	//GetBottom : Retrieves the bottom side of the reactangle
	const int GetBottom() const { return this->_y + this->_height; }

	//GetTopLeft : Retrieves the top-left point of the reactangle
	const Vector2 GetTopLeft() const { return Vector2(this->_x,this->_y); }

	//GetTopRight : Retrieves the top-right point of the reactangle
	const Vector2 GetTopRight() const { return  Vector2(this->GetRight(),this->_y); }

	//GetBottomLeft : Retrieves the bottom-left point of the reactangle
	const Vector2 GetBottomLeft() const { return Vector2(this->_x, this->GetBottom()); }

	//GetBottomRight : Retrieves the bottom-right point of the reactangle
	const Vector2 GetBottomRight() const { return Vector2(GetRight(), this->GetBottom()); }

	//GetWidth - Getter function for width
	const int GetWidth() const { return this->_width; }

	//GetHeight - Getter function for height
	const int GetHeight() const { return this->_height; }

	//GetSide - Returns value of a Side
	const int GetSide(const sides::Side side) const {
		return
			side == sides::TOP ? this->GetTop() :
			side == sides::BOTTOM ? this->GetBottom() :
			side == sides::LEFT ? this->GetLeft() :
			side == sides::RIGHT ? this->GetRight() :
			sides::NONE;
	}
	//bool CollidesWith
	//Takes in another rectangle and checks if the two are colliding
	const bool CollidesWith(const Rectangle &other) const {
		return
			this->GetRight() >= other.GetLeft() &&
			this->GetLeft() <= other.GetRight() &&
			this->GetTop() <= other.GetBottom() &&
			this->GetBottom() >= other.GetTop();
	}

	//Check if rectangle has valid dimensions
	const bool  IsValidRectangle() const {
		return (this->_x >= 0 && this->_y >= 0 && this->_width >= 0 && this->_height >= 0);
	}

	//Return a derefernced(instance) of this rectangle
	const inline Rectangle GetRect() const { return *this; }

private:
	int _x, _y, _width, _height;
};
#endif	//end of #include guard