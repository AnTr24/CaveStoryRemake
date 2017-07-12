/*************************************************************************
File name:		level.h
Description:	Header file for level class.
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef LEVEL_H
#define LEVEL_H

//includes
#include "globals.h"
#include <string>
#include <vector>
#include "tile.h"
#include "rectangle.h"

class Graphics;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

//Class definition
class Level {
public:
	Level();	//constructor
	Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);	//constructor
	~Level();	//desctructor

	//the usual....
	void Update(int elapsedTime);
	void Draw(Graphics &graphics);

	//Checks if tile collided with something
	std::vector<Rectangle> CheckTileCollisions(const Rectangle &other);

	//const Vector2 GetPlayerSpawnPoint
	//Retrieves the location of player spawn
	const Vector2 GetPlayerSpawnPoint() const;

private:
	std::string _sMapName;
	Vector2 _v2SpawnPoint;

	Vector2 _v2Size;
	Vector2 _v2TileSize;

	SDL_Texture* _backgroundTexture;

	std::vector<Tile> _vTileList;			//holds tiles to be drawn
	std::vector<Tileset> _vTilesets;		//holds loaded tilesets
	std::vector<Rectangle>_vCollisionRects;	//holds collision objects

	/*void LoadMap
	*Loads a map
	*/
	void LoadMap(std::string mapName, Graphics &graphics);
};

//Tileset structure
// used for parsing the tmx files
struct Tileset {
	SDL_Texture* Texture;
	int FirstGid;

	Tileset() {
		this->FirstGid = -1;
	}

	Tileset(SDL_Texture* texture, int firstGid) {
		this->FirstGid = firstGid;
		this->Texture = texture;
	}
};
#endif	//end of #include guard