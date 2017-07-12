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
#include <algorithm>
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

	this->_rBoundingBox = Rectangle(this->_x, this->_y, width * globals::SPRITE_SCALE, height * globals::SPRITE_SCALE);
}

Sprite::~Sprite(){}
/*************************************************************************
Functions
**************************************************************************/
//const Rectangle GetBoundingBox
//Retrieves the collision rectangle
const Rectangle Sprite::GetBoundingBox() const {
	return _rBoundingBox;
}

//const sides::Side GetCollisionSide
//Grab the side of the collision
const sides::Side Sprite::GetCollisionSide(Rectangle &other) const {
	//determine what side the collision happened on
	int amtRight, amtLeft, amtTop, amtBottom;	//amount that the rectangle collided with the other
	const Rectangle boundingBox = this->GetBoundingBox();
	
	amtRight = abs(boundingBox.GetRight() - other.GetLeft());
	amtLeft = abs(other.GetRight() - boundingBox.GetLeft());
	amtTop = abs(other.GetBottom() - boundingBox.GetTop());
	amtBottom = abs(boundingBox.GetBottom() - other.GetTop());

	//smallest amount indicates the side of collision
	int lowest = std::min({ amtRight, amtLeft, amtTop, amtBottom });

	return
		lowest == amtLeft ? sides::LEFT :
		lowest == amtRight ? sides::RIGHT :
		lowest == amtTop ? sides::TOP :
		lowest == amtBottom ? sides::BOTTOM :
		sides::NONE;
}

//Animation function
void Sprite::Update(){
	this->_rBoundingBox = Rectangle(this->_x, this->_y, _sourceRect.w * globals::SPRITE_SCALE, _sourceRect.h * globals::SPRITE_SCALE);
}

void Sprite::Draw(Graphics &graphics, int x, int y){
	//Grab area of sprite source to draw, scales it to the global sprite size modifier 
	//-make the destination rectangle twice as big as the source to daw twice the pixels
	SDL_Rect destinationRectangle = { x,y,this->_sourceRect.w * globals::SPRITE_SCALE,this->_sourceRect.h * globals::SPRITE_SCALE };

	//Draw to backbuffer
	graphics.BlitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}