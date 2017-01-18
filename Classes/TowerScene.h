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
	//���ɹ��ﲨ��
	void createWaveRusher();
	//��Ǯ
	void changeGold(int num);
	//����
	int changeLife(int num);		//����life ��ΪҪ�ж��Ƿ�Ϊ0
	void removeMonster(Node*monster);

private:
	Size visibleSize;

	TMXLayer*m_bulid;

	TMXTiledMap*m_tileMap;

	//Ӧ����cocos2d��Vector��Ԫ�ز����ǽṹ�壬������std::vector<Point> v����std��vector��
	std::vector<Point>m_pathVec;

	std::vector<Point>getWalkPath(const char*key);
	//--------------------------------
	FireManager*m_fireManager;

	//���ɹ���Ĳ���
	int m_curRound;
	//�ò����ɹ��������
	int m_monsterCreateLeft;

	int m_gold;

	int m_curLife;
};

#endif 