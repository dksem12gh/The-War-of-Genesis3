#include "stdafx.h"
#include "AsuraPacheonmu.h"
#include "battleChar.h"

HRESULT AsuraPacheonmu::init(void)
{
	_name = "아수라파천무";

	_Range.x = 11;
	_Range.y = 11;

	_costSP = 500;

	SKILLINFO si;
	//0 칼들면서 빛나는 이펙트
	si.type = TIMER;
	si.skillTime = 0.0f;
	_vSkillInfo.push_back(si);
	//1 칼넣는 모션
	si.type = TIMER;
	si.skillTime = 1.0f;
	_vSkillInfo.push_back(si);
	//2 칼소환손떠는모션
	si.type = TIMER;
	si.skillTime = 2.33f;
	_vSkillInfo.push_back(si);
	//3 칼생성
	si.type = TIMER;
	si.skillTime = 3.95f;
	_vSkillInfo.push_back(si);
	//4 타켓 한명씩 폭팔이펙트
	si.type = ALLTARGET;
	si.skillTime = 1.2f;
	_vSkillInfo.push_back(si);
	//5 타켓 전부 철가면 날라가는 이펙트
	si.type = ALLTARGET;
	si.skillTime = 1.0f;
	_vSkillInfo.push_back(si);
	//6 머리위에 반짝이는 구체생성
	si.type = TIMER;
	si.skillTime = 3.0f;
	_vSkillInfo.push_back(si);
	//7 칼올라가기
	si.type = TIMER;
	si.skillTime = 4.0f;
	_vSkillInfo.push_back(si);
	//8 손드는모션
	si.type = TIMER;
	si.skillTime = 5.0f;
	_vSkillInfo.push_back(si);
	//9 빛없어지고 용나오고 같이 올라감
	si.type = TIMER;
	si.skillTime = 5.5f;
	_vSkillInfo.push_back(si);
	//10 귀신떨어짐 약 4초간
	si.type = TIMER;
	si.skillTime = 9.5f;
	_vSkillInfo.push_back(si);
	//11 용 + 붉은선 떨어지기
	si.type = TIMER;
	si.skillTime = 9.6f;
	_vSkillInfo.push_back(si);
	//12 케릭 + 돌진이펙트 떨어지기
	si.type = TIMER;
	si.skillTime = 10.6f;
	_vSkillInfo.push_back(si);
	//13 랜덤 폭팔 이펙트
	si.type = TIMER;
	si.skillTime = 11.6f;
	_vSkillInfo.push_back(si);
	//14 내려오면서 모든타켓 데미지
	si.type = ALLTARGET;
	si.skillTime = 11.7f;
	_vSkillInfo.push_back(si);
	//15 내려오고 철가면 히트모션
	si.type = TIMER;
	si.skillTime = 13.0f;
	_vSkillInfo.push_back(si);
	return S_OK;
}

void AsuraPacheonmu::update(void)
{	
	if (_infoCount < _vSkillInfo.size())
	{
		_skillWorldTimer = TIMEMANAGER->getWorldTime();

		switch (_infoCount)
		{
			case 0:
			{
				if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					_useChar->setViewDirection(3);
					_useChar->setAnimation(16);
					EFFECTMANAGER->play("skillstart", _useChar->getPos().x * 50 - 110, _useChar->getPos().y * 50 - 100, 160, 3);
					_infoCount++;
					//_infoCount = 11;
				}
			}
			break;
			
			case 1:
			{
				if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					_useChar->setAnimation(17);
					_infoCount++;
				}
			}
			break;

			case 2:
			{
				if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					_useChar->setAnimation(18);
					EFFECTMANAGER->play("swordbackeffect", _useChar->getPos().x * 50 - 85, _useChar->getPos().y * 50 - 140, 150, 3);
					_infoCount++;
				}
			}
			break;

			case 3:
			{
				if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					EFFECTMANAGER->play("ironmaskswordeffect", _useChar->getPos().x * 50 - 15, _useChar->getPos().y * 50 - 140, 170, 2);
					_infoCount++;
					_targetCount = 0;
					_skillTimer = TIMEMANAGER->getWorldTime();
				}
			}
			break;

			case 4:
			{
				if (_targetCount < _vTargetChar.size() && _skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					_skillTimer = TIMEMANAGER->getWorldTime();
					POINT targetPos = _vTargetChar[_targetCount]->getPos();
					int x = targetPos.x * 50 - 40;
					int y = targetPos.y * 50;

					EFFECTMANAGER->play("blueboomeffect", x - 95, y - 105, 200, 1); 
					EFFECTMANAGER->play("spliteffect", x + 10, y - 20, 230, 1);
					EFFECTMANAGER->play("page1boom", x, y, x, - 50, 160, 2, 0.08f, 0, -45);
					CAMERA->vibration();

					_vTargetChar[_targetCount]->hit(1.0f);
					_targetCount++;
				}
				else if (_targetCount >= _vTargetChar.size() && _skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					_infoCount++;
					_skillTimer = TIMEMANAGER->getWorldTime();
				}
			}
			break;

			case 5:
			{
				if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					POINT usePos = _useChar->getPos();

					for (int i = 0; i < _vTargetChar.size(); i++)
					{
						POINT targetPos = _vTargetChar[i]->getPos();
						EFFECTMANAGER->play("ironmaskthruting", usePos.x * 50 - 80, usePos.y * 50 - 100, targetPos.x * 50 - 80, targetPos.y * 50 - 100, 230, 2, 0.04f, -1, -1);
					}
					_infoCount++;
				}
			}
			break;

			case 6:
			{
				if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					EFFECTMANAGER->play("lightboom1", _useChar->getPos().x * 50 - 100, _useChar->getPos().y * 50 - 250, 200, 2);
					_infoCount++;
				}
			}
			break;

			case 7:
			{
				if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					EFFECTMANAGER->stop("ironmaskswordeffect");
					EFFECTMANAGER->play("ironmaskswordeffect", _useChar->getPos().x * 50 - 15, _useChar->getPos().y * 50 - 140, _useChar->getPos().x * 50 - 15, -200, 170, 2, 0, 8);
					_infoCount++;
				}
			}
			break;

			case 8:
			{
				if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					_useChar->setAnimation(19);
					_infoCount++;
				}
			}
			break;

			case 9:
			{
				if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					EFFECTMANAGER->play("upperdragonhead", _useChar->getPos().x * 50 - 60, _useChar->getPos().y * 50 - 260, _useChar->getPos().x * 50 - 60, -150, 170, 2, 0, 10);
					EFFECTMANAGER->stop("lightboom");
					_useChar->setUpperMove(true, 10);
					_infoCount++;
				}
			}
			break;

			case 10:
			{
				if (_skillWorldTimer - _skillTimer < _vSkillInfo[_infoCount].skillTime)
				{
					int rnd = RND->getInt(20);

					if (rnd == 0)
					{
						EFFECTMANAGER->play("ghost", RND->getFromIntTo(WINSIZEX / 2 + 100, WINSIZEX) + CAMERA->getPos().x,
							RND->getFromIntTo(-100, -1) + CAMERA->getPos().y,
							RND->getFromIntTo(0, WINSIZEX / 2 - 100) + CAMERA->getPos().x,
							RND->getFromIntTo(WINSIZEY, WINSIZEY + 10) + CAMERA->getPos().y,
							230, 3);
					}
					else if (rnd == 1)
					{
						EFFECTMANAGER->play("ghost", RND->getFromIntTo(WINSIZEX, WINSIZEX + 100) + CAMERA->getPos().x,
							RND->getFromIntTo(0, WINSIZEY / 2 - 100) + CAMERA->getPos().y,
							RND->getFromIntTo(-10, -1) + CAMERA->getPos().x,
							RND->getFromIntTo(WINSIZEY / 2 + 100, WINSIZEY) + CAMERA->getPos().y,
							230, 3);
					}
				}
				else if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					_infoCount++;
				}
			}
			break;

			case 11:
			{
				if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					EFFECTMANAGER->play("falleffectback", WINSIZEX + CAMERA->getPos().x, -100 + CAMERA->getPos().y, 0 + CAMERA->getPos().x, WINSIZEY + 100 + CAMERA->getPos().y, 180, 3, 0.001f, -24, 17);
					EFFECTMANAGER->play("dragonhead", WINSIZEX-200  + CAMERA->getPos().x, -300 + CAMERA->getPos().y, -700 + CAMERA->getPos().x, WINSIZEY + CAMERA->getPos().y, 200, 4, 12, 8);
					_infoCount++;
				}
			}
			break;

			case 12:
			{
				if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					EFFECTMANAGER->play("ironmaskassaulteffect", WINSIZEX - 130 + CAMERA->getPos().x, -50 + CAMERA->getPos().y, -700 + CAMERA->getPos().x, WINSIZEY + CAMERA->getPos().y, 200, 4, 12, 8);
					EFFECTMANAGER->play("ironmaskfalleffect", WINSIZEX - 130 + CAMERA->getPos().x, -100 + CAMERA->getPos().y, -700 + CAMERA->getPos().x, WINSIZEY + CAMERA->getPos().y, 200, 4, 12, 8);
					_infoCount++;
					_targetCount = 0;
				}
			}
			break;

			case 13:
			{
				if (_skillWorldTimer - _skillTimer < _vSkillInfo[_infoCount].skillTime)
				{
					_targetCount++;
					if (_targetCount % 3 == 0)
					{
						POINT camPos = CAMERA->getPos();
						POINT rndPos;
						rndPos.x = RND->getFromIntTo(camPos.x, camPos.x + WINSIZEX);
						rndPos.y = RND->getFromIntTo(camPos.y, camPos.y + WINSIZEY);
						EFFECTMANAGER->play("purpleboomeffect", rndPos.x, rndPos.y, 150, 2);
					}
				}
				else if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					_infoCount++;
				}
			}
			break;

			case 14:
			{
				if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					_useChar->setAnimation(3);
					_useChar->setUpperMove(false, 10);
					for (int i = 0; i < _vTargetChar.size(); i++)
					{
						_vTargetChar[i]->hit(1.0f);
						_vTargetChar[i]->increaseHp(-100000);
					}
					_infoCount++;
				}
			}
			break;

			case 15:
			{
				if (_skillWorldTimer - _skillTimer > _vSkillInfo[_infoCount].skillTime)
				{
					_useChar->hit(0.4f);
					_infoCount++;
				}
			}
			break;
		}
	}
	else
	{
		_play = false;
	}
}

// 헤헤 
// 나님 들렸다감 헤헤 - 김지민
// 저도 들렀다감미다 - 김예현