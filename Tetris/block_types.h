#include <basetsd.h>

class block
{
protected:
	int upperX;
	int upperY;
	unsigned int time;
public:
	block(int _upperX, int _upperY, unsigned int _time) : upperX( _upperX), upperY(_upperY), time(_time) {};
	block() {};
	void pos(int x, int y) { upperX = x; upperY = y; time = SDL_GetTicks(); }
	virtual void move() = 0;
	virtual void moveR() = 0;
	virtual void moveL() = 0;
	virtual void turn() = 0;
};

class block_typeLong : public block
{
private:
	UINT8 turn_num;
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeLong(int x, int y, UINT8 _turn_num = 1);
	block_typeLong(int x, int y,UINT8 _turn_num,unsigned _time):  turn_num(_turn_num), block(x,y,_time) {};
};

class block_typeVertical : public block
{
private:
	UINT8 turn_num;
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	void moveLR(int newX);
	virtual void turn();
	block_typeVertical(int x, int y, UINT8 _turn_num = 0);
	block_typeVertical(int x, int y, UINT8 _turn_num, unsigned _time): turn_num(!_turn_num), block(x,y,_time) {};
};

class block_typeZ : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeZ(int x, int y);
	block_typeZ(int x, int y,unsigned _time): block(x,y,_time) {};
};

class block_typeVerticalZ : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeVerticalZ(int x, int y);
	block_typeVerticalZ(int x, int y,unsigned _time): block(x,y,_time) {};
};



class block_typeVerseZ : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeVerseZ(int x, int y);
	block_typeVerseZ(int x, int y,unsigned _time): block(x,y,_time) {};
};

class block_typeVerticalVerseZ : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeVerticalVerseZ(int x, int y);
	block_typeVerticalVerseZ(int x, int y,unsigned _time): block(x,y,_time) {};
};


class block_typeSquare : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn() {};
	block_typeSquare(int x, int y);
	//block_typeSquare(int x, int y,unsigned _time): block(x,y,_time) {};
};

class block_typeVerseLItem1 : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeVerseLItem1(int x, int y);
	block_typeVerseLItem1(int x, int y,unsigned _time): block(x,y,_time) {};
};

class block_typeVerseLItem2 : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeVerseLItem2(int x, int y);
	block_typeVerseLItem2(int x, int y,unsigned _time): block(x,y,_time) {};
};

class block_typeVerseLItem3 : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeVerseLItem3(int x, int y);
	block_typeVerseLItem3(int x, int y,unsigned _time): block(x,y,_time) {};
};

class block_typeVerseLItem4 : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeVerseLItem4(int x, int y);
	block_typeVerseLItem4(int x, int y,unsigned _time): block(x,y,_time) {};
};

class block_typeLItem1 : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeLItem1(int x, int y);
	block_typeLItem1(int x, int y,unsigned _time): block(x,y,_time) {};
};

class block_typeLItem2 : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeLItem2(int x, int y);
	block_typeLItem2(int x, int y,unsigned _time): block(x,y,_time) {};
};

class block_typeLItem3 : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeLItem3(int x, int y);
	block_typeLItem3(int x, int y,unsigned _time): block(x,y,_time) {};
};

class block_typeLItem4 : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeLItem4(int x, int y);
	block_typeLItem4(int x, int y,unsigned _time): block(x,y,_time) {};
};

class block_typeTriangleItem1 : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeTriangleItem1(int x, int y);
	block_typeTriangleItem1(int x, int y,unsigned _time): block(x,y,_time) {};
};

class block_typeTriangleItem2 : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeTriangleItem2(int x, int y);
	block_typeTriangleItem2(int x, int y,unsigned _time): block(x,y,_time) {};
};

class block_typeTriangleItem3 : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeTriangleItem3(int x, int y);
	block_typeTriangleItem3(int x, int y,unsigned _time): block(x,y,_time) {};
};


class block_typeTriangleItem4 : public block
{
public:
	virtual void move();
	virtual void moveR();
	virtual void moveL();
	virtual void turn();
	block_typeTriangleItem4(int x, int y);
	block_typeTriangleItem4(int x, int y,unsigned _time): block(x,y,_time) {};
};