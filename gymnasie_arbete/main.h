#pragma once

#include <SDL\SDL.h>

#undef main

class main
{
public:
	main(int windowWidth, int windowHeight);
	~main();

	int WIDTH;
	int HEIGHT;

	void run();
private:
	SDL_Window *window;

	void setup();
	void SDLSetup();
	void openGLSetup();
};

