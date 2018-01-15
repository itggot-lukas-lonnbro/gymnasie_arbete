#include "inputProcessing.h"

#include <SDL\SDL.h>

inputProcessing::inputProcessing()
{
}


inputProcessing::~inputProcessing()
{
}

void inputProcessing::update() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			events.quit = true;
			break;
		case SDL_KEYDOWN:
			switch (evnt.key.keysym.sym) {
			case SDLK_q:
				events.q = true;
				break;
			case SDLK_w:
				events.w = true;
				break;
			case SDLK_s:
				events.s = true;
				break;
			case SDLK_a:
				events.a = true;
				break;
			case SDLK_d:
				events.d = true;
				break;
			case SDLK_x:
				events.x = true;
				break;
			case SDLK_i:
				events.i = true;
				break;
			case SDLK_l:
				events.l = true;
				break;
			case SDLK_k:
				events.k = true;
				break;
			case SDLK_j:
				events.j = true;
				break;
			case SDLK_LEFT:
				events.arrow_left = true;
				break;
			case SDLK_RIGHT:
				events.arrow_right = true;
				break;
			case SDLK_DOWN:
				events.arrow_down = true;
				break;
			case SDLK_UP:
				events.arrow_up = true;
				break;
			case SDLK_SPACE:
				events.space = true;
				break;
			case SDLK_b:
				events.b = true;
				break;
			case SDLK_v:
				events.v = true;
				break;
			case SDLK_n:
				events.n = true;
				break;
			case SDLK_m:
				events.m = true;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (evnt.key.keysym.sym) {
			case SDLK_q:
				events.q = false;
				break;
			case SDLK_w:
				events.w = false;
				break;
			case SDLK_s:
				events.s = false;
				break;
			case SDLK_a:
				events.a = false;
				break;
			case SDLK_d:
				events.d = false;
				break;
			case SDLK_x:
				events.x = false;
				break;
			case SDLK_i:
				events.i = false;
				break;
			case SDLK_l:
				events.l = false;
				break;
			case SDLK_k:
				events.k = false;
				break;
			case SDLK_j:
				events.j = false;
				break;
			case SDLK_LEFT:
				events.arrow_left = false;
				break;
			case SDLK_RIGHT:
				events.arrow_right = false;
				break;
			case SDLK_DOWN:
				events.arrow_down = false;
				break;
			case SDLK_UP:
				events.arrow_up = false;
				break;
			case SDLK_SPACE:
				events.space = false;
				break;
			case SDLK_b:
				events.b = false;
				break;
			case SDLK_v:
				events.v = false;
				break;
			case SDLK_n:
				events.n = false;
				break;
			case SDLK_m:
				events.m = false;
				break;
			}
			break;
		}
	}

	SDL_GetMouseState(&events.mousePosX, &events.mousePosY);
}