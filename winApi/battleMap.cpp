#include "stdafx.h"
#include "battleMap.h"

void battleMap::mapLoad()
{
	char fileName[128];

	strcpy(fileName, _mapName);

	char loadFile[128] = "save\\";

	strcat(loadFile, fileName);
	strcat(loadFile, ".txt");

	vector<string> loadVec = TXTMANAGER->load(loadFile);
	int count = 0;
	_curMap.mapName = loadVec[count++];
	_curMap.mapObjectCount = atoi(loadVec[count++].c_str());

	_curMap.vMapObj.clear();
	for (int i = 0; i < _curMap.mapObjectCount; i++)
	{
		tagMapObject tmo;
		tmo.pos.x = atoi(loadVec[count++].c_str());
		tmo.pos.y = atoi(loadVec[count++].c_str());
		tmo.sizeX = atoi(loadVec[count++].c_str());
		tmo.sizeY = atoi(loadVec[count++].c_str());
		tmo.Zorder = atoi(loadVec[count++].c_str());

		tmo.rc.left = tmo.pos.x - tmo.sizeX / 2;
		tmo.rc.right = tmo.pos.x + tmo.sizeX / 2;
		tmo.rc.top = tmo.pos.y - tmo.sizeY;
		tmo.rc.bottom = tmo.pos.y;

		_curMap.vMapObj.push_back(tmo);
	}

	for (int i = 0; i < _curMap.vMapObj.size(); i++)
	{
		string keyStr;
		char imagestr[128];
		char imageName[128];
		strcpy(imagestr, _curMap.mapName.c_str());

		strcpy(imageName, "image\\map\\");
		strcat(imageName, _curMap.mapName.c_str());

		char subName[128];
		wsprintf(subName, "_1-%d", i + 1);

		strcat(imagestr, subName);

		strcat(imageName, subName);
		strcat(imageName, ".bmp");

		keyStr = imagestr;

		//cout << keyStr << endl;
		//cout << imageName << endl;
		_curMap.vMapObj[i].imageName = keyStr;
		if (i == 0)
		{
			IMAGEMANAGER->addImage(keyStr, imageName, _curMap.vMapObj[i].sizeX, _curMap.vMapObj[i].sizeY);
		}
		else
		{
			IMAGEMANAGER->addImage(keyStr, imageName, _curMap.vMapObj[i].sizeX, _curMap.vMapObj[i].sizeY, true, RGB(0, 0, 0));
		}
	}

	CAMERA->setMapSize(PointMake(_curMap.vMapObj[0].sizeX, _curMap.vMapObj[0].sizeY));

	//cout << "=====================================================================" << endl;

	_curMap.tileSizeX = atoi(loadVec[count++].c_str());
	_curMap.tileSizeY = atoi(loadVec[count++].c_str());

	for (int i = 0; i < _curMap.vvTile.size(); i++)
	{
		_curMap.vvTile[i].clear();
	}
	_curMap.vvTile.clear();

	for (int i = 0; i < _curMap.tileSizeY; i++)
	{
		vector<tagTile> loadtile;
		for (int j = 0; j < _curMap.tileSizeX; j++)
		{
			tagTile tt;
			tt.rc = RectMake(j * 50, i * 50, 50, 50);
			tt.move = atoi(loadVec[count++].c_str());
			tt.obj = (OBJECT)atoi(loadVec[count++].c_str());
			tt.Zorder = atoi(loadVec[count++].c_str());
			tt.overTile = TILE_NONE;

			loadtile.push_back(tt);
		}
		_curMap.vvTile.push_back(loadtile);
		loadtile.clear();
	}

	if (strcmp(_curMap.mapName.c_str(), "0007"))
	{
		_curMap.mapUIName = "½£¼Ó Ç×±¸";
	}
}

HRESULT battleMap::init(char* mapName)
{
	strcpy(_mapName, mapName);

	_alpha = false;
	_mapAlpha = 255;

	_gameEnd = false;

	mapLoad();
	return S_OK;
}

void battleMap::render()
{
	if (!_gameEnd)
	{
		if (_alpha && _mapAlpha > 0)
		{
			_mapAlpha -= 5;
		}
		else if (_alpha && _mapAlpha < 10)
		{
			_mapAlpha = 0;
		}

		if (!_alpha && _mapAlpha < 255)
		{
			_mapAlpha += 5;
		}
		else if (!_alpha && _mapAlpha > 255)
		{
			_mapAlpha = 255;
		}
	}
	else
	{
		if (_alpha && _mapAlpha > 100)
		{
			_mapAlpha -= 5;
		}
		else if (_alpha && _mapAlpha < 100)
		{
			_mapAlpha = 100;
		}

		if (!_alpha && _mapAlpha < 255)
		{
			_mapAlpha += 5;
		}
		else if (!_alpha && _mapAlpha > 255)
		{
			_mapAlpha = 255;
		}
	}

	if (_curMap.vMapObj.size() != 0)
	{
		vector<tagMapObject>::iterator viMapObj;

		int Count = 0;

		for (viMapObj = _curMap.vMapObj.begin(); viMapObj != _curMap.vMapObj.end(); viMapObj++)
		{
			/*if ((_curMap.vMapObj[i].pos.x - _curMap.vMapObj[i].sizeX / 2 - CAMERA->getPos().x < WINSIZEX
				&& _curMap.vMapObj[i].pos.y - _curMap.vMapObj[i].sizeY - CAMERA->getPos().y < WINSIZEY)
				&& (_curMap.vMapObj[i].pos.x + _curMap.vMapObj[i].sizeX / 2 - CAMERA->getPos().x > 0
					&& _curMap.vMapObj[i].pos.y - CAMERA->getPos().y> 0))*/
			{
				/*IMAGEMANAGER->render(mapName, getMemDC(), _curMap.vMapObj[i].pos.x - _curMap.vMapObj[i].sizeX / 2 - CAMERA->getPos().x,
				_curMap.vMapObj[i].pos.y - _curMap.vMapObj[i].sizeY - CAMERA->getPos().y);*/

				if (_mapAlpha == 255)
				{
					if (viMapObj == _curMap.vMapObj.begin())
					{
						CAMERA->addObjectRenderInfo(viMapObj->imageName, PointMake(0, 0), 0, 0, viMapObj->Zorder, RENDER, -1, -1, nullptr, 0, _mapAlpha);
					}
					else
					{
						CAMERA->addObjectRenderInfo(viMapObj->imageName, viMapObj->pos, viMapObj->sizeX, viMapObj->sizeY, viMapObj->Zorder, RENDER, -1, -1, nullptr, 0, _mapAlpha);
					}
				}
				else
				{
					if (viMapObj == _curMap.vMapObj.begin())
					{
						CAMERA->addObjectRenderInfo(viMapObj->imageName, PointMake(0, 0), 0, 0, viMapObj->Zorder, ALPHARENDER, -1, -1, nullptr, 0, _mapAlpha);
					}
					else
					{
						CAMERA->addObjectRenderInfo(viMapObj->imageName, viMapObj->pos, viMapObj->sizeX, viMapObj->sizeY, viMapObj->Zorder, ALPHARENDER, -1, -1, nullptr, 0, _mapAlpha);
					}
				}
			}
		}

		//for (int i = 0; i < _curMap.vvTile.size(); i++)
		//{
		//	for (int j = 0; j < _curMap.vvTile[i].size(); j++)
		//	{
		//		/*if (_curMap.vvTile[i][j].rc.left - CAMERA->getPos().x < WINSIZEX && _curMap.vvTile[i][j].rc.right - CAMERA->getPos().x > 0 &&
		//			_curMap.vvTile[i][j].rc.top - CAMERA->getPos().y < WINSIZEY && _curMap.vvTile[i][j].rc.bottom - CAMERA->getPos().y > 0)*/
		//		{
		//			if (_curMap.vvTile[i][j].obj != OBJ_NONE)
		//			{
		//				/*IMAGEMANAGER->frameRender("object", getMemDC(),
		//				_curMap.vvTile[i][j].rc.left + ((_curMap.vvTile[i][j].rc.right - _curMap.vvTile[i][j].rc.left) / 2) - (IMAGEMANAGER->findImage("object")->getFrameWidth() / 2) - CAMERA->getPos().x,
		//				_curMap.vvTile[i][j].rc.bottom - IMAGEMANAGER->findImage("object")->getFrameHeight() - CAMERA->getPos().y,
		//				0, _curMap.vvTile[i][j].obj);*/
		//				CAMERA->addRenderInfo("object", PointMake(_curMap.vvTile[i][j].rc.left + ((_curMap.vvTile[i][j].rc.right - _curMap.vvTile[i][j].rc.left) / 2), _curMap.vvTile[i][j].rc.bottom),
		//					IMAGEMANAGER->findImage("object")->getFrameWidth(), IMAGEMANAGER->findImage("object")->getFrameHeight(), _curMap.vvTile[i][j].Zorder + 1, FREAMRENDER, 0, _curMap.vvTile[i][j].obj);
		//			}
		//		}
		//	}
		//}
	}
}

void battleMap::release()
{
	_curMap.vMapObj.clear();
	for (int i = 0; i < _curMap.vvTile.size(); i++)
	{
		_curMap.vvTile[i].clear();
	}
	_curMap.vvTile.clear();
}