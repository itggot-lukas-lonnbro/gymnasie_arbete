#pragma once

#include <SDL\SDL.h>
#include "shaders.h"
#include "inputProcessing.h"

class mainGame
{
public:
	mainGame(int windowWidth, int windowHeight);
	~mainGame();

	int WIDTH;
	int HEIGHT;

	void run();
private:
	SDL_Window *window;

	void setup();
	void SDLSetup();
	void openGLSetup();

	void gameLoop();
	void draw();
	void update();

	enum class gameState { PLAY, EXIT, MENU };
	gameState state;

	unsigned int vao;
	unsigned int vbo;

	shaders basicShader;
	inputProcessing inputHandler;
};

