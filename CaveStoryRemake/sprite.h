/*************************************************************************
File name:		sprite.h
Description:	Header file for thing class.
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef SPRITE_H
#define SPRITE_H

//includes
#include <SDL.h>
#include <string>

class Graphics;

//Class definition
class Sprite {
public:
	Sprite();	//default constructor
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY);
	virtual ~Sprite();	//virtual desctructor

	virtual void Update();
	void Draw(Graphics &graphics, int x, int y);
protected:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;

private:
	float _x, _y;
};
#endif	//end of #include guard