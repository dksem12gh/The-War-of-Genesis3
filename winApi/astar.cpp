#include "stdafx.h"
#include "astar.h"

astar::astar()
{
}


astar::~astar()
{
}

vector<TILESTATE> astar::moveTileSearch(int** arr, int move, vector<TILESTATE> vAttack)
{
	vector<TILESTATE> returnVector;
	Heap startHeap[1000];
	Heap moveTileHeap[1000];
	Heap endHeap[1000];

	int startCount = 1;
	int moveCount = 0;
	int endCount = 0;

	arr[move + 3][move + 3] = 3;
	startHeap[0].x = move + 3;
	startHeap[0].y = move + 3;
	startHeap[0].v = 0;
	startHeap[0].g = 0;

	while (true)
	{
		for (int i = 0; i < startCount; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int leftright;
				int frontback;
				switch (j)
				{
				case 0:
					leftright = -1;
					frontback = 0;
					break;
				case 1:
					leftright = 1;
					frontback = 0;
					break;
				case 2:
					leftright = 0;
					frontback = -1;
					break;
				case 3:
					leftright = 0;
					frontback = 1;
					break;
				}
				Heap tempHeap;
				if (arr[startHeap[i].y + frontback][startHeap[i].x + leftright] == 0) //left
				{
					tempHeap.x = startHeap[i].x + leftright;
					tempHeap.y = startHeap[i].y + frontback;
					tempHeap.v = startHeap[i].v + 1;
					tempHeap.g = 0;

					moveTileHeap[moveCount++] = tempHeap;
					endHeap[endCount++] = tempHeap;
					arr[startHeap[i].y + frontback][startHeap[i].x + leftright] = 2;
				}
			}
		}

		if (endHeap[0].v >= move || endCount == 0)
		{
			break;
		}

		for (int i = 0; i < endCount; i++)
		{
			startHeap[i] = endHeap[i];
		}
		startCount = endCount;
		endCount = 0;
	}

	for (int i = 0; i < ((move + 3) * 2) + 1; i++)
	{
		for (int j = 0; j < ((move + 3) * 2) + 1; j++)
		{
			switch (arr[i][j])
			{
			case 0:
				printf(" ");
				break;
			case 1:
				printf("#");
				break;
			case 2:
				printf("*");
				break;
			case 3:
				printf("P");
				break;
			case 10:
				printf("-");
				break;
			}
		}
		printf("\n");
	}

	TILESTATE pt;
	pt.x = 0;
	pt.y = 0;
	pt.state = 1;
	returnVector.push_back(pt);

	for (int i = 0; i < moveCount; i++)
	{
		pt.x = moveTileHeap[i].x - (move + 3);
		pt.y = moveTileHeap[i].y - (move + 3);
		pt.state = 0;
		returnVector.push_back(pt);
	}

	int attackCount = returnVector.size();

	for (int i = 0; i < attackCount; i++)
	{
		for (int j = 0; j < vAttack.size(); j++)
		{
			if ((move + 3) + returnVector[i].x + vAttack[j].x > 0 && (move + 3) + returnVector[i].y + vAttack[j].y > 0
				&& (move + 3) + returnVector[i].x + vAttack[j].x < ((move + 3) * 2) + 1 && (move + 3) + returnVector[i].y + vAttack[j].y < ((move + 3) * 2) + 1
				&& arr[(move + 3) + returnVector[i].y + vAttack[j].y][(move + 3) + returnVector[i].x + vAttack[j].x] != 1
				&& arr[(move + 3) + returnVector[i].y + vAttack[j].y][(move + 3) + returnVector[i].x + vAttack[j].x] != 2)
			{
				pt.x = returnVector[i].x + vAttack[j].x;
				pt.y = returnVector[i].y + vAttack[j].y;
				pt.state = 1;
				arr[(move + 3) + returnVector[i].y + vAttack[j].y][(move + 3) + returnVector[i].x + vAttack[j].x] = 2;
				returnVector.push_back(pt);
			}
		}
	}

	return returnVector;
}

///////////////////////////////////////////////////////
vector<DIRECTION> astar::moveTile(int** arr, int x, int y, int move)
{
	int x1 = move + 1, y1 = move + 1;
	int movearr = ((move + 1) * 2) + 1;
	x = move + x + 1;
	y = move + y + 1;

	moveHeap* endPoint = nullptr;

	moveHeap startHeap[2000];
	moveHeap moveTileHeap[2000];
	moveHeap endHeap[2000];

	arr[y1][x1] = 0;
	arr[y][x] = 4;
	int startCount = 1;
	int moveCount = 0;
	int endCount = 0;

	startHeap[0].x = x;
	startHeap[0].y = y;
	startHeap[0].v = 0;
	startHeap[0].g = 0;

	while (true)
	{
		for (int i = 0; i < startCount; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int leftright;
				int frontback;
				switch (j)
				{
				case 0:
					leftright = -1;
					frontback = 0;
					break;
				case 1:
					leftright = 1;
					frontback = 0;
					break;
				case 2:
					leftright = 0;
					frontback = -1;
					break;
				case 3:
					leftright = 0;
					frontback = 1;
					break;
				}
				moveHeap tempHeap;
				if (arr[startHeap[i].y + frontback][startHeap[i].x + leftright] == 0) //left
				{
					tempHeap.x = startHeap[i].x + leftright;
					tempHeap.y = startHeap[i].y + frontback;
					tempHeap.v = startHeap[i].v + 1;
					tempHeap.g = 0;
					tempHeap.moveDirection = startHeap[i].moveDirection;
					switch (j)
					{
					case 0:
						tempHeap.moveDirection.push_back(Right);
						break;
					case 1:
						tempHeap.moveDirection.push_back(Left);
						break;
					case 2:
						tempHeap.moveDirection.push_back(Back);
						break;
					case 3:
						tempHeap.moveDirection.push_back(Front);
						break;
					}

					moveTileHeap[moveCount++] = tempHeap;
					endHeap[endCount++] = tempHeap;
					arr[startHeap[i].y + frontback][startHeap[i].x + leftright] = 2;
				}
			}
		}

		for (int i = 0; i < endCount; i++)
		{
			if (endHeap[i].x == x1 && endHeap[i].y == y1)
			{
				endPoint = &endHeap[i];
				break;
			}
		}

		if (endPoint != nullptr) break;

		for (int i = 0; i < endCount; i++)
		{
			startHeap[i] = endHeap[i];
		}

		startCount = endCount;
		endCount = 0;

	}

	arr[move + 1][move + 1] = 3;

	for (int i = 0; i < ((move + 1) * 2) + 1; i++)
	{
		for (int j = 0; j < ((move + 1) * 2) + 1; j++)
		{
			switch (arr[i][j])
			{
			case 0:
				printf(" ");
				break;
			case 1:
				printf("#");
				break;
			case 2:
				printf("*");
				break;
			case 3:
				printf("P");
				break;
			case 4:
				printf("S");
				break;
			}
		}
		printf("\n");
	}

	for (int i = endPoint->moveDirection.size() - 1; i >= 0; i--)
	{
		switch (endPoint->moveDirection[i])
		{
		case Left:
			printf("왼쪽\n");
			break;
		case Right:
			printf("오른쪽\n");
			break;
		case Front:
			printf("앞\n");
			break;
		case Back:
			printf("뒤\n");
			break;
		}
	}
	
	return endPoint->moveDirection;
}

vector<DIRECTION> astar::moveTile2(int ** arr, int x, int y, int move)
{
	int x1 = move + 1, y1 = move + 1;
	int movearr = ((move + 1) * 2) + 1;
	x = move + x + 1;
	y = move + y + 1;

	moveHeap* endPoint = nullptr;

	moveHeap startHeap[2000];
	moveHeap moveTileHeap[2000];
	moveHeap endHeap[2000];

	arr[y1][x1] = 0;
	arr[y][x] = 4;
	int startCount = 1;
	int moveCount = 0;
	int endCount = 0;

	int startIndex;

	startHeap[0].x = x;
	startHeap[0].y = y;
	startHeap[0].v = 0;
	startHeap[0].g = 0;

	int lowFIndex = 0;
	int lowF;

	while (true)
	{
		for (int j = 0; j < 4; j++)
		{
			int leftright;
			int frontback;
			switch (j)
			{
			case 0:
				leftright = -1;
				frontback = 0;
				break;
			case 1:
				leftright = 1;
				frontback = 0;
				break;
			case 2:
				leftright = 0;
				frontback = -1;
				break;
			case 3:
				leftright = 0;
				frontback = 1;
				break;
			}
			moveHeap tempHeap;
			if (arr[startHeap[lowFIndex].y + frontback][startHeap[lowFIndex].x + leftright] == 0) //left
			{
				tempHeap.x = startHeap[lowFIndex].x + leftright;
				tempHeap.y = startHeap[lowFIndex].y + frontback;
				tempHeap.v = startHeap[lowFIndex].v + 1;
				int xg = x1 - tempHeap.x;
				int yg = y1 - tempHeap.y;

				if (xg < 0) xg *= -1;
				if (yg < 0) yg *= -1;

				tempHeap.g = xg + yg;
				tempHeap.f = tempHeap.v + tempHeap.g;
				tempHeap.moveDirection = startHeap[lowFIndex].moveDirection;
				switch (j)
				{
				case 0:
					tempHeap.moveDirection.push_back(Right);
					break;
				case 1:
					tempHeap.moveDirection.push_back(Left);
					break;
				case 2:
					tempHeap.moveDirection.push_back(Back);
					break;
				case 3:
					tempHeap.moveDirection.push_back(Front);
					break;
				}

				moveTileHeap[moveCount++] = tempHeap;
				endHeap[endCount++] = tempHeap;
				arr[startHeap[lowFIndex].y + frontback][startHeap[lowFIndex].x + leftright] = 7;
			}
		}


		for (int i = 0; i < endCount; i++)
		{
			if (endHeap[i].x == x1 && endHeap[i].y == y1)
			{
				endPoint = &endHeap[i];
				break;
			}
		}

		if (endPoint != nullptr) break;

		lowF = 9999;

		for (int i = 0; i < endCount; i++)
		{
			if (endHeap[i].f < lowF)
			{
				lowF = endHeap[i].f;
				lowFIndex = i;
			}
		}

		startHeap[lowFIndex] = endHeap[lowFIndex];
		endHeap[lowFIndex].f = 9999;
		arr[startHeap[lowFIndex].y][startHeap[lowFIndex].x] = 2;
	}

	arr[move + 1][move + 1] = 3;

	for (int i = endPoint->moveDirection.size() - 1; i >= 0; i--)
	{
		switch (endPoint->moveDirection[i])
		{
		case Left:
			x1--;
			break;
		case Right:
			x1++;
			break;
		case Front:
			y1--;
			break;
		case Back:
			y1++;
			break;
		}
		if (arr[y1][x1] != 4) arr[y1][x1] = 0;
	}

	for (int i = 0; i < ((move + 1) * 2) + 1; i++)
	{
		for (int j = 0; j < ((move + 1) * 2) + 1; j++)
		{
			switch (arr[i][j])
			{
			case 0:
				printf(" ");
				break;
			case 1:
				printf("#");
				break;
			case 2:
				printf("*");
				break;
			case 3:
				printf("P");
				break;
			case 4:
				printf("S");
				break;
			case 7:
				printf("+");
				break;
			}
		}
		printf("\n");
	}



	for (int i = endPoint->moveDirection.size() - 1; i >= 0; i--)
	{
		switch (endPoint->moveDirection[i])
		{
		case Left:
			printf("왼쪽\n");
			break;
		case Right:
			printf("오른쪽\n");
			break;
		case Front:
			printf("앞\n");
			break;
		case Back:
			printf("뒤\n");
			break;
		}
	}

	return endPoint->moveDirection;
}

vector<DIRECTION> astar::enemyMove(int ** arr, int tileX, int tileY, int x, int y)
{
	cout << "시작" << endl;
	moveHeap* endPoint = nullptr;

	vector<DIRECTION> tump;

	moveHeap startHeap[2000];
	moveHeap moveTileHeap[2000];
	moveHeap endHeap[2000];

	x += 1;
	y += 1;

	int startCount = 1;
	int moveCount = 0;
	int endCount = 0;

	startHeap[0].x = x;
	startHeap[0].y = y;
	startHeap[0].v = 0;
	startHeap[0].g = 0;

	if (arr[y][x] == 9)
	{
		return tump;
	}

	while (true)
	{
		for (int i = 0; i < startCount; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int leftright;
				int frontback;
				switch (j)
				{
				case 0:
					leftright = -1;
					frontback = 0;
					break;
				case 1:
					leftright = 1;
					frontback = 0;
					break;
				case 2:
					leftright = 0;
					frontback = -1;
					break;
				case 3:
					leftright = 0;
					frontback = 1;
					break;
				}
				moveHeap tempHeap;
				if (arr[startHeap[i].y + frontback][startHeap[i].x + leftright] == 0 || arr[startHeap[i].y + frontback][startHeap[i].x + leftright] == 9) //left
				{
					tempHeap.x = startHeap[i].x + leftright;
					tempHeap.y = startHeap[i].y + frontback;
					tempHeap.v = startHeap[i].v + 1;
					tempHeap.g = 0;
					tempHeap.moveDirection = startHeap[i].moveDirection;
					switch (j)
					{
					case 0:
						tempHeap.moveDirection.push_back(Left);
						break;
					case 1:
						tempHeap.moveDirection.push_back(Right);
						break;
					case 2:
						tempHeap.moveDirection.push_back(Front);
						break;
					case 3:
						tempHeap.moveDirection.push_back(Back);
						break;
					}

					moveTileHeap[moveCount++] = tempHeap;
					endHeap[endCount++] = tempHeap;
					if(arr[startHeap[i].y + frontback][startHeap[i].x + leftright] != 9) arr[startHeap[i].y + frontback][startHeap[i].x + leftright] = 2;
				}
			}
		}

		for (int i = 0; i < endCount; i++)
		{
			if (arr[endHeap[i].y][endHeap[i].x] == 9)
			{
				endPoint = &endHeap[i];
				break;
			}
		}

		if (endPoint != nullptr) break;
		else if (endCount == 0) return tump;

		for (int i = 0; i < endCount; i++)
		{
			startHeap[i] = endHeap[i];
		}

		startCount = endCount;
		endCount = 0;

	}

	arr[y][x] = 4;

	for (int i = 0; i < tileY; i++)
	{
		for (int j = 0; j < tileX; j++)
		{
			switch (arr[i][j])
			{
			case 0:
				printf(" ");
				break;
			case 1:
				printf("#");
				break;
			case 2:
				printf("*");
				break;
			case 9:
				printf("P");
				break;
			case 4:
				printf("S");
				break;
			}
		}
		printf("\n");
	}

	reverse(endPoint->moveDirection.begin(), endPoint->moveDirection.end());

	for (int i = endPoint->moveDirection.size() - 1; i >= 0; i--)
	{
		switch (endPoint->moveDirection[i])
		{
		case Left:
			printf("왼쪽\n");
			break;
		case Right:
			printf("오른쪽\n");
			break;
		case Front:
			printf("앞\n");
			break;
		case Back:
			printf("뒤\n");
			break;
		}
	}

	cout << "끝" << endl;
	return endPoint->moveDirection;
}
