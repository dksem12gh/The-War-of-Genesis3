#pragma once
#include "battleChar.h"
class battleIronMask : public battleChar
{
public:
	HRESULT init(string imageName, int maxHp, int maxSp, int moveSpeed, int attackDamage, int imageY);

	virtual void setAni(void);

	battleIronMask() {}
	~battleIronMask() {}
};

