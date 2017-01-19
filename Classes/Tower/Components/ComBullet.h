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

	// 塔的坐标   怪物的坐标
	//返回 子弹对准怪物 所需旋转角度
	float setSpeedXY(cocos2d::Point org, cocos2d::Point des);

	CC_SYNTHESIZE_READONLY(float, m_speedX, SpeedX);					//子弹速度X轴上的分量
	CC_SYNTHESIZE_READONLY(float, m_speedY, SpeedY);					//子弹速度Y轴上的分量
	CC_SYNTHESIZE_READONLY(float, m_fireDamage, FireDamage);


private:
	float m_speed;
};

#endif