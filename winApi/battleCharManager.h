#pragma once
#include "battleChar.h"

class battleMap;

class battleCharManager
{
private:
	map<string, battleChar*> _mbattleChar;
	map<string, battleChar*>::iterator _mibattleChar;
	
	map<string, battleChar> _mAppearChar;
	map<string, battleChar>::iterator _miAppearChar;

	battleMap* _battleMap;

	vector<battleChar*> _sortChar;

	int _friendlyCount;
	int _enemyCount;

public:
	HRESULT init(battleMap* pbMap);
	void update(bool* move,bool* turn,int* friendlyCount,bool* gamePlay,bool* gameClear);
	void render(void);
	void release(void);

	void addCharacter(string charName, string imageName, int maxHp, int maxSp, int moveSpeed, int attackDamage, int imageY);
	void appearCharacter(string charName, int posX, int posY, bool FriendOrFoe);
	void clearAppearCharacter(void);

	battleChar* findCharacter(string key);
	battleChar findAppearChar(string key);

	map<string, battleChar>* getAppearChar(void) { return &_mAppearChar; }

	int getFriendlyCount(void) { return _friendlyCount; }
	int getEnemyCount(void) { return _enemyCount; }

	void CHEATFoeAllDie();

	battleCharManager() {}
	~battleCharManager() {}
};

