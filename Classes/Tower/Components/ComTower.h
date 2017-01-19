#ifndef __Tower_ComTower_H__
#define __Tower_ComTower_H__

#include "cocos2d.h"

class ComTower :public cocos2d::Component
{
protected:
	ComTower();

public:

	static ComTower*create();

	virtual void onEnter() override;

	
	CC_SYNTHESIZE(bool, m_isFiring, IsFire);				//���Ƿ񿪻�
	CC_PROPERTY_READONLY(int, m_range, Range);				//���Ĺ�����Χ
	CC_SYNTHESIZE_READONLY(float, m_reloadTime, RelodTime);	//���Ĺ������


private:

};

#endif