/*
 *  2013 - 2014 Alexander von Gluck IV
 *  Released under the terms of the MIT license
 */
#include "scopelogic.h"
  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <math.h>  

#include <SDL.h>


ScopeLogic::ScopeLogic()
	:
	channelState(0)
{
}


ScopeLogic::~ScopeLogic()
{


}


void
ScopeLogic::ToggleChannel(uint32_t item)
{
	channelState ^= item;
}


void
ScopeLogic::DrawHLine(SDL_Surface *screen, uint32_t x, uint32_t y, uint32_t w,
		uint32_t color, uint32_t flag)  
{  
	uint32_t i;  
	if ((x + w) > screen->w) {  
		w = screen->w - x;  
	}  

	uint8_t* pixel = (uint8_t*)screen->pixels + y * screen->pitch +   
		x * screen->format->BytesPerPixel;  

	if (flag == 0)  
		for (i = 0; i < w ; i ++) {  
			*(uint32_t*)pixel = color;  
			pixel += 4; 
		}  
	else  
		for (i = 0; i < w/2; i ++) {  
			*(uint32_t*)pixel = color;  
			pixel += 8;  
		}  
}  
  
void
ScopeLogic::DrawVLine(SDL_Surface *screen, uint32_t x, uint32_t y, uint32_t h,   
		uint32_t color, uint32_t flag)  
{  
	uint32_t i;  
	if ((y + h) > screen->h) {  
		h = screen->h - x;  
	}  

	uint8_t* pixel = (uint8_t*)screen->pixels + y * screen->pitch +   
		x * screen->format->BytesPerPixel;  
  
	if (flag == 0)  
		for (i = 0; i < h ; i ++) {  
			*(uint32_t *)pixel = color;  
			pixel += screen->pitch;  
		}  
	else  
		for (i = 0; i < h/2 ; i ++) {  
			*(uint32_t *)pixel = color;  
			pixel += (screen->pitch) * 2;  
		}  
}  
  
void
ScopeLogic::DrawPoint(SDL_Surface *screen, uint32_t x, uint32_t y, uint32_t color)  
{  
	uint32_t i;  
	if (y >= (screen->h - 3)) {  
		return;  
	}  
		  
	uint8_t* pixel = (uint8_t*)screen->pixels + y * screen->pitch +   
		x * screen->format->BytesPerPixel;  
  
	*(uint32_t *)pixel = color;  
	*(uint32_t *)(pixel + screen->pitch) = color;  
	*(uint32_t *)(pixel + 2 * screen->pitch) = color;  
	*(uint32_t *)(pixel + 3 * screen->pitch) = color;  
}  
 

void
ScopeLogic::GenerateWave(uint32_t position, uint32_t channel)
{

	if (channel > MAX_CHANNELS) {
		printf("%s: Requested waveform generated on improper channel!\n", __func__);
		return;
	}
	
	int i = 0;  
	for(i = 0;i < MAX_SAMPLES; i++) {
		waveTable[channel][i] = (sin(2 * 3.1415 * i / 64.0 + position * 3.1415 / 128) + 1) * 25.0 * (channel + 1);
	}  
}  
  

#if 0
void
ScopeLogic::DrawBG(SDL_Surface *screen)  
{  
	SDL_Surface *picture, *displayfmt;  
	char *bmpfile = "logo.png";   
	uint32_t color;  
	SDL_Rect rect;  
  
	picture = SDL_LoadBMP(bmpfile);  
	if (picture == NULL) {  
		printf("Load of logo.bmp failed!\n");  
		return;   
	}  
	displayfmt = SDL_DisplayFormat(picture);  
	if ( displayfmt == NULL ) {  
		fprintf(stderr, "Couldn't convert image: %s\n", SDL_GetError());  
		return;  
	}  
  
	SDL_FreeSurface(picture);  
	picture = displayfmt;  
  
	color = SDL_MapRGB(screen->format, 0x00, 0x00, 0xFF);  
	rect.x = 0;  
	rect.y = 0;  
	rect.w = screen->w;  
	rect.h = screen->h;  
	SDL_FillRect(screen, &rect, color);  
	  
	if ( SDL_BlitSurface(picture, NULL, screen, NULL) < 0 ) {  /* print Oscilloscope logo*/  
		fprintf(stderr, "Blit failed: %s\n", SDL_GetError());  
		return;  
	}  
}
#endif
  

void
ScopeLogic::CreateWindow(SDL_Surface **window, uint32_t width, uint32_t height)  
{  
	*window = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32,  
			0xFF << 24, 0xff << 16, 0xFF << 8, 0xFF);  
	if (*window == NULL) {  
		printf("Create window failed!\n");  
		return;  
	} else {  
		printf("Create window successfully!\n");
	}  
}  
  
void
ScopeLogic::DrawGrid(SDL_Surface *window)  
{  
	uint32_t i = 0;  
	uint32_t color;  
	SDL_Rect rect;  
  
	rect.x = 0;  
	rect.y = 0;  
	rect.w = window->w;  
	rect.h = window->h;  
  
	color = SDL_MapRGB(window->format, 0, 0, 0);  
	SDL_FillRect(window, &rect, color);  
  
	color = SDL_MapRGB(window->format, 100, 100, 100);	 
	for (i = 0; i < 7; i++)
		DrawHLine(window, 0, 40 + i * 40, window->w, color, 1);  
  
	for (i = 0; i < 11; i++)
		DrawVLine(window, 40 + i * 40, 0, window->h, color, 1);  
  
	for(i =0; i < 39; i++)
		DrawHLine(window, 236, 8 + i * 8, 8, color, 0);   
  
	for(i =0; i < 59; i++)
		DrawVLine(window, 8 + i * 8, 156, 8, color, 0);   
}  
 

void
ScopeLogic::DrawWave(SDL_Surface *window, uint32_t channel)
{
	int i;

	uint32_t color;
	switch(channel) {
		case 0:
			color = SDL_MapRGB(window->format, 0xFF, 0, 0);
			break;
		case 1:
			color = SDL_MapRGB(window->format, 0xFF, 0xFF, 0);
			break;
		case 2:
			color = SDL_MapRGB(window->format, 0, 0xFF, 0);
			break;
		case 3:
			color = SDL_MapRGB(window->format, 0xFF, 0, 0xFF);
			break;
	}
	
	for(i = 0; i < window->w; i++) {  
		DrawPoint(window, i, window->h / 2 - waveTable[channel][i % MAX_SAMPLES], color);  
	}	 
}  
  
  
void
ScopeLogic::Render(SDL_Surface *src, SDL_Surface *dst)  
{  
	static uint32_t position;  
  
	position += 10;  
	if (position == 128)  
		position = 0;  
	SDL_Rect update;  
	update.x = 10;  
	update.y = 50;  
	  
	DrawGrid(src);  
	GenerateWave(position, 0);
	GenerateWave(position, 1);
	GenerateWave(position, 2);
	GenerateWave(position, 3);

	if ((channelState & SCOPE_STATE_EN_CHAN_0) != 0)
		DrawWave(src, 0);
	if ((channelState & SCOPE_STATE_EN_CHAN_1) != 0)
		DrawWave(src, 1);
	if ((channelState & SCOPE_STATE_EN_CHAN_2) != 0)
		DrawWave(src, 2);
	if ((channelState & SCOPE_STATE_EN_CHAN_3) != 0)
		DrawWave(src, 3);
  
	if (SDL_BlitSurface(src, NULL, dst, &update) < 0) {  
		printf("Blit failed: %s\n", SDL_GetError());  
	}  
}
