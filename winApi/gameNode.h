#pragma once
#include "image.h"

//����� �̹����� ���������� �����
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual HRESULT init(SCENEINFO sceneInfo);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	
	virtual SCENEINFO getSceneInfo();

	//����� �̹��� ���
	image* getBackBuffer(void) { return _backBuffer; }
	//�޸� DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC ��� (ȭ��DC)
	HDC getHDC() { return _hdc; }

	//���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode(){}
	virtual ~gameNode() {}
};
