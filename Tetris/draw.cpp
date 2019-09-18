#include <SDL.h>
#include <SDL_ttf.h>

#include "global_definitions.h"
#include "draw.h"

extern int map[HEIGHT][WIDTH];
extern int score;

extern SDL_Renderer *renderer;
extern SDL_Texture *bg;
extern SDL_Texture *white;
extern SDL_Texture *cube;
extern SDL_Texture *digits;
extern SDL_Texture *end;
extern TTF_Font *gFont;

void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,int width,int height);
void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void render_texture(SDL_Texture *tex, SDL_Renderer *ren);

void draw_map()
{
	draw_gamespace();
	for(int i = 0; i < HEIGHT; i++)
	{
		for(int j = 0; j < WIDTH; j++)
		{
			if(map[i][j] & 1) // ==
			{
				render_texture(cube,renderer,X_OFFSET+j*20,Y_OFFSET+i*20);
			}
		}
	}
	SDL_RenderPresent(renderer);
}

void draw_gamespace()
{
	const SDL_Rect rct = {X_OFFSET,Y_OFFSET,GAMESPACE_WIDTH, GAMESPACE_HEIGHT};
	const SDL_Rect src = {X_OFFSET+35,Y_OFFSET,GAMESPACE_WIDTH, GAMESPACE_HEIGHT};
	SDL_RenderCopy(renderer, bg, &src, &rct);
	SDL_RenderCopy(renderer, white, NULL, &rct);
}

void draw_bg()
{
	SDL_RenderCopy(renderer, bg, NULL, NULL);
}

void add_score(int val)
{
	score += val;
	draw_score();
}

void draw_score()
{
	const int x = X_OFFSET + WIDTH * 20 + 20;
	const int y = Y_OFFSET;
	static SDL_Rect source = {0,0,16,32};
	static SDL_Rect destination = {0,y,16,32};
	const SDL_Rect rct = {x,y,100,34};
	//render_texture(white,renderer,x,y,100,34);
	SDL_RenderCopy(renderer,bg,&rct,&rct);
	SDL_RenderCopy(renderer, white, NULL, &rct);
	int d, s = score, i=0;
	do
	{
		d = s % 10;
		s = s / 10;
		source.x = d*16;
		destination.x = x + (5-i)*16;
		SDL_RenderCopy(renderer,digits,&source,&destination);
		i++;
	} while(s!=0);
}
void draw_endgame()
{
	int w,h;
	SDL_QueryTexture(end,NULL,NULL,&w,&h);
	render_texture(end,renderer,(SCREEN_WIDTH-w)/2,(SCREEN_HEIGHT-h)/2);
	SDL_RenderPresent(renderer);
}

void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,int width,int height)
{
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void render_texture(SDL_Texture *tex, SDL_Renderer *ren)
{
	SDL_RenderCopy(ren, tex, NULL, NULL);
}