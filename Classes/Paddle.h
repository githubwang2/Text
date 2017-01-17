#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

//����ש����ܶȣ�������Ħ��
const PhysicsMaterial PHYSICS_MATERIAL_BALL_WORLD(1.0f, 1.0f, 0.0f);
//������ܶȣ�������Ħ��
const PhysicsMaterial PHYSICS_MATERIAL_PADDLE(1.0f, 2.0f, 1.5f);
//�ؿ���
const int TASK_MAX = 3;

enum BodyType{
	Paddle,
	Ball,
	Target,
	DieLine
};

enum GameStatePaddle{
	WelcomePaddle,				//��ӭ����
	GamePaddle,					//��Ϸ����
	ResultPaddle,				//�������
	ExitPaddle					//�˳�
};

class PaddleScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(PaddleScene);
	//������������������������������Ϸ���߼�����������������������������������������
	//������������
	void initPhysicsWorld();
	//����С��
	void createBall(Point pos);
	//��������
	void createPaddle();
	//������Ļ����
	void createDieline();
	//������Ӧ�����Ƶ���
	void touchLisener();
	//���ز�ͬ�ؿ���ש��λ��
	void loadTask();
	//��ש���������ģ��
	void addPhysicsRect(Node*parent);
	//��ײ��Ӧ
	void attachListener();

	//������������������������������Ϸ�������ơ���������������������������������������
	//�ؿ�Ԥ��
	void loadPageList(Widget*uiroot);
	
	//��ת��ʼ����ӭ���������
	void setStart();
	void setWelcome();
	void setResult();
	
	//��ť
	void touchButton(Ref*ref,TouchEventType type);

	//��Ϸ�������
	void gameControl(GameStatePaddle gamestate);


private:
	Size visibleSize;

	Sprite*m_ball;
	Sprite*m_paddle;
	
	//
	ui::PageView*m_taskPage;

	int m_taskSceneNum;
	//ש����Ŀ
	int m_taskTargetNum;
};

#endif 