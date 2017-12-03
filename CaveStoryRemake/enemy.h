/*************************************************************************
File name:		enemy.h
Description:	Handles enemy npc logic
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef ENEMY_H
#define ENEMY_H

//#includes
#include "animatedsprite.h"
#include "globals.h"
#include "player.h"

#include <string>

//declarations
class Graphics;

//Class definition
class Enemy : public AnimatedSprite {
public:
	Enemy();	// default constructor
	Enemy(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate);	
	virtual void Update(int elapsedTime, Player &player);
	virtual void Draw(Graphics &graphics);

	const inline int GetMaxHealth() const { return this->_maxHealth; }
	const inline int GetCurrentHealth() const { return this->_currentHealth; }
protected:
	Direction _direction;
	int _maxHealth;
	int _currentHealth;
private:
};


//SPECIFIC ENEMY LOGIC BELOW
//Bat enemy
class Bat : public Enemy {
public:
	Bat();
	Bat(Graphics &graphics, Vector2 spawnPoint);

	void Update(int elapsedTime, Player &player);
	void Draw(Graphics &graphics);

	/*AnimationDone
	*Logic that occurs when animation finishes
	*Note: adding the = 0 means that the function is now pure virtual, can't be implemented in this class*/
	void AnimationDone(std::string currentAnimation);

	/*	virtual void SetupAnimation
	*	A required function that sets up the sprite's animations*/
	void SetupAnimation();
private:
};

#endif	//end of #include guard