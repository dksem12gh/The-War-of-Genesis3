#pragma once
#include "singletonBase.h"

enum ITMEINFO
{
	HPPotion,
	SPPotion,
	//19.08.11 Ãß°¡
	InvisiblePotion,
	DefenceUpPotion,
	AtackUPPotion,
	SpeedUpPotion
};

typedef struct ITEM
{
	int iconNum;
	string name;
	ITMEINFO info;
	int price;
};

struct INVENTORY
{
	ITEM item;
	int count;
};

class player : public singletonBase<player>
{
private:
	int _gold;

	vector<INVENTORY> _inventory;

public:
	HRESULT init();

	void addItem(ITMEINFO iteminfo);
	void addItem(ITMEINFO iteminfo, int count);

	void subItem(ITMEINFO iteminfo);
	void subItem(ITMEINFO iteminfo, int count);
	
	vector<INVENTORY> getInventory() { return _inventory; }

	int getGold() { return _gold; }
	void increaseGold(int val) { _gold += val; }

	player() {}
	~player() {}
};

