/*************************************************************************
File name:	input.cpp
Description:	Keeps track of keyboard state
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include "input.h"
/*************************************************************************
Constructors and Deconstructors
**************************************************************************/

/*************************************************************************
Functions
**************************************************************************/

//BeginNewFrame -	This function should get called at the beginning of each new frame.
//					It will reset keys that are no logner relevant
void Input::BeginNewFrame() {
	this->_mPressedKeys.clear();
	this->_mReleasedKeys.clear();
}

//KeyDownEvent	-	This should be called when a key has been pressed
void Input::KeyDownEvent(const SDL_Event& event) {
	this->_mPressedKeys[event.key.keysym.scancode] = true;	//key was pressed = true
	this->_mHeldKeys[event.key.keysym.scancode] = true; //key being pressed is also currently held
}

//KeyUpEvent - This should be called when a key is released
void Input::KeyUpEvent(const SDL_Event& event) {
	this->_mReleasedKeys[event.key.keysym.scancode] = true;	//key was released = true
	this->_mHeldKeys[event.key.keysym.scancode] = false; //key is no longer being held
}

//WasKeyPressed - Check if a certain key was pressed
bool Input::WasKeyPressed(SDL_Scancode scKey) {
	return this->_mPressedKeys[scKey];
}

//WasKeyReleased - Check if a certain key was released
bool Input::WasKeyReleased(SDL_Scancode scKey) {
	return this->_mReleasedKeys[scKey];
}

//IsKeyHeld - Check if a certain key is currently held
bool Input::IsKeyHeld(SDL_Scancode scKey) {
	return this->_mHeldKeys[scKey];
}
