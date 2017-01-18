#include "Components/ComMove.h"
#include"TowerScene.h"

USING_NS_CC;

ComMove::ComMove(std::vector<Point>path){
	setName("ComMove");
	m_path = path;
}

ComMove*ComMove::create(std::vector<cocos2d::Point> path){
	ComMove*ret = new ComMove(path);
	if (ret!=nullptr && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

void ComMove::initPath(std::vector<cocos2d::Point> path)
{
	if (path.size() == 0)
	{
		return;
	}
	Vector<FiniteTimeAction*>act;
	m_startPos = path.at(0);
	for (int i = 1; i < path.size(); i++)
	{
		float dur = path.at(i - 1).getDistance(path.at(i));
		float time = dur / NORMAL_SPEED;
		act.pushBack(MoveTo::create(time, path.at(i)));
	}
	//----------------------------------------------------
	act.pushBack(CallFunc::create([=](){
		auto playground = dynamic_cast<TowerScene*>(getOwner()->getParent());
		auto curLife=playground->changeLife(-2);
		if (curLife <= 0){
			CCLOG("END");
		}
		//消除走到尽头的怪物
		playground->removeMonster(getOwner());
	}));
	m_moveActions = Sequence::create(act);
}

void ComMove::onEnter(){
	initPath(m_path);
}

void ComMove::startMove(){
	auto owner = getOwner();
	if (!m_moveActions)
	{
		CCLOG("no m_moveActions");
		return;
	}

	owner->setPosition(m_startPos);
	owner->runAction(m_moveActions);
}
