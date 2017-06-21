/*************************************************************************
File name:		globals.h
Description:	Holds global variables for the game. SPOOKY STUFF
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef GLOBALS_H
#define GLOBALS_H

//includes

namespace globals {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const float SPRITE_SCALE = 2.0f;
}

//for pairs of data
struct Vector2 {
	int x, y;

	Vector2() :x(0), y(0){}

	Vector2(int x, int y): x(x), y(y){}

	Vector2 Zero() {
		return Vector2(0,0);
	}
};

#endif	//end of #include guard