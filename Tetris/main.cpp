#include <SDL.h>
#include <SDL_image.h>
#include <SDL_syswm.h>
#include <SDL_ttf.h>
#include <string>

#include "res_path.h"
#include "block_types.h"
#include "global_definitions.h"
#include "global_variables.h"
#include "func.h"
#include "draw.h"

const std::string path = getResourcePath();

void clear_map();
void load_textures();
void generate_text();
void destroy_textures();

SDL_Texture* load_texture(const std::string &file, SDL_Renderer *ren);

int main(int argc, char **argv){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		return true;
	}
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		SDL_Quit();
		return true;
	}
	if( TTF_Init() == -1 )
	{
		IMG_Quit();
		SDL_Quit();
		return true;
    }
	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		IMG_Quit();
		SDL_Quit();
		return true;
	}
	renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return true;
	}
	add_speed = 0;
	bool exit_game = false;
	load_textures();
	generate_text();
	draw_bg();
	draw_score();
	Block = generator();
	SDL_Event e;
	while(!exit_game)
	{
		quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					quit = true;
				if (e.type == SDL_KEYDOWN)
					switch( e.key.keysym.sym )
							{
								case SDLK_UP:
									Block->turn();
								break;
								case SDLK_DOWN:
									if(!add_speed)
									{
										add_speed = speed - 100;
										add_speed = add_speed>0?add_speed:0;
										speed = speed - add_speed;
									}
								break;
								case SDLK_LEFT:
									Block->moveL();
								break;
								case SDLK_RIGHT:
									Block->moveR();
								break;
							}
				if (e.type == SDL_KEYUP)
					switch( e.key.keysym.sym )
							{
								case SDLK_DOWN:
									speed = speed + add_speed;
									add_speed = 0;
								break;
							}
			}
			Block->move();
		}
		exit_game = true;
		if(lose)
		{
			lose = false;
			quit = false;
			while (!quit&&SDL_WaitEvent(&e))
			{
				if (e.type == SDL_QUIT)
					quit = true;
				if (e.type == SDL_KEYDOWN)
				switch( e.key.keysym.sym )
				{
							case SDLK_UP:
								quit = true;
								exit_game = false;
								score = 0;
								draw_score();
								add_speed = 0;
								speed = START_SPEED;
								clear_map();
								delete Block;
								Block = generator();
								break;
				}
			}
		}
	}
	delete Block;
	destroy_textures();
	TTF_CloseFont( gFont );
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	return 0;
}

void clear_map()
{
	for(int i = 0; i < HEIGHT; i++)
	{
		pull[i] = 0;
		for(int j = 0; j < WIDTH; j++)
		{
			map[i][j] = 0;
		}
	}
}

void load_textures()
{
	bg = load_texture(path + "background2.bmp",renderer);
	white = load_texture(path + "white.bmp",renderer);
	SDL_SetTextureBlendMode( white, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod( white, 150);
	cube = load_texture(path + "cube.bmp",renderer);
	end = load_texture(path + "game-over.png",renderer);
}

void generate_text()
{
	 gFont = TTF_OpenFont( (path + "game.ttf").c_str(), 28 );
	 SDL_Color textColor = { 0, 0, 0 };
	 SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, "0123456789", textColor );
	 digits = SDL_CreateTextureFromSurface( renderer, textSurface );
	 SDL_FreeSurface( textSurface );
}

void destroy_textures()
{
	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(digits);
	SDL_DestroyTexture(white);
	SDL_DestroyTexture(end);
	SDL_DestroyTexture(cube);
}

SDL_Texture* load_texture(const std::string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	return texture;
}