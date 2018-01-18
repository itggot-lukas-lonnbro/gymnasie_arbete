#include "mainGame.h"

#include <iostream>
#include <GL\glew.h>
#include <SDL\SDL.h>
#include <glm-0.9.9-a1\glm\gtc\type_ptr.hpp>
#include <glm-0.9.9-a1\glm\gtc\matrix_transform.hpp>

#include "entity.h"

mainGame::mainGame(int w, int h) : state(gameState::PLAY)
{
	WIDTH = w;
	HEIGHT = h;
}


mainGame::~mainGame()
{
}

void mainGame::SDLSetup() {
	bool successfulSetup = true;
	window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		successfulSetup = false;
		std::string errorBeautifier = "Unable to initalize SDL Window.";
		errorBeautifier += SDL_GetError();
		const char *errormsg = errorBeautifier.c_str();
		std::cout << errormsg << "\nIn function " << __FUNCTION__ <<std::endl;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

	SDL_GL_CreateContext(window);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
}
void mainGame::openGLSetup() {
	glewExperimental = true;
	
	if (glewInit() != GLEW_OK) {
		std::cout << "Unable to init glew.\n";
		int a;
		std::cin >> a;
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
}
void mainGame::setup() {
	SDLSetup();
	openGLSetup();

	//testing purposes, remove later.

	/*float textureCube[] = {
		// positions          // colors           // texture coords
		4.0f,  4.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		4.0f, 3.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		3.0f, 3.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		3.0f,  4.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};*/

	float octagon[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(octagon), octagon, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	basicShader.init("basicVertex.glsl", "basicFragment.glsl");

	entity test;
	test.loadModel("testmodel.txt");
}

void mainGame::run() {
	setup();
	gameLoop(); 
}

void mainGame::gameLoop() {
	while (state != gameState::EXIT) {
		update();
		draw();
	}
}
void mainGame::update() {
	inputHandler.update();
	if(inputHandler.events.quit ||inputHandler.events.q){
		state = gameState::EXIT;
	}
}
void mainGame::draw() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	basicShader.useShader();
	
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	basicShader.setFloat3f("objectColor", glm::value_ptr(color));

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	basicShader.unUseShader();

	SDL_GL_SwapWindow(window);
}