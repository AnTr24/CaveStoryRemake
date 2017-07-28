/*************************************************************************
File name:		game.h
Description:	Header file for Game class.
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "level.h"
#include "hud.h"

class Graphics;

class Game {
public:
	Game();
	~Game();
private:
	void GameLoop();
	void Draw(Graphics& graphics);
	void Update(float elapsedTime);

	Player _player;	//player sprite

	Level _level;	//defines the map/level

	HUD _hud;	//hud for visualizing player info 
};

#endif 
