#pragma once

#define MOVESPEED 1.0f

class battleMap;
class battleSkill;

class battleChar
{
protected:
	battleMap* _battleMap;

	image* _fimage;
	string _imageName;
	string _charName;
	string _faceImageName;
	int _imageY;
	int _shadowY;

	int _posX;
	int _posY;
	int _curHp;
	int _maxHp;
	int _curSp;
	int _maxSp;
	int _attackDamage;
	int _moveSpeed;
	RECT _clickRect;
	RECT _ZorderRect;
	vector<animation*> _vAni;
	/*0 À§idle 1 ¿Þidle 2 ¿Àidle 3 ¹Øidle 4 À§move 5 ¿Þmove 6 ¿Àmove 7 ¹Ømove 8 À§attack 9 ¿Þattack 10 ¿Àattack 11 ¹Øattack
	12 À§hit 13 ¿Þhit 14 ¿Àhit 15 ¹Øhit*/
	animation* _curAni;	

	vector<battleSkill*> _vSkill;
	battleSkill* _curSkill;

	vector<int> _hitFrame;

	vector<TILESTATE> _moveTile;
	vector<TILESTATE> _attackTile;
	vector<DIRECTION> _moveDirection;

	bool _attackEffect;
	string _attackEffectName;
	vector<int> _attackEffectFrame;
	int _beforeAttackFrame;

	float _hitWorldTimer;
	float _hitTimer;
	float _stiffenTime;

	int _stiffenTimer;

	bool _friendOrFoe;
	bool _state;
	bool _turnActivity;
	bool _moveActivity;
	bool _move;
	bool _attack;
	bool _moveAttack;
	int _beforeAniFrame;
	bool _die;
	int _dieAlpha;

	int _viewDirection;	//0À§ 1¿Þ 2¿À 3¹Ø
	int _beforeDirection;
	int _moveCount;
	float _moveX;
	float _moveY;

	int arrowFrameX;
	
	bool _moveYMove;
	bool _upperMove;
	int _upperSpeed;

	int _selSkillIndex;
	bool _selectSkill;

	battleChar* _attackChar;

public:
	virtual HRESULT init(string imageName, int maxHp, int maxSp, int moveSpeed, int attackDamage, int imageY);
	void update(void);
	void render(void);
	void release(void);

	void resetTurn(bool turn);

	void hit(float stiffenTime);
	void attack(battleChar* target);
	void playSkill();

	void setSkill(void);
	void clearSkill(void) { _vSkill.clear(); }
	virtual void setAni(void);
	void clearAni(void) { _vAni.clear(); }

	void setUpperMove(bool move, int speed) { _moveYMove = true;  _upperMove = move; _upperSpeed = speed; }
	void setMap(battleMap* battleMap) { _battleMap = battleMap; }
	void setFriendOrFoe(bool friendOrFoe) { _friendOrFoe = friendOrFoe; _turnActivity = !friendOrFoe; }
	void setPos(POINT pos) { _posX = pos.x; _posY = pos.y; }
	void setRect();
	void setTrunActivity(bool turn) { _turnActivity = turn; }
	void setAnimation(int index);
	void setViewDirection(int view) { _viewDirection = view; }
	void setSkillTarget(battleChar* target);
	void setSkillIndex(int index) { _selSkillIndex = index; }
	void setSelectSkill(bool sel) { _selectSkill = sel; }

	int getSkillTargetCount();
	int getSkillCount() { return _vSkill.size(); }
	int getSkillSP(int index);
	int getCurHp() { return _curHp; }
	int getMaxHp() { return _maxHp; }
	int getCurSp() { return _curSp; }
	int getMaxSp() { return _maxSp; }
	int getAttackDamage() { return _attackDamage; }
	int getMoveSpeed() { return _moveSpeed; }
	bool getTrunActivity() { return _turnActivity; }
	bool getMoveActivity() { return _moveActivity; }
	bool getFriendOrFoe() { return _friendOrFoe; }
	bool getState() { return _state; }
	bool getMove() { return _move; }
	bool getAttack() { return _attack; }
	bool getDie() { return _die; }
	bool getSelectSkill() { return _selectSkill; }
	RECT getRect() { return _clickRect; }
	POINT getPos() { return PointMake(_posX, _posY); }
	POINT getSkillRange();
	string getSkillName(int index);
	string getFaceName() { return _faceImageName; }
	string getName() { return _charName; }
	vector<TILESTATE> getMoveTile() { return _moveTile; }
	vector<TILESTATE> getAttackTile() { return _attackTile; }

	void searchMoveTile();
	void searchMoveDirection(int moveTileIndex);
	void moveAttack(battleChar* target);

	void enemyMoveDirection();

	void increaseHp(int val);
	void increaseSp(int val);

	battleChar() {}
	~battleChar() {}
};

