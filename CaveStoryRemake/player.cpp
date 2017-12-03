/*************************************************************************
File name:	player.cpp
Description:	player class implementation, user will control this class ingame
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include "player.h"
#include "enemy.h"
#include "graphics.h"


namespace player_constants {
	const float WALK_SPEED = 0.2f;
	const float JUMP_SPEED = 0.7f;

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
	_bGrounded(false),
	_bLookingUp(false),
	_bLookingDown(false),
	_bBusy(false),
	_iMaxHealth(3),
	_iCurrentHealth(3),
	_iIFramesMax(500.0),
	_iIFramesCurrent(0.0)
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
	this->_bGrounded = false; //assume we are always falling

	//Alter IFrame timer
	_iIFramesCurrent -= elapsedTime;

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

	//Animation for idleing left & looking up
	std::vector<Vector2> idleLeftLookUpFrames = { Vector2(48,0) };
	//Animation for idleing right & looking up
	std::vector<Vector2> idleRightLookUpFrames = { Vector2(48,16) };
	//Animation for running left & looking up
	std::vector<Vector2> runLeftLookUpFrames = { Vector2(48,0), Vector2(64,0), Vector2(80,0)};
	//Animation for running right & looking up
	std::vector<Vector2> runRightLookUpFrames = { Vector2(48,16), Vector2(64,16), Vector2(80,16) };

	//Animation for facing left & looking down
	std::vector<Vector2> faceLeftLookDownFrames = { Vector2(96,0)};
	//Animation for facing right & looking down
	std::vector<Vector2> faceRightLookDownFrames = { Vector2(96,16) };

	//Animation for facing left & looking backwards
	std::vector<Vector2> faceLeftLookBackFrames = { Vector2(112,0) };
	//Animation for facing right & looking backwards
	std::vector<Vector2> faceRightLookBackFrames = { Vector2(112,16) };


	//Now add the animations
	this->AddAnimation(idleLeftFrames, "IdleLeft", width, height, Vector2(0, 0));	//Player stands still, looking to the left
	this->AddAnimation(idleRightFrames, "IdleRight", width, height, Vector2(0, 0));	//Player stands still, looking to the right
	this->AddAnimation(runLeftFrames, "RunLeft", width, height, Vector2(0, 0));		//Player runs and faces towards the left
	this->AddAnimation(runRightFrames, "RunRight", width, height, Vector2(0, 0));	//Player runs and faces towards the right

	this->AddAnimation(idleLeftLookUpFrames, "IdleLeftLookUp", width, height, Vector2(0, 0));	//Player stands still, looking to the left
	this->AddAnimation(idleRightLookUpFrames, "IdleRightLookUp", width, height, Vector2(0, 0));	//Player stands still, looking to the right
	this->AddAnimation(runLeftLookUpFrames, "RunLeftLookUp", width, height, Vector2(0, 0));		//Player runs left and looks up
	this->AddAnimation(runRightLookUpFrames, "RunRightLookUp", width, height, Vector2(0, 0));	//Player runs right and looks up

	this->AddAnimation(faceLeftLookDownFrames, "FaceLeftLookDown", width, height, Vector2(0, 0));	//Player faces the left, looking downards
	this->AddAnimation(faceRightLookDownFrames, "FaceRightLookDown", width, height, Vector2(0, 0));	//Player faces the right, looking downards

	this->AddAnimation(faceLeftLookBackFrames, "FaceLeftLookBack", width, height, Vector2(0, 0));	//Player faces the left, looking backwards
	this->AddAnimation(faceRightLookBackFrames, "FaceRightLookBack", width, height, Vector2(0, 0));	//Player faces the right, looking backwards
}

/*void AnimationDone
*Logic that occurs when animation finishes
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
	if (_bBusy) {
		//Player is interacting with something, don't move!
		return;
	}

	//Determine which move left animation to use
	if (!this->_bLookingUp) {
		//Not looking up, use regular animation
		this->PlayAnimation("RunLeft");
	}
	else {
		//run while looking upwards
		this->PlayAnimation("RunLeftLookUp");
	}
	
	this->_dx = -player_constants::WALK_SPEED;
	this->_facing = LEFT;
}

//void MoveRight
//Moves the player right by dx
void Player::MoveRight() {
	if (_bBusy) {
		//Player is interacting with something, don't move!
		return;
	}

	//Determine which move right animation to use
	if (!this->_bLookingUp) {
		//Not looking up, use regular animation
		this->PlayAnimation("RunRight");
	}
	else {
		//run while looking upwards
		this->PlayAnimation("RunRightLookUp");
	}

	this->_dx = player_constants::WALK_SPEED;
	this->_facing = RIGHT;
}

//void StopMoving
//Stops moving the player
void Player::StopMoving() {
	this->_dx = 0;

	//Determine which idle animation to use
	if (!this->_bLookingUp && !this->_bLookingDown) {
		//Looking straight
		this->PlayAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
	}
}

//void LookUp
//Makes the player view upwards
void Player::LookUp() {
	if (_bBusy) {
		//Player is interacting with something, don't move!
		return;
	}

	this->_bLookingUp = true;

	//Assumign we're idleing, look up
	if (this->_dx == 0) {
		//not moving horizontally
		this->PlayAnimation(this->_facing == RIGHT ? "IdleRightLookUp" : "IdleLeftLookUp");
	}
}

//void StopLookingUp
//Stops the LookingUp action
void Player::StopLookingUp() {
	this->_bLookingUp = false;
}

//void LookDown
//Makes the player view downwards OR interacts with a game object (turns around)
void Player::LookDown() {
	if (_bBusy) {
		//Player is interacting with something, don't move!
		return;
	}

	//check whether in air on on ground
	if (this->_bGrounded && this->_dx == 0) {
		//grounded and not moving, we need to interact(look backwards)
		this->PlayAnimation(this->_facing == RIGHT ? "FaceRightLookBack" : "FaceLeftLookBack");
		this->_bLookingDown = true;
	}
	else if (!this->_bGrounded) {
		//in the air (look downwards)
		this->PlayAnimation(this->_facing == RIGHT ? "FaceRightLookDown" : "FaceLeftLookDown");
		this->_bLookingDown = true;
	}
}

//void StopLookingDown
//Stops the LookingDown action
void Player::StopLookingDown(){
	this->_bLookingDown = false;
}

//void Jump
//Starts jumping
void Player::Jump() {
	if (_bBusy) {
		//Player is interacting with something, don't move!
		return;
	}

	if (this->_bGrounded) {
		this->_dy = 0;
		this->_dy -= player_constants::JUMP_SPEED;
		this->_bGrounded = false;
	}
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
				this->_dy = 0;
				this->_y = others.at(i).GetBottom() + 1;
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

//void HandleSlopeCollisions
//handles a detected collision with ALL slopes the player is colliding with
void Player::HandleSlopeCollisions(std::vector<Slope> &others) {
	//loop through to check each slope
	for (int i = 0; i < others.size(); i++) {

		//Calculate where on the slope the player's bottom center is touching
		//then use y=mx+b to determine the y pos to place him at
		//First calculate "b"(slope intercept) using one of the points
		//(b = y - mx)
		int b = (others.at(i).GetP1()).y - others.at(i).GetSlope() * fabs(others.at(i).GetP1().x);

		//Now get player's center x
		int centerX = this->_rBoundingBox.GetCenterX();

		//now pass the newly found x and b into the y=mx+b equation
		//to get the new y position
		int newY = others.at(i).GetSlope() * centerX + b;	//8 is a temporary fix
		//-8 moves the player a bit higher since we lost sound accuracy due to rounding?
		//or perhaps due to Quote being 16 pixels long, with half of him drawn into the slope, causing a collision, again

		//Reposition player to correct "y"
		//depending on type of slope
		if (others.at(i).Type == Slope::SlopeType::Ground && this->_dy >= 0) {
			//coliding onto a ground slope by falling
			this->_y =newY - this->_rBoundingBox.GetHeight();
			this->_bGrounded = true;
		}
		else if(others.at(i).Type == Slope::SlopeType::Ceiling)
		{//handle ceiling slope collision
			this->_dy = 0;
			this->_y += 1;
		}
	}
}

//void HandleDoorCollisions
//handles a detected collision with a door the player is colliding with
//ignores the rest of the doors in the collision list
void Player::HandleDoorCollision(std::vector<Door> &others, Level &level, Graphics &graphics) {
	//check if player is grounded and holding the down arrow(interacting with door)
	//if so go through the door
	if (!this->_bGrounded || !this->_bLookingDown) {
		return;
	}

	for (int i = 0; i < others.size(); i++) {
		level = Level(others.at(i).GetDestination(), graphics);
		this->_x = level.GetPlayerSpawnPoint().x;
		this->_y = level.GetPlayerSpawnPoint().y;
	}
}

//void HandleEnemyCollisions
//handles a detected collision with ALL enemies the player is colliding with
void Player::HandleEnemyCollision(std::vector<std::shared_ptr<Enemy>> &others) {
	for (int i = 0; i < others.size(); i++) {
		others.at(i)->TouchPlayer(this);
	}
}

//self explanatory
void Player::GainHealth(int amount) {
	if (_iIFramesCurrent <= 0) {
		this->_iCurrentHealth += amount;
	}

	//Took damage...
	if(amount < 0)
		_iIFramesCurrent = _iIFramesMax;	//Give i-Frames after taking damage
}