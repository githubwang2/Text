#include "Tower/Components/ComTower.h"

USING_NS_CC;


ComTower::ComTower()
:m_isFiring(false)
{
	setName("ComTower");
}


ComTower*ComTower::create()
{
	ComTower*ret = new ComTower();
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

void ComTower::onEnter(){
	m_range = 100;			//�ӵ�������Χ
	m_reloadTime = 0.3;		//�ӵ��������ʱ��
}

int ComTower::getRange() const
{
	return m_range;
}