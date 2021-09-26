#include "stdafx.h"
#include "camera.h"

bool compare(renderInfo left, renderInfo right)
{
	return left.renderPos.y < right.renderPos.y;
}

HRESULT camera::init(void)
{
	_Pos.x = 0;
	_Pos.y = 0;
	_CameraPosX = 0;
	_CameraPosY = 0;

	_MapSizeX = WINSIZEX;
	_MapSizeY = WINSIZEY;

	renderClear = false;

	_vibrationPos.x = 0;
	_vibrationPos.y = 0;

	return S_OK;
}

void camera::update(void)
{
	if (_Pos.x < 0) _Pos.x = 0;
	else if (_Pos.x + WINSIZEX > _MapSizeX) _Pos.x = _MapSizeX - WINSIZEX;

	if (_Pos.y < 0) _Pos.y = 0;
	else if (_Pos.y + WINSIZEY > _MapSizeY) _Pos.y = _MapSizeY - WINSIZEY;

	float disX = getDistance(_CameraPosX, 0, _Pos.x, 0) / 10;
	float disY = getDistance(0, _CameraPosY, 0, _Pos.y) / 10;

	if (disX > 6) disX = 10;
	if (disY > 6) disY = 10;

	if (_vibration == true)
	{
		_vibrationWorldTimer = TIMEMANAGER->getWorldTime();

		if (_vibrationWorldTimer - _vibrationTimer >= 0.16f)
		{
			_vibrationPos.y = 0;
			_vibration = false;
		}
		else if (_vibrationWorldTimer - _vibrationTimer >= 0.12f)
		{
			_vibrationPos.x = 0;
		}
		else if (_vibrationWorldTimer - _vibrationTimer >= 0.08f)
		{
			_vibrationPos.y -= 3;
		}
		else if (_vibrationWorldTimer - _vibrationTimer >= 0.04f)
		{
			_vibrationPos.x -= 3;
		}
	}

	if (disX != 0)
	{
		if (_CameraPosX > _Pos.x)
		{
			_CameraPosX -= disX;
		}
		else
		{
			_CameraPosX += disX;
		}
	}

	if (disY != 0)
	{
		if (_CameraPosY > _Pos.y)
		{
			_CameraPosY -= disY;
		}
		else
		{
			_CameraPosY += disY;
		}
	}
}

void camera::release(void)
{
	_vRenderInfo.clear();
	_vObjectRenderInfo.clear();
}

void camera::vibration(void)
{
	_vibration = true;
	_vibrationWorldTimer = TIMEMANAGER->getWorldTime();
	_vibrationTimer = TIMEMANAGER->getWorldTime();
}

void camera::addObjectRenderInfo(string imageName, POINT renderPos, int imageW, int imageH, int Zorder, RENDERMETHOD renderMethod, int frameX, int frameY, animation * ani, int standardY, int alpha)
{
	if (objectRenderClear == true)
	{
		_vObjectRenderInfo.clear();
		objectRenderClear = false;
	}

	renderInfo ri;
	ri.imageName = imageName;
	ri.renderPos = renderPos;
	ri.imageW = imageW;
	ri.imageH = imageH;
	ri.frameX = frameX;
	ri.frameY = frameY;
	ri.ani = ani;
	ri.standardY = standardY;
	ri.alpha = alpha;
	ri.Zorder = Zorder;
	ri.renderMethod = renderMethod;
	_vObjectRenderInfo.push_back(ri);
}

vector<renderInfo>* camera::getObjectRenderInfo(int * ZorderCount)
{
	*ZorderCount = 0;

	for (int i = 0; i < _vObjectRenderInfo.size(); i++)
	{
		if ((*ZorderCount) < _vObjectRenderInfo[i].Zorder)
		{
			*ZorderCount = _vObjectRenderInfo[i].Zorder;
		}
	}
	//qsort(&returnInfo[0], returnInfo.size(), sizeof(vector<renderInfo>), compare1);

	//sort(returnInfo.begin(), returnInfo.end(), compare);

	//boost::sort::spreadsort::integer_sort(returnInfo.begin(), returnInfo.end(), rightshift(), compare);
	objectRenderClear = true;
	return &_vObjectRenderInfo;
}

void camera::addRenderInfo(string imageName, POINT renderPos, int imageW, int imageH, int Zorder, RENDERMETHOD renderMethod, int frameX, int frameY, animation* ani, int standardY, int alpha)
{
	if (renderClear == true)
	{
		_vRenderInfo.clear();
		renderClear = false;
	}

	renderInfo ri;
	ri.imageName = imageName;
	ri.renderPos = renderPos;
	ri.imageW = imageW;
	ri.imageH = imageH;
	ri.frameX = frameX;
	ri.frameY = frameY;
	ri.ani = ani;
	ri.standardY = standardY;
	ri.alpha = alpha;
	ri.Zorder = Zorder;
	ri.renderMethod = renderMethod;
	_vRenderInfo.push_back(ri);
}

vector<renderInfo>* camera::getRenderInfo(int* ZorderCount)
{
	*ZorderCount = 0;

	for (int i = 0; i < _vRenderInfo.size(); i++)
	{
		if ((*ZorderCount) < _vRenderInfo[i].Zorder)
		{
			*ZorderCount = _vRenderInfo[i].Zorder;
		}
	}
	//qsort(&returnInfo[0], returnInfo.size(), sizeof(vector<renderInfo>), compare1);

	//sort(returnInfo.begin(), returnInfo.end(), compare);

	//boost::sort::spreadsort::integer_sort(returnInfo.begin(), returnInfo.end(), rightshift(), compare);
	renderClear = true;
	return &_vRenderInfo;
}
