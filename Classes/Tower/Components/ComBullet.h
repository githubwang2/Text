#ifndef __Tower_ComBullet_H__
#define __Tower_ComBullet_H__

#include "cocos2d.h"



//�������ӵ����

class ComBullet :public cocos2d::Component
{
protected:
	//�ӵ��˺����ӵ��ٶ�
	ComBullet(float fireDamage, float speed);

public:
	
	static ComBullet*create(float fireDamage, float speed);

	virtual void onEnter() override;

	// ��������   ���������
	//���� �ӵ���׼���� ������ת�Ƕ�
	float setSpeedXY(cocos2d::Point org, cocos2d::Point des);

	CC_SYNTHESIZE_READONLY(float, m_speedX, SpeedX);					//�ӵ��ٶ�X���ϵķ���
	CC_SYNTHESIZE_READONLY(float, m_speedY, SpeedY);					//�ӵ��ٶ�Y���ϵķ���
	CC_SYNTHESIZE_READONLY(float, m_fireDamage, FireDamage);


private:
	float m_speed;
};

#endif