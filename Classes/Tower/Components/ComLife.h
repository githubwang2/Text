#ifndef __Monster_ComLife_H__
#define __Monster_ComLife_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"

//怪物的HP组件
class ComLife :public cocos2d::Component
{
protected:
	ComLife(int maxLife);

public:
	//满HP
	static ComLife*create(int maxLife);

	virtual void onEnter() override;
	bool attacked(int damage);


private:

	cocos2d::ui::LoadingBar*m_hpBar;
	float m_maxLife;
	float m_currentHp;		//	当前HP

};

#endif