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

	//���ر��� ��Ƭ��ͼ HUD
	void initBG();
	//���ɹ���
	void makeMonster(float dt);
	//������Ӧ���ڸõ㴴��������
	void attachTowerBuild();
	void createTower(Point pos);

	Point worldToTile(Point &pos);		//cocos2dx����  ת��Ϊ  Tiled���� ��y���෴��
	//ȡ����Ƭ �ڸ���Ƭ��ͼ   �ò�  ������ 
	std::string getValue(std::string key, Point&posIngl, TMXLayer*layer, TMXTiledMap*map);
	//--------------HUD
	//���ɹ��ﲨ��
	void createWaveRusher();
	//��Ǯ
	void changeGold(int num);
	//����
	int changeLife(int num);		//����life ��ΪҪ�ж��Ƿ�Ϊ0
	void removeMonster(Node*monster);

	//����˵�
	void endGame(bool isWin);
	void touchButton(Ref *object, TouchEventType type);

private:
	Size visibleSize;
	
	TMXLayer*m_bulid;				//��Ƭ��ͼ

	TMXTiledMap*m_tileMap;			//��Ƭ��ͼ�� ���Է��÷������Ķ����meta

	//Ӧ����cocos2d��Vector��Ԫ�ز����ǽṹ�壬������std��vector��
	std::vector<Point>m_pathVec;	//�������ߵ�·����Ϣ
	//��walk�������ȡ��ÿ�����λ��
	std::vector<Point>getWalkPath(const char*key);

	//--------------------------------
	FireManager*m_fireManager;

	//���ɹ���Ĳ���
	int m_curRound;
	//�ò����ɹ��������
	int m_monsterCreateLeft;

	int m_gold = 0;

	int m_curLife = 0;
};

#endif 