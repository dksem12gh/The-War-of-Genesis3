#include "stdafx.h"
#include "effect.h"
#include "image.h"
#include "animation.h"

effect::effect() : _image(NULL),
				   _animation(NULL),
				   _isRunning(false),
				   _x(0), _y(0)
{
}

HRESULT effect::init(image* img, string imageName, EFFECTKIND effectKind, int frameW, int frameH, int fps, string endEffect, int endEffectX, int endEffectY, int endAlpha, int endZorder)
{
	if (!img) return E_FAIL;

	//활성화 여부
	_isRunning = false;

	_image = img;
	_imageName = imageName;
	_effectName = imageName;

	_effectKind = effectKind;

	//애니메이션 객체가 없으면 생성
	if (!_animation) _animation = new animation;

	_animation->init(_image->getWidth(), _image->getHeight(), frameW, frameH);

	if (_effectKind == EndureEffect)
	{
		_animation->setDefPlayFrame(false, true);
	}
	else
	{
		_animation->setDefPlayFrame(false, false);
	}

	_animation->setFPS(fps);
	_fps = fps;
	_animation->stop();

	_endEffect = endEffect;
	_endEffectX = endEffectX;
	_endEffectY = endEffectY;
	_endAlpha = endAlpha;
	_endZorder = endZorder;

	return S_OK;
}

void effect::release(void)
{
	_image = NULL;
	SAFE_DELETE(_animation);
}

void effect::stopRelease(void)
{
	SAFE_DELETE(_curAnimation);
}

void effect::setAni()
{
	_curAnimation = new animation;
	_curAnimation->init(_image->getWidth(), _image->getHeight(), _animation->getFrameWidth(), _animation->getFrameHeight());
	if (_effectKind == EndureEffect || _effectKind == ShootingEffect)
	{
		_curAnimation->setDefPlayFrame(false, true);
	}
	else
	{
		_curAnimation->setDefPlayFrame(false, false);
	}
	_curAnimation->setFPS(_fps);
}

void effect::update(float elapsedTime)
{
	//활성화 되어 있지 않으면 실행불가
	if (!_isRunning) return;
	_curAnimation->frameUpdate(elapsedTime);

	if (_effectKind == DirectionAlphaEffect || _effectKind == DirectionAfterImageAlphaEffect)
	{
		_alpha -= 5;
	}

	if (_effectKind == ShootingEffect)
	{
		if (_endX - _speedX < _x && _x < _endX + _speedX)
		{
			_x = _endX;
		}
		else if (_x > _endX) _x -= _speedX;
		else if (_x < _endX) _x += _speedX;

		if (_endY - _speedY < _y && _y < _endY + _speedY)
		{
			_y = _endY;
		}
		else if (_y > _endY) _y -= _speedY;
		else if (_y < _endY) _y += _speedY;

		if (_x == _endX && _y == _endY)
		{
			stop();
		}
	}
	else if (_effectKind == AfterImageEffect || _effectKind == DirectionAfterImageAlphaEffect)
	{
		_worldIntervalTimer = TIMEMANAGER->getWorldTime();
		if (_worldIntervalTimer - _intervalTimer >= _interval)
		{
			_intervalTimer = TIMEMANAGER->getWorldTime();
			if (_speedX > 0 && _endX - _speedX < _x && _x < _endX + _speedX)
			{
				_x = _endX;
			}
			else if (_speedX < 0 && _endX + _speedX < _x && _x < _endX - _speedX)
			{
				_x = _endX;
			}
			else _x += _speedX;

			if (_speedY > 0 && _endY - _speedY < _y && _y < _endY + _speedY)
			{
				_y = _endY;
			}
			else if (_speedY < 0 && _endY + _speedY < _y && _y < _endY - _speedY)
			{
				_y = _endY;
			}
			else _y += _speedY;

			char effectName[64];
			wsprintf(effectName, "%s%d", _imageName.c_str(), 1);

			if (_effectKind == DirectionAfterImageAlphaEffect)
			{
				EFFECTMANAGER->play(effectName, _x, _y, _direction, _afterAlpha, _Zorder);
			}
			else
			{
				EFFECTMANAGER->play(effectName, _x, _y, _afterAlpha, _Zorder);
			}
			if (_x == _endX && _y == _endY)
			{
				stop();
				if (_endEffect != "empyt")
				{
					EFFECTMANAGER->play(_endEffect, _x + _endEffectX, _y + _endEffectY, _endAlpha, _endZorder);
				}
			}
		}
	}

	if (_alpha <= 0 && _effectKind != DirectionAfterImageAlphaEffect)
	{
		_alpha = 0;
		stop();
	}

	//이펙트 애니메이션이 종료 되었으면 정지
	if (!_curAnimation->isPlay() && _effectKind != AfterImageEffect && _effectKind != ShootingEffect && _effectKind != DirectionAfterImageAlphaEffect &&
		_effectKind != DirectionAlphaEffect) stop();
}

void effect::render(void)
{
	if (!_isRunning) return;

	//_image->aniRender(getMemDC(), _x, _y, _animation);
	CAMERA->addRenderInfo(_imageName, PointMake(_x, _y), 0, 0, _Zorder, ANIALPHARENDER, -1, -1, _curAnimation, 0, _alpha);
}

void effect::start(int x, int y, int alpha, int Zorder)
{
	//초기화가 되어 있지 않으면 실행불가
	if (!_image || !_animation) return;

	setAni();

	_x = x;
	_y = y;

	_effectKind = DefaultEffect;
	_isRunning = true;
	_curAnimation->start();

	_alpha = alpha;

	_Zorder = Zorder;
}

void effect::start(int x, int y, int direction, int alpha, int Zorder)
{
	//초기화가 되어 있지 않으면 실행불가
	if (!_image || !_animation) return;

	setAni();

	_x = x;
	_y = y;

	_isRunning = true;

	int frameYcount = _image->getWidth() / _image->getFrameWidth();
	
	_curAnimation->setPlayFrame(frameYcount * direction, frameYcount * (direction + 1) - 1, false);
	_curAnimation->start();

	_alpha = alpha;

	_Zorder = Zorder;
}

void effect::start(int x, int y, int endX, int endY, int alpha, int Zorder, int speedX, int speedY)
{
	//초기화가 되어 있지 않으면 실행불가
	if (!_image || !_animation) return;

	setAni();

	_x = x;
	_y = y;

	_endX = endX;
	_endY = endY;

	_effectKind = ShootingEffect;

	if (speedX == -1)
	{
		_speedX = getDistance(_x, 0, _endX, 0) / 80;
		_speedY = getDistance(0, _y, 0, _endY) / 80;
	}
	else
	{
		_speedX = speedX;
		_speedY = speedY;
	}

	_isRunning = true;
	_curAnimation->setDefPlayFrame(false, true);
	_curAnimation->start();

	_alpha = alpha;

	_Zorder = Zorder;
}

void effect::start(int x, int y, int endX, int endY, int alpha, int Zorder, float interval, int speedX, int speedY)
{
	if (!_image || !_animation) return;

	setAni();

	_x = x;
	_y = y;

	_endX = endX;
	_endY = endY;

	if (_effectKind == DirectionAfterImageAlphaEffect)
	{
		float angle = getAngle(x, y, endX, endY);

		if (0.785398185f <= angle && angle < 2.35619450f)
		{
			_direction = 0;
		}
		else if (2.35619450f <= angle && angle < 3.92699099f)
		{
			_direction = 1;
		}
		else if (3.92699099f <= angle && angle < 5.49778748f)
		{
			_direction = 3;
		}
		else
		{
			_direction = 2;
		}


		int frameYcount = _image->getWidth() / _image->getFrameWidth();
		
		_curAnimation->setPlayFrame(frameYcount * _direction, frameYcount * (_direction + 1) - 1, false);

		_speedX = cos(angle) * 30;
		_speedY = -sin(angle) * 30;
	}
	else if (speedX == -1)
	{
		
	}
	else
	{
		_speedX = speedX;
		_speedY = speedY;
	}

	_isRunning = true;
	if (_effectKind != DirectionAfterImageAlphaEffect)
	{
		_curAnimation->setDefPlayFrame(false, false);
	}
	_curAnimation->start();

	_afterAlpha = _alpha = alpha;

	_Zorder = Zorder;

	_interval = interval;

	_worldIntervalTimer = TIMEMANAGER->getWorldTime();
	_intervalTimer = TIMEMANAGER->getWorldTime();
}

void effect::stop(void)
{
	_isRunning = false;
}