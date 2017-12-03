/*************************************************************************
File name: enemy.cpp
Description: Contains all the logic for the game's enemies
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include "enemy.h"

/*************************************************************************
Base Enemy class
**************************************************************************/
Enemy::Enemy(){}

Enemy::Enemy(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate)
: AnimatedSprite(graphics, filePath,  sourceX,  sourceY,  width,  height,  posX,  posY,  timeToUpdate),
_direction(LEFT),
_maxHealth(0),
_currentHealth(0)
{}

void Enemy::Update(int elapsedTime, Player &player) {
	AnimatedSprite::Update(elapsedTime);
}

void Enemy::Draw(Graphics &graphics) {
	AnimatedSprite::Draw(graphics, this->_x, this->_y);
}

/*************************************************************************
Bat class
**************************************************************************/
Bat::Bat(){}

Bat::Bat(Graphics &graphics, Vector2 spawnPoint) :
	Enemy(graphics, "Content/Sprites/NpcCemet.png", 32, 32, 16, 16, spawnPoint.x, spawnPoint.y, 140),
	_startingX(spawnPoint.x),
	_startingY(spawnPoint.y)
{
	this->SetupAnimation();
	this->PlayAnimation("FlyLeft");
}

void Bat::Update(int elapsedTime, Player &player) {
	//Make bats face the player's direction
	this->_direction = player.GetX() > this->_x ? RIGHT : LEFT;
	this->PlayAnimation(this->_direction == RIGHT ? "FlyRight" : "FlyLeft");

	//Move up or down
	float movement = 0.05 * elapsedTime;
	this->_y += this->_bMovingUp ? -movement : movement;
	if (this->_y > (this->_startingY + 20) || this->_y < (this->_startingY - 20))
		this->_bMovingUp = !this->_bMovingUp;

	Enemy::Update(elapsedTime, player);
}

void Bat::Draw(Graphics &graphics) {
	Enemy::Draw(graphics);
}

void Bat::AnimationDone(std::string currentAnimation) {
}

void Bat::SetupAnimation() {
	//Sprite dimensions
	int width = 16;
	int height = 16;

	//Get animation frames from spritesheet
	//Animation for flying left
	std::vector<Vector2> flyLeftFrames = { Vector2(32,32), Vector2(48,32), Vector2(64,32)};
	//Animation for flying right
	std::vector<Vector2> flyRightFrames = { Vector2(32,48), Vector2(48,48), Vector2(64,48)};

	//Add the animations
	this->AddAnimation(flyLeftFrames, "FlyLeft", width, height, Vector2(0,0));
	this->AddAnimation(flyRightFrames, "FlyRight", width, height, Vector2(0, 0));
}

void Bat::TouchPlayer(Player* player) {
	player->GainHealth(-1);
}