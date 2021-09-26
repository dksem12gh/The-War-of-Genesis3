#include "stdafx.h"
#include "battleGreatSwordKnight.h"
#include "animation.h"

HRESULT battleGreatSwordKnight::init(string imageName, int maxHp, int maxSp, int moveSpeed, int attackDamage, int imageY)
{
	battleChar::init(imageName, maxHp, maxSp, moveSpeed, attackDamage, imageY);
	_charName = "대검기사";
	_faceImageName = "empty";

	return S_OK;
}

void battleGreatSwordKnight::setAni(void)
{
	int imageSizeX = IMAGEMANAGER->findImage(_imageName)->getWidth();
	int imageSizeY = IMAGEMANAGER->findImage(_imageName)->getHeight();

	int imageFrameX = IMAGEMANAGER->findImage(_imageName)->getFrameWidth();
	int imageFrameY = IMAGEMANAGER->findImage(_imageName)->getFrameHeight();

	int aniArr[20];

	//0
	animation* addani = new animation;
	addani->init(2000, 2000, 200, 200);
	addani->setPlayFrame(0, 2, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//1
	addani = new animation;
	addani->init(2000, 2000, 200, 200);
	addani->setPlayFrame(10, 12, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//2
	addani = new animation;
	addani->init(2000, 2000, 200, 200);
	addani->setPlayFrame(20, 22, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//3
	addani = new animation;
	addani->init(2000, 2000, 200, 200);
	addani->setPlayFrame(30, 32, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//4
	addani = new animation;
	addani->init(2000, 2000, 200, 200);
	addani->setPlayFrame(40, 45, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//5
	addani = new animation;
	addani->init(2000, 2000, 200, 200);
	addani->setPlayFrame(50, 55, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//6
	addani = new animation;
	addani->init(2000, 2000, 200, 200);
	addani->setPlayFrame(60, 65, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//7
	addani = new animation;
	addani->init(2000, 2000, 200, 200);
	addani->setPlayFrame(70, 75, false, true);
	addani->setFPS(3);
	_vAni.push_back(addani);
	//8
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	aniArr[0] = 80;
	aniArr[1] = 81;
	aniArr[2] = 82;
	aniArr[3] = 83;
	aniArr[4] = 84;
	aniArr[5] = 85;
	aniArr[6] = 86;
	aniArr[7] = 87;
	addani->setPlayFrame(aniArr, 8, false);
	addani->setFPS(4);
	_vAni.push_back(addani);
	//9
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	aniArr[0] = 90;
	aniArr[1] = 91;
	aniArr[2] = 92;
	aniArr[3] = 93;
	aniArr[4] = 94;
	aniArr[5] = 95;
	aniArr[6] = 96;
	aniArr[7] = 97;
	addani->setPlayFrame(aniArr, 8, false);
	addani->setFPS(4);
	_vAni.push_back(addani);
	//10
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	aniArr[0] = 100;
	aniArr[1] = 101;
	aniArr[2] = 102;
	aniArr[3] = 103;
	aniArr[4] = 104;
	aniArr[5] = 105;
	aniArr[6] = 106;
	aniArr[7] = 107;
	addani->setPlayFrame(aniArr, 8, false);
	addani->setFPS(4);
	_vAni.push_back(addani);
	//11
	addani = new animation;
	addani->init(imageSizeX, imageSizeY, imageFrameX, imageFrameY);
	aniArr[0] = 110;
	aniArr[1] = 111;
	aniArr[2] = 112;
	aniArr[3] = 113;
	aniArr[4] = 114;
	aniArr[5] = 115;
	aniArr[6] = 116;
	aniArr[7] = 117;
	addani->setPlayFrame(aniArr, 8, false);
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

	_viewDirection = RND->getInt(4);
	_curAni = _vAni[_viewDirection];

	_curAni->start();

	_shadowY = 34;

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
	_hitFrame.push_back(86);
	_hitFrame.push_back(92);
	_hitFrame.push_back(96);
	_hitFrame.push_back(102);
	_hitFrame.push_back(106);
	_hitFrame.push_back(112);
	_hitFrame.push_back(116);

	_attackEffect = false;
}
