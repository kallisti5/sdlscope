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
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE:
							quit = SDL_TRUE;
							break;
						case SDLK_1:
							scope->ToggleChannel(SCOPE_STATE_EN_CHAN_0);
							break;
						case SDLK_2:
							scope->ToggleChannel(SCOPE_STATE_EN_CHAN_1);
							break;
						case SDLK_3:
							scope->ToggleChannel(SCOPE_STATE_EN_CHAN_2);
							break;
						case SDLK_4:
							scope->ToggleChannel(SCOPE_STATE_EN_CHAN_3);
							break;
						case SDLK_q:
							scope->ChannelPosition(0, -5);
							break;
						case SDLK_a:
							scope->ChannelPosition(0, 5);
							break;
						case SDLK_w:
							scope->ChannelPosition(1, -5);
							break;
						case SDLK_s:
							scope->ChannelPosition(1, 5);
							break;
						case SDLK_e:
							scope->ChannelPosition(2, -5);
							break;
						case SDLK_d:
							scope->ChannelPosition(2, 5);
							break;
						case SDLK_r:
							scope->ChannelPosition(3, -5);
							break;
						case SDLK_f:
							scope->ChannelPosition(3, 5);
							break;
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
