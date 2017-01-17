#include "TowerScene.h"

#include "Components/ComMove.h"
#include "Components/ComBullet.h"
#include "Components/ComTower.h"
#include "Components/ComLife.h"


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

	m_bulid = m_tileMap->getLayer("meta");
	m_bulid->setVisible(false);

	attachTowerBuild();

	return true;
}

void TowerScene::initBG(){
	auto spriteBG = Sprite::create("Tower/background.png");
	spriteBG->setPosition(visibleSize / 2);
	spriteBG->setScale(visibleSize.width / spriteBG->getContentSize().width,
		visibleSize.height / spriteBG->getContentSize().height);
	addChild(spriteBG, -1);
}

void TowerScene::start(){
	initBG();

	 m_tileMap = TMXTiledMap::create("Tower/TowerTileMap/gate1.tmx");
	 addChild(m_tileMap, -1);

	 m_pathVec = getWalkPath("Walk");

	 schedule(schedule_selector(TowerScene::makeMonster), 1.0f);
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
	auto comLife = ComLife::create(30);
	monster->addComponent(comLife);
	auto comMove = ComMove::create(m_pathVec);
	monster->addComponent(comMove);
	comMove->startMove();
	addChild(monster, 1);
}

void TowerScene::attachTowerBuild(){
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [=](Touch *pTouch, Event *pEvent)
	{
		return true;
	};

	listener->onTouchEnded = [=](Touch *pTouch, Event *pEvent)
	{
		auto touchPos = pTouch->getLocation();
		createTower(touchPos);
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void TowerScene::createTower(Point pos){

	int offestX = -(int)pos.x % (int)m_tileMap->getTileSize().width +
		m_tileMap->getTileSize().width / 2;
	int offestY = -(int)pos.y % (int)m_tileMap->getTileSize().height +
		m_tileMap->getTileSize().height / 2;
	auto blockCenter = Point((int)(pos.x + offestX), (int)(pos.y + offestY));

	std::string str = getValue("Build", pos, m_bulid, m_tileMap);


	if (str.size()!=0)
	{
		CCLOG("answer:%s", str.c_str());
		if (str.compare("True")==0)
		{
			Sprite*tower = Sprite::create("Tower/Tower.png");
			tower->setPosition(blockCenter);
			addChild(tower, 2);
			return;
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

