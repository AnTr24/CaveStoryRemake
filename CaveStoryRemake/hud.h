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

	//Health-related
	Sprite _spriteHealthBar;		//the background health sprite
	Sprite _spriteHealthNumber1;	//sprite for the current health number
	Sprite _spriteCurrentHealthBar;	//sprite for the current health bar

	//Exp
	Sprite _spriteLVLWord;
	Sprite _spriteLVLNum;
	Sprite _spriteEXPBar;

	//Weapon Info
	Sprite _spriteUISlashes;
	Sprite _spriteUIDashes;

};
#endif	//end of #include guard