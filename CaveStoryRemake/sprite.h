/*************************************************************************
File name:		sprite.h
Description:	Defines the drawable objects in the game
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef SPRITE_H
#define SPRITE_H

//includes
#include <SDL.h>
#include <string>
#include "rectangle.h"
#include "globals.h"

class Graphics;

//Class definition
class Sprite {
public:
	Sprite();	//default constructor
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY);
	virtual ~Sprite();	//virtual desctructor

	//const Rectangle GetBoundingBox
	//Retrieves the collision rectangle
	const Rectangle GetBoundingBox() const;

	//const sides::Side GetCollisionSide
	//Grab the side of the collision
	const sides::Side GetCollisionSide(Rectangle &other) const;

	const inline float GetX() const { return this->_x; };	//Getter for sprite X coordinate
	const inline float GetY() const { return this->_y; };	//Getter for sprite Y coordinate

	void SetSourceRectX(int value); //changes the X position of the source rectangle
	void SetSourceRectY(int value);	//changes the Y position of the source rectangle
	void SetSourceRectWidth(int value);		//changes the width of the source rectangle
	void SetSourceRectHeight(int value);	//changes the height of the source rectangle

	virtual void Update();
	void Draw(Graphics &graphics, int x, int y);
protected:
	SDL_Rect _sourceRect;		//rectangle defining area of spritesheet to be drawn
	SDL_Texture* _spriteSheet;	//holds the spritesheet reference
	float _x, _y;

	Rectangle _rBoundingBox;
private:
	
};
#endif	//end of #include guard