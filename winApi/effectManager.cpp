#include "StdAfx.h"
#include "effectManager.h"
#include "effect.h"

HRESULT effectManager::init(void)
{
	return S_OK;
}

void effectManager::release(void)
{
	iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���� �˻�
	/*vIter = _vTotalEffects.begin();
	for (vIter; vIter != _vTotalEffects.end(); ++vIter)
	{
		mIter = vIter->begin();
		for (mIter; mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				iterEffects vArrIter = mIter->second.begin();
				for (vArrIter; vArrIter != mIter->second.end();)
				{
					(*vArrIter)->release();
					SAFE_DELETE(*vArrIter);
					vArrIter = mIter->second.erase(vArrIter);
				}
			}
			else
			{
				++mIter;
			}
		}
	}

	_vTotalEffects.clear();*/

	for (_miEffectList = _mEffectList.begin(); _miEffectList != _mEffectList.end(); _miEffectList++)
	{
		_miEffectList->second->release();
		SAFE_DELETE(_miEffectList->second);
	}
	_mEffectList.clear();

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); _viEffect++)
	{
		(*_viEffect)->stopRelease();
		SAFE_DELETE(*_viEffect);
	}
	_vEffect.clear();
}

void effectManager::update(void)
{
	/*iterTotalEffect vIter;
	iterEffect mIter;
	
	float elapsed = TIMEMANAGER->getElapsedTime();

	//����Ʈ�� ��� �־�� ���� �˻�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->update(elapsed);
			}
		}
	}*/

	float elapsed = TIMEMANAGER->getElapsedTime();

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end();)
	{
		(*_viEffect)->update(elapsed);
		if (!(*_viEffect)->getIsRunning())
		{
			(*_viEffect)->stopRelease();
			SAFE_DELETE((*_viEffect));
			_viEffect = _vEffect.erase(_viEffect);
		}
		else
		{
			++_viEffect;
		}
	}
}

void effectManager::render(void)
{
	/*iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���� �˻�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{				
				(*vArrIter)->render();
			}
		}
	}*/

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->render();
	}
}

void effectManager::addEffect(string effectName, const char* imageName,
	int imageWidth, int imageHeight, int effectWidth, int effectHeight,
	int fps, int buffer, EFFECTKIND effectKind, string endEffect, int endEffectX, int endEffectY, int endAlpha, int endZorder)
{
	/*image* img;
	arrEffects vEffectBuffer;		//����Ʈ ���۸� ��´�
	arrEffect mArrEffect;			//Ű���� ���� ����Ʈ�� ��´�


	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	else	//�̹��� ������ �߰�
	{
		//img = IMAGEMANAGER->addImage(imageName, imageName, imageWidth, imageHeight, true, RGB(255, 0, 255));
		return;
	}

	//����Ʈ ���ͷ� Ǫ��
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, imageName, effectKind, img->getFrameWidth(), img->getFrameHeight(), fps);
	}

	//����Ʈ ���۸� �ʿ� ��´�
	mArrEffect.insert(make_pair(effectName, vEffectBuffer));

	_vTotalEffects.push_back(mArrEffect);*/

	image* img;
	effect* ef = new effect;

	img = IMAGEMANAGER->findImage(imageName);
	ef->init(img, imageName, effectKind, img->getFrameWidth(), img->getFrameHeight(), fps, endEffect, endEffectX, endEffectY, endAlpha, endZorder);
	_mEffectList.insert(make_pair(effectName, ef));
}

void effectManager::play(string effectName, int x, int y, int alpha, int Zorder)
{
	/*iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���� �˻�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//����Ʈ �̸��� ���ؼ� ���� ������ ���� ������ �Ѿ��
			if (!(effectName == mIter->first)) break;

			//����Ʈ Ű�� ��ġ�ϸ� ����Ʈ�� ����
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->start(x, y, alpha, Zorder);
				return;
			}
		}
	}*/

	_miEffectList = _mEffectList.find(effectName);

	if (_miEffectList == _mEffectList.end()) return;
	
	effect* ef = new effect;
	*ef = *(_miEffectList->second);
	ef->start(x, y, alpha, Zorder);
	_vEffect.push_back(ef);
	_viEffect = _vEffect.begin();
}

void effectManager::play(string effectName, int x, int y, int direction, int alpha, int Zorder)
{
	/*iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���� �˻�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//����Ʈ �̸��� ���ؼ� ���� ������ ���� ������ �Ѿ��
			if (!(effectName == mIter->first)) break;

			//����Ʈ Ű�� ��ġ�ϸ� ����Ʈ�� ����
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->start(x, y, direction, alpha, Zorder);
				return;
			}
		}
	}*/

	_miEffectList = _mEffectList.find(effectName);

	if (_miEffectList == _mEffectList.end()) return;

	effect* ef = new effect;
	*ef = *(_miEffectList->second);
	ef->start(x, y, direction, alpha, Zorder);
	_vEffect.push_back(ef);
	_viEffect = _vEffect.begin();
}

void effectManager::play(string effectName, int x, int y, int endX, int endY, int alpha, int Zorder, int speedX, int speedY)
{
	/*iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���� �˻�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//����Ʈ �̸��� ���ؼ� ���� ������ ���� ������ �Ѿ��
			if (!(effectName == mIter->first)) break;

			//����Ʈ Ű�� ��ġ�ϸ� ����Ʈ�� ����
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->start(x, y, endX, endY, alpha, Zorder, speedX, speedY);
				return;
			}
		}
	}*/

	_miEffectList = _mEffectList.find(effectName);

	if (_miEffectList == _mEffectList.end()) return;

	effect* ef = new effect;
	*ef = *(_miEffectList->second);
	ef->start(x, y, endX, endY, alpha, Zorder, speedX, speedY);
	_vEffect.push_back(ef);
}

void effectManager::play(string effectName, int x, int y, int endX, int endY, int alpha, int Zorder, float interval, int speedX, int speedY)
{
	/*iterTotalEffect vIter;
	iterEffect mIter;

	//����Ʈ�� ��� �־�� ���� �˻�
	for (vIter = _vTotalEffects.begin(); vIter != _vTotalEffects.end(); ++vIter)
	{
		//��Ż����Ʈ ���� �ȿ� �ִ� ���� ����Ʈ Ű �˻�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//����Ʈ �̸��� ���ؼ� ���� ������ ���� ������ �Ѿ��
			if (!(effectName == mIter->first)) break;

			//����Ʈ Ű�� ��ġ�ϸ� ����Ʈ�� ����
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->start(x, y, endX, endY, alpha, Zorder, speedX, speedY, interval);
				return;
			}
		}
	}*/

	_miEffectList = _mEffectList.find(effectName);

	if (_miEffectList == _mEffectList.end()) return;

	effect* ef = new effect;
	*ef = *(_miEffectList->second);
	ef->start(x, y, endX, endY, alpha, Zorder, interval, speedX, speedY);
	_vEffect.push_back(ef);
}

void effectManager::stop(string effectName)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		if ((*_viEffect)->getEffectName() == effectName)
		{
			(*_viEffect)->stop();
		}
	}
}
