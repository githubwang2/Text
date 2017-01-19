#ifndef __Tower_ComBullet_H__
#define __Tower_ComBullet_H__

#include "cocos2d.h"



//防御塔子弹组件

class ComBullet :public cocos2d::Component
{
protected:
	//子弹伤害，子弹速度
	ComBullet(float fireDamage, float speed);

public:
	
	static ComBullet*create(float fireDamage, float speed);

	virtual void onEnter() override;
	//塔的坐标   怪物的坐标
	float setSpeedXY(cocos2d::Point org, cocos2d::Point des);

	CC_SYNTHESIZE_READONLY(float, m_speedX, SpeedX);
	CC_SYNTHESIZE_READONLY(float, m_speedY, SpeedY);
	CC_SYNTHESIZE_READONLY(float, m_fireDamage, FireDamage);


private:
	float m_speed;
};

#endif