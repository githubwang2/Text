



#include "Tower/FireManager.h"

bool FireManager::init(){
	if (!Layer::init())
	{
		return false;
	}

	schedule(schedule_selector(FireManager::moveBullet));

	return true;
}

void FireManager::moveBullet(float dt){
	if (m_tmpMonster.size() > 0)
	{
		for (auto tmp : m_tmpMonster)
		{
			m_monsters.pop_front();
			tmp->getOwner()->removeFromParent();
		}
		m_tmpMonster.clear();
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();

	bool hitMonster = false;			//子弹是否已经打中怪物

	//bullets

	for (auto bullet : m_bullets)
	{
		hitMonster = false;
		auto owner = bullet->getOwner();
		Point realPos = Point(bullet->getSpeedX() + owner->getPositionX(),    //子弹现在的坐标加上速度
			bullet->getSpeedY() + owner->getPositionY());
		for (auto monster : m_monsters)
		{
			auto distance = realPos.getDistance(monster->getOwner()->getPosition());
			if (distance < monster->getOwner()->getContentSize().width / 2) 
			{
				//如果子弹命中怪物   
				//怪物掉血   
				//hitMonster为true
				//怪物死亡 移除怪物
				auto comLife = dynamic_cast<ComLife*>(monster->getOwner()->getComponent("ComLife"));
				bool isDead = comLife->attacked(bullet->getFireDamage());
				hitMonster = true;
				if (isDead)
				{
					monster->getOwner()->removeFromParent();
					m_monsters.remove(monster);
					break;
				}
			}
		}
		//如果子弹命中怪物  或者子弹飞出屏幕  移除子弹
		if (hitMonster || visibleSize.width < realPos.x || visibleSize.height <realPos.y || 0 > realPos.x || 0>realPos.y)
		{
			owner->removeFromParent();
			m_bullets.remove(bullet);
			break;
		}
		else
		{
			owner->setPosition(realPos);
		}
	}

	//tower
	for (auto tower : m_towers)
	{
		auto owner = tower->getOwner();
		if (tower->getIsFire())
		{
			continue;
		}
		else
		{
			int fireRange = tower->getRange();
			Point towerPos = tower->getOwner()->getPosition();
			for (auto monster : m_monsters)
			{
				if (towerPos.getDistance(monster->getOwner()->getPosition()) <= fireRange)
				{
					Sprite* bullet = Sprite::create("Tower/Bullet.png");
					bullet->setPosition(owner->getPosition());
					auto comBullet = ComBullet::create(bullet_damage, bullet_speed);
					bullet->addComponent(comBullet);
					m_bullets.push_back(comBullet);

					float angle = comBullet->setSpeedXY(owner->getPosition(), monster->getOwner()->getPosition());

					owner->getParent()->addChild(bullet, 2);
					tower->setIsFire(true);
					runAction(Sequence::create(DelayTime::create(tower->getRelodTime()),
						CallFunc::create([=]{
						tower->setIsFire(false);
					}), nullptr));

					bullet->setRotation(angle);				//子弹旋转对准怪物
					owner->setRotation(angle);				//防御塔旋转对准怪物
					break;
				}
			}
		}
	}
}
		


