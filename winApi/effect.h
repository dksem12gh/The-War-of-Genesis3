#pragma once
#include "gameNode.h"

class image;
class animation;

enum EFFECTKIND
{
	DefaultEffect,
	DirectionEffect,
	ShootingEffect,
	EndureEffect,
	AfterImageEffect,
	DirectionAfterImageAlphaEffect,
	DirectionAlphaEffect
};

class effect : public gameNode
{
protected:
	float _x;							//이펙트의 위치 x
	float _y;							//이펙트의 위치 y

	int _endX;
	int _endY;

	int _direction;

	int _alpha;
	int _afterAlpha;
	int _Zorder;

	int _speed;
	int _fps;

	float _speedX;
	float _speedY;

	EFFECTKIND _effectKind;

	image*		_image;				//이펙트 이미지
	string		_imageName;
	string		_effectName;
	animation*	_animation;			//이펙트 애니메이션
	animation*	_curAnimation;
	bool		_isRunning;			//이펙트 실행되고 있는지

	float _interval;

	float _worldIntervalTimer; 
	float _intervalTimer;

	string _endEffect;
	int _endEffectX;
	int _endEffectY;
	int _endAlpha;
	int _endZorder;

public:
	HRESULT init(image* img, string imageName, EFFECTKIND effectKind, int frameW, int frameH, int fps, string endEffect = "empty", int endEffectX = -1, int endEffectY = -1, int endAlpha = -1, int endZorder = -1);
	void update(float elapsedTime);
	void render(void);
	void release(void);
	void stopRelease(void);

	void setAni();

	void start(int x, int y, int alpha, int Zorder);
	void start(int x, int y, int direction, int alpha, int Zorder);
	void start(int x, int y, int endX, int endY, int alpha, int Zorder, int speedX = -1 , int speedY = -1);
	void start(int x, int y, int endX, int endY, int alpha, int Zorder, float interval, int speedX = -1, int speedY = -1);
	void stop(void);

	bool getIsRunning(void) { return _isRunning; }

	string getEffectName(void) { return _effectName; }

	effect();
	~effect() {}
};

