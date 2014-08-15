/* Bring up a window and play with it */  
  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <math.h>  
  

#include <SDL.h>
uint32_t wavetab[64];  
  


void DrawHLine(SDL_Surface *screen, uint32_t x, uint32_t y, uint32_t w,   
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
  
void DrawVLine(SDL_Surface *screen, uint32_t x, uint32_t y, uint32_t h,   
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
  
void Drawpoint(SDL_Surface *screen, uint32_t x, uint32_t y, uint32_t color)  
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
 

void generatewave(uint32_t position)  
{  
	int i = 0;  
	for(i = 0;i < 64; i++) {  
		wavetab[i] = (sin(2 * 3.1415 * i / 64.0 + position * 3.1415 / 128) + 1) * 25.0;  
	}  
}  
  

void DrawBg(SDL_Surface *screen)  
{  
	SDL_Surface *picture, *displayfmt;  
	char *bmpfile = "logo.png";   
	uint32_t color;  
	SDL_Rect rect;  
  
	picture = SDL_LoadBMP(bmpfile);  
	if (picture == NULL) {  
		printf("Load logo.bmp failed!\n");  
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
  

void CreateWindow(SDL_Surface **window, uint32_t width, uint32_t height)  
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
  
void DrawGrid(SDL_Surface *window)  
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
  
void DrawWave(SDL_Surface *window)  
{  
	int i;  
	uint32_t color;  
	color = SDL_MapRGB(window->format, 0xFF,0,0);  
	for(i = 0; i < window->w; i++) {  
		Drawpoint(window, i, window->h/2 - wavetab[i%64], color);  
	}	 
}  
  
  
void DrawWave2(SDL_Surface *window)  
{  
	int i;  
	uint32_t color;  
	color = SDL_MapRGB(window->format, 0xFF,0xff,0);  
	for(i = 0; i < window->w; i++) {  
		Drawpoint(window, i, window->h/2 - (wavetab[(i+15)%64] >> 1), color);  
	}	 
}  
  
void render(SDL_Surface *src, SDL_Surface *dst)  
{  
	static uint32_t position = 0;  
  
	position += 10;  
	if (position == 128)  
		position = 0;  
	SDL_Rect update;  
	update.x = 10;  
	update.y = 50;  
	  
	DrawGrid(src);  
	generatewave(position);  
	DrawWave(src);  
	DrawWave2(src);  
  
	if (SDL_BlitSurface(src, NULL, dst, &update) < 0) {  
		printf("Blit failed: %s\n", SDL_GetError());  
	}  
}  
  
int main(int argc, char *argv[])  
{  
	SDL_Surface *screen, *window;  
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
  
	DrawBg(screen);  
	SDL_UpdateRect(screen, 0, 0, 0, 0);  
	CreateWindow(&window, 480, 320);  
	  
	uint32_t quit = 0;  
	//int j = 0;  
	while (!quit) {  
		render(window, screen);  
		SDL_UpdateRect(screen, 10, 50, 480, 320);  
		  
		SDL_Event   event;  
		uint32_t ret = 0;	 
		//j = 0;	  
		while (ret = SDL_PollEvent(&event)) {  
			//printf("j = %d,ret = %d ", j++, ret);  
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
