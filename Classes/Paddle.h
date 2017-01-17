#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

//球与砖块的密度，弹力，摩擦
const PhysicsMaterial PHYSICS_MATERIAL_BALL_WORLD(1.0f, 1.0f, 0.0f);
//挡板的密度，弹力，摩擦
const PhysicsMaterial PHYSICS_MATERIAL_PADDLE(1.0f, 2.0f, 1.5f);
//关卡数
const int TASK_MAX = 3;

enum BodyType{
	Paddle,
	Ball,
	Target,
	DieLine
};

enum GameStatePaddle{
	WelcomePaddle,				//欢迎界面
	GamePaddle,					//游戏界面
	ResultPaddle,				//结果界面
	ExitPaddle					//退出
};

class PaddleScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(PaddleScene);
	//——————————————游戏主逻辑————————————————————
	//加载物理世界
	void initPhysicsWorld();
	//创建小球
	void createBall(Point pos);
	//创建挡板
	void createPaddle();
	//创建屏幕底线
	void createDieline();
	//触摸响应，控制挡板
	void touchLisener();
	//加载不同关卡中砖块位置
	void loadTask();
	//给砖块添加物理模型
	void addPhysicsRect(Node*parent);
	//碰撞响应
	void attachListener();

	//——————————————游戏场景控制————————————————————
	//关卡预览
	void loadPageList(Widget*uiroot);
	
	//跳转开始，欢迎，结果界面
	void setStart();
	void setWelcome();
	void setResult();
	
	//按钮
	void touchButton(Ref*ref,TouchEventType type);

	//游戏界面控制
	void gameControl(GameStatePaddle gamestate);


private:
	Size visibleSize;

	Sprite*m_ball;
	Sprite*m_paddle;
	
	//
	ui::PageView*m_taskPage;

	int m_taskSceneNum;
	//砖块数目
	int m_taskTargetNum;
};

#endif 