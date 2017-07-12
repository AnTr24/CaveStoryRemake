/*************************************************************************
File name: animatedsprite.cpp
Description: Inherits Sprite class to add animation
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include "animatedsprite.h"
#include "graphics.h"
#include "sprite.h"

/*************************************************************************
Constructors and Deconstructors
**************************************************************************/
AnimatedSprite::AnimatedSprite() {}	//constructor

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
	int width, int height, float posX, float posY, float timeToUpdate)
	: Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
	_iFrameIndex(0),
	_dTimeElapsed(0),	//visual studio will initialize it to  -9.E61 by default(sprite will never update)..set it to 0!
	_dTimeToUpdate(timeToUpdate),
	_bVisible(true),
	_bCurrentAnimationOnce(false),
	_sCurrentAnimation("")
	{

	}

	AnimatedSprite::~AnimatedSprite() {}	//desctructor

	/*************************************************************************
	Functions
	**************************************************************************/

	//void PlayAnimation - Plays the animation if it's not already playing
void AnimatedSprite::PlayAnimation(std::string sAnimationName, bool once) {
	this->_bCurrentAnimationOnce = once;

	//check if animation is currently playing
	if (this->_sCurrentAnimation == sAnimationName)
		return;
	
	//set new current animation
	this->_sCurrentAnimation = sAnimationName;
	this->_iFrameIndex = 0;
}

//void Update - Updated animated sprite(timer)
void AnimatedSprite::Update(int elapsedTime) {
	Sprite::Update();

	//update elapsed time
	this->_dTimeElapsed += elapsedTime;

	//check if it is time to update animation
	if (this->_dTimeElapsed < this->_dTimeToUpdate)
		return;

	//moving to next frame, so have to adjust time elapsed
	this->_dTimeElapsed -= this->_dTimeToUpdate;

	//check what frame we are(especially for last frame), update to next frame (or beginning frame if on the last frame)
	if (this->_iFrameIndex < this->_mAnimations[this->_sCurrentAnimation].size() - 1) {
		//not at last frame of animation
		_iFrameIndex++;
	}
	else {
		//at the last frame of animation, repeat again?
		if (this->_bCurrentAnimationOnce)
		{
			//animation only plays once
			this->SetVisible(false);
		}
		//no matter what, frame index goes back to beginning and animation finishes
		this->_iFrameIndex = 0;
		this->AnimationDone(this->_sCurrentAnimation);
	}
}

//void Draw - Draws sprite to screen
void AnimatedSprite::Draw(Graphics &graphics, int x, int y) {
	if (this->_bVisible) {
		SDL_Rect destinationRectangle;	//determines where sprite is drawn
		//determine x and y positions, including offset
		destinationRectangle.x = x + _mOffsets[this->_sCurrentAnimation].x;
		destinationRectangle.y = y + _mOffsets[this->_sCurrentAnimation].y;

		//determine dimensions
		destinationRectangle.w = this->_sourceRect.w * globals::SPRITE_SCALE;
		destinationRectangle.h = this->_sourceRect.h * globals::SPRITE_SCALE;

		//grab animation frame to draw
		SDL_Rect frameRect = this->_mAnimations[this->_sCurrentAnimation][this->_iFrameIndex];
		graphics.BlitSurface(this->_spriteSheet, &frameRect, &destinationRectangle);
	}
}

//OLD WAY OF ADDING ANIMATION
/*void AddAnimation
*Adds an animation to the map of animations for the sprite
*/
/*
void AnimatedSprite::AddAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset) 
{
	std::vector<SDL_Rect> rectangles;	//cuts up sprite sheet to the frames we need

	//loop through the spritesheet to get each frame
	for (int i = 0; i < frames; i++)
	{
		SDL_Rect newRect = {(i + x)*width, y, width, height, };
		rectangles.push_back(newRect);
	}

	//load the frames for the animation
	this->_mAnimations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles));
	this->_mOffsets.insert(std::pair<std::string, Vector2>(name, offset));
}
*/

void AnimatedSprite::AddAnimation(std::vector<Vector2> frameLocations, std::string name, int width, int height, Vector2 offset)
{
std::vector<SDL_Rect> rectangles;	//cuts up sprite sheet to the frames we need

//error for array size..
//loop through the Vector2 locations to get each frame from the spritesheet  
for (int i = 0; i < (int)frameLocations.size(); i++)
{
SDL_Rect newRect = { frameLocations[i].x, frameLocations[i].y, width, height, };
rectangles.push_back(newRect);
}

//load the frames for the animation
this->_mAnimations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles));
this->_mOffsets.insert(std::pair<std::string, Vector2>(name, offset));
}


/*void ResetAnimation
*Resets all animation associated with sprite
*/
void AnimatedSprite::ResetAnimation() {
	this->_mAnimations.clear();
	this->_mOffsets.clear();
}

/*void StopAnimation
*Stops the current animation
*/
void AnimatedSprite::StopAnimation() {
	this->_iFrameIndex = 0;
	this->AnimationDone(this->_sCurrentAnimation);
}

/*void SetVisible
*Changes visibility of the animated sprite
*/
void AnimatedSprite::SetVisible(bool visible) {
	this->_bVisible = visible;
}
/*
virtual void AnimationDone
*Logic that occurs when animation finishes

void AnimatedSprite::AnimationDone(std::string currentAnimation) {

}
*/