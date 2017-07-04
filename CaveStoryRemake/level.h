/*************************************************************************
File name:		level.h
Description:	Header file for thing class.
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef LEVEL_H
#define LEVEL_H

//includes
#include "globals.h"
#include <string>

class Graphics;
struct SDL_Texture;

//Class definition
class Level {
public:
	Level();	//constructor
	Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);	//constructor
	~Level();	//desctructor

	//the usual....
	void Update(int elapsedTime);
	void Draw(Graphics &graphics);

private:
	std::string _sMapName;
	Vector2 _v2SpawnPoint;
	Vector2 _v2Size;
	SDL_Texture* _backgroundTexture;

	/*void LoadMap
	*Loads a map
	*/
	void LoadMap(std::string mapName, Graphics &graphics);
};
#endif	//end of #include guard