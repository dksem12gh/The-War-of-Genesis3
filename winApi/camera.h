#pragma once
#include "singletonBase.h"

enum RENDERMETHOD
{
	RENDER,
	FREAMRENDER,
	ANIRENDER,
	ANIALPHARENDER,
	ALPHARENDER,
	ALPHAFRAMERENDER
};

struct renderInfo
{
	string imageName;
	POINT renderPos;
	int imageW;
	int imageH;
	int frameX;
	int frameY;
	animation* ani;
	int standardY;
	int alpha;
	int Zorder;
	RENDERMETHOD renderMethod;
};

class camera : public singletonBase<camera>
{
private:
	POINT _Pos;

	float _CameraPosX;
	float _CameraPosY;

	int _MapSizeX;
	int _MapSizeY;

	vector<renderInfo> _vObjectRenderInfo;
	bool objectRenderClear;

	vector<renderInfo> _vRenderInfo;
	bool renderClear;

	POINT _vibrationPos;
	bool _vibration;

	float _vibrationWorldTimer;
	float _vibrationTimer;
public:
	HRESULT init(void);
	void update(void);
	void release(void);

	POINT getPos() { return PointMake(_CameraPosX + _vibrationPos.x, _CameraPosY + _vibrationPos.y); }
	void setPos(POINT pos) { _Pos = pos; }

	void vibration(void);

	void setMapSize(POINT size) { _MapSizeX = size.x; _MapSizeY = size.y; }

	void increaseX(int val) { _Pos.x += val; }
	void increaseY(int val) { _Pos.y += val; }

	void addObjectRenderInfo(string imageName, POINT renderPos, int imageW, int imageH, int Zorder, RENDERMETHOD renderMethod, int frameX = -1, int frameY = -1, animation* ani = nullptr, int standardY = 0, int alpha = -1);
	vector<renderInfo>* getObjectRenderInfo(int* ZorderCount);

	void addRenderInfo(string imageName, POINT renderPos, int imageW, int imageH, int Zorder, RENDERMETHOD renderMethod, int frameX = -1, int frameY = -1, animation* ani = nullptr, int standardY = 0, int alpha = -1);
	vector<renderInfo>* getRenderInfo(int* ZorderCount);

	camera() {}
	~camera() {}
};

