/*	Graphics class header file	
*/

//this is a #include guard. If graphics.h is included my multiple files,
//it will only define the Graphics class once
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
#endif