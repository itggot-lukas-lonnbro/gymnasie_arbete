#include "main.h"

#include <GL\glew.h>
#include <fstream>
#include <iostream>
#include <string>

main::main(int w, int h)
{
	WIDTH = w;
	HEIGHT = h;
}


main::~main()
{
}

//Implement timestamp.
struct errorLogger {
	void log(const std::string& msg, const std::string& function) { 
		std::ofstream myfile("error.txt");
		if (myfile.is_open())
		{
			myfile << msg << "\n----\n";
		}
	}
}error;


void main::run() {
	setup();
}

void main::SDLSetup() {
	bool successfulSetup = true;
	window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		successfulSetup = false;
		std::string errorBeautifier = "Unable to initalize SDL Window.";
		errorBeautifier += SDL_GetError();
		const char *errormsg = errorBeautifier.c_str();
		error.log(errormsg, __FUNCTION__);
	}
	SDL_GL_CreateContext(window);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

}
void main::openGLSetup() {

}
void main::setup() {
	SDLSetup();
	openGLSetup();
}