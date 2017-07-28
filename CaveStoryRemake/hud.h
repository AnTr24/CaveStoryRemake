/*************************************************************************
File name:		hud.h
Description:	Controls the head-up-display holding game state info of the player
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef HUD_H
#define HUD_H

//includes
#include "sprite.h"
#include "player.h"

//declarations
class Graphics;


//Class definition
class HUD {
public:
	HUD();	// default constructor
	HUD(Graphics &graphics, Player &player);

	void Update(int elapsedTime);
	void Draw(Graphics &graphics);
protected:
private:
	Player _player;

	Sprite _spriteHealthBar;
	Sprite _spriteHealthNumber1;
};
#endif	//end of #include guard