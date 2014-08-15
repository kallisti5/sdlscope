/*
 *  2013 - 2014 Alexander von Gluck IV
 *  Released under the terms of the MIT license
 */
#ifndef __SCOPELOGIC_H_
#define __SCOPELOGIC_H_


#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  

#include <SDL.h>


class ScopeLogic {
public:
				ScopeLogic();
				~ScopeLogic();

    void        Render(SDL_Surface *src, SDL_Surface *dst);
	void 		CreateWindow(SDL_Surface** window, uint32_t width, uint32_t height);

//	void 		DrawBG(SDL_Surface* screen);

private:
	uint32_t 	waveTable[64];
	void 		GenerateWave(uint32_t position);

	void 		DrawGrid(SDL_Surface* window);
	void 		DrawWave(SDL_Surface* window);
	void 		DrawWave2(SDL_Surface* window);

	void 		DrawHLine(SDL_Surface* screen, uint32_t x, uint32_t y, uint32_t w, uint32_t color, uint32_t flag);
	void 		DrawVLine(SDL_Surface* screen, uint32_t x, uint32_t y, uint32_t h, uint32_t color, uint32_t flag);
	void 		DrawPoint(SDL_Surface* screen, uint32_t x, uint32_t y, uint32_t color);
};
	

#endif /* __SCOPELOGIC_H_ */