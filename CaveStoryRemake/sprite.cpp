/*************************************************************************
File name: sprite.cpp
Description:	Contains texture of sprites
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include "sprite.h"
#include "graphics.h"
#include "globals.h"
/*************************************************************************
Constructors and Deconstructors
**************************************************************************/
Sprite::Sprite(){}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY) : _x(posX),_y(posY)
{
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;


	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.GetRenderer(), graphics.LoadImage(filePath));
	if (this->_spriteSheet == NULL) {
		printf("\nError: Unable to load image\n");
	}
}

Sprite::~Sprite(){}
/*************************************************************************
Functions
**************************************************************************/
//Animation function
void Sprite::Update(){

}

void Sprite::Draw(Graphics &graphics, int x, int y){
	//Grab area of sprite source to draw, scales it to the global sprite size modifier 
	//-make the destination rectangle twice as big as the source to daw twice the pixels
	SDL_Rect destinationRectangle = { x,y,this->_sourceRect.w * globals::SPRITE_SCALE,this->_sourceRect.h * globals::SPRITE_SCALE };

	//Draw to backbuffer
	graphics.BlitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}