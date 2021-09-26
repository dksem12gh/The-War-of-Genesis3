#pragma once
#include "gameNode.h"

class mainGame : public gameNode
{
private:
	bool _cursorLock;

	float _renderTimer;
	float _worldRenderTimer;

	float _updateTimer;
	float _worldUpdateTimer;

	float _mouseFrameX;
public:
	HRESULT init(void);
	void release(void);
	void update();
	void render(float);
	
	mainGame() {}
	~mainGame() {}
};

