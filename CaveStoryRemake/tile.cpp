/*************************************************************************
File name: tile.cpp
Description:
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include "tile.h"
#include "graphics.h"
#include <SDL.h>

/*************************************************************************
Constructors and Deconstructors
**************************************************************************/
Tile::Tile() {}	// default constructor

Tile::Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position) :
	_tileset(tileset),
	_v2Size(size),
	_v2TilesetPosition(tilesetPosition),
	_v2Position(Vector2(position.x * globals::SPRITE_SCALE, position.y * globals::SPRITE_SCALE))
{}

Tile::~Tile() {}	//desctructor

/*************************************************************************
Functions
**************************************************************************/
void Tile::Update(int elapsedTime) {}

void Tile::Draw(Graphics &graphics) {
	SDL_Rect destRect = { this->_v2Position.x, this->_v2Position.y,
		this->_v2Size.x* globals::SPRITE_SCALE,this->_v2Size.y* globals::SPRITE_SCALE 
	};

	SDL_Rect sourceRect = { this->_v2TilesetPosition.x,this->_v2TilesetPosition.y,this->_v2Size.x,this->_v2Size.y};

	graphics.BlitSurface(this->_tileset, &sourceRect, &destRect);
}