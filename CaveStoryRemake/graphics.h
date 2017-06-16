/*************************************************************************
File name:		graphics.h
Description:	Header file for Graphics class.
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef GRAPHICS_H
#define GRAPHICS_H

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics();
	~Graphics();
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

};
#endif	//end of #include guard