#include "global_definitions.h"

bool quit;
bool lose = false;
int score = 0;
int map[HEIGHT][WIDTH] = {0};	// 1 - звездочка, 0 - пусто
int pull[HEIGHT] = {0};
unsigned int speed = START_SPEED;		// задержка в милисекундах
unsigned int add_speed;
block* Block;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *bg;
SDL_Texture *white;
SDL_Texture *cube;
SDL_Texture *digits;
SDL_Texture *end;
TTF_Font *gFont;