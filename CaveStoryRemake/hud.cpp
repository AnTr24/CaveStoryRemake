/*************************************************************************
File name:
Description:
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include "hud.h"
#include "graphics.h"

/*************************************************************************
Constructors and Deconstructors
**************************************************************************/
HUD::HUD() {}	// default constructor
HUD::HUD(Graphics &graphics, Player &player) {
	this->_player = player;
	this->_spriteHealthBar = Sprite(graphics, "content/sprites/Textbox.png", 0, 40, 64, 8, 35, 70);
	this->_spriteHealthNumber1 = Sprite(graphics, "content/sprites/Textbox.png", 0, 56, 8, 8, 66, 70);
}

/*************************************************************************
Functions
**************************************************************************/
void HUD::Update(int elapsedTime) {
	this->_spriteHealthNumber1.SetSourceRectX(8 * this->_player.GetCurrentHealth());
}

void HUD::Draw(Graphics &graphics) {
	this->_spriteHealthBar.Draw(graphics, this->_spriteHealthBar.GetX(), this->_spriteHealthBar.GetY());
	this->_spriteHealthNumber1.Draw(graphics, this->_spriteHealthNumber1.GetX(), this->_spriteHealthNumber1.GetY());

}