#ifndef __Monster_ComLife_H__
#define __Monster_ComLife_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"

class ComLife :public cocos2d::Component
{
protected:
	ComLife(int maxLife);

public:

	static ComLife*create(int maxLife);

	virtual void onEnter() override;
	bool attacked(int damage);


private:

	cocos2d::ui::LoadingBar*m_hpBar;
	float m_maxLife;
	float m_currentHp;

};

#endif