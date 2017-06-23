/*************************************************************************
File name:		animatedsprite.h
Description:	Header file for AnimatedSprite class.
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

//includes
#include <map>
#include <string>
#include <vector>
#include "sprite.h";
#include "globals.h"

class Graphics;

//Class AnimatedSprites - Holds logic for animated sprites, inherits from Sprites
class AnimatedSprite : public Sprite {
public:

	AnimatedSprite();	//constructor
	AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate);
	~AnimatedSprite();	//desctructor

	//void PlayAnimation - Plays the animation if it's not already playing
	void PlayAnimation(std::string sAnimationName, bool once = false);

	//void Update - Updated animated sprite(timer)
	void Update(int elapsedTime);

	//void Draw - Draws sprite to screen
	void Draw(Graphics &graphics, int x, int y);



protected:
	double _dTimeToUpdate;
	bool _bCurrentAnimationOnce;
	std::string _sCurrentAnimation;

	/*void AddAnimation
	*Adds an animation to the map of animations for the sprite
	*Note to self: C style arrays like: Vector2 frameLocations[] do not contain the info on # of elements/length of array
	*..use std::array(closer to C#) for fixed sizes or std::vectors(like C# lsits) for unknown sizes
	*here, we'll use a std::vector since animations can have different number of frames...
	*/
	void AddAnimation(std::vector<Vector2> frameLocations, std::string name, int width, int height, Vector2 offset);

	/*void ResetAnimation
	*Resets all animation associated with sprite
	*/
	void ResetAnimation();

	/*void StopAnimation
	*Stops the current animation
	*/
	void StopAnimation();

	/*void SetVisible
	*Changes visibility of the animated sprite
	*/
	void SetVisible(bool visible);

	/*virtual void AnimationDone
	*Logic that occurs when animation finishes
	*Note: adding the = 0 means that the function is now pure virtual, can't be implemented in this class
	*/
	virtual void AnimationDone(std::string currentAnimation) = 0;

	/*	virtual void SetupAnimation
	*	A required function that sets up the sprite's animations
	*/
	virtual void SetupAnimation() = 0;

private:
	std::map<std::string, std::vector<SDL_Rect>> _mAnimations;
	std::map<std::string, Vector2> _mOffsets;

	int _iFrameIndex;
	double _dTimeElapsed;
	bool _bVisible;
};
#endif	//end of #include guard