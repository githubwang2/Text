#ifndef __TOWERSCENE_H__
#define __TOWERSCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Tower/Components/Constants.h"
#include "Tower/FireManager.h"

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

	//加载背景 瓦片地图 HUD
	void initBG();
	//生成怪物
	void makeMonster(float dt);
	//触摸响应及在该点创建防御塔
	void attachTowerBuild();
	void createTower(Point pos);

	Point worldToTile(Point &pos);		//cocos2dx坐标  转化为  Tiled坐标 （y轴相反）
	//取该瓦片 在该瓦片地图   该层  的属性 
	std::string getValue(std::string key, Point&posIngl, TMXLayer*layer, TMXTiledMap*map);
	//--------------HUD
	//生成怪物波数
	void createWaveRusher();
	//金钱
	void changeGold(int num);
	//生命
	int changeLife(int num);		//返回life 因为要判定是否为0
	void removeMonster(Node*monster);

	//结果菜单
	void endGame(bool isWin);
	void touchButton(Ref *object, TouchEventType type);

private:
	Size visibleSize;
	
	TMXLayer*m_bulid;				//瓦片地图

	TMXTiledMap*m_tileMap;			//瓦片地图中 可以放置防御塔的对象层meta

	//应该是cocos2d的Vector其元素不能是结构体，可以用std的vector。
	std::vector<Point>m_pathVec;	//怪物行走的路径信息
	//从walk对象层中取出每个点的位置
	std::vector<Point>getWalkPath(const char*key);

	//--------------------------------
	FireManager*m_fireManager;

	//生成怪物的波数
	int m_curRound;
	//该波生成怪物的数量
	int m_monsterCreateLeft;

	int m_gold = 0;

	int m_curLife = 0;
};

#endif 