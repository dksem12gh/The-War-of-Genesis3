#include "stdafx.h"
#include "battleChar.h"
#include "battleMap.h"
#include "battleSkill.h"
#include "animation.h"

HRESULT battleChar::init(string imageName, int maxHp, int maxSp, int moveSpeed, int attackDamage, int imageY)
{
	_fimage = IMAGEMANAGER->findImage(imageName);
	_imageName = imageName;
	_curHp = _maxHp = maxHp;
	_curSp = _maxSp = maxSp;
	_imageY = imageY;
	_moveSpeed = moveSpeed;
	_attackDamage = attackDamage;

	_state = true;
	_turnActivity = false;
	_moveActivity = false;
	_move = false;
	_attack = false;
	_moveAttack = false;
	_die = false;
	_dieAlpha = 255;

	_curAni = nullptr;

	_beforeDirection = -1;
	_moveCount = 0;
	_moveX = 0;
	_moveY = 0;

	arrowFrameX = 0;
	
	_hitWorldTimer = 0;
	_hitTimer = 0;
	_stiffenTime = 0;

	_curSkill = nullptr;

	_upperMove = false;

	_selSkillIndex = 0;
	_selectSkill = false;

	return S_OK;
}

void battleChar::update(void)
{
	if (_curAni != nullptr)
	{
		_curAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}

	if (_moveYMove)
	{
		if (_upperMove == true)
		{
			int Camera = CAMERA->getPos().y;
			if (_posY * 50 + 40 + _moveY - CAMERA->getPos().y > -100)
			{
				_moveY -= _upperSpeed;
			}
			else
			{
				_moveYMove = false;
			}
		}
		else
		{
			if (_moveY < 0)
			{
				_moveY += _upperSpeed;
			}
			else
			{
				_moveYMove = false;
				_moveY = 0;
			}
		}
	}

	if (_die)
	{
		_dieAlpha -= 2;
		if (_dieAlpha <= 0)
		{
			_state = false;
			_battleMap->setTileMove(PointMake(_posX, _posY), 0);
			_battleMap->setTileOver(PointMake(_posX, _posY), TILE_NONE);
			_dieAlpha = 0;
			_die = false;
		}
	}

	if (_hitWorldTimer - _hitTimer < _stiffenTime)
	{
		_stiffenTimer++;
		if (_stiffenTimer % 10 == 0)
		{
			if (_moveX != 3)
			{
				_moveX = 3;
			}
			else
			{
				_moveX = -3;
			}
		}
		_hitWorldTimer = TIMEMANAGER->getWorldTime();
	}
	else if (_stiffenTime != 0)
	{
		_curAni = _vAni[_viewDirection];
		_moveX = 0;
		if (_curSkill == nullptr)
		{
			_attack = false;
		}
		_stiffenTime = 0;

		if (_curHp <= 0)
		{
			_dieAlpha = 200;
			_die = true;
			_curAni = _vAni[12 + _viewDirection];
		}

		_curAni->start();
	}
	else if (_attack == true && _curSkill != nullptr)
	{
		_curSkill->update();
		CAMERA->setPos(PointMake(_posX * 50 + 25 - WINSIZEX / 2, _posY * 50 + 50 - WINSIZEY / 2));
		if (!_curSkill->isPlaying())
		{
			_curSkill->targetClear();
			_selectSkill = false;
			_curSkill = nullptr;
			_battleMap->mapAlphaRender(false);
			_curAni = _vAni[_viewDirection];
			_curAni->start();
			_attack = false;
			_turnActivity = true;
		}
	}
	else if (_attack == true)
	{
		for (int i = 0; i < _hitFrame.size(); i++)
		{
			if (_curAni->getFrameIdx() != _beforeAniFrame && _curAni->getFrameIdx() == _hitFrame[i])
			{
				_beforeAniFrame = _curAni->getFrameIdx();
				_attackChar->hit(1.0f);
				_attackChar->increaseHp(-_attackDamage);
				break;
			}
		}

		if (_attackEffect)
		{
			for (int i = 0; i < _attackEffectFrame.size(); i++)
			{
				if (_curAni->getFrameIdx() != _beforeAttackFrame && _curAni->getFrameIdx() == _attackEffectFrame[i])
				{
					int Zorder = _battleMap->getTagMap().vvTile[_posY][_posX].Zorder;
					_beforeAttackFrame = _curAni->getFrameIdx();
					EFFECTMANAGER->play(_attackEffectName, (_posX * 50) + 25 - (_fimage->getFrameWidth() / 2), (_posY * 50) + 40 - _imageY, _viewDirection, 180, Zorder + 1);
					break;
				}
			}
		}

		if (!_curAni->isPlay())
		{
			_curAni = _vAni[_viewDirection];
			_curAni->start();
			_attack = false;
			_turnActivity = true;
		}

		CAMERA->setPos(PointMake(_posX * 50 + 25 + _moveX - WINSIZEX / 2, _posY * 50 + 50 + _moveY - WINSIZEY / 2));
	}

	if (_move == true)
	{
		_clickRect.left = _posX * 50;
		_clickRect.right = _posX * 50 + 50;
		_clickRect.bottom = _posY * 50 + 40;
		_clickRect.top = _posY * 50 - 25;

		_ZorderRect.left = _posX * 50 + 20;
		_ZorderRect.right = _posX * 50 + 30;
		_ZorderRect.bottom = _posY * 50 + 25;
		_ZorderRect.top = _posY * 50 - 35;

		if (_moveCount < 0 && _moveX == 0 && _moveY == 0)
		{
			int view = _moveDirection.size() - _moveSpeed;
			if (view <= 0) view = 0;
			switch (_moveDirection[view])
			{
				case Left:
				{
					_viewDirection = 1;
					_curAni = _vAni[1];
				}
				break;

				case Right:
				{
					_viewDirection = 2;
					_curAni = _vAni[2];
				}
				break;

				case Front:
				{
					_viewDirection = 0;
					_curAni = _vAni[0];
				}
				break;

				case Back:
				{
					_viewDirection = 3;
					_curAni = _vAni[3];
				}
				break;
			}

			_move = false;
			_moveX = 0;
			_moveY = 0;
			_moveCount = 0;
			_moveDirection.clear();
			_curAni->start();
			_moveActivity = true;
			_battleMap->setTileMove(PointMake(_posX, _posY), 1);
			if (_friendOrFoe) _battleMap->setTileOver(PointMake(_posX, _posY), TILE_FRIENDLY);
			else if (!_friendOrFoe)
			{
				_battleMap->setTileOver(PointMake(_posX, _posY), TILE_ENEMY);
			}
		}
		else if (_moveX == 0 && _moveY == 0)
		{
			_battleMap->setTileMove(PointMake(_posX, _posY), 0);
			_battleMap->setTileOver(PointMake(_posX, _posY), TILE_NONE);
			switch (_moveDirection[_moveCount])
			{
				case Left:
				{
					if (_beforeDirection != _moveDirection[_moveCount])
					{
						_curAni = _vAni[5];
						_beforeDirection = _moveDirection[_moveCount];
						_curAni->start();
					}
					_posX--;
					_moveX = 50;
				}
				break;

				case Right:
				{
					if (_beforeDirection != _moveDirection[_moveCount])
					{
						_curAni = _vAni[6];
						_beforeDirection = _moveDirection[_moveCount];
						_curAni->start();
					}
					_posX++;
					_moveX = -50;
				}
				break;

				case Front:
				{
					if (_beforeDirection != _moveDirection[_moveCount])
					{
						_curAni = _vAni[4];
						_beforeDirection = _moveDirection[_moveCount];
						_curAni->start();
					}
					_posY--;
					_moveY = +50;
				}
				break;

				case Back:
				{
					if (_beforeDirection != _moveDirection[_moveCount])
					{
						_curAni = _vAni[7];
						_beforeDirection = _moveDirection[_moveCount];
						_curAni->start();
					}
					_posY++;
					_moveY = -50;
				}
				break;
			}
			_moveCount--;
		}
		else
		{
			if (_moveX > 0) _moveX -= MOVESPEED;
			else _moveX += MOVESPEED;

			if (_moveY > 0) _moveY -= MOVESPEED;
			else _moveY += MOVESPEED;

			if (_moveX <= MOVESPEED && _moveX >= -MOVESPEED) _moveX = 0;
			if (_moveY <= MOVESPEED && _moveY >= -MOVESPEED) _moveY = 0;

			if (_moveSpeed < _moveDirection.size() - _moveCount) _moveCount = -1;

			CAMERA->setPos(PointMake(_posX * 50 + 25 + _moveX - WINSIZEX / 2, _posY * 50 + 50 + _moveY - WINSIZEY / 2));
		}
	}
	else if (_moveAttack)
	{
		attack(_attackChar);
		_moveAttack = false;
	}
}

void battleChar::render(void)
{
	POINT cameraPos = CAMERA->getPos();

	if (_dieAlpha > 0)
	{
		if (_clickRect.left - cameraPos.x < WINSIZEX && _clickRect.right - cameraPos.x >0 &&
			_clickRect.top - cameraPos.y < WINSIZEY && _clickRect.bottom - cameraPos.y > 0)
		{

			POINT rendPos;
			POINT shadowPos;
			POINT arrowPos;

			rendPos.x = _posX * 50 + 25 + _moveX;
			rendPos.y = _posY * 50 + 40 + _moveY;

			shadowPos.x = rendPos.x - 25;
			shadowPos.y = rendPos.y - _shadowY;

			arrowPos.x = rendPos.x - 5;
			arrowPos.y = rendPos.y - 100;

			/*if (_curAni != nullptr &&
				(rendPos.x - (fimage->getFrameWidth() / 2) - CAMERA->getPos().x < WINSIZEX &&
					rendPos.x + (fimage->getFrameWidth() / 2) - CAMERA->getPos().x > 0 &&
					rendPos.y - fimage->getFrameHeight() - CAMERA->getPos().y < WINSIZEY &&
					rendPos.y - CAMERA->getPos().y> 0))*/

			bool objectCollition = false;
			RECT temp;

			vector<tagMapObject> vMapObj = _battleMap->getTagMap().vMapObj;
			vector<tagMapObject>::iterator viMapObj;

			int Zorder = _battleMap->getTagMap().vvTile[_posY][_posX].Zorder;

			for (viMapObj = vMapObj.begin() + 1; viMapObj != vMapObj.end(); viMapObj++)
			{
				if (IntersectRect(&temp, &viMapObj->rc, &_ZorderRect) && (viMapObj->rc.bottom > _ZorderRect.bottom || Zorder + 1 < viMapObj->Zorder))
				{
					objectCollition = true;
					break;
				}
			}


			if (objectCollition == true)
			{
				int Alpha = _dieAlpha;
				if (Alpha > 140)
				{
					Alpha = 140;
				}
				CAMERA->addRenderInfo(_imageName, rendPos, _fimage->getFrameWidth(), _fimage->getFrameHeight(), Zorder + 1, ANIALPHARENDER, -1, -1, _curAni, _fimage->getFrameHeight() - _imageY, Alpha);
			}
			else
			{
				CAMERA->addRenderInfo(_imageName, rendPos, _fimage->getFrameWidth(), _fimage->getFrameHeight(), Zorder + 1, ANIALPHARENDER, -1, -1, _curAni, _fimage->getFrameHeight() - _imageY, _dieAlpha);
			}

			if (!_turnActivity)
			{
				arrowFrameX++;
				if (arrowFrameX >= 80) arrowFrameX = 0;

				if (_friendOrFoe) CAMERA->addRenderInfo("turnarrow", arrowPos, 0, 0, Zorder + 1, FREAMRENDER, arrowFrameX / 8, 0, nullptr, 0, 150);
				else CAMERA->addRenderInfo("enemyturnarrow", arrowPos, 0, 0, Zorder + 1, FREAMRENDER, arrowFrameX / 8, 0, nullptr, 0, 150);
			}

			//±×¸²ÀÚ
			CAMERA->addRenderInfo("charshadow", shadowPos, 0, 0, Zorder, ALPHARENDER, -1, -1, nullptr, 0, 150);
		}
	}
}

void battleChar::release(void)
{
	for (int i = 0; i < _vAni.size(); i++)
	{
		_vAni[i]->release();
		SAFE_DELETE(_vAni[i]);
	}
	_vAni.clear();
}

void battleChar::resetTurn(bool turn)
{
	if (turn == _friendOrFoe)
	{
		_turnActivity = false;
		_moveActivity = false;
	}
	else
	{
		_turnActivity = true;
		_moveActivity = true;
	}
}

void battleChar::hit(float stiffenTime)
{
	_attack = true;

	_curAni = _vAni[12 + _viewDirection];
	_curAni->start();

	_hitWorldTimer = TIMEMANAGER->getWorldTime();
	_hitTimer = TIMEMANAGER->getWorldTime();
	_stiffenTimer = 0;

	_stiffenTime = stiffenTime;
}

void battleChar::attack(battleChar* target)
{
	_attack = true;
	_attackChar = target;

	int xDis = _attackChar->getPos().x - _posX;
	int yDis = _attackChar->getPos().y - _posY;

	if (xDis < 0) xDis *= -1;
	if (yDis < 0) yDis *= -1;

	_beforeAniFrame = -1;
	_beforeAttackFrame = -1;

	if (xDis > yDis)
	{
		xDis = _attackChar->getPos().x - _posX;
		if (xDis > 0)
		{
			_curAni = _vAni[10];
			_viewDirection = 2;
		}
		else
		{
			_curAni = _vAni[9];
			_viewDirection = 1;
		}
	}
	else
	{
		yDis = _attackChar->getPos().y - _posY;
		if (yDis > 0)
		{
			_curAni = _vAni[11];
			_viewDirection = 3;
		}
		else
		{
			_curAni = _vAni[8];
			_viewDirection = 0;
		}
	}

	_moveActivity = true;
	_moveTile.clear();
	
	_curAni->start();
}

void battleChar::playSkill()
{
	_attack = true;
	_battleMap->mapAlphaRender(true);
	_selectSkill = false;
	_moveTile.clear();
	_curSkill = _vSkill[_selSkillIndex];
	increaseSp(-_curSkill->getSkillSP());
	_curSkill->play();
}

void battleChar::setSkill(void)
{
	for (int i = 0; i < _vSkill.size(); i++)
	{
		_vSkill[i]->setUseChar(this);
	}
}

void battleChar::setAni(void)
{
}

void battleChar::setRect()
{
	_clickRect.left = _posX * 50;
	_clickRect.right = _posX * 50 + 50;
	_clickRect.bottom = _posY * 50 + 50;
	_clickRect.top = _posY * 50 - 25;

	_ZorderRect.left = _posX * 50 + 20;
	_ZorderRect.right = _posX * 50 + 30;
	_ZorderRect.bottom = _posY * 50 + 50;
	_ZorderRect.top = _posY * 50 - 25;
}

void battleChar::setAnimation(int index)
{
	_curAni = _vAni[index];
	_curAni->start();
}

void battleChar::setSkillTarget(battleChar* target)
{
	_vSkill[_selSkillIndex]->setTarget(target);
}

int battleChar::getSkillTargetCount()
{
	return _vSkill[_selSkillIndex]->getTargetCount();
}

int battleChar::getSkillSP(int index)
{
	return _vSkill[index]->getSkillSP();
}

POINT battleChar::getSkillRange()
{
	return _vSkill[_selSkillIndex]->getRange();
}

string battleChar::getSkillName(int index)
{
	return _vSkill[index]->getSkillName();
}

void battleChar::searchMoveTile()
{
	int x = _posX, y = _posY;
	int move = _moveSpeed;
	int movearr = ((move + 3) * 2) + 1;
	int** arr1;
	arr1 = new int*[movearr];
	for (int i = 0; i < movearr; i++)
	{
		arr1[i] = new int[movearr];
	}

	for (int i = 0; i < movearr; i++)
	{
		for (int j = 0; j < movearr; j ++)
		{
			if (i == 0 || i == movearr - 1 || j == 0 || j == movearr - 1)
			{
				arr1[i][j] = 1;
			}
			else
			{
				arr1[i][j] = 0;
			}
		}
	}

	int tileSizeX = _battleMap->getTagMap().tileSizeX;
	int tileSizeY = _battleMap->getTagMap().tileSizeY;

	vector<vector<tagTile>> vvTile = _battleMap->getTagMap().vvTile;

	for (int i = -(move + 2); i <= move + 2; i++)
	{
		for (int j = -(move + 2); j <= move + 2; j++)
		{
			if (y + j < 0 || x + i < 0 || y + j >= tileSizeY || x + i >= tileSizeX)
			{
				arr1[j + move + 3][i + move + 3] = 1;
			}
			else if (vvTile[y + j][x + i].move == 0 || vvTile[y + j][x + i].move == 1)
			{
				arr1[j + move + 3][i + move + 3] = vvTile[y + j][x + i].move;
			}
			else
			{
				arr1[j + move + 3][i + move + 3] = 0;
			}
		}
	}

	for (int i = -(move + 2); i <= (move + 2); i++)
	{
		for (int j = -(move + 2); j <= (move + 2); j++)
		{
			if (y + j < 0 || x + i < 0 || y + j >= tileSizeY || x + i >= tileSizeY)
			{
				
			}
			else if (vvTile[y + j][x + i].overTile == TILE_ENEMY)
			{
				arr1[j + move + 3][i + move + 3] = 10;
				if(arr1[j + move + 3 - 1][i + move + 3] != 1)
					arr1[j + move + 3 - 1][i + move + 3] = 10;
				if (arr1[j + move + 3 + 1][i + move + 3] != 1)
					arr1[j + move + 3 + 1][i + move + 3] = 10;
				if (arr1[j + move + 3][i + move + 3 - 1] != 1)
					arr1[j + move + 3][i + move + 3 - 1] = 10;
				if (arr1[j + move + 3][i + move + 3 + 1] != 1)
					arr1[j + move + 3][i + move + 3 + 1] = 10;
			}
		}
	}
	

	_moveTile.clear();
	_moveTile = ASTAR->moveTileSearch(arr1, move, _attackTile);

	for (int i = 0; i < movearr; i++) delete[] arr1[i];
	delete[] arr1;
}

void battleChar::searchMoveDirection(int moveTileIndex)
{
	int x = _posX, y = _posY;
	int move = _moveSpeed;
	int movearr = ((move + 1) * 2) + 1;
	int** arr1;
	arr1 = new int*[movearr];
	for (int i = 0; i < movearr; i++)
	{
		arr1[i] = new int[movearr];
	}

	for (int i = 0; i < movearr; i++)
	{
		for (int j = 0; j < movearr; j++)
		{
			if (i == 0 || i == movearr - 1 || j == 0 || j == movearr - 1)
			{
				arr1[i][j] = 1;
			}
			else
			{
				arr1[i][j] = 0;
			}
		}
	}

	int tileSizeX = _battleMap->getTagMap().tileSizeX;
	int tileSizeY = _battleMap->getTagMap().tileSizeY;

	vector<vector<tagTile>> vvTile = _battleMap->getTagMap().vvTile;

	for (int i = -move; i <= move; i++)
	{
		for (int j = -move; j <= move; j++)
		{
			if (y + j < 0 || x + i < 0 || y + j >= tileSizeY || x + i >= tileSizeX)
			{
				arr1[j + move + 1][i + move + 1] = 1;
			}
			else if (vvTile[y + j][x + i].move == 0 || vvTile[y + j][x + i].move == 1 || vvTile[y + j][x + i].move == 2)
			{
				arr1[j + move + 1][i + move + 1] = vvTile[y + j][x + i].move;
			}
			else
			{
				arr1[j + move + 1][i + move + 1] = 0;
			}
		}
	}

	for (int i = -move; i <= move; i++)
	{
		for (int j = -move; j <= move; j++)
		{
			if (0 <= x + i && x + i < tileSizeX &&
				0 <= y + j && y + j < tileSizeY &&
				vvTile[y + j][x + i].overTile == TILE_ENEMY)
			{
				arr1[j + move + 2][i + move + 1] = 1;
				arr1[j + move][i + move + 1] = 1;
				arr1[j + move + 1][i + move + 2] = 1;
				arr1[j + move + 1][i + move] = 1;
			}
		}
	}

	_moveDirection = ASTAR->moveTile2(arr1, _moveTile[moveTileIndex].x, _moveTile[moveTileIndex].y, move);
	_move = true;
	_moveTile.clear();
	_moveCount = _moveDirection.size() - 1;
	_beforeDirection = -1;
	for (int i = 0; i < movearr; i++) delete[] arr1[i];
	delete[] arr1;
}

void battleChar::moveAttack(battleChar * target)
{
	_attackChar = target;
	_moveAttack = true;

	int tileX = _battleMap->getTagMap().tileSizeX;
	int tileY = _battleMap->getTagMap().tileSizeY;

	tileY += 2;
	tileX += 2;

	int** arr1;
	arr1 = new int*[tileY];
	for (int i = 0; i < tileY; i++)
	{
		arr1[i] = new int[tileX];
	}

	vector<vector<tagTile>> vvTile = _battleMap->getTagMap().vvTile;

	for (int i = 0; i < tileY; i++)
	{
		for (int j = 0; j < tileX; j++)
		{
			if (i == 0 || i == tileY - 1 || j == 0 || j == tileX - 1)
			{
				arr1[i][j] = 1;
			}
			else
			{
				arr1[i][j] = vvTile[i - 1][j - 1].move;
			}
		}
	}

	POINT targetPos = _attackChar->getPos();

	for (int i = 1; i < tileX - 1; i++)
	{
		for (int j = 1; j < tileY - 1; j++)
		{
			if (j - 1 == targetPos.y && i - 1 == targetPos.x)
			{
				if (arr1[j + 1][i] != 1 || (_posX == i - 1 && _posY == j)) arr1[j + 1][i] = 1;
				if (arr1[j - 1][i] != 1 || (_posX == i - 1 && _posY == j - 2)) arr1[j - 1][i] = 1;
				if (arr1[j][i + 1] != 1 || (_posX == i && _posY == j - 1)) arr1[j][i + 1] = 1;
				if (arr1[j][i - 1] != 1 || (_posX == i - 2 && _posY == j - 1)) arr1[j][i - 1] = 1;
				for (int k = 0; k < _attackTile.size(); k++)
				{
					if (j + _attackTile[k].y >= 0 && i + _attackTile[k].x >= 0
						&& j + _attackTile[k].y < tileY - 1 && i + _attackTile[k].x < tileX - 1
						&& arr1[j + _attackTile[k].y][i + _attackTile[k].x] != 1)
					{
						arr1[j + _attackTile[k].y][i + _attackTile[k].x] = 9;
					}
					else if (j + _attackTile[k].y - 1 == _posY && i + _attackTile[k].x - 1 == _posX)
					{
						arr1[j + _attackTile[k].y][i + _attackTile[k].x] = 9;
					}
				}
			}
		}
	}

	_moveDirection = ASTAR->enemyMove(arr1, tileX, tileY, _posX, _posY);
	_move = true;

	_moveCount = _moveDirection.size() - 1;
	_beforeDirection = -1;

	if (_moveDirection.size() == 0)
	{
		_move = false;
		_moveActivity = true;
	}

	_moveTile.clear();

	for (int i = 0; i < tileY; i++) delete[] arr1[i];
	delete[] arr1;
}

void battleChar::enemyMoveDirection()
{
	int tileX = _battleMap->getTagMap().tileSizeX;
	int tileY = _battleMap->getTagMap().tileSizeY;

	tileY += 2;
	tileX += 2;

	int** arr1;
	arr1 = new int*[tileY];
	for (int i = 0; i < tileY; i++)
	{
		arr1[i] = new int[tileX];
	}

	vector<vector<tagTile>> vvTile = _battleMap->getTagMap().vvTile;

	for (int i = 0; i < tileY; i++)
	{
		for (int j = 0; j < tileX; j++)
		{
			if (i == 0 || i == tileY - 1 || j == 0 || j == tileX - 1)
			{
				arr1[i][j] = 1;
			}
			else
			{
				arr1[i][j] = vvTile[i - 1][j - 1].move;
			}
		}
	}
	
	for (int i = 1; i < tileX - 1; i++)
	{
		for (int j = 1; j < tileY - 1; j++)
		{
			if (vvTile[j - 1][i - 1].overTile == TILE_FRIENDLY)
			{
				if (arr1[j + 1][i] != 1 || (_posX == i - 1 && _posY == j)) arr1[j + 1][i] = 1;
				if (arr1[j - 1][i] != 1 || (_posX == i - 1 && _posY == j - 2)) arr1[j - 1][i] = 1;
				if (arr1[j][i + 1] != 1 || (_posX == i && _posY == j - 1)) arr1[j][i + 1] = 1;
				if (arr1[j][i - 1] != 1 || (_posX == i - 2 && _posY == j - 1)) arr1[j][i - 1] = 1;
				for (int k = 0; k < _attackTile.size(); k++)
				{
					if (j + _attackTile[k].y >= 0 && i + _attackTile[k].x >= 0 
						&& j + _attackTile[k].y < tileY - 1 && i + _attackTile[k].x < tileX - 1 
						&& arr1[j + _attackTile[k].y][i + _attackTile[k].x] != 1)
					{
						arr1[j + _attackTile[k].y][i + _attackTile[k].x] = 9;
					}
					else if (j + _attackTile[k].y - 1 == _posY && i + _attackTile[k].x - 1 == _posX)
					{
						arr1[j + _attackTile[k].y][i + _attackTile[k].x] = 9;
					}
				}
			}
		}
	}

	_moveDirection = ASTAR->enemyMove(arr1, tileX, tileY, _posX, _posY);
	_move = true;

	_moveCount = _moveDirection.size() - 1;
	_beforeDirection = -1;

	if (_moveDirection.size() == 0)
	{
		_move = false;
		_moveActivity = true;
	}

	for (int i = 0; i < tileY; i++) delete[] arr1[i];
	delete[] arr1;
}

void battleChar::increaseHp(int val)
{
	_curHp += val;

	if (_curHp > _maxHp)
	{
		_curHp = _maxHp;
	}
}

void battleChar::increaseSp(int val)
{
	_curSp += val;

	if (_curSp > _maxSp)
	{
		_curSp = _maxSp;
	}
}
