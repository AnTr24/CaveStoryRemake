/*************************************************************************
File name:		graphics.cpp
Description:	Holds information dealing with all graphics of the game
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include <SDL.h>
#include <SDL_image.h>

#include "graphics.h"
#include "globals.h"

/*************************************************************************
Constructors and Deconstructors
**************************************************************************/
//class constructor implementation
Graphics::Graphics() {

	//create a window 'graphic' for the game. Cavestory is 640x480 originally.
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->_window, &this->_renderer);

	//Self explanatory
	SDL_SetWindowTitle(this->_window, "Cavestory");
}

//and deconstructor
Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
}
/*************************************************************************
Functions
**************************************************************************/
/*	SDL_Surface* loadImage
*	Loads an image into the _mSpriteSheets map if it doesn't already exist.
As a result, each image will only be loaded once.
Returns the image from the map regardless of whether or not it was just loaded
*/
SDL_Surface* Graphics::LoadImage(const std::string& filepath){
	//Check if image was already loaded
	if (this->_mSpriteSheets.count(filepath) == 0) {
		//Not loaded, using SDL, load image from filepath
		this->_mSpriteSheets[filepath] = IMG_Load(filepath.c_str());
	}
	//return the loaded image
	return this->_mSpriteSheets[filepath];
}

/*	void BlitSurface
Draws a texture to a certain part of the backbuffer
(SDL_Texture* source	-	Texture to be drawn
SDL_Rect* sourceRectangle	-	 Spreadsheet source
SDL_Rect* destinationRectangle	-	Part of screen to draw to
*/
void Graphics::BlitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) {
	//SDL_RenderCopy - Takes whatever texture you give it and copies it to the renderer backbuffer
	SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinationRectangle);
}

/*	void Render
Renders everything to the screen
*/
void Graphics::Render() {
	//SDL_RenderPresent - Flips the backbuffer to the front
	SDL_RenderPresent(this->_renderer);
}

/*	void Clear
Clears the screen
*/
void Graphics::Clear() {
	SDL_RenderClear(this->_renderer);
}

/*	SDL_Renderer* GetRenderer
Returns the renderer
*/
SDL_Renderer* Graphics::GetRenderer() const {
	return this->_renderer;
}



