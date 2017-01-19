#include "Menu/MenuScene.h"

#include"Paddle/Paddle.h";
#include"Piano/Piano.h";
#include"Plane/PlaneScene.h";
#include"Tower/TowerScene.h";


#define  NORMAL_MENU		"MENU/normal_menu.png"
#define  PRESS_MENU			"MENU/press_menu.png"

#define FONT_MENU			"Marker Felt"

#define PIANO				"piano"
#define PLANE				"plane"
#define PADDLE				"paddle"
#define TOWER				"tower"
#define QUIT				"quit"

const int Btn_FontSize = 20;
const int Btn_Width = 222;
const int Btn_Height = 50;

const int Btn_Piano_Game_TAG = 10001;
const int Btn_Plane_Game_TAG = 10002;
const int Btn_Paddle_Game_TAG = 10003;
const int Btn_Tower_Game_TAG = 10004;
const int Btn_Quit_Game_TAG = 10005;


Scene*MenuScene::createScene(){
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init(){
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

	//5¸ö°´Å¥Î»ÖÃ
	Point Btn_Piano_Game_POS = Point(visibleSize.width / 4, visibleSize.height * 3 / 4);
	Point Btn_Plane_Game_POS = Point(visibleSize.width * 3 / 4, visibleSize.height * 3 / 4);
	Point Btn_Paddle_Game_POS = Point(visibleSize.width / 4, visibleSize.height / 2);
	Point Btn_Tower_Game_POS = Point(visibleSize.width * 3 / 4, visibleSize.height / 2);
	Point Btn_Quit_Game_POS = Point(visibleSize.width / 2, visibleSize.height / 2 - 120);


	addMenuSprite(PIANO, Btn_Piano_Game_POS, Btn_Piano_Game_TAG);

	addMenuSprite(PLANE, Btn_Plane_Game_POS, Btn_Plane_Game_TAG);

	addMenuSprite(PADDLE, Btn_Paddle_Game_POS, Btn_Paddle_Game_TAG);

	addMenuSprite(TOWER, Btn_Tower_Game_POS, Btn_Tower_Game_TAG);

	addMenuSprite(QUIT, Btn_Quit_Game_POS, Btn_Quit_Game_TAG);

	return true;
}

void MenuScene::addMenuSprite(std::string name, Point pos, int tag){
	Scale9Sprite* btnNormal = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite* btnPress = Scale9Sprite::create(PRESS_MENU);
	LabelTTF *btnGameTTf = LabelTTF::create(name, FONT_MENU, Btn_FontSize);

	ControlButton* gameBtn = ControlButton::create(btnGameTTf, btnNormal);
	gameBtn->setBackgroundSpriteForState(btnPress, Control::State::HIGH_LIGHTED);
	gameBtn->setPosition(pos);
	gameBtn->setPreferredSize(Size(Btn_Width, Btn_Height));
	gameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	gameBtn->setTag(tag);
	addChild(gameBtn, 1);

}



void MenuScene::menuTouchDown(Object* pSender, Control::EventType event){
	ControlButton*button = (ControlButton*)pSender;
	int tag = button->getTag();
	switch (tag)
	{
	case Btn_Piano_Game_TAG:{
								auto transScene = TransitionFadeTR::create(1, Piano::createScene());
								Director::getInstance()->replaceScene(transScene);
								break; }
	case Btn_Plane_Game_TAG:{
								auto transScene = TransitionTurnOffTiles::create(1, PlaneScene::createScene());
								Director::getInstance()->replaceScene(transScene);
								break; }
	case Btn_Paddle_Game_TAG:{
								 auto transScene = TransitionSlideInL::create(1, PaddleScene::createScene());
								 Director::getInstance()->replaceScene(transScene);
								 break; }
	case Btn_Tower_Game_TAG:{
								auto transScene = TransitionProgressOutIn::create(1, TowerScene::createScene());
								Director::getInstance()->replaceScene(transScene);
								break; }
	case Btn_Quit_Game_TAG:{
							   Director::getInstance()->end();
							   break; }


	default:
		break;
	}
}
