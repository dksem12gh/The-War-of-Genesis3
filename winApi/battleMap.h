#pragma once

enum OVERTILE
{
	TILE_NONE,
	TILE_FRIENDLY,
	TILE_ENEMY
};

struct tagMapObject
{
	string imageName;
	int sizeX;
	int sizeY;
	POINT pos;
	int Zorder;
	RECT rc;
};

enum OBJECT
{
	OBJ_WOODBOX,
	OBJ_WOODBOX2,
	OBJ_FLOWEPOT,
	OBJ_WOODDRUM,
	OBJ_POLE,
	OBJ_BROKENPOLE,
	OBJ_WOODITEMBOX,
	OBJ_IRONITEMBOX,
	OBJ_NONE
};

struct tagTile
{
	OBJECT obj;
	RECT rc;

	int move; //0 가능 1 불가능
	int Zorder; 
	int overTile;
};

struct tagMap
{
	string mapName;
	string mapUIName;
	int mapObjectCount;
	vector<tagMapObject> vMapObj;
	vector<vector<tagTile>> vvTile;

	int tileSizeX;
	int tileSizeY;
};

class battleMap
{
private:
	char _mapName[128];

	tagMap _curMap;

	bool _alpha;
	int _mapAlpha;

	bool _gameEnd;

	void mapLoad(); // 다른클래스에서 실행하면 안되는 함수
public:
	HRESULT init(char* mapName);
	void render();
	void release();

	tagMap getTagMap() { return _curMap; }

	void setTileMove(POINT pt, int move) { _curMap.vvTile[pt.y][pt.x].move = move; }
	void setTileOver(POINT pt, int over) { _curMap.vvTile[pt.y][pt.x].overTile = over; }
 
	void mapAlphaRender(bool alpha) { _alpha = alpha; }
	void setGameEnd(bool gameEnd) { _gameEnd = gameEnd; }

	battleMap() {}
	~battleMap() {}
};

