/*************************************************************************
File name:		animatedtile.h
Description:	Header file for AnimatedTiles. Derives from Tile in tile.h
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef ANIMATED_TILE_H
#define ANIMATED_TILE_H

//includes
#include <vector>

#include "tile.h"
#include "globals.h"

//declarations
struct AnimatedTileInfo {
public:
	int TilesetsFirstGid;
	int StartTileID;
	int Duration;
	std::vector<int> TileIds;
};

//Class definition
class AnimatedTile : public Tile {
public:
	//constructor
	AnimatedTile(std::vector<Vector2> tilesetPosition, int duration, SDL_Texture* tileset, Vector2 size, Vector2 position);

	//The usual
	void Update(int elapsedTime);
	void Draw(Graphics &graphics);
protected:
	int _iAmountOfTime = 0;	//current time that has passed in animation
	bool _bNotDone = false;	//animation finished playing?
private:
	std::vector<Vector2> _v2TilesetPositions;	//points to tilset location of frame
	int _iTileFrame;		//index of current playing/animated frame
	int _iFrameDuration;	//time each frame of animation lasts(ms)
};
#endif	//end of #include guard