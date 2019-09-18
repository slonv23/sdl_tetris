#include <SDL.h>

#include "block_types.h"
#include "global_definitions.h"
#include "func.h"
#include "draw.h"

extern int score;
extern int map[HEIGHT][WIDTH]; // 1 - звездочка, 0 - пусто
extern int pull[HEIGHT];
extern unsigned int speed;
extern unsigned int add_speed;

extern block* Block;

//---------------------------block type long---------------------------//
block_typeLong::block_typeLong(int x, int y, UINT8 _turn_num)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY][upperX+1]==0&&map[upperY][upperX+2]==0&&map[upperY][upperX+3]==0)
	{
		map[upperY][upperX]=1;
		map[upperY][upperX+1]=1;
		map[upperY][upperX+2]=1;
		map[upperY][upperX+3]=1;
		turn_num = _turn_num;
		draw_map();
	}
	else endgame();
}

void block_typeLong::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=HEIGHT-1)&&(map[upperY+1][upperX]==0)&&(map[upperY+1][upperX + 1]==0)&&(map[upperY+1][upperX + 2]==0)&&(map[upperY+1][upperX + 3]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY][upperX + 1]=0;
			map[upperY][upperX + 2]=0;
			map[upperY][upperX + 3]=0;
			map[upperY+1][upperX]=1;
			map[upperY+1][upperX + 1]=1;
			map[upperY+1][upperX + 2]=1;
			map[upperY+1][upperX + 3]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]+=4;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}


void block_typeLong::moveR()
{
	if(upperX != WIDTH - 4)
	{
		if(map[upperY][upperX + 4]==0)
		{
			map[upperY][upperX]=0;
			map[upperY][upperX + 4]=1;
			draw_map();
			upperX++;
		}
	}
}
void block_typeLong::moveL()
{
	if(upperX)
	{
		if(map[upperY][upperX - 1]==0)
		{
			map[upperY][upperX - 1]=1;
			map[upperY][upperX + 3]=0;
			draw_map();
			upperX--;
		}
	}
}

void block_typeLong::turn()
{
	int y = upperY - 1;
	int x = upperX + 1 + turn_num;
	if(y+3<HEIGHT&&map[y][x]==0&&map[y+2][x]==0&&map[y+3][x]==0)
	{
		map[upperY][upperX] = 0;
		map[upperY][upperX+1] = 0;
		map[upperY][upperX+2] = 0;
		map[upperY][upperX+3] = 0;
		map[y][x] = 1;
		map[y+1][x] = 1;
		map[y+2][x] = 1;
		map[y+3][x] = 1;
		delete Block;
		Block = new block_typeVertical(x,y,turn_num,time);
		draw_map();
	}
}
//---------------------------block type vertical---------------------------//

block_typeVertical::block_typeVertical(int x, int y, UINT8 _turn_num)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY+1][upperX]==0&&map[upperY+2][upperX]==0&&map[upperY+3][upperX]==0)
	{
		map[upperY][upperX]=1;
		map[upperY+1][upperX]=1;
		map[upperY+2][upperX]=1;
		map[upperY+3][upperX]=1;
		turn_num = _turn_num;
		draw_map();
	}
	else endgame();
}

void block_typeVertical::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=HEIGHT-4)&&(map[upperY+4][upperX]==0))
		{
			map[upperY][upperX]=0;
			map[upperY+4][upperX]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]++;
			pull[upperY+1]++;
			pull[upperY+2]++;
			pull[upperY+3]++;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeVertical::moveLR(int newX)
{
	if((map[upperY][newX]==0)&&(map[upperY+1][newX]==0)&&(map[upperY+2][newX]==0)&&(map[upperY+3][newX]==0))
	{
		map[upperY][upperX]=0;
		map[upperY+1][upperX]=0;
		map[upperY+2][upperX]=0;
		map[upperY+3][upperX]=0;
		map[upperY][newX]=1;
		map[upperY+1][newX]=1;
		map[upperY+2][newX]=1;
		map[upperY+3][newX]=1;
		draw_map();
		upperX = newX;
	}
}

void block_typeVertical::moveR()
{
	if(upperX != WIDTH-1)
	{
		moveLR(upperX + 1);
	}
}

void block_typeVertical::moveL()
{
	if(upperX)
	{
		moveLR(upperX-1);
	}
}

void block_typeVertical::turn()
{
	int y = upperY + 1;
	int x = upperX - (2 - turn_num);
	if(x>=0&&x+3<WIDTH&&map[y][x]==0&&map[y][x+1+turn_num]==0&&map[y][x+3]==0)
	{
		map[upperY][upperX] = 0;
		map[upperY+1][upperX] = 0;
		map[upperY+2][upperX] = 0;
		map[upperY+3][upperX] = 0;
		map[y][x] = 1;
		map[y][x+1] = 1;
		map[y][x+2] = 1;
		map[y][x+3] = 1;
		delete Block;
		Block = new block_typeLong(x,y,turn_num,time);
		draw_map();
	}
}

//---------------------------block type z---------------------------//
block_typeZ::block_typeZ(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY][upperX+1]==0&&map[upperY+1][upperX+1]==0&&map[upperY+1][upperX+2]==0)
	{
		map[upperY][upperX]=1;
		map[upperY][upperX+1]=1;
		map[upperY+1][upperX+1]=1;
		map[upperY+1][upperX+2]=1;
		draw_map();
	}
	else endgame();
}

void block_typeZ::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=HEIGHT-2)&&(map[upperY+1][upperX]==0)&&(map[upperY+2][upperX+1]==0)&&(map[upperY+2][upperX+2]==0))
		{
			map[upperY][upperX]=0;
			map[upperY][upperX+1]=0;
			map[upperY+1][upperX+2]=0;
			map[upperY+1][upperX]=1;
			map[upperY+2][upperX+1]=1;
			map[upperY+2][upperX+2]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]+=2;
			pull[upperY+1]+=2;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeZ::moveR()
{
	if(upperX != WIDTH-3)
	{
		if(map[upperY][upperX+2]==0&&map[upperY+1][upperX+3]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX+1]=0;
			map[upperY][upperX+2]=1;
			map[upperY+1][upperX+3]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeZ::moveL()
{
	if(upperX)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX]==0)
		{
			map[upperY][upperX+1]=0;
			map[upperY+1][upperX+2]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeZ::turn()
{
	int y = upperY;
	int x = upperX + 1;
	if(y!=(HEIGHT - 2)&&map[y+1][x-1]==0&&map[y+2][x-1]==0)
	{
		map[upperY][upperX]=0;
		map[upperY+1][upperX+2]=0;
		map[upperY+1][upperX]=1;
		map[upperY+2][upperX]=1;
		delete Block;
		Block = new block_typeVerticalZ(x,y,time);
		draw_map();
	}
}

//---------------------------block type vertical z---------------------------//
block_typeVerticalZ::block_typeVerticalZ(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY+1][upperX]==0&&map[upperY+1][upperX-1]==0&&map[upperY+2][upperX-1]==0)
	{
		map[upperY][upperX]=1;
		map[upperY+1][upperX]=1;
		map[upperY+1][upperX-1]=1;
		map[upperY+2][upperX-1]=1;
		draw_map();
	}
	else endgame();
}

void block_typeVerticalZ::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=HEIGHT-3)&&(map[upperY+2][upperX]==0)&&(map[upperY+3][upperX-1]==0))
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX-1]=0;
			map[upperY+2][upperX]=1;
			map[upperY+3][upperX-1]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]++;
			pull[upperY+1]+=2;
			pull[upperY+2]++;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeVerticalZ::moveR()
{
	if(upperX != WIDTH-1)
	{
		if(map[upperY][upperX+1]==0&&map[upperY+1][upperX+1]==0&&map[upperY+2][upperX]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX-1]=0;
			map[upperY+2][upperX-1]=0;
			map[upperY][upperX+1]=1;
			map[upperY+1][upperX+1]=1;
			map[upperY+2][upperX]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeVerticalZ::moveL()
{
	if(upperX!=1)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX-2]==0&&map[upperY+2][upperX-2]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX]=0;
			map[upperY+2][upperX-1]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX-2]=1;
			map[upperY+2][upperX-2]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeVerticalZ::turn()
{
	int y = upperY;
	int x = upperX - 1;
	if(upperX!=(WIDTH - 1)&&map[y][x]==0&&map[y+1][x+2]==0)
	{
		map[upperY+1][upperX-1]=0;
		map[upperY+2][upperX-1]=0;
		map[upperY][upperX-1]=1;
		map[upperY+1][upperX+1]=1;
		delete Block;
		Block = new block_typeZ(x,y,time);
		draw_map();
	}
}

//---------------------------block type verse z---------------------------//
block_typeVerseZ::block_typeVerseZ(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY][upperX+1]==0&&map[upperY+1][upperX]==0&&map[upperY+1][upperX-1]==0)
	{
		map[upperY][upperX]=1;
		map[upperY][upperX+1]=1;
		map[upperY+1][upperX]=1;
		map[upperY+1][upperX-1]=1;
		draw_map();
	}
	else endgame();
}

void block_typeVerseZ::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=HEIGHT-2)&&(map[upperY+1][upperX+1]==0)&&(map[upperY+2][upperX]==0)&&(map[upperY+2][upperX-1]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY][upperX+1]=0;
			map[upperY+1][upperX-1]=0;
			map[upperY+1][upperX+1]=1;
			map[upperY+2][upperX]=1;
			map[upperY+2][upperX-1]=1;
			upperY++;
			draw_map();
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]+=2;
			pull[upperY+1]+=2;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeVerseZ::moveR()
{
	if(upperX != WIDTH-2)
	{
		if(map[upperY][upperX+2]==0&&map[upperY+1][upperX+1]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX-1]=0;
			map[upperY][upperX+2]=1;
			map[upperY+1][upperX+1]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeVerseZ::moveL()
{
	if(upperX != 1)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX-2]==0)
		{
			map[upperY][upperX+1]=0;
			map[upperY+1][upperX]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX-2]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeVerseZ::turn()
{
	int y = upperY;
	int x = upperX - 1;
	if(y!=(HEIGHT - 2)&&map[y+2][x+1]==0&&map[y][x]==0)
	{
		map[y][x+1]=0;
		map[y][x+2]=0;
		map[y][x]=1;
		map[y+2][x+1]=1;
		delete Block;
		Block = new block_typeVerticalVerseZ(x,y,time);
		draw_map();
	}
}

//---------------------------block type vertical verse z---------------------------//
block_typeVerticalVerseZ::block_typeVerticalVerseZ(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY+1][upperX]==0&&map[upperY+1][upperX+1]==0&&map[upperY+2][upperX+1]==0)
	{
		map[upperY][upperX]=1;
		map[upperY+1][upperX]=1;
		map[upperY+1][upperX+1]=1;
		map[upperY+2][upperX+1]=1;
		draw_map();
	}
	else endgame();
}

void block_typeVerticalVerseZ::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=HEIGHT-3)&&(map[upperY+2][upperX]==0)&&(map[upperY+3][upperX+1]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX+1]=0;
			map[upperY+2][upperX]=1;
			map[upperY+3][upperX+1]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]++;
			pull[upperY+1]+=2;
			pull[upperY+2]++;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeVerticalVerseZ::moveR()
{
	if(upperX != WIDTH-2)
	{
		if(map[upperY][upperX+1]==0&&map[upperY+1][upperX+2]==0&&map[upperY+2][upperX+2]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX]=0;
			map[upperY+2][upperX+1]=0;
			map[upperY][upperX+1]=1;
			map[upperY+1][upperX+2]=1;
			map[upperY+2][upperX+2]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeVerticalVerseZ::moveL()
{
	if(upperX)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX-1]==0&&map[upperY+2][upperX]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX+1]=0;
			map[upperY+2][upperX+1]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX-1]=1;
			map[upperY+2][upperX]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeVerticalVerseZ::turn()
{
	int y = upperY;
	int x = upperX + 1;
	if(x!=(WIDTH-1)&&map[y][x]==0&&map[y][x+1]==0)
	{
		map[upperY][upperX]=0;
		map[upperY+2][upperX+1]=0;
		map[upperY][upperX+1]=1;
		map[upperY][upperX+2]=1;
		delete Block;
		Block = new block_typeVerseZ(x,y,time);
		draw_map();
	}
}

//---------------------------block type square---------------------------//
block_typeSquare::block_typeSquare(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY][upperX+1]==0&&map[upperY+1][upperX]==0&&map[upperY+1][upperX+1]==0)
	{
		map[upperY][upperX]=1;
		map[upperY][upperX+1]=1;
		map[upperY+1][upperX]=1;
		map[upperY+1][upperX+1]=1;
		draw_map();
	}
	else endgame();
}

void block_typeSquare::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=HEIGHT-2)&&(map[upperY+2][upperX]==0)&&(map[upperY+2][upperX+1]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY][upperX+1]=0;
			map[upperY+2][upperX]=1;
			map[upperY+2][upperX+1]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]+=2;
			pull[upperY+1]+=2;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeSquare::moveR()
{
	if(upperX != WIDTH-2)
	{
		if(map[upperY][upperX+2]==0&&map[upperY+1][upperX+2]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX]=0;
			map[upperY][upperX+2]=1;
			map[upperY+1][upperX+2]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeSquare::moveL()
{
	if(upperX)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX-1]==0)
		{
			map[upperY][upperX+1]=0;
			map[upperY+1][upperX+1]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX-1]=1;
			draw_map();
			upperX--;
		}
	}
}

//---------------------------block type VerseLItem1---------------------------//
block_typeVerseLItem1::block_typeVerseLItem1(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY+1][upperX]==0&&map[upperY+1][upperX+1]==0&&map[upperY+1][upperX+2]==0)
	{
		map[upperY][upperX]=1;
		map[upperY+1][upperX]=1;
		map[upperY+1][upperX+1]=1;
		map[upperY+1][upperX+2]=1;
		draw_map();
	}
	else endgame();
}

void block_typeVerseLItem1::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=(HEIGHT-2))&&(map[upperY+2][upperX]==0)&&(map[upperY+2][upperX+1]==0)&&(map[upperY+2][upperX+2]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX+1]=0;
			map[upperY+1][upperX+2]=0;
			map[upperY+2][upperX]=1;
			map[upperY+2][upperX+1]=1;
			map[upperY+2][upperX+2]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]++;
			pull[upperY+1]+=3;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeVerseLItem1::moveR()
{
	if(upperX != WIDTH-3)
	{
		if(map[upperY][upperX+1]==0&&map[upperY+1][upperX+3]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX]=0;
			map[upperY][upperX+1]=1;
			map[upperY+1][upperX+3]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeVerseLItem1::moveL()
{
	if(upperX)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX-1]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX+2]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX-1]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeVerseLItem1::turn()
{
	if(upperY!=(HEIGHT-2)&&map[upperY][upperX+1]==0&&map[upperY+2][upperX]==0)
	{
		map[upperY+1][upperX+1]=0;
		map[upperY+1][upperX+2]=0;
		map[upperY+2][upperX]=1;
		map[upperY][upperX+1]=1;
		delete Block;
		Block = new block_typeVerseLItem2(upperX,upperY,time);
		draw_map();
	}
}

//---------------------------block type VerseLItem2---------------------------//
block_typeVerseLItem2::block_typeVerseLItem2(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY][upperX+1]==0&&map[upperY+1][upperX]==0&&map[upperY+2][upperX]==0)
	{
		map[upperY][upperX]=1;
		map[upperY+1][upperX]=1;
		map[upperY+2][upperX]=1;
		map[upperY][upperX+1]=1;
		draw_map();
	}
	else endgame();
}

void block_typeVerseLItem2::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=(HEIGHT-3))&&(map[upperY+3][upperX]==0)&&(map[upperY+1][upperX+1]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY][upperX+1]=0;
			map[upperY+3][upperX]=1;
			map[upperY+1][upperX+1]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]+=2;
			pull[upperY+1]++;
			pull[upperY+2]++;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeVerseLItem2::moveR()
{
	if(upperX != WIDTH-2)
	{
		if(map[upperY][upperX+2]==0&&map[upperY+1][upperX+1]==0&&map[upperY+2][upperX+1]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX]=0;
			map[upperY+2][upperX]=0;
			map[upperY+1][upperX+1]=1;
			map[upperY+2][upperX+1]=1;
			map[upperY][upperX+2]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeVerseLItem2::moveL()
{
	if(upperX)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX-1]==0&&map[upperY+2][upperX-1]==0)
		{
			map[upperY][upperX+1]=0;
			map[upperY+1][upperX]=0;
			map[upperY+2][upperX]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX-1]=1;
			map[upperY+2][upperX-1]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeVerseLItem2::turn()
{
	if(upperX!=(WIDTH-2)&&map[upperY][upperX+2]==0&&map[upperY+1][upperX+2]==0)
	{
		map[upperY+1][upperX]=0;
		map[upperY+2][upperX]=0;
		map[upperY][upperX+2]=1;
		map[upperY+1][upperX+2]=1;
		delete Block;
		Block = new block_typeVerseLItem3(upperX,upperY,time);
		draw_map();
	}
}

//---------------------------block type VerseLItem3---------------------------//
block_typeVerseLItem3::block_typeVerseLItem3(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY][upperX+1]==0&&map[upperY][upperX+2]==0&&map[upperY+1][upperX+2]==0)
	{
		map[upperY][upperX]=1;
		map[upperY][upperX+1]=1;
		map[upperY][upperX+2]=1;
		map[upperY+1][upperX+2]=1;
		draw_map();
	}
	else endgame();
}

void block_typeVerseLItem3::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=(HEIGHT-2))&&(map[upperY+1][upperX]==0)&&(map[upperY+1][upperX+1]==0)&&(map[upperY+2][upperX+2]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY][upperX+1]=0;
			map[upperY][upperX+2]=0;
			map[upperY+1][upperX]=1;
			map[upperY+1][upperX+1]=1;
			map[upperY+2][upperX+2]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]+=3;
			pull[upperY+1]++;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeVerseLItem3::moveR()
{
	if(upperX != WIDTH-3)
	{
		if(map[upperY][upperX+3]==0&&map[upperY+1][upperX+3]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX+2]=0;
			map[upperY][upperX+3]=1;
			map[upperY+1][upperX+3]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeVerseLItem3::moveL()
{
	if(upperX)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX+1]==0)
		{
			map[upperY][upperX+2]=0;
			map[upperY+1][upperX+2]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX+1]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeVerseLItem3::turn()
{
	int y = upperY;
	int x = upperX + 1;
	if(upperY!=(HEIGHT-2)&&map[y+1][x]==0&&map[y+2][x+1]==0&&map[y+2][upperX]==0)
	{
		map[upperY][upperX]=0;
		map[upperY][upperX+2]=0;
		map[upperY+1][upperX+2]=0;
		map[y+1][x]=1;
		map[y+2][x]=1;
		map[y+2][upperX]=1;
		delete Block;
		Block = new block_typeVerseLItem4(x,y,time);
		draw_map();
	}
}

//---------------------------block type VerseLItem4---------------------------//
block_typeVerseLItem4::block_typeVerseLItem4(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY+1][upperX]==0&&map[upperY+2][upperX]==0&&map[upperY+2][upperX-1]==0)
	{
		map[upperY][upperX]=1;
		map[upperY+1][upperX]=1;
		map[upperY+2][upperX]=1;
		map[upperY+2][upperX-1]=1;
		draw_map();
	}
	else endgame();
}

void block_typeVerseLItem4::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=(HEIGHT-3))&&(map[upperY+3][upperX]==0)&&(map[upperY+3][upperX-1]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY+2][upperX-1]=0;
			map[upperY+3][upperX]=1;
			map[upperY+3][upperX-1]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]++;
			pull[upperY+1]++;
			pull[upperY+2]+=2;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeVerseLItem4::moveR()
{
	if(upperX != WIDTH-1)
	{
		if(map[upperY][upperX+1]==0&&map[upperY+1][upperX+1]==0&&map[upperY+2][upperX+1]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX]=0;
			map[upperY+2][upperX-1]=0;
			map[upperY][upperX+1]=1;
			map[upperY+1][upperX+1]=1;
			map[upperY+2][upperX+1]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeVerseLItem4::moveL()
{
	if(upperX!=1)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX-1]==0&&map[upperY+2][upperX-2]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX]=0;
			map[upperY+2][upperX]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX-1]=1;
			map[upperY+2][upperX-2]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeVerseLItem4::turn()
{
	int y = upperY;
	int x = upperX - 1;
	if(upperX!=(WIDTH-1)&&map[upperY+1][upperX+1]==0&&map[upperY+1][upperX-1]==0&&map[upperY][upperX-1]==0)
	{
		map[upperY][upperX]=0;
		map[upperY+2][upperX]=0;
		map[upperY+2][upperX-1]=0;
		map[upperY+1][upperX+1]=1;
		map[upperY+1][upperX-1]=1;
		map[upperY][upperX-1]=1;
		delete Block;
		Block = new block_typeVerseLItem1(x,y,time);
		draw_map();
	}
}

//---------------------------block type LItem1---------------------------//
block_typeLItem1::block_typeLItem1(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY+1][upperX]==0&&map[upperY+1][upperX-1]==0&&map[upperY+1][upperX-2]==0)
	{
		map[upperY][upperX]=1;
		map[upperY+1][upperX]=1;
		map[upperY+1][upperX-1]=1;
		map[upperY+1][upperX-2]=1;
		draw_map();
	}
	else endgame();
}

void block_typeLItem1::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=(HEIGHT-2))&&(map[upperY+2][upperX]==0)&&(map[upperY+2][upperX-1]==0)&&(map[upperY+2][upperX-2]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX-1]=0;
			map[upperY+1][upperX-2]=0;
			map[upperY+2][upperX]=1;
			map[upperY+2][upperX-1]=1;
			map[upperY+2][upperX-2]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]++;
			pull[upperY+1]+=3;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeLItem1::moveR()
{
	if(upperX != WIDTH-1)
	{
		if(map[upperY][upperX+1]==0&&map[upperY+1][upperX+1]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX-2]=0;
			map[upperY][upperX+1]=1;
			map[upperY+1][upperX+1]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeLItem1::moveL()
{
	if(upperX != 2)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX-3]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX-3]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeLItem1::turn()
{
	int y = upperY;
	int x = upperX-2;
	if(upperY!=(HEIGHT-2)&&map[upperY][upperX-2]==0&&map[upperY+2][upperX-2]==0&&map[upperY+2][upperX-1]==0)
	{
		map[upperY][upperX]=0;
		map[upperY+1][upperX]=0;
		map[upperY+1][upperX-1]=0;
		map[upperY][upperX-2]=1;
		map[upperY+2][upperX-2]=1;
		map[upperY+2][upperX-1]=1;
		delete Block;
		Block = new block_typeLItem2(x,y,time);
		draw_map();
	}
}

//---------------------------block type LItem2---------------------------//
block_typeLItem2::block_typeLItem2(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY+1][upperX]==0&&map[upperY+2][upperX]==0&&map[upperY+2][upperX+1]==0)
	{
		map[upperY][upperX]=1;
		map[upperY+1][upperX]=1;
		map[upperY+2][upperX]=1;
		map[upperY+2][upperX+1]=1;
		draw_map();
	}
	else endgame();
}

void block_typeLItem2::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=(HEIGHT-3))&&(map[upperY+3][upperX]==0)&&(map[upperY+3][upperX+1]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY+2][upperX+1]=0;
			map[upperY+3][upperX]=1;
			map[upperY+3][upperX+1]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]++;
			pull[upperY+1]++;
			pull[upperY+2]+=2;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeLItem2::moveR()
{
	if(upperX != WIDTH-2)
	{
		if(map[upperY][upperX+1]==0&&map[upperY+1][upperX+1]==0&&map[upperY+2][upperX+2]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX]=0;
			map[upperY+2][upperX]=0;
			map[upperY][upperX+1]=1;
			map[upperY+1][upperX+1]=1;
			map[upperY+2][upperX+2]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeLItem2::moveL()
{
	if(upperX)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX-1]==0&&map[upperY+2][upperX-1]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX]=0;
			map[upperY+2][upperX+1]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX-1]=1;
			map[upperY+2][upperX-1]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeLItem2::turn()
{
	int y = upperY;
	int x = upperX;
	if(upperX!=(WIDTH-2)&&map[upperY][upperX+1]==0&&map[upperY][upperX+2]==0)
	{
		map[upperY+2][upperX]=0;
		map[upperY+2][upperX+1]=0;
		map[upperY][upperX+1]=1;
		map[upperY][upperX+2]=1;
		delete Block;
		Block = new block_typeLItem3(x,y,time);
		draw_map();
	}
}

//---------------------------block type LItem3---------------------------//
block_typeLItem3::block_typeLItem3(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY][upperX+1]==0&&map[upperY][upperX+2]==0&&map[upperY+1][upperX]==0)
	{
		map[upperY][upperX]=1;
		map[upperY][upperX+1]=1;
		map[upperY][upperX+2]=1;
		map[upperY+1][upperX]=1;
		draw_map();
	}
	else endgame();
}

void block_typeLItem3::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=(HEIGHT-2))&&(map[upperY+2][upperX]==0)&&(map[upperY+1][upperX+1]==0)&&(map[upperY+1][upperX+2]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY][upperX+1]=0;
			map[upperY][upperX+2]=0;
			map[upperY+1][upperX+1]=1;
			map[upperY+1][upperX+2]=1;
			map[upperY+2][upperX]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]+=3;
			pull[upperY+1]++;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeLItem3::moveR()
{
	if(upperX != WIDTH-3)
	{
		if(map[upperY][upperX+3]==0&&map[upperY+1][upperX+1]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX]=0;
			map[upperY][upperX+3]=1;
			map[upperY+1][upperX+1]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeLItem3::moveL()
{
	if(upperX)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX-1]==0)
		{
			map[upperY][upperX+2]=0;
			map[upperY+1][upperX]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX-1]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeLItem3::turn()
{
	int y = upperY;
	int x = upperX;
	if(upperY!=(HEIGHT-2)&&map[upperY+1][upperX+1]==0&&map[upperY+2][upperX+1]==0)
	{
		map[upperY+1][upperX]=0;
		map[upperY][upperX+2]=0;
		map[upperY+1][upperX+1]=1;
		map[upperY+2][upperX+1]=1;
		delete Block;
		Block = new block_typeLItem4(upperX,upperY,time);
		draw_map();
	}
}

//---------------------------block type LItem4---------------------------//
block_typeLItem4::block_typeLItem4(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY][upperX+1]==0&&map[upperY+1][upperX+1]==0&&map[upperY+2][upperX+1]==0)
	{
		map[upperY][upperX]=1;
		map[upperY][upperX+1]=1;
		map[upperY+1][upperX+1]=1;
		map[upperY+2][upperX+1]=1;
		draw_map();
	}
	else endgame();
}

void block_typeLItem4::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=(HEIGHT-3))&&(map[upperY+1][upperX]==0)&&(map[upperY+3][upperX+1]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY][upperX+1]=0;
			map[upperY+1][upperX]=1;
			map[upperY+3][upperX+1]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]+=2;
			pull[upperY+1]++;
			pull[upperY+2]++;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeLItem4::moveR()
{
	if(upperX != WIDTH-2)
	{
		if(map[upperY][upperX+2]==0&&map[upperY+1][upperX+2]==0&&map[upperY+2][upperX+2]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX+1]=0;
			map[upperY+2][upperX+1]=0;
			map[upperY][upperX+2]=1;
			map[upperY+1][upperX+2]=1;
			map[upperY+2][upperX+2]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeLItem4::moveL()
{
	if(upperX)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX]==0&&map[upperY+2][upperX]==0)
		{
			map[upperY][upperX+1]=0;
			map[upperY+1][upperX+1]=0;
			map[upperY+2][upperX+1]=0;
			map[upperY+1][upperX]=1;
			map[upperY+2][upperX]=1;
			map[upperY][upperX-1]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeLItem4::turn()
{
	int y = upperY;
	int x = upperX + 2;
	if(upperX!=(WIDTH-2)&&map[upperY][upperX+2]==0&&map[upperY+1][upperX+2]==0&&map[upperY+1][upperX]==0)
	{
		map[upperY][upperX]=0;
		map[upperY][upperX+1]=0;
		map[upperY+2][upperX+1]=0;
		map[upperY][upperX+2]=1;
		map[upperY+1][upperX+2]=1;
		map[upperY+1][upperX]=1;
		delete Block;
		Block = new block_typeLItem1(x,y,time);
		draw_map();
	}
}

//---------------------------block type TriangleItem1---------------------------//
block_typeTriangleItem1::block_typeTriangleItem1(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY+1][upperX-1]==0&&map[upperY+1][upperX]==0&&map[upperY+1][upperX+1]==0)
	{
		map[upperY][upperX]=1;
		map[upperY+1][upperX-1]=1;
		map[upperY+1][upperX]=1;
		map[upperY+1][upperX+1]=1;
		draw_map();
	}
	else endgame();
}

void block_typeTriangleItem1::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=(HEIGHT-2))&&(map[upperY+2][upperX-1]==0)&&(map[upperY+2][upperX]==0)&&(map[upperY+2][upperX+1]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX-1]=0;
			map[upperY+1][upperX+1]=0;
			map[upperY+2][upperX-1]=1;
			map[upperY+2][upperX]=1;
			map[upperY+2][upperX+1]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]++;
			pull[upperY+1]+=3;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeTriangleItem1::moveR()
{
	if(upperX != WIDTH-2)
	{
		if(map[upperY][upperX+1]==0&&map[upperY+1][upperX+2]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX-1]=0;
			map[upperY][upperX+1]=1;
			map[upperY+1][upperX+2]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeTriangleItem1::moveL()
{
	if(upperX!=1)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX-2]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX+1]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX-2]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeTriangleItem1::turn()
{
	int y = upperY;
	int x = upperX-1;
	if(upperY!=(HEIGHT-2)&&map[upperY][upperX-1]==0&&map[upperY+2][upperX-1]==0)
	{
		map[upperY][upperX]=0;
		map[upperY+1][upperX+1]=0;
		map[upperY][upperX-1]=1;
		map[upperY+2][upperX-1]=1;
		delete Block;
		Block = new block_typeTriangleItem2(x,y,time);
		draw_map();
	}
}

//---------------------------block type TriangleItem2---------------------------//
block_typeTriangleItem2::block_typeTriangleItem2(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY+1][upperX+1]==0&&map[upperY+1][upperX]==0&&map[upperY+2][upperX]==0)
	{
		map[upperY][upperX]=1;
		map[upperY+1][upperX+1]=1;
		map[upperY+1][upperX]=1;
		map[upperY+2][upperX]=1;
		draw_map();
	}
	else endgame();
}

void block_typeTriangleItem2::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=(HEIGHT-3))&&(map[upperY+2][upperX+1]==0)&&(map[upperY+3][upperX]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX+1]=0;
			map[upperY+2][upperX+1]=1;
			map[upperY+3][upperX]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]++;
			pull[upperY+1]+=2;
			pull[upperY+2]++;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeTriangleItem2::moveR()
{
	if(upperX != WIDTH-2)
	{
		if(map[upperY][upperX+1]==0&&map[upperY+1][upperX+2]==0&&map[upperY+2][upperX+1]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX]=0;
			map[upperY+2][upperX]=0;
			map[upperY][upperX+1]=1;
			map[upperY+1][upperX+2]=1;
			map[upperY+2][upperX+1]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeTriangleItem2::moveL()
{
	if(upperX)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX-1]==0&&map[upperY+2][upperX-1]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX+1]=0;
			map[upperY+2][upperX]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX-1]=1;
			map[upperY+2][upperX-1]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeTriangleItem2::turn()
{
	if(upperX!=(WIDTH-2)&&map[upperY][upperX+1]==0&&map[upperY][upperX+2]==0)
	{
		map[upperY+1][upperX]=0;
		map[upperY+2][upperX]=0;
		map[upperY][upperX+1]=1;
		map[upperY][upperX+2]=1;
		delete Block;
		Block = new block_typeTriangleItem3(upperX,upperY,time);
		draw_map();
	}
}

//---------------------------block type TriangleItem3---------------------------//
block_typeTriangleItem3::block_typeTriangleItem3(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY+1][upperX+1]==0&&map[upperY][upperX+1]==0&&map[upperY][upperX+2]==0)
	{
		map[upperY][upperX]=1;
		map[upperY+1][upperX+1]=1;
		map[upperY][upperX+1]=1;
		map[upperY][upperX+2]=1;
		draw_map();
	}
	else endgame();
}

void block_typeTriangleItem3::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=(HEIGHT-2))&&(map[upperY+1][upperX]==0)&&(map[upperY+2][upperX+1]==0)&&(map[upperY+1][upperX+2]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY][upperX+1]=0;
			map[upperY][upperX+2]=0;
			map[upperY+1][upperX]=1;
			map[upperY+2][upperX+1]=1;
			map[upperY+1][upperX+2]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]+=3;
			pull[upperY+1]++;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeTriangleItem3::moveR()
{
	if(upperX != WIDTH-3)
	{
		if(map[upperY][upperX+3]==0&&map[upperY+1][upperX+2]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX+1]=0;
			map[upperY][upperX+3]=1;
			map[upperY+1][upperX+2]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeTriangleItem3::moveL()
{
	if(upperX)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX]==0)
		{
			map[upperY][upperX+2]=0;
			map[upperY+1][upperX+1]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeTriangleItem3::turn()
{
	int y = upperY;
	int x = upperX+1;
	if(upperY!=(HEIGHT-2)&&map[upperY+1][upperX]==0&&map[upperY+2][upperX+1]==0)
	{
		map[upperY][upperX]=0;
		map[upperY][upperX+2]=0;
		map[upperY+1][upperX]=1;
		map[upperY+2][upperX+1]=1;
		delete Block;
		Block = new block_typeTriangleItem4(x,y,time);
		draw_map();
	}
}

//---------------------------block type TriangleItem4---------------------------//
block_typeTriangleItem4::block_typeTriangleItem4(int x, int y)
{
	pos(x,y);
	if(map[upperY][upperX]==0&&map[upperY+1][upperX-1]==0&&map[upperY+1][upperX]==0&&map[upperY+2][upperX]==0)
	{
		map[upperY][upperX]=1;
		map[upperY+1][upperX-1]=1;
		map[upperY+1][upperX]=1;
		map[upperY+2][upperX]=1;
		draw_map();
	}
	else endgame();
}

void block_typeTriangleItem4::move()
{
	unsigned int newTime;
	newTime = SDL_GetTicks();
	if((newTime - time )>=speed)
	{
		if((upperY!=(HEIGHT-3))&&(map[upperY+2][upperX-1]==0)&&(map[upperY+3][upperX]==0)) // <
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX-1]=0;
			map[upperY+2][upperX-1]=1;
			map[upperY+3][upperX]=1;
			draw_map();
			upperY++;
			time  = time + speed;
		}
		else
		{
			add_score((START_SPEED*2-(speed+add_speed))/30);
			pull[upperY]++;
			pull[upperY+1]+=2;
			pull[upperY+2]++;
			full_line();
			delete Block;
			Block = generator();
		}
	}
}

void block_typeTriangleItem4::moveR()
{
	if(upperX != WIDTH-1)
	{
		if(map[upperY][upperX+1]==0&&map[upperY+1][upperX+1]==0&&map[upperY+2][upperX+1]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX-1]=0;
			map[upperY+2][upperX]=0;
			map[upperY][upperX+1]=1;
			map[upperY+1][upperX+1]=1;
			map[upperY+2][upperX+1]=1;
			draw_map();
			upperX++;
		}
	}
}

void block_typeTriangleItem4::moveL()
{
	if(upperX!=1)
	{
		if(map[upperY][upperX-1]==0&&map[upperY+1][upperX-2]==0&&map[upperY+2][upperX-1]==0)
		{
			map[upperY][upperX]=0;
			map[upperY+1][upperX]=0;
			map[upperY+2][upperX]=0;
			map[upperY][upperX-1]=1;
			map[upperY+1][upperX-2]=1;
			map[upperY+2][upperX-1]=1;
			draw_map();
			upperX--;
		}
	}
}

void block_typeTriangleItem4::turn()
{
	int y = upperY;
	int x = upperX;
	if(upperX!=(WIDTH-1)&&map[upperY+1][upperX+1]==0)
	{
		map[upperY+2][upperX]=0;
		map[upperY+1][upperX+1]=1;
		delete Block;
		Block = new block_typeTriangleItem1(upperX,upperY,time);
		draw_map();
	}
}
