#pragma once
#include "battleChar.h"

class battleGreatSwordKnight : public battleChar
{
public:
	HRESULT init(string imageName, int maxHp, int maxSp, int moveSpeed, int attackDamage, int imageY);

	void setAni(void);

	battleGreatSwordKnight() {}
	~battleGreatSwordKnight() {}
};

