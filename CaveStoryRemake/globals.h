/*************************************************************************
File name:		globals.h
Description:	Holds global variables for the game. SPOOKY STUFF
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef GLOBALS_H
#define GLOBALS_H

//includes

//declarations
namespace globals {
	const int SCREEN_WIDTH = 640;	//Cavestory's default window is 640 x 480
	const int SCREEN_HEIGHT = 480;

	const float SPRITE_SCALE = 2.0f;	//sprites in cavestory seem to be scaled by x2
}

namespace sides {
	enum Side {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};

	const inline Side GetOppositeSide(Side side) {
		return
			side == TOP ? BOTTOM :
			side == BOTTOM ? TOP :
			side == LEFT ? RIGHT :
			side == RIGHT ? LEFT :
			NONE;
	}
}
//represents the direction the character is facing
enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

//for pairs of data
struct Vector2 {
	int x, y;

	Vector2() :x(0), y(0) {}

	Vector2(int x, int y) : x(x), y(y) {}

	static Vector2 Zero() {
		return Vector2(0, 0);
	}
};

#endif	//end of #include guard