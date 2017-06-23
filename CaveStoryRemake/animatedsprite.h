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

	/*	virtual void SetupAnimation
	*	A required function that sets up the sprite's animations
	*/
	virtual void SetupAnimation();

protected:
	double _dTimeToUpdate;
	bool _bCurrentAnimationOnce;
	std::string _sCurrentAnimation;

	/*void AddAnimation
	*Adds an animation to the map of animations for the sprite
	*/
	void AddAnimation(Vector2 frameLocations[], std::string name, int width, int height, Vector2 offset);

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
	*/
	virtual void AnimationDone(std::string currentAnimation);


private:
	std::map<std::string, std::vector<SDL_Rect>> _mAnimations;
	std::map<std::string, Vector2> _mOffsets;

	int _iFrameIndex;
	double _dTimeElapsed;
	bool _bVisible;
};
#endif	//end of #include guard