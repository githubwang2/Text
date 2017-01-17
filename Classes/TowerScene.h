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

	//Ӧ����cocos2d��Vector��Ԫ�ز����ǽṹ�壬������std::vector<Point> v����std��vector��
	std::vector<Point>m_pathVec;

	std::vector<Point>getWalkPath(const char*key);

};

#endif 