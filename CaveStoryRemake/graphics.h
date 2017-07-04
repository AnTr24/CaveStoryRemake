/*************************************************************************
File name:		graphics.h
Description:	Header file for Graphics class.
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics();
	~Graphics();

	/*	SDL_Surface* loadImage
	*	Loads an image into the _mSpriteSheets map if it doesn't already exist.
		As a result, each image will only be loaded once.
		Returns the image from the map regardless of whether or not it was just loaded
	*/
	SDL_Surface* LoadImage(const std::string& filepath);

	/*	void BlitSurface
		Draws a texture to a certain part of the backbuffer
		(SDL_Texture* source	-	Texture to be drawn
		SDL_Rect* sourceRectangle	-	 Spreadsheet source
		SDL_Rect* destinationRectangle	-	Part of screen to draw to
	*/		
	void BlitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	/*	void Render
		Renders everything to the screen
	*/
	void Render();

	/*	void Clear
	Clears the screen
	*/
	void Clear();

	/*	SDL_Renderer* GetRenderer
		Returns the renderer
	*/
	SDL_Renderer* GetRenderer() const;

private:
	SDL_Window* _window;		//game window
	SDL_Renderer* _renderer;	//this acts as the backbuffer for rendering

	std::map<std::string, SDL_Surface*> _mSpriteSheets;
};
#endif	//end of #include guard