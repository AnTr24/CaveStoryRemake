/*************************************************************************
File name: level.cpp
Description: Handles the level data
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include "level.h"
#include "graphics.h"
#include <SDL.h>

/*************************************************************************
Constructors and Deconstructors
**************************************************************************/
Level::Level() {}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
	_sMapName(mapName),
	_v2SpawnPoint(spawnPoint),
	_v2Size(Vector2::Zero())
{
	this->LoadMap(mapName, graphics);
}
Level::~Level() {

}
/*************************************************************************
Functions
**************************************************************************/
void Level::Update(int elapsedTime) {

}

void Level::Draw(Graphics &graphics) {
	//Draw the background
	SDL_Rect sourceRect = { 0,0,64,64 };
	SDL_Rect destRect;
	//bkBlue.png tile is 64x64
	destRect.w = 64;
	destRect.h = 64;

	for (int x = 0; x < _v2Size.x / 64; x++)
		for (int y = 0; y < _v2Size.y / 64; y++)
		{
			destRect.x = x * 64;
			destRect.y = y * 64;
			
			graphics.BlitSurface(this->_backgroundTexture, &sourceRect, &destRect);
		}
}

/*void LoadMap
*Loads a map
*/
void Level::LoadMap(std::string mapName, Graphics &graphics) {
	//TEMPORARY CODE TO LOAD BACKGROUND
	this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.GetRenderer(),
		graphics.LoadImage("Content/Backgrounds/bkBlue.png"));

	this->_v2Size = Vector2(1280, 960);
}