#pragma once
#include "battleChar.h"

class battleSaladin : public battleChar
{
public:
	HRESULT init(string imageName, int maxHp, int maxSp, int moveSpeed, int attackDamage, int imageY);

	void setAni(void);

	battleSaladin() {}
	~battleSaladin() {}
};

