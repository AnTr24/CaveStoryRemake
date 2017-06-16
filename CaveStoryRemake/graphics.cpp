/*************************************************************************
File name:		graphics.cpp
Description:	Holds information dealing with all graphics of the game
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include "graphics.h"
#include <SDL.h>

/*************************************************************************
Constructors and Deconstructors
**************************************************************************/
//class constructor implementation
Graphics::Graphics() {

	//create a window 'graphic' for the game. Cavestory is 640x480 originally.
	SDL_CreateWindowAndRenderer(640, 480, 0, &this->_window, &this->_renderer);

	//Self explanatory
	SDL_SetWindowTitle(this->_window, "Cavestory");
}

//and deconstructor
Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
}
/*************************************************************************
Functions
**************************************************************************/
