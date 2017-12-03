/*************************************************************************
File name:		player.h
Description:	Header file for player class.
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef PLAYER_H
#define PLAYER_H

//includes
#include "animatedsprite.h"
#include "globals.h"
#include "slope.h"
#include "door.h"
#include "level.h"

class Enemy;
class Graphics;

//Class definition
class Player : public AnimatedSprite {
public:
	Player();	//default constructor
	Player(Graphics &graphics, Vector2 spawnPoint);	//constructor
	~Player();	//desctructor

	//Standard...
	void Draw(Graphics &graphics);
	void Update(float elapsedTime);

	//void MoveLeft
	//Moves the player left by -dx
	void MoveLeft();

	//void MoveRight
	//Moves the player right by dx
	void MoveRight();

	//void StopMoving
	//Stops moving the player
	void StopMoving();

	//void LookUp
	//Makes the player view upwards
	void LookUp();

	//void StopLookingUp
	//Stops the LookingUp action
	void StopLookingUp();

	//void LookDown
	//Makes the player view downwards OR interacts with a game object (turns around)
	void LookDown();

	//void StopLookingDown
	//Stops the LookingDown action
	void StopLookingDown();

	//void Jump
	//Starts jumping
	void Jump();

	/*virtual void AnimationDone
	*Logic that occurs when animation finishes
	*Note: adding the = 0 means that the function is now pure virtual, can't be implemented in this class
	*/
	virtual void AnimationDone(std::string currentAnimation);

	/*	virtual void SetupAnimation
	*	A required function that sets up the sprite's animations
	*/
	virtual void SetupAnimation();

	//void HandleTileCollisions
	//handles a detected collision with ALL tiles the player is colliding with
	void HandleTileCollisions(std::vector<Rectangle> &others);

	//void HandleSlopeCollisions
	//handles a detected collision with ALL slopes the player is colliding with
	void HandleSlopeCollisions(std::vector<Slope> &others);

	//void HandleDoorCollisions
	//handles a detected collision with a door the player is colliding with
	//ignores the rest of the doors in the collision list
	void HandleDoorCollision(std::vector<Door> &others, Level &level, Graphics &graphics);

	//void HandleEnemyCollisions
	//handles a detected collision with ALL enemies the player is colliding with
	void HandleEnemyCollision(std::vector<std::shared_ptr<Enemy>> &others);

	//Getter functions to get X or Y coordinates
	const float GetX() const;
	const float GetY() const;

	//Getter functions to get player max health
	const inline int GetMaxHealth() const{return this->_iMaxHealth;}

	//Getter functions to get player current health
	const inline int GetCurrentHealth() const {return this->_iCurrentHealth;}

	void GainHealth(int amount);

private:
	float _dx, _dy;	//change in x and y positions

	Direction _facing;	//determines direction player is facing

	bool _bGrounded;	//flag for being on ground or in air
	bool _bBusy;		//flag for interactions/cutscenes
	bool _bLookingUp;	//flag for player looking up
	bool _bLookingDown;	//flag for player looking down
	int _iMaxHealth;		//Total health of the player
	int _iCurrentHealth;	//and current health
	float _iIFramesMax;		//time for invincibility after getting hit
	float _iIFramesCurrent;	//current time for invincibility after getting hit
};
#endif	//end of #include guard