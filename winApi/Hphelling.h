#pragma once
#include "battleSkill.h"
class Hphelling : public battleSkill
{
private:

public:
	HRESULT init(void);
	void update(void);

	Hphelling() {}
	~Hphelling() {}
};

