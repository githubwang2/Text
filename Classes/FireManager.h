#include "Components/Constants.h"

USING_NS_CC;

//防御塔子弹管理(移动和碰撞)
class FireManager:public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(FireManager);

	void moveBullet(float dt);

public:
	std::list<ComBullet*>	m_bullets;
	std::list<ComTower*>	m_towers;;
	std::list<ComMove*>		m_monsters;

	//--
	std::list<ComMove*>m_tmpMonster;
	
};

