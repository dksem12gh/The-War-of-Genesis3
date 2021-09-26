#include "stdafx.h"
#include "battleIronMask.h"
#include "animation.h"
#include "battleSkill.h"
#include "AsuraPacheonmu.h"

HRESULT battleIronMask::init(string imageName, int maxHp, int maxSp, int moveSpeed, int attackDamage, int imageY)
{
	battleChar::init(imageName, maxHp, maxSp, moveSpeed, attackDamage, imageY);
	_charName = "철가면";
	_faceImageName = "ironmaskface";
	return S_OK;
}

void battleIronMask::setAni(void)
{
	int imageSizeX = IMAGEMANAGER->findImage(_imageName)->getWidth();
	int imageSizeY = IMAGEMANAGER->findImage(_imageName)->getHeight();

	int imageFrameX = IMAGEMANAGER->findImage(_imageName)->getFrameWidth();
	int imageFrameY = IMAGEMANAGER->findImage(_imageName)->getFrameHeight();

	int aniArr[20];

	//0
	animation* addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(0, 2, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//1
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(10, 13, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//2
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(20, 23, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//3
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(30, 32, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//4
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(40, 45, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//5
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(50, 55, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//6
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(60, 65, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//7
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(70, 75, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//8
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(80, 83, false, false);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//9
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(90, 93, false, false);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//10
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(100, 103, false, false);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//11
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(110, 113, false, false);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//12
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(4, 4, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//13
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(14, 14, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//14
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(24, 24, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//15
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(34, 34, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//16	스킬시작모션
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(120, 121, false, false);
	addani->setFPS(4);
	_vAni.push_back(addani);
	//17	칼넣는모션
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(122, 126, false, false);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//18	칼소환하는 손떠는모션
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(131, 132, false, true);
	addani->setFPS(6);
	_vAni.push_back(addani);
	//19	손들고올라가는모션
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(133, 135, false, true);
	addani->setFPS(4);
	_vAni.push_back(addani);

	_shadowY = 30;

	_viewDirection = 0;
	_curAni = _vAni[0];

	_curAni->start();

	TILESTATE ts;

	ts.x = -2;
	ts.y = 0;
	ts.state = 1;
	_attackTile.push_back(ts);
	ts.x = 2;
	ts.y = 0;
	ts.state = 1;
	_attackTile.push_back(ts);
	ts.x = 0;
	ts.y = -2;
	ts.state = 1;
	_attackTile.push_back(ts);
	ts.x = 0;
	ts.y = 2;
	ts.state = 1;
	_attackTile.push_back(ts);

	_hitFrame.push_back(82);
	_hitFrame.push_back(92);
	_hitFrame.push_back(102);
	_hitFrame.push_back(112);

	_attackEffect = true;
	_attackEffectName = "thrusting";

	_attackEffectFrame.push_back(82);
	_attackEffectFrame.push_back(92);
	_attackEffectFrame.push_back(102);
	_attackEffectFrame.push_back(112);

	battleSkill* bs = new AsuraPacheonmu;
	bs->init();
	bs->setUseChar(this);
	_vSkill.push_back(bs);
}
