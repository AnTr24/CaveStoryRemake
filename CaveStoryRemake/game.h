/*************************************************************************
File name:		game.h
Description:	Header file for Game class.
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef GAME_H
#define GAME_H

#include "sprite.h";

class Graphics;

class Game {
public:
	Game();
	~Game();
private:
	void GameLoop();
	void Draw(Graphics& graphics);
	void Update(float elapsedTime);

	Sprite _sPlayer;	//player sprite
};

#endif 
