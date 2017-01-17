#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class MenuScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(MenuScene);

private:

	void addMenuSprite(std::string name, Point pos, int tag);
	void menuTouchDown(Object* pSender, Control::EventType event);

	Size visibleSize;
};

#endif 
