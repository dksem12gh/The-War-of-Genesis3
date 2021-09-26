#include "stdafx.h"
#include "mainGame.h"
#include "battleScene.h"
#include "shopScene.h"
#include "effect.h"

//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	ShowCursor(false);
	//케릭터이미지 추가
	IMAGEMANAGER->addFrameImage("saladin", "image\\character\\saladin.bmp", 2000, 2800, 10, 14, true, RGB(168, 208, 168));
	IMAGEMANAGER->addFrameImage("greatSwordKnight", "image\\character\\greatswordknight.bmp", 2000, 2400, 10, 12, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("ironMask", "image\\character\\ironmask.bmp", 2000, 2800, 10, 14, true, RGB(168, 208, 168));

	//그림자
	IMAGEMANAGER->addImage("charshadow", "image\\character\\charshadow.bmp", 50, 50, true, RGB(255, 255, 255));

	//커서
	IMAGEMANAGER->addFrameImage("cursor", "image\\cursor.bmp", 112, 24, 7, 1, true, RGB(80, 120, 116));

	//이펙트추가
	IMAGEMANAGER->addFrameImage("thrusting", "image\\effect\\thrusting.bmp", 800, 800, 4, 4, true, RGB(0, 0, 0));
	EFFECTMANAGER->addEffect("thrusting", "thrusting", 0, 0, 0, 0, 4, 5, DirectionEffect);

	IMAGEMANAGER->addFrameImage("blueboomeffect", "image\\effect\\blueboomeffect.bmp", 10106, 268, 31, 1, true, RGB(36, 216, 196));
	EFFECTMANAGER->addEffect("blueboomeffect", "blueboomeffect", 0, 0, 0, 0, 31, 5, DefaultEffect);

	IMAGEMANAGER->addFrameImage("swordbackeffect", "image\\effect\\swordbackeffect.bmp", 6660, 220, 37, 1, true, RGB(0, 96, 0));
	EFFECTMANAGER->addEffect("swordbackeffect", "swordbackeffect", 0, 0, 0, 0, 8, 1, DefaultEffect);

	IMAGEMANAGER->addFrameImage("purpleboomeffect", "image\\effect\\purpleboomeffect.bmp", 3375, 192, 15, 1, true, RGB(0, 56, 0));
	EFFECTMANAGER->addEffect("purpleboomeffect", "purpleboomeffect", 0, 0, 0, 0, 15, 20, DefaultEffect);

	IMAGEMANAGER->addFrameImage("ironmaskswordeffect", "image\\effect\\ironmaskswordeffect.bmp", 156, 130, 4, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("ironmaskswordeffect", "ironmaskswordeffect", 0, 0, 0, 0, 2, 1, EndureEffect);

	IMAGEMANAGER->addFrameImage("ghost", "image\\effect\\ghost.bmp", 324, 62, 4, 1, true, RGB(252, 248, 140));
	EFFECTMANAGER->addEffect("ghost", "ghost", 0, 0, 0, 0, 4, 20, ShootingEffect);

	IMAGEMANAGER->addFrameImage("page1boom", "image\\effect\\page1boom.bmp", 3048, 113, 24, 1, true, RGB(72, 120, 20));
	EFFECTMANAGER->addEffect("page1boom", "page1boom", 0, 0, 0, 0, 12, 20, AfterImageEffect);
	EFFECTMANAGER->addEffect("page1boom1", "page1boom", 0, 0, 0, 0, 12, 100, DefaultEffect);

	IMAGEMANAGER->addFrameImage("dragonhead", "image\\effect\\dragonhead.bmp", 510, 500, 1, 1, true, RGB(8, 4, 4));
	EFFECTMANAGER->addEffect("dragonhead", "dragonhead", 0, 0, 0, 0, 1, 1, ShootingEffect);

	IMAGEMANAGER->addFrameImage("falleffectback", "image\\effect\\falleffectback.bmp", 360, 124, 15, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("falleffectback", "falleffectback", 0, 0, 0, 0, 3, 1, AfterImageEffect);
	EFFECTMANAGER->addEffect("falleffectback1", "falleffectback", 0, 0, 0, 0, 3, 100, DefaultEffect);

	IMAGEMANAGER->addFrameImage("purpleboomeffect", "image\\effect\\purpleboomeffect.bmp", 3375, 192, 15, 1, true, RGB(0, 56, 0));
	EFFECTMANAGER->addEffect("purpleboomeffect", "purpleboomeffect", 0, 0, 0, 0, 13, 30, DefaultEffect);

	IMAGEMANAGER->addFrameImage("skillstart", "image\\effect\\skillstart.bmp", 6325, 192, 25, 1, true, RGB(80, 0, 0));
	EFFECTMANAGER->addEffect("skillstart", "skillstart", 0, 0, 0, 0, 25, 0, DefaultEffect);

	IMAGEMANAGER->addFrameImage("spliteffect", "image\\effect\\spliteffect.bmp", 2996, 92, 28, 1, true, RGB(8, 88, 8));
	EFFECTMANAGER->addEffect("spliteffect", "spliteffect", 0, 0, 0, 0, 3, 0, DefaultEffect);

	IMAGEMANAGER->addFrameImage("ironmaskthruting", "image\\effect\\ironmaskthruting.bmp", 200, 800, 1, 4, true, RGB(168, 208, 168));
	EFFECTMANAGER->addEffect("ironmaskthruting", "ironmaskthruting", 0, 0, 0, 0, 1, 0, DirectionAfterImageAlphaEffect, "redboomdeffect", -30, -10, 130, 2);
	EFFECTMANAGER->addEffect("ironmaskthruting1", "ironmaskthruting", 0, 0, 0, 0, 1, 0, DirectionAlphaEffect);

	IMAGEMANAGER->addFrameImage("redboomdeffect", "image\\effect\\redboomdeffect.bmp", 2560, 250, 10, 1, true, RGB(4, 96, 4));
	EFFECTMANAGER->addEffect("redboomdeffect", "redboomdeffect", 0, 0, 0, 0, 5, 0, DefaultEffect);

	IMAGEMANAGER->addFrameImage("lightboom", "image\\effect\\lightboom.bmp", 1470, 245, 6, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("lightboom", "lightboom", 0, 0, 0, 0, 10, 0, DefaultEffect);
	EFFECTMANAGER->addEffect("lightboom1", "lightboom", 0, 0, 0, 0, 20, 0, EndureEffect);

	IMAGEMANAGER->addFrameImage("upperdragonhead", "image\\effect\\upperdragonhead.bmp", 2788, 227, 17, 1, true, RGB(252, 252, 88));
	EFFECTMANAGER->addEffect("upperdragonhead", "upperdragonhead", 0, 0, 0, 0, 3, 0, ShootingEffect);

	IMAGEMANAGER->addFrameImage("ironmaskassaulteffect", "image\\effect\\ironmaskassaulteffect.bmp", 692, 127, 4, 1, true, RGB(168, 208, 168));
	EFFECTMANAGER->addEffect("ironmaskassaulteffect", "ironmaskassaulteffect", 0, 0, 0, 0, 4, 0, ShootingEffect);

	IMAGEMANAGER->addFrameImage("ironmaskfalleffect", "image\\effect\\ironmaskfalleffect.bmp", 900, 191, 4, 1, true, RGB(252, 248, 208));
	EFFECTMANAGER->addEffect("ironmaskfalleffect", "ironmaskfalleffect", 0, 0, 0, 0, 4, 0, ShootingEffect);

	//UI 이미지 추가
	IMAGEMANAGER->addImage("charuiback", "image\\UI\\charui.bmp", 102, 28, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("charuiicon", "image\\UI\\charuiicon.bmp", 100, 25, 4, 1, true, RGB(0, 0, 0));

	IMAGEMANAGER->addImage("abilityui", "image\\UI\\abilityui.bmp", 250, 200);

	IMAGEMANAGER->addFrameImage("itemicon", "image\\UI\\itemicon.bmp", 48, 24, 2, 1);

	IMAGEMANAGER->addImage("targetui", "image\\UI\\targetui.bmp", 200, 100);

	//클리어 UI
	IMAGEMANAGER->addImage("clearbar", "image\\UI\\clearbar.bmp", 1420, 90);
	IMAGEMANAGER->addImage("cleartxt", "image\\UI\\cleartxt.bmp", 320, 36, true, RGB(8, 36, 44));

	IMAGEMANAGER->addImage("gameoverbar", "image\\UI\\gameoverbar.bmp", 1420, 90);
	IMAGEMANAGER->addImage("gameovertxt", "image\\UI\\gameovertxt.bmp", 250, 36, true, RGB(8, 36, 44));

	//케릭터 상태창 페이스
	IMAGEMANAGER->addImage("ironmaskface", "image\\UI\\철가면.bmp", 50, 50);

	//상점씬 이미지 추가
	IMAGEMANAGER->addImage("214", "image\\shopback\\214.bmp", 1280, 960);
	IMAGEMANAGER->addImage("208", "image\\shopback\\208.bmp", 1280, 960);

	IMAGEMANAGER->addFrameImage("button1", "image\\UI\\button1.bmp", 750, 80, 5, 1);

	IMAGEMANAGER->addImage("shoppingback", "image\\UI\\shoppingback.bmp", 500, 500);

	IMAGEMANAGER->addImage("shopnpcback", "image\\UI\\shopnpcback.bmp", 480, 70);

	IMAGEMANAGER->addImage("npc1", "image\\UI\\노인1.bmp", 50, 50);
	IMAGEMANAGER->addImage("npc2", "image\\UI\\노인2.bmp", 50, 50);

	IMAGEMANAGER->addFrameImage("upbutton", "image\\UI\\upbutton.bmp", 48, 24, 2, 1);
	IMAGEMANAGER->addFrameImage("downbutton", "image\\UI\\downbutton.bmp", 48, 24, 2, 1);

	IMAGEMANAGER->addImage("buysellbutton", "image\\UI\\buysellbutton.bmp", 60, 24);

	IMAGEMANAGER->addImage("invenback", "image\\UI\\invenback.bmp", 150, 500);

	gameNode::init(TRUE);
	//이곳에서 초기화
	
	SCENEMANAGER->addScene("battle", new battleScene);
	SCENEMANAGER->addScene("shop", new shopScene);

	SCENEMANAGER->changeScene("battle");

	_cursorLock = false;

	_renderTimer = TIMEMANAGER->getWorldTime();
	_worldRenderTimer = TIMEMANAGER->getWorldTime();

	_updateTimer = TIMEMANAGER->getWorldTime();
	_worldUpdateTimer = TIMEMANAGER->getWorldTime();

	_mouseFrameX = 0;

	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	ShowCursor(true);
	gameNode::release();
	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용		
}

//=============================
//	## update(void) ## 업데이트
//=============================
void mainGame::update()
{
	//이곳에서 계산식, 키보드, 마우스등등 업데이트

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		if (_cursorLock == false)
		{
			RECT rc;

			GetClientRect(_hWnd, &rc);
			ClientToScreen(_hWnd, (LPPOINT)&rc);
			ClientToScreen(_hWnd, (LPPOINT)(&rc.right));

			ClipCursor(&rc);
			_cursorLock = true;
		}
		else
		{
			ClipCursor(NULL);
			_cursorLock = false;
		}
	}

	if ((WINSIZEX - 2 < _ptMouse.x && _ptMouse.x <= WINSIZEX) || KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERA->increaseX(6);
	}
	else if ((0 <= _ptMouse.x && _ptMouse.x < 2) || KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERA->increaseX(-6);
	}

	if ((WINSIZEY - 2 < _ptMouse.y && _ptMouse.y <= WINSIZEY) || KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERA->increaseY(6);
	}
	else if ((0 <= _ptMouse.y && _ptMouse.y < 2) || KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERA->increaseY(-6);
	}

	CAMERA->update();
	SCENEMANAGER->update();
	EFFECTMANAGER->update();
}

//============================
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(float fps)
{
	_worldRenderTimer = TIMEMANAGER->getWorldTime();

	//검은색 빈 비트맵 (이것도 렌더에 그대로 둘것)
	//if (_worldRenderTimer - _renderTimer > 1.0f / fps)
	{
		_renderTimer = TIMEMANAGER->getWorldTime();

		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
		//=============================================================

		//_renderTimer = TIMEMANAGER->getWorldTime();
		SCENEMANAGER->render();

		_mouseFrameX++;

		if (_mouseFrameX >= 56) _mouseFrameX = 0;

		IMAGEMANAGER->frameRender("cursor", getMemDC(), _ptMouse.x, _ptMouse.y, _mouseFrameX / 8, 0);

		TIMEMANAGER->render(getMemDC());

		//=============================================================
		//백버퍼의 내용을 HDC에 그린다
		this->getBackBuffer()->render(getHDC());
	}
}
