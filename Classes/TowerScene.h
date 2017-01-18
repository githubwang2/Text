#ifndef __TOWERSCENE_H__
#define __TOWERSCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Components/Constants.h"
#include "FireManager.h"

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
	//--------------HUD
	//生成怪物波数
	void createWaveRusher();
	//金钱
	void changeGold(int num);
	//生命
	int changeLife(int num);		//返回life 因为要判定是否为0
	void removeMonster(Node*monster);

private:
	Size visibleSize;

	TMXLayer*m_bulid;

	TMXTiledMap*m_tileMap;

	//应该是cocos2d的Vector其元素不能是结构体，可以用std::vector<Point> v；用std的vector。
	std::vector<Point>m_pathVec;

	std::vector<Point>getWalkPath(const char*key);
	//--------------------------------
	FireManager*m_fireManager;

	//生成怪物的波数
	int m_curRound;
	//该波生成怪物的数量
	int m_monsterCreateLeft;

	int m_gold;

	int m_curLife;
};

#endif 