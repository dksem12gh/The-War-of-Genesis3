#include "stdafx.h"
#include "battleSkill.h"
#include "battleChar.h"
#include "battleIronMask.h"

battleSkill::battleSkill() : _play(false),
							 _skillWorldTimer(0.0f),
							 _skillTimer(0.0f)
{
}

void battleSkill::play(void)
{
	_play = true;
	_skillWorldTimer = TIMEMANAGER->getWorldTime();
	_skillTimer = TIMEMANAGER->getWorldTime();
	_infoCount = 0;
}

HRESULT battleSkill::init(void)
{
	return S_OK;
}

void battleSkill::update(void)
{
}

