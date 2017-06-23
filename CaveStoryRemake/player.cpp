/*************************************************************************
File name:	player.cpp
Description:	player class implementation, user will control this class ingame
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include "player.h"
#include "graphics.h"


namespace player_constants {
	const float WALK_SPEED = 0.2f;
}


/*************************************************************************
Constructors and Deconstructors
**************************************************************************/
Player::Player() {}	//default constructor

//custom constructor
Player::Player(Graphics &graphics, float x, float y) :
	AnimatedSprite(graphics, "Content/Sprites/MyChar.png", 0, 0, 16, 16, x, y, 100)
{
	graphics.LoadImage("Content/Sprites/MyChar.png");

	this->SetupAnimation();	//preform initial setup
	this->_facing = RIGHT;
	this->PlayAnimation("IdleRight");	//temp
}
Player::~Player() {}//desctructor

/*************************************************************************
Functions
**************************************************************************/
void Player::Draw(Graphics &graphics) {
	AnimatedSprite::Draw(graphics, this->_x, this->_y);
}

void Player::Update(float elapsedTime) {
	//Move by dx(horizontal movement)
	this->_x += this->_dx * elapsedTime;

	AnimatedSprite::Update(elapsedTime);
}

/*	void SetupAnimation
*	A required function that sets up the sprite's animations
*/
void Player::SetupAnimation() {
	//Default frame parameters
	int width = 16;
	int height = 16;

	//Determine the frame positions for each animation

	//Animation for idleing left
	std::vector<Vector2> idleLeftFrames = { Vector2(0,0) };
	//Animation for idleing right
	std::vector<Vector2> idleRightFrames = { Vector2(0,16) };
	//Animation for running left
	std::vector<Vector2> runLeftFrames = { Vector2(0,0), Vector2(16,0), Vector2(0,0), Vector2(32,0) };
	//Animation for running right
	std::vector<Vector2> runRightFrames = { Vector2(0,16), Vector2(16,16), Vector2(0,16), Vector2(32,16) };

	//Now add the animations
	this->AddAnimation(idleLeftFrames, "IdleLeft", width, height, Vector2(0, 0));
	this->AddAnimation(idleRightFrames, "IdleRight", width, height, Vector2(0, 0));
	this->AddAnimation(runLeftFrames, "RunLeft", width, height, Vector2(0, 0));
	this->AddAnimation(runRightFrames, "RunRight", width, height, Vector2(0, 0));
}

/*void AnimationDone
*Logic that occurs when animation finishes
*Note: adding the = 0 means that the function is now pure virtual, can't be implemented in this class
*/
void Player::AnimationDone(std::string currentAnimation) {}

//void MoveLeft
//Moves the player left by -dx
void Player::MoveLeft() {
	this->_dx = -player_constants::WALK_SPEED;
	this->PlayAnimation("RunLeft");
	this->_facing = LEFT;
}

//void MoveRight
//Moves the player right by dx
void Player::MoveRight() {
	this->_dx = player_constants::WALK_SPEED;
	this->PlayAnimation("RunRight");
	this->_facing = RIGHT;
}

//void StopMoving
//Stops moving the player
void Player::StopMoving() {
	this->_dx = 0;
	this->PlayAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}
