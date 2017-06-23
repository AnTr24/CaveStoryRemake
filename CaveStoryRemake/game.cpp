/*************************************************************************
File name: game.cpp
Description:	Implements the game logic / holds information for our main game loop
**************************************************************************/

/*************************************************************************
Includes
**************************************************************************/
#include <SDL.h>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include <algorithm> //access to std::min
/*************************************************************************
Constructors and Deconstructors
**************************************************************************/
namespace {
	//define some constants for the game
	const int FPS = 50;	//limit frames to 50
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;	//limit time a frame can last
}

//Game constructor
//Initializes some things
Game::Game() {
	//Initializes some subsystems such as timer,audio, etc for SDL. SDL Inits must be done before msot SDL commands.
	SDL_Init(SDL_INIT_EVERYTHING);

	//Start the game loop from constructor
	this->GameLoop();
}

//Game destructor
Game::~Game() {

}
/*************************************************************************
Functions
**************************************************************************/

//loop that controls the Game on a frame-by-frame basis
void Game::GameLoop() {
	//Game loop Inits*****************************************************************************
	Graphics graphics;	//Game graphic/window
	Input input;		//Controls and contains info on user inputs(Cavestory is keyboard only)
	SDL_Event event;	//Holds what event happens in a frame

	//player spritesheet is 16x16 per sprite, floats are for location on screen
	//for visual studio, filepath starts at the folder where the .cpp and .h files are
	this->_player = Player(graphics, 100, 100);

	int LAST_UPDATE_TIME = SDL_GetTicks();	//get timing of first frame

	//Game loop Inits END***************************************************************************
	//Start gameloop and it occurs continuously...
	while (true) {	//this is the beginning of a frame

		input.BeginNewFrame();	//Reset key states for new frame
		SDL_PollEvent(&event);	//Poll for what event occured

		//Take action depending on event type
		switch (event.type)
		{
		case SDL_KEYDOWN:	//Key was pressed
			if (event.key.repeat == 0) //check for keys that weren't held
			{
				input.KeyDownEvent(event);	//trigger keydown event
			}
			break;
		case SDL_KEYUP:	//Key was released
			input.KeyUpEvent(event);	//trigger keyup event
			break;
		case SDL_QUIT:	//occurs when the window is exited
			return;	//leave the gameloop
		}

		//Now that the inputs/keys have been set, take an action

		//Esc key - closes game
		if (input.WasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}
		//Left Key - Moves player left
		else if (input.WasKeyPressed(SDL_SCANCODE_LEFT) == true) {
			this->_player.MoveLeft();
		}
		//Right Key - Moves player right
		else if (input.WasKeyPressed(SDL_SCANCODE_RIGHT) == true) {
			this->_player.MoveRight();
		}

		//if neither horizontal move keys are being held, stop moving
		if (!input.IsKeyHeld(SDL_SCANCODE_LEFT) && !input.IsKeyHeld(SDL_SCANCODE_RIGHT)) {
			this->_player.StopMoving();
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();	//get frame end time
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;	//find the elapsed time between frame start & end

		this->Update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME)); //update with the smaller value, at a max of 50ms

		LAST_UPDATE_TIME = CURRENT_TIME_MS;	//update next frame start time

		this->Draw(graphics);
	}	//end of frame
}

void Game::Draw(Graphics& graphics) {
	graphics.Clear();

	this->_player.Draw(graphics);
	graphics.Render();
}

void Game::Update(float elapsedTime) {
	this->_player.Update(elapsedTime);
}