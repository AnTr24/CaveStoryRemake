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

	//Initialize health sprites
	this->_spriteHealthBar = Sprite(graphics, "content/sprites/Textbox.png", 0, 40, 64, 8, 35, 70);
	this->_spriteCurrentHealthBar = Sprite(graphics, "content/sprites/Textbox.png", 0, 25, 39, 5, 83, 72);
	this->_spriteHealthNumber1 = Sprite(graphics, "content/sprites/Textbox.png", 0, 56, 8, 8, 66, 70);
	
	//Initialize EXP sprites
	this->_spriteLVLWord = Sprite(graphics, "content/sprites/Textbox.png", 81, 81, 11, 7, 38, 55);
	this->_spriteLVLNum = Sprite(graphics, "content/sprites/Textbox.png", 0, 56, 8, 8, 66, 52);
	this->_spriteEXPBar = Sprite(graphics, "content/sprites/Textbox.png", 0, 72, 40, 8, 83, 52);

	//Initialize Weapon info sprites
	this->_spriteUISlashes = Sprite(graphics, "content/sprites/Textbox.png", 72, 48, 8, 8, 100, 36);
	this->_spriteUIDashes = Sprite(graphics, "content/sprites/Textbox.png", 81, 51, 15, 11, 132, 26);

}

/*************************************************************************
Functions
**************************************************************************/
void HUD::Update(int elapsedTime, Player &player) {
	//On the sprite sheet Textbox.png, each number is offsetted by 8px
	int numOffset = 8;

	//update palyer info
	this->_player = player;	
	this->_spriteHealthNumber1.SetSourceRectX(numOffset * this->_player.GetCurrentHealth());

	//calculate the width of the current-health bar
	//100% is a width of 39px
	float maxWidth = 39;
	float num = (float)this->_player.GetCurrentHealth() / (float)this->_player.GetMaxHealth();
	int barWidth = std::floor(maxWidth * num);

	this->_spriteCurrentHealthBar.SetSourceRectWidth(barWidth);

}

void HUD::Draw(Graphics &graphics) {
	//Draw health sprites
	this->_spriteHealthBar.Draw(graphics, this->_spriteHealthBar.GetX(), this->_spriteHealthBar.GetY());
	this->_spriteCurrentHealthBar.Draw(graphics, this->_spriteCurrentHealthBar.GetX(), this->_spriteCurrentHealthBar.GetY());
	this->_spriteHealthNumber1.Draw(graphics, this->_spriteHealthNumber1.GetX(), this->_spriteHealthNumber1.GetY());
	
	//draw exp sprites
	this->_spriteLVLWord.Draw(graphics, this->_spriteLVLWord.GetX(), this->_spriteLVLWord.GetY());
	this->_spriteLVLNum.Draw(graphics, this->_spriteLVLNum.GetX(), this->_spriteLVLNum.GetY());
	this->_spriteEXPBar.Draw(graphics, this->_spriteEXPBar.GetX(), this->_spriteEXPBar.GetY());

	//weapon info draws
	this->_spriteUISlashes.Draw(graphics, this->_spriteUISlashes.GetX(), this->_spriteUISlashes.GetY());
	this->_spriteUIDashes.Draw(graphics, this->_spriteUIDashes.GetX(), this->_spriteUIDashes.GetY());

}