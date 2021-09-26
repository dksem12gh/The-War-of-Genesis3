#include "stdafx.h"
#include "battleSaladin.h"
#include "animation.h"

HRESULT battleSaladin::init(string imageName, int maxHp, int maxSp, int moveSpeed, int attackDamage, int imageY)
{
	battleChar::init(imageName, maxHp, maxSp, moveSpeed, attackDamage, imageY);
	_charName = "»ì¶óµò";
	_faceImageName = "empty";

	return S_OK;
}

void battleSaladin::setAni(void)
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
	addani->setPlayFrame(10, 12, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//2
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(20, 22, false, true);
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
	aniArr[0] = 80;
	aniArr[1] = 80;
	aniArr[2] = 81;
	aniArr[3] = 82;
	aniArr[4] = 83;
	aniArr[5] = 84;
	aniArr[6] = 85;
	aniArr[7] = 85;
	addani->setPlayFrame(aniArr, 8, false);
	addani->setFPS(4);
	_vAni.push_back(addani);
	//9
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY); 
	aniArr[0] = 90;
	aniArr[1] = 90;
	aniArr[2] = 91;
	aniArr[3] = 92;
	aniArr[4] = 93;
	aniArr[5] = 94;
	aniArr[6] = 94;
	addani->setPlayFrame(aniArr, 7, false);
	addani->setFPS(4);
	_vAni.push_back(addani);
	//10
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	aniArr[0] = 100;
	aniArr[1] = 100;
	aniArr[2] = 101;
	aniArr[3] = 102;
	aniArr[4] = 103;
	aniArr[5] = 104;
	aniArr[6] = 104;
	addani->setPlayFrame(aniArr, 7, false);
	addani->setFPS(4);
	_vAni.push_back(addani);
	//11
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	aniArr[0] = 110;
	aniArr[1] = 110;
	aniArr[2] = 111;
	aniArr[3] = 112;
	aniArr[4] = 113;
	aniArr[5] = 114;
	aniArr[6] = 114;
	addani->setPlayFrame(aniArr, 7, false);
	addani->setFPS(4);
	_vAni.push_back(addani);
	//12
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(3, 3, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//13
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(13, 13, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//14
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(23, 23, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//15
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	addani->setPlayFrame(33, 33, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);

	_shadowY = 38;

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

	_hitFrame.push_back(83);
	_hitFrame.push_back(93);
	_hitFrame.push_back(103);
	_hitFrame.push_back(113);

	_attackEffect = false;
}
