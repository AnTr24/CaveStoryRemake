/*************************************************************************
File name:		game.h
Description:	Header file for Game class.
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef GAME_H
#define GAME_H

#include "player.h";

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
};

#endif 
