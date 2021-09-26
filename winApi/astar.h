#pragma once
#include "singletonBase.h"

struct TILESTATE
{
	int x;
	int y;
	int state;
};

enum DIRECTION
{
	Left,
	Right,
	Front,
	Back
};

enum Vector
{
	Ypos,
	Ypos01,
	Ypos02,
	Up,
	Down
};


struct Heap
{
	int x, y, v, g;
};

struct moveHeap
{
	int x, y, v, g, f;
	std::vector<DIRECTION> moveDirection;
};

class astar : public singletonBase <astar>
{
public:
	astar();
	~astar();

	vector<TILESTATE> moveTileSearch(int** arr, int move, vector<TILESTATE> vAttack);
	vector<DIRECTION> moveTile(int** arr, int x, int y, int move);

	vector<DIRECTION> moveTile2(int** arr, int x, int y, int move);

	vector<DIRECTION> enemyMove(int** arr, int tileX, int tileY, int x, int y); //찾아야하는 곳 9로 넘겨줄것
};

