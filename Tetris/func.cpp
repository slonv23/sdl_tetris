#include <SDL.h>
#include <random>
#include <ctime>

#include "block_types.h"
#include "global_definitions.h"
#include "draw.h"

extern SDL_Renderer *renderer;
extern SDL_Texture *cube;
extern SDL_Texture *white;
extern SDL_Texture *bg;

extern bool quit;
extern bool lose;
extern unsigned int speed;
extern unsigned int add_speed;
extern int score;
extern int pull[HEIGHT];
extern int map[HEIGHT][WIDTH];		// 1 - звездочка, 0 - пусто

extern block* Block;

unsigned int random(unsigned int range)
{
	static std::mt19937 gen(time(0));
	std::uniform_int_distribution<int> uid(0, range);
	return uid(gen);
}

block* generator()
{
	int rv = random(18);				// random(<кол-во типов блоков>)
	block *returnBlock = NULL;
	switch(rv)
	{
	case 0:
		returnBlock = new block_typeLong(random(WIDTH-4),0);
		break;
	case 1:
		returnBlock = new block_typeVertical(random(WIDTH-1),0);
		break;
	case 2:
		returnBlock = new block_typeZ(random(WIDTH-3),0);
		break;
	case 3:
		returnBlock = new block_typeVerticalZ(random(WIDTH-2)+1,0);
		break;
	case 4:
		returnBlock = new block_typeVerseZ(random(WIDTH-3)+1,0);
		break;
	case 5:
		returnBlock = new block_typeVerticalVerseZ(random(WIDTH-2),0);
		break;
	case 6:
		returnBlock = new block_typeSquare(random(WIDTH-2),0);
		break;
	case 7:
		returnBlock = new block_typeVerseLItem1(random(WIDTH-3),0);
		break;
	case 8:
		returnBlock = new block_typeVerseLItem2(random(WIDTH-2),0);
		break;
	case 9:
		returnBlock = new block_typeVerseLItem3(random(WIDTH-3),0);
		break;
	case 10:
		returnBlock = new block_typeVerseLItem4(random(WIDTH-2)+1,0);
		break;
	case 11:
		returnBlock = new block_typeLItem1(random(WIDTH-3)+2,0);
		break;
	case 12:
		returnBlock = new block_typeLItem2(random(WIDTH-2),0);
		break;
	case 13:
		returnBlock = new block_typeLItem3(random(WIDTH-3),0);
		break;
	case 14:
		returnBlock = new block_typeLItem4(random(WIDTH-2),0);
		break;
	case 15:
		returnBlock = new block_typeTriangleItem1(random(WIDTH-3)+1,0);
		break;
	case 16:
		returnBlock = new block_typeTriangleItem2(random(WIDTH-2),0);
		break;
	case 17:
		returnBlock = new block_typeTriangleItem3(random(WIDTH-3),0);
		break;
	case 18:
		returnBlock = new block_typeTriangleItem4(random(WIDTH-2)+1,0);
		break;
	}
	return returnBlock;
}


void delete_line(int line)
{
	for(int i=0;i<WIDTH;i++)
	{
		map[line][i] = 0;
		pull[line] = 0;
	}
	for(int i=line-1;i>=0;i--)
	{
		for(int j=0;j<WIDTH;j++)
		{
			if(map[i][j]==1)
			{
				pull[i+1]++;
				pull[i]--;
				map[i+1][j]=1;
				map[i][j]=0;
			}
		}
	}
	draw_map();
}

bool full_line()
{
	for(int i=0; i<HEIGHT; i++)
	{
		if(pull[i]==WIDTH)
		{
			add_score((START_SPEED*2-(speed+add_speed))/3); //100
			speed -=10;
			delete_line(i);
		}
	}
	return 0;
}

void endgame()
{
	quit = true;
	lose = true;
	draw_endgame();
}