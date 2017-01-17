#ifndef __Tower_ComMove_H__
#define __Tower_ComMove_H__
#include "cocos2d.h"


const float NORMAL_SPEED = 150.0f;

class ComMove:public cocos2d::Component
{
protected:
	ComMove(std::vector<cocos2d::Point>path);

public:
	static ComMove*create(std::vector<cocos2d::Point> path);
//-------------------
	virtual void onEnter() override;
//---------------------------------------------------
	void startMove();

private:
	void initPath(std::vector<cocos2d::Point> path);
	cocos2d::Point m_startPos;
	cocos2d::Action*m_moveActions;


private:
	std::vector<cocos2d::Point>m_path;

};

#endif