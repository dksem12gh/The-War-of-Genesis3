#pragma once
#include "gameNode.h"

class battleMap;
class battleCharManager;
class battleChar;

class battleScene : public gameNode
{
private:
	int _curMapNum;
	battleMap* _battleMap;
	battleCharManager* _battleCharManager;

	battleChar* _selectChar;
	battleChar* _targetChar;

	int _selectCharCount;
	int _friendlyTrunCount;
	int _tileCount;

	bool _UIActive;
	bool _CharUI;
	bool _abilityUI;
	bool _itemUI;
	bool _stateUI;
	bool _userTurn;
	bool _userAttack;
	bool _move;

	int _mouseTileFrameX;
	int _tileCrossFrameX;

	POINT _cameraPt;

	POINT _mouseTile;
	int _mouseTileState;
	POINT _charPos;

	bool _charOver;
	bool _tileCross;

	bool _gamePlay;
	bool _gameClear;
	int _gameEndAlpha;

	float _worldSceneChangeTimer;
	float _sceneChangeTimer;

	HFONT _hFont;
	HFONT _hOldFont;
	HFONT _hBigFont;
	HFONT _hOldBigFont;
	HFONT _hMiddleFont;
	HFONT _hOldMiddleFont;

	bool _sceneChange;
	
public:
	HRESULT init(SCENEINFO sceneInfo);
	void release(void);
	void update(void);
	void render(void);

	SCENEINFO getSceneInfo();

	battleScene();
	~battleScene() {}
};

