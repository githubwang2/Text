#include "Paddle/Paddle.h"

Scene* PaddleScene::createScene(){
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));
	auto layer = PaddleScene::create();
	scene->addChild(layer);
	return scene;
}

 bool PaddleScene::init(){
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	gameControl(WelcomePaddle);

	return true;
}

 void PaddleScene::initPhysicsWorld(){
	 auto edgedgeSprite = Sprite::create();
	 auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICS_MATERIAL_BALL_WORLD,3);
	 edgedgeSprite->setPhysicsBody(body);
	 edgedgeSprite->setPosition(visibleSize / 2);
	 addChild(edgedgeSprite);
 }

 void PaddleScene::createBall(Point pos){
	 m_ball = Sprite::create("Paddle/ball.png");
	 m_ball->setPosition(pos);
	 addChild(m_ball, 1);

	 auto ballBody = PhysicsBody::createCircle(m_ball->getContentSize().width / 2,
		 PHYSICS_MATERIAL_BALL_WORLD);
	 ballBody->setVelocityLimit(600);
	
	 ballBody->setVelocity(Vec2(600, 800));
	 m_ball->setPhysicsBody(ballBody);

	 ballBody->setContactTestBitmask(0xFFFFFFFF);
 }

 void PaddleScene::createPaddle(){
	 m_paddle = Sprite::create("Paddle/paddle.png");
	 m_paddle->setPosition(visibleSize.width / 2, m_paddle->getContentSize().height / 2);
	 addChild(m_paddle, 1);
	 //改成多边形算了。。。
	 //auto paddleBody = PhysicsBody::createPolygon( ,5,PHYSICS_MATERIAL_PADDLE);
	 auto paddleBody = PhysicsBody::createBox(m_paddle->getContentSize(), PHYSICS_MATERIAL_PADDLE);
	 paddleBody->setDynamic(false);
	 m_paddle->setPhysicsBody(paddleBody);
	 paddleBody->setContactTestBitmask(0xFFFFFFFF);

	 touchLisener();
 }

 void PaddleScene::touchLisener(){
	 auto listener = EventListenerTouchOneByOne::create();

	 listener->onTouchBegan = [=](Touch *pTouch, Event *pEvent)
	 {
		 return true;
	 };

	 listener->onTouchMoved = [=](Touch *pTouch, Event *pEvent)
	 {
		 auto offset = pTouch->getDelta();
		 auto newPos = m_paddle->getPosition() + offset;
		 if (newPos.x<m_paddle->getContentSize().width / 2) {
			 newPos.x = m_paddle->getContentSize().width / 2;
		 }
		 else if (newPos.x>visibleSize.width - m_paddle->getContentSize().width / 2)
		 {
			 newPos.x = visibleSize.width - m_paddle->getContentSize().width / 2;
		 }
		 m_paddle->setPosition(newPos.x, m_paddle->getPositionY());
	 };

	 Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
 }

 void PaddleScene::createDieline(){
	 auto dieLine = Sprite::create();
	 auto dieLineBody = PhysicsBody::createEdgeBox(Size(visibleSize.width, 6),
		 PHYSICS_MATERIAL_BALL_WORLD, 6);
	 dieLineBody->setTag(DieLine);
	 dieLine->setPosition(visibleSize.width / 2, 3);
	 dieLine->setPhysicsBody(dieLineBody);
	 dieLineBody->setContactTestBitmask(0xFFFFFFFF);
	 
	 addChild(dieLine, 1);
 }



 void PaddleScene::loadTask(){
	 char name[32] = {0};
	 sprintf(name, "Paddle/publish/taskScene%d.json", m_taskSceneNum);
	 auto taskScene1 = SceneReader::getInstance()->
		 createNodeWithSceneFile(name);
	 addChild(taskScene1, 1);
	 auto realTask = static_cast<ComRender*>(taskScene1->
		 getChildByTag(10003)->getComponent("GUIComponent"))->getNode();

	 addPhysicsRect(realTask->getChildByTag(5));
	 
	 attachListener();
 }


 void PaddleScene::addPhysicsRect(Node*parent){
	 for (auto child : parent->getChildren())
	 {
		 auto blickBody = PhysicsBody::createBox(child->getContentSize(), PHYSICS_MATERIAL_BALL_WORLD);
		 blickBody->setDynamic(false);
		 blickBody->setContactTestBitmask(0xFFFFFFFF);
		 blickBody->setTag(Target);
		 child->setPhysicsBody(blickBody);

		 m_taskTargetNum++;
	 }
 }

 void PaddleScene::attachListener(){
	 EventListenerPhysicsContact* hitListener = EventListenerPhysicsContact::create();

	 hitListener->onContactBegin = [=](const PhysicsContact& contact)
	 {
		 auto tagA = contact.getShapeA()->getBody()->getTag();
		 auto tagB = contact.getShapeB()->getBody()->getTag();

		 if (tagA == Target || tagB == Target)
		 {
			 Node* block = nullptr;
			 if (tagA == Target) {
				 block = contact.getShapeA()->getBody()->getNode();
			 }
			 else
			 {
				 block = contact.getShapeB()->getBody()->getNode();
			 }
			 block->removeFromParent();
			 m_taskTargetNum--;
			 if (m_taskTargetNum==0)
			 {
				 gameControl(ResultPaddle);
			 }
		 }
		 else if (tagA == DieLine || tagB == DieLine)
		 {
			 gameControl(ResultPaddle);
		 }
		 return true;
	 };
	 Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(hitListener, this);
 }



 void PaddleScene::loadPageList(Widget*uiroot){
	 m_taskPage = dynamic_cast<PageView*>(uiroot->getChildByName("taskList"));
	 char name[32] = { 0 };
	 for (int i = 1; i <=TASK_MAX;++i)
	 {
		 memset(name, 0, sizeof(name));
		 sprintf(name, "Paddle/publish/task%d.json", i);
		 auto task = dynamic_cast<Widget*>(GUIReader::getInstance()->widgetFromJsonFile(name));
		 task->setScale(0.5);
		 m_taskPage->addWidgetToPage(task, i - 1, true);
	 }
 }

 void PaddleScene::setStart(){
	 initPhysicsWorld();
	 createBall(visibleSize * 3 / 4);
	 createPaddle();
	 createDieline();
	 loadTask();
 }

 void PaddleScene::setWelcome(){
	 auto welcome = dynamic_cast<Widget*>(GUIReader::getInstance()
		 ->widgetFromJsonFile("Paddle/publish/Welcome.json"));
	 welcome->setPosition(Point::ZERO);
	 
	 loadPageList(welcome);

	 auto start = dynamic_cast<Widget*>(welcome->getChildByName("Start"));
	 start->addTouchEventListener(this, toucheventselector(PaddleScene::touchButton));
	 addChild(welcome, 1);
 }

 void PaddleScene::setResult(){
	 auto result = dynamic_cast<Widget*>(GUIReader::getInstance()->widgetFromJsonFile("Paddle/GameOverDlg/GameOverDlg.json"));
	 result->setPosition(visibleSize/2);
	 result->setScale(0.5);
	 result->setAnchorPoint(Point::ANCHOR_MIDDLE);
	 TextBMFont* text = dynamic_cast<TextBMFont*>(result->getChildByName("background")->getChildByName("lblGameOver"));
	 if (m_taskTargetNum == 0)
	 {
		text->setText("You Win!!");
	 }
	 else
	 {
		 text->setText("You Lose...");
	 }



	 auto start = dynamic_cast<Widget*>(result->getChildByName("background")->getChildByName("Restart"));
	 start->addTouchEventListener(this, toucheventselector(PaddleScene::touchButton));

	
	 auto back = dynamic_cast<Widget*>(result->getChildByName("background")->getChildByName("Exit"));
	 back->addTouchEventListener(this, toucheventselector(PaddleScene::touchButton));

	 addChild(result, 2);

 }

 void PaddleScene::touchButton(Ref*ref, TouchEventType type){
	 if (type == TOUCH_EVENT_ENDED)
	 {
		 auto buttonName = dynamic_cast<Widget*>(ref)->getName();
		 if (buttonName=="Start")
		 {
			 gameControl(GamePaddle);
		 }
		 else if (buttonName == "Restart"){
			 gameControl(WelcomePaddle);
		 }
		 else if (buttonName == "Exit")
		 {
			 gameControl(ExitPaddle);
		 }
 }
 }

 void PaddleScene::gameControl(GameStatePaddle gamestate){
	 switch (gamestate)
	 {
	 case WelcomePaddle:
	 {
						   removeAllChildren();
						   setWelcome();
						   break;
	 }
	 case GamePaddle:
	 {
						//这东西必须写在removeAllChildren之前 m_taskPage会为默认值
						m_taskSceneNum = (int)m_taskPage->getCurPageIndex() + 1;
						removeAllChildren();
					
						Director::getInstance()->getEventDispatcher()->removeAllEventListeners();

						setStart();
						break;
	 }
	 case ResultPaddle:
	 {
						  removeAllChildren();
						  Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
						  Director::getInstance()->getRunningScene()->getPhysicsWorld()->removeAllBodies();
						  
						  setResult();
						  break; 
	 }
	 case ExitPaddle:
	 {
						Director::getInstance()->end();
						  break;
	 }
	 default:
	 {
				break; 
	 }
	 }
 }