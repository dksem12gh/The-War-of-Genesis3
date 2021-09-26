#pragma once
#include "gameNode.h"

struct BUTTON
{
	string imgName;
	string buttonTxt;
	HFONT hFont;
	RECT rc;
	bool click;
	bool over;
	int frameX;
};

struct SHOPITEM
{
	ITEM item;
	int count;
	BUTTON button[2];
	BUTTON buysellButton;
};

class shopScene : public gameNode
{
private:
	string _backName;
	int _curMapNum;

	vector<BUTTON> _vButton;

	HFONT _hFont;
	HFONT _hOldFont;

	vector<SHOPITEM> _buyItem;
	vector<SHOPITEM> _sellItem;

	int _playerGold;

	float _worldCountTimer;
	float _countTimer;
public:
	HRESULT init(SCENEINFO sceneInfo);
	void release(void);
	void update(void);
	void render(void);

	void settingSellItem();

	SCENEINFO getSceneInfo();

	shopScene() {}
	~shopScene() {}
};

