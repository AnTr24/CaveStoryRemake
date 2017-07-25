/*************************************************************************
File name:		animatedtile.cpp
Description:	Source file for AnimatedTiles. AnimatedTiles derives from Tile in tile.h
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include "animatedtile.h"
#include "graphics.h"
/*************************************************************************
Constructors and Deconstructors
**************************************************************************/
//constructor
AnimatedTile::AnimatedTile(std::vector<Vector2> tilesetPosition, int duration, SDL_Texture* tileset, Vector2 size, Vector2 position)
	: Tile(tileset, size, tilesetPosition.at(0), position),
	_v2TilesetPositions(tilesetPosition),
	_iAmountOfTime(duration),
	_iFrameDuration(duration),
	_iTileFrame(0)
{}

/*************************************************************************
Functions
**************************************************************************/
void AnimatedTile::Update(int elapsedTime) {

	//Timer code
	this->_iAmountOfTime -= elapsedTime; //countdown time till next frame

	if (this->_iAmountOfTime <= 0) {
		//amount of time expired, move to next frame
		if (this->_iTileFrame == this->_v2TilesetPositions.size() - 1) {
			//reached the end of animation
			this->_iTileFrame = 0; //loop back to start
		}
		else {
			this->_iTileFrame++;	//Move to next frame in animation
		}

		this->_iAmountOfTime = this->_iFrameDuration;
	}
}

void AnimatedTile::Draw(Graphics &graphics) {
	SDL_Rect destRect = { this->_v2Position.x,this->_v2Position.y,
		this->_v2Size.x * globals::SPRITE_SCALE, this->_v2Size.y * globals::SPRITE_SCALE };

	SDL_Rect sourceRect = { this->_v2TilesetPositions.at(this->_iTileFrame).x,this->_v2TilesetPositions.at(this->_iTileFrame).y,
		this->_v2Size.x, this->_v2Size.y};

	graphics.BlitSurface(this->_tileset, &sourceRect, &destRect);
}