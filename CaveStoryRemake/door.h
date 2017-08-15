/*************************************************************************
File name:		door.h
Description:
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef DOOR_H
#define DOOR_H

//includes
#include <string>

#include "rectangle.h"
#include "globals.h"
//declarations

//Class definition
class Door : public Rectangle {
public:
	Door() {}	// default constructor
	Door(Rectangle r, std::string destination) :
		Rectangle(r.GetLeft()*globals::SPRITE_SCALE, r.GetTop()*globals::SPRITE_SCALE, 
			r.GetWidth()*globals::SPRITE_SCALE, r.GetHeight()*globals::SPRITE_SCALE),
		_destination(destination)
	{}

	const inline Rectangle GetRectangle() const { return this->GetRect(); }
	const inline std::string GetDestination() const { return this->_destination; }

protected:
private:
	std::string _destination;
};
#endif	//end of #include guard