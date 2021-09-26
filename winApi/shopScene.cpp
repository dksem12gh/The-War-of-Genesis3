#include "stdafx.h"
#include "shopScene.h"

HRESULT shopScene::init(SCENEINFO sceneInfo)
{
	_backName = sceneInfo.nextMapName;
	_curMapNum = atoi(_backName.c_str());

	BUTTON bt;

	_worldCountTimer = 0;
	_countTimer = 0; 

	_hFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "HY견고딕");

	if (_vButton.size() == 0)
	{
		bt.imgName = "button1";
		bt.buttonTxt = "상점";
		bt.hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "HY견고딕");
		bt.rc = { 10,200,160,280 };
		bt.click = false;
		bt.over = false;
		bt.frameX = 0;
		_vButton.push_back(bt);

		bt.imgName = "button1";
		bt.buttonTxt = "인벤토리";
		bt.hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "HY견고딕");
		bt.rc = { 10,290,160,370 };
		bt.click = false;
		bt.over = false;
		bt.frameX = 0;
		_vButton.push_back(bt);

		bt.imgName = "button1";
		bt.buttonTxt = "다음전투로";
		bt.hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "HY견고딕");
		bt.rc = { WINSIZEX - 160,380,WINSIZEX - 10,460 };
		bt.click = false;
		bt.over = false;
		bt.frameX = 0;
		_vButton.push_back(bt);

		bt.imgName = "button1";
		bt.buttonTxt = "구입하기";
		bt.hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "HY견고딕");
		bt.rc = { 200,10,350,90 };
		bt.click = true;
		bt.over = false;
		bt.frameX = 0;
		_vButton.push_back(bt);

		bt.imgName = "button1";
		bt.buttonTxt = "판매하기";
		bt.hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "HY견고딕");
		bt.rc = { 360,10,510,90 };
		bt.click = false;
		bt.over = false;
		bt.frameX = 0;
		_vButton.push_back(bt);
	}

	for (int i = 0; i < _vButton.size(); i++)
	{
		_vButton[i].click = false;
		_vButton[i].over = false;
		_vButton[i].frameX = 0;

		if (i == 3)
		{
			_vButton[i].click = true;
		}
	}

	if (_buyItem.size() == 0)
	{
		SHOPITEM si;
		si.item.iconNum = 0;
		si.item.name = "체력회복약";
		si.item.info = HPPotion;
		si.item.price = 100;
		si.count = 1;
		_buyItem.push_back(si);

		si.item.iconNum = 1;
		si.item.name = "기력환단";
		si.item.info = SPPotion;
		si.item.price = 200;
		si.count = 1;
		_buyItem.push_back(si);
	}

	for (int i = 0; i < _buyItem.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			_buyItem[i].button[j].over = false;
			_buyItem[i].button[j].click = false;
			_buyItem[i].button[j].frameX = 0;
			if (j == 0)
			{
				_buyItem[i].button[j].imgName = "downbutton";
			}
			else
			{
				_buyItem[i].button[j].imgName = "upbutton";
			}
			_buyItem[i].button[j].rc = RectMake(370 + (j * 100), 190 + (i * 30), 24, 24);
		}
		_buyItem[i].buysellButton.buttonTxt = "구매";
		_buyItem[i].buysellButton.rc = RectMake(630, 190 + (i * 30), 60, 24);
	}

	return S_OK;
}

void shopScene::release(void)
{
	for (int i = 0; i < _vButton.size(); i++)
	{
		DeleteObject(_vButton[i].hFont);
	}
	_vButton.clear();
}

void shopScene::update(void)
{
	_playerGold = PLAYER->getGold();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i].rc, _ptMouse))
			{
				if(i == 2)
				{
					SCENEMANAGER->changeScene("battle");
				}
				else if (i == 3)
				{
					_vButton[3].click = true;
					_vButton[4].click = false;
					for (int i = 0; i < _buyItem.size(); i++)
					{
						_buyItem[i].count = 1;
					}
				}
				else if (i == 4)
				{
					_vButton[3].click = false;
					_vButton[4].click = true;
					settingSellItem();
				}
				else
				{
					_vButton[i].click = !_vButton[i].click;
					if (i == 1)
					{
						settingSellItem();
					}
				}
			}
		}

		if (_vButton[0].click)
		{
			if (_vButton[3].click)
			{
				for (int i = 0; i < _buyItem.size(); i++)
				{
					for (int j = 0; j < 2; j++)
					{
						if (PtInRect(&_buyItem[i].button[j].rc, _ptMouse))
						{
							_buyItem[i].button[j].click = true;
							_buyItem[i].button[j].frameX = 1;
							if (j == 1)_buyItem[i].count++;
							else _buyItem[i].count--;

							if (_buyItem[i].count < 1) _buyItem[i].count = 1;
							if (_buyItem[i].count * _buyItem[i].item.price > _playerGold) _buyItem[i].count = _playerGold / _buyItem[i].item.price;

							_worldCountTimer = TIMEMANAGER->getWorldTime();
							_countTimer = TIMEMANAGER->getWorldTime() + 0.5f;
						}
					}
					if (PtInRect(&_buyItem[i].buysellButton.rc, _ptMouse))
					{
						
						int buyGold = _buyItem[i].item.price * _buyItem[i].count;

						if (buyGold > _playerGold) break;

						PLAYER->addItem(_buyItem[i].item.info, _buyItem[i].count);
						PLAYER->increaseGold(-buyGold);
						settingSellItem();
						for (int i = 0; i < 2; i++)
						{
							_buyItem[i].count = 1;
						}
					}
				}
			}

			else if (_vButton[4].click)
			{
				for (int i = 0; i < _sellItem.size(); i++)
				{
					for (int j = 0; j < 2; j++)
					{
						if (PtInRect(&_sellItem[i].button[j].rc, _ptMouse))
						{
							_sellItem[i].button[j].click = true;
							_sellItem[i].button[j].frameX = 1;
							if (j == 1)_sellItem[i].count++;
							else _sellItem[i].count--;

							if (_sellItem[i].count < 1) _sellItem[i].count = 1;
							if (_sellItem[i].count > PLAYER->getInventory()[i].count) _sellItem[i].count = PLAYER->getInventory()[i].count;
							_worldCountTimer = TIMEMANAGER->getWorldTime();
							_countTimer = TIMEMANAGER->getWorldTime() + 0.5f;
						}
					}
					if (PtInRect(&_sellItem[i].buysellButton.rc, _ptMouse))
					{
						PLAYER->subItem(_sellItem[i].item.info, _sellItem[i].count);
						int sellGold = _sellItem[i].item.price * _sellItem[i].count * 0.8f;
						PLAYER->increaseGold(sellGold);
						settingSellItem();
					}
				}
			}

		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_vButton[3].click)
		{
			for (int i = 0; i < _buyItem.size(); i++)
			{
				for (int j = 0; j < 2; j++)
				{
					if (_buyItem[i].button[j].click)
					{
						_worldCountTimer = TIMEMANAGER->getWorldTime();
						if (_worldCountTimer - _countTimer >= 0.05f)
						{
							_countTimer = TIMEMANAGER->getWorldTime();
							if (j == 1)_buyItem[i].count++;
							else _buyItem[i].count--;

							if (_buyItem[i].count < 1) _buyItem[i].count = 1;
							if (_buyItem[i].count * _buyItem[i].item.price > _playerGold) _buyItem[i].count = _playerGold / _buyItem[i].item.price;
						}
					}
				}
			}
		}

		else if (_vButton[4].click)
		{
			for (int i = 0; i < _sellItem.size(); i++)
			{
				for (int j = 0; j < 2; j++)
				{
					if (_sellItem[i].button[j].click)
					{
						_worldCountTimer = TIMEMANAGER->getWorldTime();
						if (_worldCountTimer - _countTimer >= 0.05f)
						{
							_countTimer = TIMEMANAGER->getWorldTime();
							if (j == 1)_sellItem[i].count++;
							else _sellItem[i].count--;

							if (_sellItem[i].count < 1) _sellItem[i].count = 1;
							if (_sellItem[i].count > PLAYER->getInventory()[i].count) _sellItem[i].count = PLAYER->getInventory()[i].count;
						}
					}
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		for (int i = 0; i < _buyItem.size(); i++)
		{
			for (int j = 0; j < 2; j++)
			{
				_buyItem[i].button[j].click = false;
				_buyItem[i].button[j].frameX = 0;
			}
		}

		for (int i = 0; i < _sellItem.size(); i++)
		{
			for (int j = 0; j < 2; j++)
			{
				_sellItem[i].button[j].click = false;
				_sellItem[i].button[j].frameX = 0;
			}
		}
	}

	for (int i = 0; i < _vButton.size(); i++)
	{
		if (PtInRect(&_vButton[i].rc, _ptMouse))
		{
			_vButton[i].over = true;
		}
		else
		{
			_vButton[i].over = false;
		}
	}
}

void shopScene::render(void)
{
	IMAGEMANAGER->render(_backName, getMemDC(), 0, -100);
	
	_hOldFont = (HFONT)SelectObject(getMemDC(), _hFont);

	for (int i = 0; i < _vButton.size(); i++)
	{
		if (!_vButton[0].click && (i == 3 || i == 4)) continue;

		if (_vButton[i].over)
		{
			_vButton[i].frameX++;
			if (_vButton[i].frameX >= 50) _vButton[i].frameX = 0;
		}
		else if (_vButton[i].click)
		{
			_vButton[i].frameX = 40;
		}
		else
		{
			_vButton[i].frameX = 0;
		}

		IMAGEMANAGER->alphaFrameRender(_vButton[i].imgName, getMemDC(), _vButton[i].rc.left, _vButton[i].rc.top, _vButton[i].frameX / 10, 0, 200);
		SelectObject(getMemDC(), _vButton[i].hFont);
		int txtX = _vButton[i].rc.left + ((_vButton[i].rc.right - _vButton[i].rc.left) / 2) - (10 * strlen(_vButton[i].buttonTxt.c_str()) / 2);
		int txtY = _vButton[i].rc.top + ((_vButton[i].rc.bottom - _vButton[i].rc.top) / 2) - 10;
		TextOut(getMemDC(), txtX, txtY, _vButton[i].buttonTxt.c_str(), strlen(_vButton[i].buttonTxt.c_str()));
	}
	
	if (_vButton[0].click)
	{
		SelectObject(getMemDC(), _hFont);
		IMAGEMANAGER->alphaRender("shoppingback", getMemDC(), 200, 100, 200);
		IMAGEMANAGER->alphaRender("shopnpcback", getMemDC(), 210, 110, 200);
		if (_backName == "214")
		{
			IMAGEMANAGER->render("npc1", getMemDC(), 220, 120);
		}
		else
		{
			IMAGEMANAGER->render("npc2", getMemDC(), 220, 120);
		}
		TextOut(getMemDC(), 280, 130, "어서오시게나... 물건을 골라보시게", strlen("어서오시게나... 물건을 골라보시게"));

		char goldch[64];
		wsprintf(goldch, "Gold : %d", _playerGold);
		TextOut(getMemDC(), 550, 160, goldch, strlen(goldch));

		if (_vButton[3].click)
		{
			for (int i = 0; i < _buyItem.size(); i++)
			{
				IMAGEMANAGER->frameRender("itemicon", getMemDC(), 210, 190 + (i * 30), _buyItem[i].item.iconNum, 0);
				SelectObject(getMemDC(), _hFont);
				TextOut(getMemDC(), 240, 194 + (i * 30), _buyItem[i].item.name.c_str(), strlen(_buyItem[i].item.name.c_str()));

				for (int j = 0; j < 2; j++)
				{
					IMAGEMANAGER->frameRender(_buyItem[i].button[j].imgName, getMemDC(), _buyItem[i].button[j].rc.left, _buyItem[i].button[j].rc.top, _buyItem[i].button[j].frameX, 0);
				}

				char countch[32];
				wsprintf(countch, "%d", _buyItem[i].count);
				TextOut(getMemDC(), 432 - (strlen(countch) * 17 / 4), 194 + (i * 30), countch, strlen(countch));

				wsprintf(countch, "%d", _buyItem[i].count * _buyItem[i].item.price);
				TextOut(getMemDC(), 532 - (strlen(countch) * 17 / 4), 194 + (i * 30), countch, strlen(countch));

				IMAGEMANAGER->render("buysellbutton", getMemDC(), _buyItem[i].buysellButton.rc.left, _buyItem[i].buysellButton.rc.top);
				int txtX = _buyItem[i].buysellButton.rc.left + ((_buyItem[i].buysellButton.rc.right - _buyItem[i].buysellButton.rc.left) / 2) - (8 * strlen(_buyItem[i].buysellButton.buttonTxt.c_str()) / 2);
				int txtY = _buyItem[i].buysellButton.rc.top + ((_buyItem[i].buysellButton.rc.bottom - _buyItem[i].buysellButton.rc.top) / 2) - 8;
				TextOut(getMemDC(), txtX, txtY, _buyItem[i].buysellButton.buttonTxt.c_str(), strlen(_buyItem[i].buysellButton.buttonTxt.c_str()));
			}
		}
		else if (_vButton[4].click)
		{
			for (int i = 0; i < _sellItem.size(); i++)
			{
				IMAGEMANAGER->frameRender("itemicon", getMemDC(), 210, 190 + (i * 30), _sellItem[i].item.iconNum, 0);
				SelectObject(getMemDC(), _hFont);
				TextOut(getMemDC(), 240, 194 + (i * 30), _sellItem[i].item.name.c_str(), strlen(_sellItem[i].item.name.c_str()));

				for (int j = 0; j < 2; j++)
				{
					IMAGEMANAGER->frameRender(_sellItem[i].button[j].imgName, getMemDC(), _sellItem[i].button[j].rc.left, _sellItem[i].button[j].rc.top, _sellItem[i].button[j].frameX, 0);
				}

				char countch[32];
				wsprintf(countch, "%d", _sellItem[i].count);
				TextOut(getMemDC(), 432 - (strlen(countch) * 17 / 4), 194 + (i * 30), countch, strlen(countch));
				int sellPrice = _sellItem[i].count * _sellItem[i].item.price * 0.8f;
				wsprintf(countch, "%d", sellPrice);
				TextOut(getMemDC(), 532 - (strlen(countch) * 17 / 4), 194 + (i * 30), countch, strlen(countch));

				IMAGEMANAGER->render("buysellbutton", getMemDC(), _sellItem[i].buysellButton.rc.left, _sellItem[i].buysellButton.rc.top);
				int txtX = _sellItem[i].buysellButton.rc.left + ((_sellItem[i].buysellButton.rc.right - _sellItem[i].buysellButton.rc.left) / 2) - (8 * strlen(_sellItem[i].buysellButton.buttonTxt.c_str()) / 2);
				int txtY = _sellItem[i].buysellButton.rc.top + ((_sellItem[i].buysellButton.rc.bottom - _sellItem[i].buysellButton.rc.top) / 2) - 8;
				TextOut(getMemDC(), txtX, txtY, _sellItem[i].buysellButton.buttonTxt.c_str(), strlen(_sellItem[i].buysellButton.buttonTxt.c_str()));
			}
		}
	}

	if (_vButton[1].click)
	{
		IMAGEMANAGER->alphaRender("invenback", getMemDC(), 710, 100, 200);
		SelectObject(getMemDC(), _hFont);
		for (int i = 0; i < _sellItem.size(); i++)
		{
			IMAGEMANAGER->frameRender("itemicon", getMemDC(), 720, 110 + (i * 30), _sellItem[i].item.iconNum, 0);
			TextOut(getMemDC(), 750, 110 + (i * 30), _sellItem[i].item.name.c_str(), strlen(_sellItem[i].item.name.c_str()));

			char countch[32];
			wsprintf(countch, "%d", PLAYER->getInventory()[i].count);
			TextOut(getMemDC(), 840 - (strlen(countch) * 17 / 4), 110 + (i * 30), countch, strlen(countch));
		}
	}

	SelectObject(getMemDC(), _hOldFont);
}

void shopScene::settingSellItem()
{
	_sellItem.clear();

	SHOPITEM si;
	for (int i = 0; i < PLAYER->getInventory().size(); i++)
	{
		si.item = PLAYER->getInventory()[i].item;
		si.count = 1;

		for (int j = 0; j < 2; j++)
		{
			si.button[j].over = false;
			si.button[j].click = false;
			si.button[j].frameX = 0;
			if (j == 0)
			{
				si.button[j].imgName = "downbutton";
			}
			else
			{
				si.button[j].imgName = "upbutton";
			}
			si.button[j].rc = RectMake(370 + (j * 100), 190 + (i * 30), 24, 24);
		}

		si.buysellButton.buttonTxt = "판매";
		si.buysellButton.rc = RectMake(630, 190 + (i * 30), 60, 24);

		_sellItem.push_back(si);
	}
}

SCENEINFO shopScene::getSceneInfo()
{
	SCENEINFO nextInfo;

	switch (_curMapNum)
	{
	case 214:
		wsprintf(nextInfo.nextMapName, "0172");
		break;
	case 208:
		wsprintf(nextInfo.nextMapName, "0045");
		break;
	}

	return nextInfo;
}
