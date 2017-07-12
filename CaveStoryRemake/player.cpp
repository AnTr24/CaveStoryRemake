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

	const float GRAVITY = 0.002f;
	const float GRAVITY_CAP = 0.8f;
}


/*************************************************************************
Constructors and Deconstructors
**************************************************************************/
Player::Player() {}	//default constructor

//custom constructor
Player::Player(Graphics &graphics, Vector2 spawnPoint) :
	AnimatedSprite(graphics, "Content/Sprites/MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
	_dx(0),
	_dy(0),
	_facing(RIGHT),
	_bGrounded(false)
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
	//Apply gravity
	if (this->_dy <= player_constants::GRAVITY_CAP) {
		this->_dy += player_constants::GRAVITY*elapsedTime;
	}

	//Move by dx(horizontal movement)
	this->_x += this->_dx * elapsedTime;

	//Move by dy(vertical movement)
	this->_y += this->_dy * elapsedTime;

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

//GetX - getter function retrieves the X coordinate
const float Player::GetX() const {
	return this->_x;
}


//GetY - getter function retrieves the Y coordinate
const float Player::GetY() const {
	return this->_y;
}

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

//void HandleTileCollisions
//handles a detected collision with ALL tiles the palyer is colliding with
void Player::HandleTileCollisions(std::vector<Rectangle> &others) {
	//Figure out what side the collision happened on and move the player accordingly
	for (int i = 0; i < others.size(); i++) {
		sides::Side collisionSide = Sprite::GetCollisionSide(others.at(i));
		if (collisionSide != sides::NONE) {
			switch (collisionSide)
			{
			case sides::LEFT:
				this->_x = others.at(i).GetRight() + 1;
				break;
			case sides::RIGHT:
				this->_x = others.at(i).GetLeft() - this->_rBoundingBox.GetWidth();
				break;
			case sides::TOP:
				this->_y = others.at(i).GetBottom();
				this->_dy = 0;
				break;
			case sides::BOTTOM:
				this->_y = others.at(i).GetTop() - this->_rBoundingBox.GetHeight();
				this->_dy = 0;
				this->_bGrounded = true;
				break;
			}
		}
	}


}