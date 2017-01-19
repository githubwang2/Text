#include "Tower/Components/Constants.h"

USING_NS_CC;

//�������ӵ�����(�ƶ�����ײ)
class FireManager:public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(FireManager);

	//�ӵ��ƶ�
	void moveBullet(float dt);

public:
	std::list<ComBullet*>	m_bullets;
	std::list<ComTower*>	m_towers;;
	std::list<ComMove*>		m_monsters;

	
	std::list<ComMove*>m_tmpMonster;
	
};

