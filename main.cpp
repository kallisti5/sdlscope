/*
 *  2013 - 2014 Alexander von Gluck IV
 *  Released under the terms of the MIT license
 */

#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scopelogic.h"


int
main(int argc, char *argv[])
{
	SDL_Surface *screen;
	SDL_Surface *window;

	/* Options */
	uint32_t position = 0;
	int w = 600;
	int h = 400;
	int desired_bpp = 0;
	uint32_t video_flags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		return(1);
	} else {
		printf("SDL_Init is ok!\n");
	}

	/* Initialize the display */
	screen = SDL_SetVideoMode(w, h, 32, SDL_SWSURFACE);
	if (screen == NULL) {
		printf("Couldn't set %dx%dx%d video mode: %s\n",
			w, h, desired_bpp, SDL_GetError());
		return -1;
	}

	ScopeLogic* scope = new ScopeLogic();

	//scope->DrawBG(screen);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	scope->CreateWindow(&window, 480, 320);

	uint32_t quit = 0;
	//int j = 0;
	while (!quit) {
		scope->Render(window, screen);
		SDL_UpdateRect(screen, 10, 50, 480, 320);
		SDL_Event event;
		uint32_t ret = 0;
		//j = 0;
		while ((ret = SDL_PollEvent(&event))) {
			//printf("j = %d,ret = %d^@", j++, ret);
			switch(event.type) {
				/*case SDL_MOUSEBUTTONDOWN:
					break;*/
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						quit = SDL_TRUE;
					}
					break;
				case SDL_QUIT:
					quit = SDL_TRUE;
					break;
			}
		}
		SDL_Delay(50);
	}
	SDL_Quit();
}
