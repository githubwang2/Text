#ifndef __TOWERSCENE_H__
#define __TOWERSCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class TowerScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TowerScene);

	void start();

	void initBG();
	
	void makeMonster(float dt);

	void attachTowerBuild();
	
	void createTower(Point pos);

	

	Point worldToTile(Point &pos);
	std::string getValue(std::string key, Point&posIngl, TMXLayer*layer, TMXTiledMap*map);
private:
	Size visibleSize;

	TMXLayer*m_bulid;

	TMXTiledMap*m_tileMap;

	//应该是cocos2d的Vector其元素不能是结构体，可以用std::vector<Point> v；用std的vector。
	std::vector<Point>m_pathVec;

	std::vector<Point>getWalkPath(const char*key);

};

#endif 