#include "stdafx.h"
#include "battleCharManager.h"
#include "battleMap.h"
#include "battleSaladin.h"
#include "battleGreatSwordKnight.h"
#include "battleIronMask.h"

bool compare(battleChar* left, battleChar* right)
{
	return left->getPos().y < right->getPos().y;
}

HRESULT battleCharManager::init(battleMap* pbMap)
{
	_battleMap = pbMap;
	return S_OK;
}

void battleCharManager::update(bool* move, bool* turn, int* friendlyCount, bool* gamePlay, bool* gameClear)
{
	*move = false;

	bool turnBool = true;

	int friendCount = 0;
	int foeCount = 0;

	for (_miAppearChar = _mAppearChar.begin(); _miAppearChar != _mAppearChar.end(); _miAppearChar++)
	{
		_miAppearChar->second.update();
		if (_miAppearChar->second.getFriendOrFoe())
		{
			friendCount++;
		}
		else
		{
			foeCount++;
		}

		if (*move == false && (_miAppearChar->second.getMove() || _miAppearChar->second.getAttack() || _miAppearChar->second.getDie()))
		{
			*move = true;
		}
		if (_miAppearChar->second.getFriendOrFoe() && *turn)
		{
			if (turnBool) turnBool = _miAppearChar->second.getTrunActivity();
		}
		else if (!_miAppearChar->second.getFriendOrFoe() && !*turn)
		{
			if (turnBool) turnBool = _miAppearChar->second.getTrunActivity();
		}

		if (_miAppearChar->second.getFriendOrFoe() && !_miAppearChar->second.getTrunActivity())
		{
			(*friendlyCount)++;
		}
	}

	if (friendCount == 0 && *gamePlay)
	{
		*gamePlay = false;
		*gameClear = false;
	}
	else if (foeCount == 0 && *gamePlay)
	{
		*gamePlay = false;
		*gameClear = true;
	}

	if (turnBool && !*move)
	{
		*turn = !*turn;
		for (_miAppearChar = _mAppearChar.begin(); _miAppearChar != _mAppearChar.end();)
		{
			if (_miAppearChar->second.getState())
			{
				_miAppearChar->second.resetTurn(*turn);
				_miAppearChar++;
			}
			else
			{
				_miAppearChar = _mAppearChar.erase(_miAppearChar);
			}
		}
	}
}

void battleCharManager::render(void)
{

	if (_sortChar.size() != _mAppearChar.size())
	{
		_sortChar.clear();
		for (_miAppearChar = _mAppearChar.begin(); _miAppearChar != _mAppearChar.end(); _miAppearChar++)
		{
			_sortChar.push_back(&_miAppearChar->second);
		}

	}
	sort(_sortChar.begin(), _sortChar.end(), compare);

	for (int i = 0; i < _sortChar.size(); i++)
	{
		_sortChar[i]->render();
	}
}

void battleCharManager::release(void)
{
	_mibattleChar = _mbattleChar.begin();

	for (; _mibattleChar != _mbattleChar.end();)
	{
		_mibattleChar->second->release();
		SAFE_DELETE(_mibattleChar->second);
		_mibattleChar = _mbattleChar.erase(_mibattleChar);
	}

	_miAppearChar = _mAppearChar.begin();

	for (; _miAppearChar != _mAppearChar.end();)
	{
		_miAppearChar->second.release();
		_miAppearChar = _mAppearChar.erase(_miAppearChar);
	}
}

void battleCharManager::addCharacter(string charName, string imageName, int maxHp, int maxSp, int moveSpeed, int attackDamage, int imageY)
{
	battleChar* btch;

	if (charName == "saladin")
	{
		btch = new battleSaladin;
	}
	else if (charName == "greatSwordKnight")
	{
		btch = new battleGreatSwordKnight;
	}
	else if(charName == "ironMask")
	{
		btch = new battleIronMask;
	}

	btch->init(imageName, maxHp, maxSp, moveSpeed, attackDamage, imageY);
	btch->setMap(_battleMap);

	_mbattleChar.insert(make_pair(charName, btch));
}

void battleCharManager::appearCharacter(string charName, int posX, int posY, bool FriendOrFoe)
{
	battleChar btch;

	if (_mbattleChar.find(charName) == _mbattleChar.end()) return;

	_mbattleChar.find(charName)->second->setAni();
	btch = *_mbattleChar.find(charName)->second;

	btch.setPos(PointMake(posX, posY));
	btch.setFriendOrFoe(FriendOrFoe);
	btch.setRect();

	int count = 1;
	char countch[128];
	string countstr;

	char charNamech[128];

	strcpy(charNamech, charName.c_str());

	while (true)
	{
		wsprintf(countch, "%d", count);

		countstr = strcat(charNamech, countch);
		strcpy(charNamech, charName.c_str());

		if (_mAppearChar.find(countstr) == _mAppearChar.end()) break;

		count++;
	}

	_battleMap->setTileMove(PointMake(posX, posY), 1);
	if (FriendOrFoe) _battleMap->setTileOver(PointMake(posX, posY), TILE_FRIENDLY);
	else if (!FriendOrFoe) _battleMap->setTileOver(PointMake(posX, posY), TILE_ENEMY);

	_mAppearChar.insert(make_pair(countstr, btch));
	_mAppearChar.find(countstr)->second.setSkill();
	_mbattleChar.find(charName)->second->clearAni();
	_mbattleChar.find(charName)->second->clearSkill();

	_friendlyCount = 0;
	_enemyCount = 0;

	for (_miAppearChar = _mAppearChar.begin(); _miAppearChar != _mAppearChar.end(); _miAppearChar++) 
	{
		if (_miAppearChar->second.getFriendOrFoe()) _friendlyCount++;
		else _enemyCount++;
	}
}

void battleCharManager::clearAppearCharacter(void)
{
	_miAppearChar = _mAppearChar.begin();

	for (; _miAppearChar != _mAppearChar.end();)
	{
		_miAppearChar->second.release();
		_miAppearChar = _mAppearChar.erase(_miAppearChar);
	}
}

battleChar * battleCharManager::findCharacter(string key)
{
	_mibattleChar = _mbattleChar.find(key);

	if (_mibattleChar == _mbattleChar.end()) return nullptr;

	return _mibattleChar->second;
}

battleChar battleCharManager::findAppearChar(string key)
{
	_miAppearChar = _mAppearChar.find(key);

	if (_miAppearChar == _mAppearChar.end()) return battleChar();

	return _miAppearChar->second;
}

void battleCharManager::CHEATFoeAllDie()
{
	for (_miAppearChar = _mAppearChar.begin(); _miAppearChar != _mAppearChar.end(); _miAppearChar++)
	{
		if (!_miAppearChar->second.getFriendOrFoe())
		{
			_miAppearChar->second.hit(0.5f);
			_miAppearChar->second.increaseHp(-100000);
		}
	}
}
