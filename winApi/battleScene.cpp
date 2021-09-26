#include "stdafx.h"
#include "battleScene.h"
#include "battleMap.h"
#include "battleCharManager.h"

HRESULT battleScene::init(SCENEINFO sceneInfo)
{
	_battleMap = new battleMap;
	_battleMap->init(sceneInfo.nextMapName);
	_curMapNum = atoi(sceneInfo.nextMapName);

	_battleCharManager = new battleCharManager;
	_battleCharManager->init(_battleMap);
	
	_battleCharManager->addCharacter("saladin", "saladin", 2000, 1000, 8, 300 ,140);
	_battleCharManager->addCharacter("greatSwordKnight", "greatSwordKnight",2300, 1000, 6, 100, 100);
	_battleCharManager->addCharacter("ironMask", "ironMask", 3000, 1000, 7, 4000, 120);

	_mouseTileState = 0;

	switch (_curMapNum)
	{
		case 0007:
			//_battleCharManager->appearCharacter("saladin", 10, 10, true);
			//_battleCharManager->appearCharacter("greatSwordKnight", 10, 11, true);
			_battleCharManager->appearCharacter("ironMask", 4, 6, true);
			CAMERA->setPos(PointMake(4 * 50 - (WINSIZEX / 2), 6 * 50 - (WINSIZEY / 2)));
			_battleCharManager->appearCharacter("saladin", 4, 8, true);
			_battleCharManager->appearCharacter("greatSwordKnight", 31, 20, false);
			_battleCharManager->appearCharacter("greatSwordKnight", 33, 19, false);
			_battleCharManager->appearCharacter("greatSwordKnight", 33, 16, false);
			_battleCharManager->appearCharacter("greatSwordKnight", 30, 16, false);
			_battleCharManager->appearCharacter("greatSwordKnight", 28, 13, false);
			_battleCharManager->appearCharacter("greatSwordKnight", 26, 23, false);
			//_battleCharManager->appearCharacter("greatSwordKnight", 30, 20, false);
			//_battleCharManager->appearCharacter("greatSwordKnight", 30, 22, false);
			break;

		case 172:
			_battleCharManager->appearCharacter("ironMask", 10, 12, true);

			CAMERA->setPos(PointMake(10 * 50 - (WINSIZEX / 2), 12 * 50 - (WINSIZEY / 2)));
			_battleCharManager->appearCharacter("greatSwordKnight", 29, 19, false);
			_battleCharManager->appearCharacter("greatSwordKnight", 29, 22, false);
			_battleCharManager->appearCharacter("greatSwordKnight", 30, 19, false);
			_battleCharManager->appearCharacter("greatSwordKnight", 30, 14, false);
			break;
		case 45:
			_battleCharManager->appearCharacter("ironMask", 15, 32, true);
			CAMERA->setPos(PointMake(15 * 50 - (WINSIZEX / 2), 32 * 50 - (WINSIZEY / 2)));
			_battleCharManager->appearCharacter("greatSwordKnight", 15, 14, false);
			break;
	}

	IMAGEMANAGER->addFrameImage("moveTile", "image\\MoveTile.bmp", 300, 50, 6, 1, true, RGB(252, 252, 252));
	IMAGEMANAGER->addFrameImage("attackTile", "image\\unMoveTile.bmp", 300, 50, 6, 1, true, RGB(254, 254, 254));

	IMAGEMANAGER->addFrameImage("turnarrow", "image\\turnarrow.bmp", 72, 11, 8, 1, true, RGB(80, 120, 116));
	IMAGEMANAGER->addFrameImage("enemyturnarrow", "image\\enemyturnarrow.bmp", 72, 11, 8, 1, true, RGB(80, 120, 116));
	IMAGEMANAGER->addFrameImage("tilecross", "image\\tilecross.bmp", 100, 50, 2, 1, true, RGB(0, 0, 0));

	_UIActive = false;
	_CharUI = false;
	_abilityUI = false;
	_itemUI = false;
	_stateUI = false;
	_selectChar = nullptr;
	_userTurn = true;
	_move = false;

	_gamePlay = true;
	_gameClear = true;
	_gameEndAlpha = 0;
	_sceneChange = false;

	_mouseTileFrameX = 0;
	_tileCrossFrameX = 0;

	_mouseTileState = 0;

	_charOver = false;
	_tileCross = false;
	_userAttack = false;

	_selectCharCount = -1;
	if (_hFont == NULL)
	{
		_hFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "HY견고딕");
		_hBigFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "HY견고딕");
		_hMiddleFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "HY견고딕");
	}
	_worldSceneChangeTimer = 0;
	_sceneChangeTimer = 0;

	return S_OK;
}

void battleScene::release(void)
{
	_battleMap->release();
	SAFE_DELETE(_battleMap);

	_battleCharManager->release();
	SAFE_DELETE(_battleCharManager);

	DeleteObject(_hFont);
	DeleteObject(_hBigFont);
	DeleteObject(_hMiddleFont);
}

void battleScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
	{
		_battleMap->mapAlphaRender(true);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
	{
		_battleMap->mapAlphaRender(false);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3))
	{
		_battleCharManager->CHEATFoeAllDie();
	}

	_friendlyTrunCount = 0;
	_battleCharManager->update(&_move, &_userTurn, &_friendlyTrunCount, &_gamePlay, &_gameClear);
	if (_gamePlay)
	{
		_cameraPt.x = _ptMouse.x + CAMERA->getPos().x;
		_cameraPt.y = _ptMouse.y + CAMERA->getPos().y;

		if (_cameraPt.x < 0) _cameraPt.x = 0;
		if (_cameraPt.y < 0) _cameraPt.y = 0;

		_mouseTileState = 0;

		vector<vector<tagTile>> vvTile = _battleMap->getTagMap().vvTile;

		_tileCross = false;

		if (_userTurn)
		{
			map<string, battleChar>* mAppChar = _battleCharManager->getAppearChar();
			map<string, battleChar>::iterator miAppChar = mAppChar->begin();

			bool click = false;

			int selectCount = 0;

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !_move)
			{
				//UI클릭

				if (_UIActive && _selectChar != nullptr)
				{
					RECT UIRect;
					POINT selPos = _selectChar->getPos();

					selPos.x *= 50;
					selPos.y *= 50;
					selPos.x -= CAMERA->getPos().x;
					selPos.y -= CAMERA->getPos().y;

					if (_CharUI)
					{
						for (int i = 0; i < 4; i++)
						{
							UIRect = RectMake(-130 + ((i % 2) * 200) + selPos.x, -50 + ((i / 2) * 60) + selPos.y, 102, 28);
							if (PtInRect(&UIRect, _ptMouse))
							{
								switch (i)
								{
								case 0:
								{
									_CharUI = false;
									_abilityUI = true;
									click = true;
								}
								break;

								case 1:
								{
									_selectChar->setTrunActivity(true);
									_selectChar = nullptr;
									_UIActive = false;
									click = true;

								}
								break;

								case 2:
								{
									_CharUI = false;
									_itemUI = true;
									click = true;
								}
								break;

								case 3:
								{
									_CharUI = false;
									_stateUI = true;
									click = true;
								}
								}
							}
						}
					}

					if (_abilityUI)
					{
						for (int i = 0; i < _selectChar->getSkillCount(); i++)
						{
							UIRect = RectMake(80 + selPos.x, -40 + selPos.y + (i * 20), 230, 20);
							if (PtInRect(&UIRect, _ptMouse))
							{
								_selectChar->setSelectSkill(true);
								_selectChar->setSkillIndex(i);
								_UIActive = false;
								click = true;
								break;
							}
						}
					}
					else if (_itemUI)
					{
						vector<INVENTORY> inven = PLAYER->getInventory();
						for (int i = 0; i < inven.size(); i++)
						{
							UIRect = RectMake(80 + selPos.x, -40 + selPos.y + (i * 20), 230, 20);
							if (PtInRect(&UIRect, _ptMouse))
							{
								switch (inven[i].item.info)
								{
								case HPPotion:
								{
									_selectChar->increaseHp(1000);
								}
								break;

								case SPPotion:
								{
									_selectChar->increaseSp(1000);
								}
								break;
								}
								PLAYER->subItem(inven[i].item.info);
								_UIActive = false;
								click = true;
								break;
							}
						}
					}
				}

				if (!click)
				{
					//케릭터클릭

					for (miAppChar = mAppChar->begin(); miAppChar != mAppChar->end(); miAppChar++)
					{
						/*if (_userAttack && _selectChar == &miAppChar->second && !miAppChar->second.getTrunActivity() && PtInRect(&miAppChar->second.getRect(), _cameraPt))
						{
							click = true;
							_userAttack = true;
							CAMERA->setPos(PointMake(_selectChar->getPos().x * 50 - WINSIZEX / 2 + 25, _selectChar->getPos().y * 50 - WINSIZEY / 2));
							break;
						}
						else */if (PtInRect(&miAppChar->second.getRect(), _cameraPt) && !miAppChar->second.getTrunActivity() && miAppChar->second.getFriendOrFoe())
						{
							if (_selectChar != &miAppChar->second)
							{
								_selectChar = &miAppChar->second;
								if (!miAppChar->second.getMoveActivity())
								{
									_selectChar->searchMoveTile();
									_tileCount = _selectChar->getMoveTile().size();
									_userAttack = false;
								}
								else
								{
									_userAttack = true;
								}
							}
							else
							{
								if (!_userAttack)
								{
									_userAttack = true;
								}
								else if (_userAttack && !_selectChar->getMoveActivity())
								{
									_userAttack = false;
									_selectChar->searchMoveTile();
									_tileCount = _selectChar->getMoveTile().size();
								}
							}
							CAMERA->setPos(PointMake(_selectChar->getPos().x * 50 - WINSIZEX / 2 + 25, _selectChar->getPos().y * 50 - WINSIZEY / 2));
							_selectCharCount = selectCount;
							click = true;
							break;
						}
					/*else if (!_userAttack && PtInRect(&miAppChar->second.getRect(), _cameraPt) && !miAppChar->second.getMoveActivity() && !miAppChar->second.getFriendOrFoe())
					{
						click = true;
						break;
					}*/
						else
						{
							selectCount++;
						}
					}
				}


				if (!click && !_UIActive)
				{
					//스킬타일 클릭
					if (_selectChar != nullptr && _selectChar->getSelectSkill())
					{
						POINT skillRange = _selectChar->getSkillRange();
						POINT selectCharPos = _selectChar->getPos();
						int tileYSize = _battleMap->getTagMap().tileSizeY;
						int tileXSize = _battleMap->getTagMap().tileSizeX;

						for (int j = -_selectChar->getSkillRange().y / 2; j < (_selectChar->getSkillRange().y / 2) + 1; j++)
						{
							for (int i = -_selectChar->getSkillRange().x / 2; i < (_selectChar->getSkillRange().x / 2) + 1; i++)
							{
								if (0 <= selectCharPos.x + i && selectCharPos.x + i < tileXSize &&
									0 <= selectCharPos.y + j && selectCharPos.y + j < tileYSize &&
									(i != 0 || j != 0) && vvTile[selectCharPos.y + j][selectCharPos.x + i].overTile == TILE_ENEMY)
								{
									for (miAppChar = mAppChar->begin(); miAppChar != mAppChar->end(); ++miAppChar)
									{
										POINT charPos = (*miAppChar).second.getPos();
										if (charPos.x == selectCharPos.x + i && charPos.y == selectCharPos.y + j)
										{
											_selectChar->setSkillTarget(&(*miAppChar).second);
											break;
										}
									}
								}
							}
						}

						if (_selectChar->getSkillTargetCount() != 0)
						{
							_selectChar->playSkill();
							_selectChar = nullptr;
						}

						click = true;
					}
					//이동타일클릭
					else if (_selectChar != nullptr && _selectChar->getMoveTile().size() != 0 && !_userAttack)
					{
						vector<TILESTATE> vMoveTile = _selectChar->getMoveTile();
						POINT selectCharPos = _selectChar->getPos();
						for (int i = 0; i < vMoveTile.size() - 1; i++)
						{
							if (PtInRect(&vvTile[selectCharPos.y + vMoveTile[i].y][selectCharPos.x + vMoveTile[i].x].rc, _cameraPt))
							{
								if (vMoveTile[i].state == 0)
								{
									_selectChar->searchMoveDirection(i);
									click = true;
									break;
								}
								else if (vMoveTile[i].state == 1 && _targetChar != nullptr)
								{
									_selectChar->moveAttack(_targetChar);
									click = true;
									break;
								}
							}
						}
					}
					//공격타일클릭
					else if (_selectChar != nullptr && _targetChar != nullptr && _userAttack)
					{
						vector<TILESTATE> vMoveTile = _selectChar->getAttackTile();
						POINT selectCharPos = _selectChar->getPos();
						for (int i = 0; i < vMoveTile.size(); i++)
						{
							if (PtInRect(&vvTile[selectCharPos.y + vMoveTile[i].y][selectCharPos.x + vMoveTile[i].x].rc, _cameraPt))
							{
								_selectChar->attack(_targetChar);
								_userAttack = false;
								click = true;
								_selectChar = nullptr;
								break;
							}
						}
					}
				}

				//빈곳 클릭

				if (!click)
				{
					selectCount = 0;
					_selectCharCount++;
					if (_selectCharCount >= _friendlyTrunCount)
					{
						_selectCharCount = 0;
					}

					for (miAppChar = mAppChar->begin(); miAppChar != mAppChar->end(); miAppChar++)
					{
						if (!miAppChar->second.getTrunActivity() && miAppChar->second.getFriendOrFoe())
						{
							if (selectCount == _selectCharCount)
							{
								/*_selectChar = &miAppChar->second;
								if (!miAppChar->second.getMoveActivity())
								{
									_selectChar->searchMoveTile();
									_tileCount = _selectChar->getMoveTile().size();
									_userAttack = false;
									CAMERA->setPos(PointMake(_selectChar->getPos().x * 50 - WINSIZEX / 2 + 25, _selectChar->getPos().y * 50 - WINSIZEY / 2));
								}
								else
								{
									click = true;
									_userAttack = true;
									CAMERA->setPos(PointMake(_selectChar->getPos().x * 50 - WINSIZEX / 2 + 25, _selectChar->getPos().y * 50 - WINSIZEY / 2));
								}
								click = true;
								break;*/
								_selectChar = &miAppChar->second;

								if (!miAppChar->second.getMoveActivity())
								{
									_selectChar->searchMoveTile();
									_tileCount = _selectChar->getMoveTile().size();
									_userAttack = false;
								}
								else
								{
									_userAttack = true;
								}
								CAMERA->setPos(PointMake(_selectChar->getPos().x * 50 - WINSIZEX / 2 + 25, _selectChar->getPos().y * 50 - WINSIZEY / 2));
								click = true;
								break;
							}
							else
							{
								selectCount++;
							}
						}
					}
				}
			}

			bool mouseOver = false;
			bool _charOver = false;

			vector<TILESTATE> moveTile;

			if (_selectChar != nullptr && !_userAttack)
			{
				moveTile = _selectChar->getMoveTile();
			}
			else if (_selectChar != nullptr && _userAttack)
			{
				moveTile = _selectChar->getAttackTile();
			}

			_targetChar = nullptr;

			for (miAppChar = mAppChar->begin(); miAppChar != mAppChar->end(); miAppChar++)
			{
				if (PtInRect(&miAppChar->second.getRect(), _cameraPt) && miAppChar->second.getState())
				{
					_targetChar = &miAppChar->second;

					_charPos = _targetChar->getPos();
					_mouseTile.x = vvTile[_charPos.y][_charPos.x].rc.left;
					_mouseTile.y = vvTile[_charPos.y][_charPos.x].rc.top;

					mouseOver = true;
					_charOver = true;

					if (!_userAttack && _selectChar != nullptr && moveTile.size() != 0 && _targetChar->getFriendOrFoe())
					{
						_tileCross = true;
						_mouseTileState = 1;
					}
					else if (!_userAttack && _selectChar != nullptr && moveTile.size() != 0 && !_targetChar->getFriendOrFoe())
					{
						_mouseTileState = 1;
					}
					else if (!_userAttack && !_targetChar->getFriendOrFoe())
					{
						_tileCross = true;
						_mouseTileState = 1;
					}
					else if (_userAttack && !_targetChar->getFriendOrFoe())
					{
						_tileCross = true;
						_mouseTileState = 1;
						for (int i = 0; i < moveTile.size(); i++)
						{
							if (_selectChar->getPos().x + moveTile[i].x == _charPos.x &&
								_selectChar->getPos().y + moveTile[i].y == _charPos.y)
							{
								_tileCross = false;
								break;
							}
						}
					}

					break;
				}
			}

			if (!mouseOver && _userTurn)
			{
				_mouseTile.x = (_cameraPt.x / 50) * 50;//vvTile[_cameraPt.y / 50][_cameraPt.x / 50].rc.left;
				_mouseTile.y = (_cameraPt.y / 50) * 50;//vvTile[_cameraPt.y / 50][_cameraPt.x / 50].rc.top;

				if (_selectChar != nullptr && moveTile.size() != 0 && !_userAttack)
				{
					_tileCross = true;
					_mouseTileState = 1;
					POINT selectCharPos = _selectChar->getPos();
					for (int i = 0; i < moveTile.size() - 1; i++)
					{
						if (PtInRect(&vvTile[selectCharPos.y + moveTile[i].y][selectCharPos.x + moveTile[i].x].rc, _cameraPt))
						{
							if (moveTile[i].state == 0)
							{
								if (_tileCross)
								{
									_tileCross = false;
									_mouseTileState = 0;
								}
							}
							else if (moveTile[i].state == 1 && vvTile[selectCharPos.y + moveTile[i].y][selectCharPos.x + moveTile[i].x].overTile == TILE_ENEMY)
							{
								if (_tileCross)
								{
									_tileCross = false;
									_mouseTileState = 1;
								}
							}
							break;
						}
					}
				}
				else if (_selectChar != nullptr && moveTile.size() != 0 && _userAttack)
				{
					_tileCross = true;
					_mouseTileState = 1;
				}
			}

			if (_selectChar != nullptr && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				//_selectChar->setTrunActivity(true);
				/*_selectChar->playSkill(0);
				_selectChar->setSkillTarget(0, &(_battleCharManager->getAppearChar()->find("greatSwordKnight1")->second));
				_selectChar->setSkillTarget(0, &(_battleCharManager->getAppearChar()->find("greatSwordKnight2")->second));
				_selectChar->setSkillTarget(0, &(_battleCharManager->getAppearChar()->find("greatSwordKnight3")->second));
				_selectChar->setSkillTarget(0, &(_battleCharManager->getAppearChar()->find("greatSwordKnight4")->second));
				_selectChar->setSkillTarget(0, &(_battleCharManager->getAppearChar()->find("greatSwordKnight5")->second));
				_selectChar->setSkillTarget(0, &(_battleCharManager->getAppearChar()->find("greatSwordKnight6")->second));
				_selectChar->setSkillTarget(0, &(_battleCharManager->getAppearChar()->find("greatSwordKnight7")->second));
				_selectChar = nullptr;*/
				//_selectChar->setSelectSkill(true);
				//_selectChar->setSkillIndex(0);
				_UIActive = !_UIActive;
				_CharUI = true;
				_abilityUI = false;
				_itemUI = false;
				_stateUI = false;
				_selectChar->setSelectSkill(false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				/*EFFECTMANAGER->play("ironmaskthruting", 200, 200, 100, 200, 230, 2, 0.04f, -1, -1);
				EFFECTMANAGER->play("ironmaskthruting", 200, 200, 300, 200, 230, 2, 0.04f, -1, -1);
				EFFECTMANAGER->play("ironmaskthruting", 200, 200, 200, 100, 230, 2, 0.04f, -1, -1);
				EFFECTMANAGER->play("ironmaskthruting", 200, 200, 200, 300, 230, 2, 0.04f, -1, -1);*/

				//EFFECTMANAGER->play("lightboom1", _ptMouse.x, _ptMouse.y, 170, 2);

				//EFFECTMANAGER->play("ironmaskswordeffect", 300, 300, 300, -200, 170, 2, 0, 8);

				//EFFECTMANAGER->play("ironmaskswordeffect", _ptMouse.x, _ptMouse.y, 180, 2);
				//EFFECTMANAGER->play("swordbackeffect", _ptMouse.x, _ptMouse.y, 150, 3);

				/*int rnd = RND->getInt(30);

				if (rnd == 0)
				{
					EFFECTMANAGER->play("ghost", RND->getFromIntTo(WINSIZEX / 2 + 100, WINSIZEX) + CAMERA->getPos().x,
						RND->getFromIntTo(-10, -1) + CAMERA->getPos().y,
						RND->getFromIntTo(0, WINSIZEX / 2 - 100) + CAMERA->getPos().x,
						RND->getFromIntTo(WINSIZEY, WINSIZEY + 10) + CAMERA->getPos().y,
						230, 3);
				}
				else if (rnd == 1)
				{
					EFFECTMANAGER->play("ghost", RND->getFromIntTo(WINSIZEX, WINSIZEX + 10) + CAMERA->getPos().x,
						RND->getFromIntTo(0, WINSIZEY / 2 - 100) + CAMERA->getPos().y,
						RND->getFromIntTo(-10,-1) + CAMERA->getPos().x,
						RND->getFromIntTo(WINSIZEY / 2 + 100,WINSIZEY) + CAMERA->getPos().y,
						230, 3);
				}*/

				//EFFECTMANAGER->play("page1boom", _ptMouse.x, _ptMouse.y, _ptMouse.x, -100, 150, 3, 0, 45, 0.08f);

				//EFFECTMANAGER->play("falleffectback", WINSIZEX + CAMERA->getPos().x, -100 + CAMERA->getPos().y, 0 + CAMERA->getPos().x, WINSIZEY + 100 + CAMERA->getPos().y, 180, 3, 0.001f, 24, 17);
				//EFFECTMANAGER->play("dragonhead", WINSIZEX-200  + CAMERA->getPos().x, -300 + CAMERA->getPos().y, -700 + CAMERA->getPos().x, WINSIZEY + CAMERA->getPos().y, 200, 4, 12, 8);

				//EFFECTMANAGER->play("ironmaskassaulteffect", WINSIZEX - 200 + CAMERA->getPos().x, -0 + CAMERA->getPos().y, -700 + CAMERA->getPos().x, WINSIZEY + CAMERA->getPos().y, 200, 4, 12, 8);
				//EFFECTMANAGER->play("ironmaskfalleffect", WINSIZEX - 200 + CAMERA->getPos().x, -50 + CAMERA->getPos().y, -700 + CAMERA->getPos().x, WINSIZEY + CAMERA->getPos().y, 150, 4, 12, 8);
			}
		}
		else
		{
			map<string, battleChar>* mAppChar = _battleCharManager->getAppearChar();
			map<string, battleChar>::iterator miAppChar = mAppChar->begin();

			if (!_move && mAppChar->size() != 0)
			{
				for (miAppChar = mAppChar->begin(); miAppChar != mAppChar->end(); miAppChar++)
				{
					if (!miAppChar->second.getTrunActivity() && miAppChar->second.getMoveActivity() && !miAppChar->second.getFriendOrFoe())
					{
						bool search = false;

						POINT enemyPos = miAppChar->second.getPos();

						map<string, battleChar>::iterator miSearchChar;

						vector<TILESTATE> enemyAttack = miAppChar->second.getAttackTile();

						for (miSearchChar = mAppChar->begin(); miSearchChar != mAppChar->end(); miSearchChar++)
						{
							if (!miSearchChar->second.getFriendOrFoe()) continue;

							POINT charPos = miSearchChar->second.getPos();
							for (int j = 0; j < enemyAttack.size(); j++)
							{
								if (charPos.x == enemyPos.x + enemyAttack[j].x && charPos.y == enemyPos.y + enemyAttack[j].y)
								{
									miAppChar->second.attack(&miSearchChar->second);
									search = true;
									break;
								}
							}

							if (search) break;
						}

						if (search)
						{
							break;
						}
						else
						{
							miAppChar->second.setTrunActivity(true);
							break;
						}
					}
					else if (!miAppChar->second.getMoveActivity() && !miAppChar->second.getFriendOrFoe())
					{
						miAppChar->second.enemyMoveDirection();
						break;
					}
				}
			}
		}
	}
	else
	{
		if (_gameEndAlpha == 0)
		{
			_gameEndAlpha = 1;
			_selectChar = nullptr;
			_targetChar = nullptr;
			_battleMap->setGameEnd(true);
			_battleMap->mapAlphaRender(true);
		}

		if (_gameEndAlpha < 100)
		{
			_gameEndAlpha += 2;
		}

		if (_gameEndAlpha > 100)
		{
			_gameEndAlpha = 100;
			_worldSceneChangeTimer = TIMEMANAGER->getWorldTime();
			_sceneChangeTimer = TIMEMANAGER->getWorldTime();
		}

		if (_gameEndAlpha == 100)
		{
			_worldSceneChangeTimer = TIMEMANAGER->getWorldTime();
			if (_worldSceneChangeTimer - _sceneChangeTimer > 3.0f)
			{
				_battleCharManager->clearAppearCharacter();
				if (_curMapNum == 45)
				{
					PostQuitMessage(0);
				}
				SCENEMANAGER->changeScene("shop");
				_sceneChange = true;
			}
		}
	}
}

void battleScene::render(void)
{
	_battleMap->render();
	_battleCharManager->render();

	if (_cameraPt.x < 0) _cameraPt.x = 0;
	if (_cameraPt.y < 0) _cameraPt.y = 0;

	vector<vector<tagTile>> vvTile = _battleMap->getTagMap().vvTile;

	if (_selectChar != nullptr && !_UIActive)
	{
		/*vector<POINT> moveTile = _selectChar->getMoveTile();
		int x = _selectChar->getPos().x;
		int y = _selectChar->getPos().y;
		for (int i = 0; i < moveTile.size(); i++)
		{

		}*/
		vector<TILESTATE> moveTile;
		POINT pos = _selectChar->getPos();

		int x = 100;
		int y = 100;

		int Zorder;

		
		if (_tileCount > 0) _tileCount -= 4;
		
		if (_tileCount <= 0) _tileCount = 0;

		if (_userAttack == false || _selectChar->getSelectSkill())
		{
			if (_selectChar->getSelectSkill() == true)
			{
				int tileYSize = _battleMap->getTagMap().tileSizeY;
				int tileXSize = _battleMap->getTagMap().tileSizeX;

				for (int i = -_selectChar->getSkillRange().x / 2; i < (_selectChar->getSkillRange().x / 2) + 1; i++)
				{
					for (int j = -_selectChar->getSkillRange().y / 2; j < (_selectChar->getSkillRange().y / 2) + 1; j++)
					{
						if (0 <= pos.x + i && pos.x + i < tileXSize &&
							0 <= pos.y + j && pos.y + j < tileYSize &&
							(i != 0 || j != 0))
						{
							x = (pos.x + i) * 50;
							y = (pos.y + j) * 50;
							Zorder = vvTile[pos.y + j][pos.x + i].Zorder;
							if (vvTile[pos.y + j][pos.x + i].move == 0 || vvTile[pos.y + j][pos.x + i].overTile == TILE_ENEMY)
							{
								CAMERA->addRenderInfo("attackTile", PointMake(x, y), 0, 0, Zorder, ALPHAFRAMERENDER, 5, 0, nullptr, 0, 200);
							}
						}
					}
				}
			}
			else
			{
				moveTile = _selectChar->getMoveTile();

				for (int i = 0; i < moveTile.size() - _tileCount && moveTile.size() != 0; i++)
				{
					//x = vvTile[pos.y + moveTile[i].y][pos.x + moveTile[i].x].rc.left;
					//y = vvTile[pos.y + moveTile[i].y][pos.x + moveTile[i].x].rc.bottom - 1;
					x = (pos.x + moveTile[i].x) * 50;
					y = (pos.y + moveTile[i].y) * 50;
					Zorder = vvTile[pos.y + moveTile[i].y][pos.x + moveTile[i].x].Zorder;
					if (moveTile[i].state == 0)
						CAMERA->addRenderInfo("moveTile", PointMake(x, y), 0, 0, Zorder, ALPHAFRAMERENDER, 5, 0, nullptr, 0, 200);
					else if (moveTile[i].state == 1)
						CAMERA->addRenderInfo("attackTile", PointMake(x, y), 0, 0, Zorder, ALPHAFRAMERENDER, 5, 0, nullptr, 0, 200);
					//IMAGEMANAGER->alphaRender("moveTile", getMemDC(), x, y, 100);
				}
			}
		}
		else
		{
			moveTile = _selectChar->getAttackTile();

			for (int i = 0; i < moveTile.size(); i++)
			{
				//x = vvTile[pos.y + moveTile[i].y][pos.x + moveTile[i].x].rc.left;
				//y = vvTile[pos.y + moveTile[i].y][pos.x + moveTile[i].x].rc.bottom - 1;
				x = (pos.x + moveTile[i].x) * 50;
				y = (pos.y + moveTile[i].y) * 50;
				Zorder = vvTile[pos.y + moveTile[i].y][pos.x + moveTile[i].x].Zorder;
				if (moveTile[i].state == 0)
					CAMERA->addRenderInfo("moveTile", PointMake(x, y), 0, 0, Zorder, ALPHAFRAMERENDER, 5, 0, nullptr, 0, 200);
				else if (moveTile[i].state == 1)
					CAMERA->addRenderInfo("attackTile", PointMake(x, y), 0, 0, Zorder, ALPHAFRAMERENDER, 5, 0, nullptr, 0, 200);
				//IMAGEMANAGER->alphaRender("moveTile", getMemDC(), x, y, 100);
			}
		}
	}

	if (_userTurn && !_move && _gamePlay)
	{
		if (_cameraPt.y / 50 < 0 || _cameraPt.y / 50 >= vvTile.size())
		{
			_cameraPt.y = 0;
		}

		if (_cameraPt.x / 50 < 0 || _cameraPt.x / 50 >= vvTile[0].size())
		{
			_cameraPt.x = 0;
		}

		int mouseTileZ = 1; vvTile[_cameraPt.y / 50][_cameraPt.x / 50].Zorder;

		_mouseTileFrameX++;

		if (_mouseTileFrameX >= 60) _mouseTileFrameX = 0;

		if(_mouseTileState == 0)
			CAMERA->addRenderInfo("moveTile", _mouseTile, 0, 0, mouseTileZ, ALPHAFRAMERENDER, _mouseTileFrameX / 10, 0, nullptr, 0, 180);
		else if (_mouseTileState == 1)
			CAMERA->addRenderInfo("attackTile", _mouseTile, 0, 0, mouseTileZ, ALPHAFRAMERENDER, _mouseTileFrameX / 10, 0, nullptr, 0, 180);

		if (_tileCross)
		{
			_tileCrossFrameX++;

			if (_tileCrossFrameX >= 20) _tileCrossFrameX = 0;

			CAMERA->addRenderInfo("tilecross", _mouseTile, 0, 0, mouseTileZ, ALPHAFRAMERENDER, _tileCrossFrameX / 10, 0, nullptr, 0, 210);
		}
	}

	int ZorderCount;

	int x;
	int y;

	vector<renderInfo>* vRenderInfo = CAMERA->getObjectRenderInfo(&ZorderCount);
	vector<renderInfo>::iterator viRenderInfo;

	for (int z = 0; z <= ZorderCount; z++)
	{
		for (viRenderInfo = vRenderInfo->begin(); viRenderInfo != vRenderInfo->end(); viRenderInfo++)
		{
			if (z == viRenderInfo->Zorder)
			{
				x = viRenderInfo->renderPos.x - viRenderInfo->imageW / 2 - CAMERA->getPos().x;
				y = viRenderInfo->renderPos.y - viRenderInfo->imageH - CAMERA->getPos().y + viRenderInfo->standardY;

				switch (viRenderInfo->renderMethod)
				{
				case RENDER:
				{
					IMAGEMANAGER->render(viRenderInfo->imageName, getMemDC(), x, y);
				}
				break;

				case ANIALPHARENDER:
				{
					IMAGEMANAGER->findImage(viRenderInfo->imageName)->aniAlphaRender(getMemDC(), x, y, viRenderInfo->ani, viRenderInfo->alpha);
				}
				break;

				case ALPHARENDER:
				{
					IMAGEMANAGER->alphaRender(viRenderInfo->imageName, getMemDC(), x, y, viRenderInfo->alpha);
				}
				break;

				case ANIRENDER:
				{
					IMAGEMANAGER->findImage(viRenderInfo->imageName)->aniRender(getMemDC(), x, y, viRenderInfo->ani);
				}
				break;

				case FREAMRENDER:
				{
					IMAGEMANAGER->frameRender(viRenderInfo->imageName, getMemDC(), x, y, viRenderInfo->frameX, viRenderInfo->frameY);
				}
				break;

				case ALPHAFRAMERENDER:
				{
					IMAGEMANAGER->alphaFrameRender(viRenderInfo->imageName, getMemDC(), x, y, viRenderInfo->frameX, viRenderInfo->frameY, viRenderInfo->alpha);
				}
				break;
				}

				if (z == 0)
				{
					break;
				}
			}
		}
	}

	EFFECTMANAGER->render();

	vRenderInfo = vRenderInfo = CAMERA->getRenderInfo(&ZorderCount);

	if (!_sceneChange)
	{
		for (int z = 0; z <= ZorderCount; z++)
		{
			for (viRenderInfo = vRenderInfo->begin(); viRenderInfo != vRenderInfo->end(); viRenderInfo++)
			{
				if (z == viRenderInfo->Zorder)
				{
					x = viRenderInfo->renderPos.x - viRenderInfo->imageW / 2 - CAMERA->getPos().x;
					y = viRenderInfo->renderPos.y - viRenderInfo->imageH - CAMERA->getPos().y + viRenderInfo->standardY;

					switch (viRenderInfo->renderMethod)
					{
					case RENDER:
					{
						IMAGEMANAGER->render(viRenderInfo->imageName, getMemDC(), x, y);
					}
					break;

					case ANIALPHARENDER:
					{
						IMAGEMANAGER->findImage(viRenderInfo->imageName)->aniAlphaRender(getMemDC(), x, y, viRenderInfo->ani, viRenderInfo->alpha);
					}
					break;

					case ALPHARENDER:
					{
						IMAGEMANAGER->alphaRender(viRenderInfo->imageName, getMemDC(), x, y, viRenderInfo->alpha);
					}
					break;

					case ANIRENDER:
					{
						IMAGEMANAGER->findImage(viRenderInfo->imageName)->aniRender(getMemDC(), x, y, viRenderInfo->ani);
					}
					break;

					case FREAMRENDER:
					{
						IMAGEMANAGER->frameRender(viRenderInfo->imageName, getMemDC(), x, y, viRenderInfo->frameX, viRenderInfo->frameY);
					}
					break;

					case ALPHAFRAMERENDER:
					{
						IMAGEMANAGER->alphaFrameRender(viRenderInfo->imageName, getMemDC(), x, y, viRenderInfo->frameX, viRenderInfo->frameY, viRenderInfo->alpha);
					}
					break;
					}

					if (z == 0)
					{
						break;
					}
				}
			}
		}
	}
	//UI 그리기
	_hOldFont = (HFONT)SelectObject(getMemDC(), _hFont);

	if (_UIActive)
	{
		POINT selPos = _selectChar->getPos();

		selPos.x *= 50;
		selPos.y *= 50;
		selPos.x -= CAMERA->getPos().x;
		selPos.y -= CAMERA->getPos().y;

		if (_CharUI && _selectChar != nullptr)
		{
			for (int i = 0; i < 4; i++)
			{

				IMAGEMANAGER->render("charuiback", getMemDC(), -130 + ((i % 2) * 200) + selPos.x, -50 + ((i / 2) * 60) + selPos.y);
				IMAGEMANAGER->frameRender("charuiicon", getMemDC(), -122 + ((i % 2) * 200) + selPos.x, -48 + ((i / 2) * 60) + selPos.y, i, 0);

				string str;

				switch (i)
				{
					case 0:
					{
						str = "어빌리티";
					}
					break;

					case 1:
					{
						str = "휴  식";
					}
					break;

					case 2:
					{
						str = "아이템";
					}
					break;

					case 3:
					{
						str = "상  태";
					}
					break;
				}
				TextOut(getMemDC(), -95 + ((i % 2) * 200) + selPos.x, -43 + ((i / 2) * 60) + selPos.y, str.c_str(), strlen(str.c_str()));
			}
		}

		if (_abilityUI && _selectChar != nullptr)
		{
			IMAGEMANAGER->alphaRender("abilityui", getMemDC(), 70 + selPos.x, -50 + selPos.y, 200);
			for (int i = 0; i < _selectChar->getSkillCount(); i++)
			{
				TextOut(getMemDC(), 80 + selPos.x, -40 + selPos.y + (i * 20), _selectChar->getSkillName(i).c_str(), strlen(_selectChar->getSkillName(i).c_str()));

				SetTextColor(getMemDC(), RGB(255, 255, 0));
				char sp[64];
				wsprintf(sp, "SP : %d", _selectChar->getSkillSP(i));
				TextOut(getMemDC(), 240 + selPos.x, -40 + selPos.y + (i * 20), sp, strlen(sp));
				SetTextColor(getMemDC(), RGB(255, 255, 255));
			}
		}

		if (_itemUI && _selectChar != nullptr)
		{
			vector<INVENTORY> inven = PLAYER->getInventory();
			IMAGEMANAGER->alphaRender("abilityui", getMemDC(), 70 + selPos.x, -50 + selPos.y, 200);
			for (int i = 0; i < inven.size(); i++)
			{
				IMAGEMANAGER->frameRender("itemicon", getMemDC(), 80 + selPos.x, -40 + selPos.y + (i * 25), inven[i].item.iconNum, 0);
				TextOut(getMemDC(), 110 + selPos.x, -36 + selPos.y + (i * 25), inven[i].item.name.c_str(), strlen(inven[i].item.name.c_str()));

				char itemCount[64];
				wsprintf(itemCount, "%d", inven[i].count);
				TextOut(getMemDC(), 280 + selPos.x, -36 + selPos.y + (i * 25), itemCount, strlen(itemCount));
			}
		}

		if (_stateUI && _selectChar != nullptr)
		{
			IMAGEMANAGER->alphaRender("abilityui", getMemDC(), 70 + selPos.x, -50 + selPos.y, 200);
			IMAGEMANAGER->render(_selectChar->getFaceName(), getMemDC(), 90 + selPos.x, -30 + selPos.y);
			_hOldBigFont = (HFONT)SelectObject(getMemDC(), _hBigFont);
			TextOut(getMemDC(), 150 + selPos.x, -20 + selPos.y, _selectChar->getName().c_str(), strlen(_selectChar->getName().c_str()));
			SelectObject(getMemDC(), _hOldBigFont);
			
			char statCh[64];
			wsprintf(statCh, "생명력 : %d / %d", _selectChar->getCurHp(), _selectChar->getMaxHp());
			SetTextColor(getMemDC(), RGB(255, 0, 0));
			TextOut(getMemDC(), 90 + selPos.x, 30 + selPos.y, statCh, strlen(statCh));

			wsprintf(statCh, "SP : %d / %d", _selectChar->getCurSp(), _selectChar->getMaxSp());
			SetTextColor(getMemDC(), RGB(255, 255, 0));
			TextOut(getMemDC(), 90 + selPos.x, 50 + selPos.y, statCh, strlen(statCh));

			SetTextColor(getMemDC(), RGB(255, 255, 255));

			wsprintf(statCh, "공격력 : %d", _selectChar->getAttackDamage());
			TextOut(getMemDC(), 90 + selPos.x, 70 + selPos.y, statCh, strlen(statCh));

			wsprintf(statCh, "이동속도 : %d", _selectChar->getMoveSpeed());
			TextOut(getMemDC(), 90 + selPos.x, 90 + selPos.y, statCh, strlen(statCh));
		}
	}

	if (_targetChar != nullptr && !_UIActive && _userTurn && !_move)
	{
		IMAGEMANAGER->alphaRender("targetui", getMemDC(), _ptMouse.x, _ptMouse.y, 200);
		_hOldMiddleFont = (HFONT)SelectObject(getMemDC(), _hMiddleFont);
		TextOut(getMemDC(), _ptMouse.x + 20, _ptMouse.y + 10, _targetChar->getName().c_str(), strlen(_targetChar->getName().c_str()));
		SelectObject(getMemDC(), _hOldMiddleFont);

		char targetch[64];
		wsprintf(targetch, "생명력 : %d / %d", _targetChar->getCurHp(), _targetChar->getMaxHp());
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 40, targetch, strlen(targetch));

		wsprintf(targetch, "SP : %d / %d", _targetChar->getCurSp(), _targetChar->getMaxSp());
		SetTextColor(getMemDC(), RGB(255, 255, 0));
		TextOut(getMemDC(), _ptMouse.x + 10, _ptMouse.y + 70, targetch, strlen(targetch));
	}

	if (!_gamePlay)
	{
		if (_gameClear)
		{
			IMAGEMANAGER->alphaRender("clearbar", getMemDC(), 0, WINSIZEY / 2 - 45, _gameEndAlpha);
			IMAGEMANAGER->alphaRender("cleartxt", getMemDC(), WINSIZEX / 2 - 160, WINSIZEY / 2 - 18, _gameEndAlpha + 150);
		}
		else
		{
			IMAGEMANAGER->alphaRender("gameoverbar", getMemDC(), 0, WINSIZEY / 2 - 45, _gameEndAlpha);
			IMAGEMANAGER->alphaRender("gameovertxt", getMemDC(), WINSIZEX / 2 - 160, WINSIZEY / 2 - 18, _gameEndAlpha + 150);
		}
	}

	//RECT rc = { 400,100,650,300 };
	//RectangleMake(getMemDC(), rc);

	SelectObject(getMemDC(), _hOldFont);

	/*if (KEYMANAGER->isToggleKey(VK_F5))
	{
		for (int i = 0; i < _battleMap->getTagMap().vvTile.size(); i++)		//타일표시
		{
			for (int j = 0; j < _battleMap->getTagMap().vvTile[i].size(); j++)
			{
				if (_battleMap->getTagMap().vvTile[i][j].rc.left - CAMERA->getPos().x < WINSIZEX && _battleMap->getTagMap().vvTile[i][j].rc.right - CAMERA->getPos().x > 0 &&
					_battleMap->getTagMap().vvTile[i][j].rc.top - CAMERA->getPos().y < WINSIZEY && _battleMap->getTagMap().vvTile[i][j].rc.bottom - CAMERA->getPos().y > 0)
				{
					if (_battleMap->getTagMap().vvTile[i][j].move == 1 || _battleMap->getTagMap().vvTile[i][j].obj != OBJ_NONE)
					{
						IMAGEMANAGER->alphaRender("attackTile", getMemDC(), _battleMap->getTagMap().vvTile[i][j].rc.left - CAMERA->getPos().x, _battleMap->getTagMap().vvTile[i][j].rc.top - CAMERA->getPos().y, 100);
					}
					else if (_battleMap->getTagMap().vvTile[i][j].move == 0)
					{
						IMAGEMANAGER->alphaRender("moveTile", getMemDC(), _battleMap->getTagMap().vvTile[i][j].rc.left - CAMERA->getPos().x, _battleMap->getTagMap().vvTile[i][j].rc.top - CAMERA->getPos().y, 100);
					}
				}
			}
		}
	}*/
}

SCENEINFO battleScene::getSceneInfo()
{
	SCENEINFO nextInfo;

	switch (_curMapNum)
	{
		case 0007:
			wsprintf(nextInfo.nextMapName, "214");
			break;
		case 172:
			wsprintf(nextInfo.nextMapName, "208");
			break;
	}

	return nextInfo;
}

battleScene::battleScene() : 
						_hFont(NULL),
						_hBigFont(NULL),
						_hMiddleFont(NULL)
{
}
