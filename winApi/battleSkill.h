#pragma once

class battleChar;

enum SKILLTYPE
{
	ALLTARGET,
	TIMER
};

struct SKILLINFO
{
	SKILLTYPE type;
	float skillTime;
};

class battleSkill
{
protected:
	float _skillWorldTimer;
	float _skillTimer;

	bool _play;

	int _infoCount;
	int _targetCount;

	int _costSP;

	string _name;

	POINT _Range;

	vector<SKILLINFO> _vSkillInfo;

	battleChar* _useChar;
	vector<battleChar*> _vTargetChar;

public:
	virtual HRESULT init(void);
	virtual void update(void);

	void setTarget(battleChar* target) { _vTargetChar.push_back(target); }
	void setUseChar(battleChar* useChar) { _useChar = useChar; }

	void targetClear() { _vTargetChar.clear(); }

	void play(void);
	bool isPlaying(void) { return _play; }

	POINT getRange(void) { return _Range; }
	int getTargetCount() { return _vTargetChar.size(); }
	int getSkillSP() { return _costSP; }
	string getSkillName() { return _name; }

	battleSkill();
	~battleSkill() {}
};

