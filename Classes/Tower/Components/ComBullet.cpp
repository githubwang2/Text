#include "Tower/Components/ComBullet.h"

USING_NS_CC;

ComBullet::ComBullet(float fireDamage, float speed){
	setName("ComBullet");
	m_fireDamage = fireDamage;
	m_speed = speed;
}


ComBullet*ComBullet::create(float fireDamage, float speed){
	ComBullet*ret = new ComBullet(fireDamage, speed);
	if (ret!=nullptr&&ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

void ComBullet::onEnter(){

}

//----------------------
//子弹旋转角度
//----------------------
float ComBullet::setSpeedXY(Point org, Point des){
	Point diff = des - org;
	float dis = diff.getLength();
	float sinx = diff.x / dis;
	float cosx = diff.y / dis;

	m_speedX = m_speed*sinx;		//子弹速度X轴上的分量
	m_speedY = m_speed*cosx;		//子弹速度Y轴上的分量

	float angleRadians = atanf(diff.x / diff.y);
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	if (angleDegrees<0)
	{
		angleDegrees = -1 * angleDegrees;
	}
	if (diff.y<0)
	{
		angleDegrees = 180 - angleDegrees;
	}
	if (diff.x<0)
	{
		angleDegrees = -1 * angleDegrees;
	}
	return angleDegrees;
}