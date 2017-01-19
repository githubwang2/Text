#ifndef __Tower_ComMove_H__
#define __Tower_ComMove_H__
#include "cocos2d.h"


const float NORMAL_SPEED = 150.0f;			//�����ƶ��ٶ�
//���������ƶ�
class ComMove:public cocos2d::Component
{
protected:
	ComMove(std::vector<cocos2d::Point>path);		//�ƶ�·���ϵ����е�

public:
	static ComMove*create(std::vector<cocos2d::Point> path);
	virtual void onEnter() override;
	
	//������ʼ�㲢��ʼ�ƶ�
	void startMove();

private:
	//�����ƶ�·���ϵ����е� Ϊ��ʼ���Լ������ƶ��Ķ�����ֵ
	void initPath(std::vector<cocos2d::Point> path);
	//��ʼ��
	cocos2d::Point m_startPos;
	//�����ƶ��Ķ���
	cocos2d::Action*m_moveActions;
	//�ƶ�·���ϵ����е�
	std::vector<cocos2d::Point>m_path;

};

#endif