#include "Tower/TowerScene.h"
#include"Menu/MenuScene.h"



Scene* TowerScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TowerScene::create();
	scene->addChild(layer);
	return scene;
}

bool TowerScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	start();
	
	m_fireManager = FireManager::create();
	addChild(m_fireManager);

	return true;
}

void TowerScene::initBG(){
	//����
	auto spriteBG = Sprite::create("Tower/background.png");
	spriteBG->setPosition(visibleSize / 2);
	spriteBG->setScale(visibleSize.width / spriteBG->getContentSize().width,
		visibleSize.height / spriteBG->getContentSize().height);
	addChild(spriteBG, -1);

	//��Ƭ��ͼ
	m_tileMap = TMXTiledMap::create("Tower/TowerTileMap/gate1.tmx");
	addChild(m_tileMap, -1);

	//Hud    
	auto hud = GUIReader::getInstance()->widgetFromJsonFile("Tower/HUD/HUD.json");
	hud->setTag(1);
	addChild(hud, 2);
}

void TowerScene::start(){
	
	initBG();

	//���ù�����ƶ�·��
	 m_pathVec = getWalkPath("Walk");
	 //���ÿ������÷�����������
	 m_bulid = m_tileMap->getLayer("meta");
	 m_bulid->setVisible(false);
	 attachTowerBuild();

	 

	 //���ó�ʼ ����Ϊ1  ��Ǯ600  ����30
	 m_curRound = 1;
	 changeGold(600);
	 changeLife(30);

	 //��ʼ��������������
	 createWaveRusher();

	 
}

std::vector<Point>TowerScene::getWalkPath(const char*key){
	std::vector<Point>pathVec;
	if (!m_tileMap)
	{
		CCLOG("can't find map");
		return pathVec;
	}
	
	TMXObjectGroup*walk = m_tileMap->getObjectGroup(key);
	
	if (!walk)
	{
		CCLOG("no such key = %s", key);
		return pathVec;
	}

	ValueVector path = walk->getObjects();

	int myX = 0;
	int myY = 0;
	for (auto pos:path)
	{
		myX = pos.asValueMap()["x"].asInt();
		myY = pos.asValueMap()["y"].asInt();
		pathVec.push_back(Point(myX, myY));
	}
	return pathVec;
}

void TowerScene::makeMonster(float dt){

	Sprite *monster = Sprite::create("Tower/Monster.png");
	/*auto path=m_pathVec ;
	if (path.size()==0)
	{
		return;
	}
	Vector<FiniteTimeAction*>act;
	auto starPos = path.at(0);
	for ( int i = 1; i < path.size();i++)
	{
		float dur = path.at(i - 1).getDistance(path.at(i));
		float time = dur / 100.0f;
		act.pushBack(MoveTo::create(time, path.at(i)));
	}
	monster->setPosition(starPos);
	auto act2 = Sequence::create(act);
	monster->runAction(act2);
	*/
	//���ع���HP���
	auto comLife = ComLife::create(monster_hp);
	monster->addComponent(comLife);
	//���ع����ƶ����
	auto comMove = ComMove::create(m_pathVec);
	monster->addComponent(comMove);
	comMove->startMove();
	//����FireManager��m_monsters list��
	m_fireManager->m_monsters.push_back(comMove);
	//-----------------------------------------------------------
	//ÿ����һ������ò������һ��Ϊ0ֹͣ�������
	//������1
	m_monsterCreateLeft--;
	if (m_monsterCreateLeft==0)
	{
		unschedule(schedule_selector(TowerScene::makeMonster));
		runAction(Sequence::create(DelayTime::create(3 + m_curRound),
			CallFunc::create([=](){
			m_curRound++;
			createWaveRusher();
		})
			,nullptr));
	}

	addChild(monster, 1);
}

void TowerScene::attachTowerBuild(){
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [=](Touch *pTouch, Event *pEvent){return true;};
	listener->onTouchEnded = [=](Touch *pTouch, Event *pEvent){
		auto touchPos = pTouch->getLocation();
		createTower(touchPos);
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void TowerScene::createTower(Point pos){
	//ͨ������ȡ���������Ƭ������ ���ĵ���÷�����
	int offestX = -(int)pos.x % (int)m_tileMap->getTileSize().width +
		m_tileMap->getTileSize().width / 2;
	int offestY = -(int)pos.y % (int)m_tileMap->getTileSize().height +
		m_tileMap->getTileSize().height / 2;
	auto blockCenter = Point((int)(pos.x + offestX), (int)(pos.y + offestY));

	std::string str = getValue("Build", pos, m_bulid, m_tileMap); //����ֵΪTrue ��õ���Է��÷�����
	if (str.size() != 0)
	{
		CCLOG("answer:%s", str.c_str());
		if (str.compare("True") == 0)
		{
			if (m_gold < 150)		//�жϽ�Ǯ�Ƿ��㹻 ����ʱ��Ǯ��� �޷�����������
			{
				auto goldLable = dynamic_cast<Widget*>(getChildByTag(1))->getChildByName("LabelGold");
				auto toRed = TintBy::create(0.5f, -127, -255, -127);
				goldLable->runAction(Sequence::create(toRed, toRed->reverse(), nullptr));
				return;//���� ��������������ͼƬ
			}
			else                   ///��Ǯ�㹻  �۳���Ǯ  ����������
			{
				changeGold(-150);

				Sprite*tower = Sprite::create("Tower/Tower.png");
				tower->setPosition(blockCenter);

				//��comTower���ص�ÿ��tower��
				auto comTower = ComTower::create();
				tower->addComponent(comTower);
				//����FireManager��m_towers list��
				m_fireManager->m_towers.push_back(comTower);
				//-----------------
				addChild(tower, 2);
				return;//���� ��������������ͼƬ
			}

		}
	}
	Sprite*errorPos = Sprite::create("Tower/ErrorPos.png");
	errorPos->setPosition(blockCenter);
	addChild(errorPos, 2);
	auto action = Sequence::create(FadeOut::create(3), CallFunc::create([=]{
		errorPos->removeFromParent(); }), NULL);
	errorPos->runAction(action);
	return;
}


Point TowerScene::worldToTile(Point &pos){
	int x = pos.x / m_tileMap->getTileSize().width;
	int y = (m_tileMap->getContentSize().height - pos.y) /
		m_tileMap->getTileSize().height;
	
	return Point(x, y);
}

std::string TowerScene::getValue(std::string key, Point&posIngl, TMXLayer*layer, TMXTiledMap*map){
	Point pos = worldToTile(posIngl);
	int tileGID = layer->getTileGIDAt(pos);
	if (tileGID)
	{
		Value pro = map->getPropertiesForGID(tileGID);
		auto map = pro.asValueMap();
		auto pos = map.find(key);
		if (pos != map.end())
		{
			return pos->second.asString();
		}
		else
		{
			return "";
		}
	}
	else
	{
		return "";
	}
}

//----------------------------------HUD
void TowerScene::createWaveRusher(){
	//- ����
	auto hud = dynamic_cast<Widget*>(this->getChildByTag(1));
	auto waveLabel = dynamic_cast<TextAtlas*>(hud->getChildByName("LableWave"));
	char num[32] = { 0 };
	sprintf(num, "%d", m_curRound);
	waveLabel->setStringValue(num);

	m_monsterCreateLeft = 1 + m_curRound * 2;
	schedule(schedule_selector(TowerScene::makeMonster), 0.5f);
}
 

void TowerScene::changeGold(int num){
	auto hud = dynamic_cast<Widget*>(this->getChildByTag(1));
	auto gold = dynamic_cast<TextAtlas*>(hud->getChildByName("LabelGold"));
	char numStr[32] = { 0 };
	m_gold += num;
	sprintf(numStr, "%d", m_gold);
	gold->setStringValue(numStr);
}

int TowerScene::changeLife(int num){
	auto hud = dynamic_cast<Widget*>(this->getChildByTag(1));
	auto life = dynamic_cast<TextAtlas*>(hud->getChildByName("LableLife"));
	char numStr[32] = { 0 };
	m_curLife += num;
	sprintf(numStr, "%d", m_curLife);
	life->setStringValue(numStr);
	return m_curLife;
}

void TowerScene::removeMonster(Node*monster){
	auto comMove = dynamic_cast<ComMove*>(monster->getComponent("ComMove"));
	//���뻺��
	m_fireManager->m_tmpMonster.push_back(comMove);
}

void TowerScene::endGame(bool isWin){
	m_fireManager->unscheduleUpdate();
	unscheduleAllSelectors();

	auto resultDlg = GUIReader::getInstance()->widgetFromJsonFile("Tower/ResultDlg/ResultDlg.json");
	auto btnReturn = dynamic_cast<Button*>(resultDlg->getChildByName("DlgBK")->getChildByName("btnReturn"));
	btnReturn->addTouchEventListener(this, toucheventselector(TowerScene::touchButton));
	
	auto lblWin = resultDlg->getChildByName("DlgBK")->getChildByName("lblWin");
	auto lblFail = resultDlg->getChildByName("DlgBK")->getChildByName("lblFail");

	if (isWin)
	{
		lblWin->setVisible(true);
		lblFail->setVisible(false);
	}
	else
	{
		lblWin->setVisible(false);
		lblFail->setVisible(true);
	}
	addChild(resultDlg, 3);
}

void TowerScene::touchButton(Ref *object, TouchEventType type){
	auto transScene = TransitionProgressInOut::create(1, MenuScene::createScene());
	Director::getInstance()->replaceScene(transScene);
}