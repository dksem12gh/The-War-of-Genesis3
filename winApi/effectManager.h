#pragma once
#include "singletonbase.h"

enum EFFECTKIND;
class effect;

class effectManager : public singletonBase<effectManager>
{
private:
	//이펙트 클래스를 담을 벡터
	typedef vector<effect*> arrEffects;
	typedef vector<effect*>::iterator iterEffects;
	//이펙트 클래스가 담겨있는 벡터를 담을 맵
	typedef map<string, arrEffects> arrEffect;
	typedef map<string, arrEffects>::iterator iterEffect;
	typedef vector<map<string, arrEffects>> arrTotalEffect;
	typedef vector<map<string, arrEffects>>::iterator iterTotalEffect;

private:
	arrTotalEffect _vTotalEffects;

	map<string, effect*> _mEffectList;
	map<string, effect*>::iterator _miEffectList;
	vector<effect*> _vEffect;
	vector<effect*>::iterator _viEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addEffect(string effectName, const char* imageName,
		int imageWidth, int imageHeight, int effectWidth, int effectHeight,
		int fps, int buffer,EFFECTKIND effectKind, string endEffect = "empty", int endEffectX = -1, int endEffectY = -1, int endAlpha = -1, int endZorder = -1);

	void play(string effectName, int x, int y, int alpha, int Zorder);
	void play(string effectName, int x, int y, int direction, int alpha, int Zorder);
	void play(string effectName, int x, int y, int endX, int endY, int alpha, int Zorder, int speedX = -1, int speedY = -1);
	void play(string effectName, int x, int y, int endX, int endY, int alpha, int Zorder, float interval, int speedX = -1, int speedY = -1);

	void stop(string effectName);

	effectManager() {}
	~effectManager() {}
};
