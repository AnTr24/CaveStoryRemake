/*************************************************************************
File name:		input.h
Description:	Header file for Input class.
**************************************************************************/

//#include guard.  Prevents double definitions
#ifndef INPUT_H
#define INPUT_H

//includes
#include <SDL.h>	
#include <map>	//basically the same as a dictionary...


//Class definition
class Input {
public:
	void BeginNewFrame();

	void KeyUpEvent(const SDL_Event& event);	
	void KeyDownEvent(const SDL_Event& event);

	//Determine if key...
	bool WasKeyPressed(SDL_Scancode scKey);	//...was pressed
	bool WasKeyReleased(SDL_Scancode scKey);//...was released
	bool IsKeyHeld(SDL_Scancode scKey);//...is currently held
private:
	//std(namespace)::(scrope operator)map .... like doing a local include?
	//SDL_Scancode: holds values of SDL keyboard scancode representations https://wiki.libsdl.org/SDL_Scancode
	std::map<SDL_Scancode, bool> _mHeldKeys;	//map member variable _mHeldKeys, relating SDL_Scancode(Key) and bool(value), used for held keys
	std::map<SDL_Scancode, bool> _mPressedKeys; //contains info on keys pressed
	std::map<SDL_Scancode, bool> _mReleasedKeys;//contains info on keys released
};
#endif	//end of #include guard