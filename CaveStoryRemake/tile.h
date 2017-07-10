/*************************************************************************
File name:		tile.h
Description:	Header file for thing class.
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef TILE_H
#define TILE_H

//includes
#include "globals.h"

struct SDL_Texture;
class Graphics;


//Class definition
class Tile {
public:
	Tile();	//constructor
	Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
	~Tile();	//desctructor

	void Update(int elapsedTime);
	void Draw(Graphics &graphics);
private:
	SDL_Texture* _tileset;
	Vector2 _v2Size;
	Vector2 _v2TilesetPosition;
	Vector2 _v2Position;
};
#endif	//end of #include guard