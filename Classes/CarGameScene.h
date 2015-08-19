#ifndef __CarGame_SCENE_H__
#define __CarGame_SCENE_H__

#include "cocos2d.h"
#include "GameStopLayer.h"

USING_NS_CC;

class CarGame : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float delta);
	virtual void onEnter();//һ��ȥ��Ϸ��ʾ����
	void updateBackground(float delta);//��������
	void collisionDetection();//��ײ���
	void carControl();//���ӿ��ƣ���Ҫ�����ҷ���
	void setCarPosition(bool isMove, int derection);
	void produceEnemyCar();//�����ϰ���С��
	//void enemyCarMove();
	void removeEnemyCar();

	void gameOver();
	void showScores();

	CREATE_FUNC(CarGame);
protected:
	int _count;//������

	int _screenWidth;
	int _screenHeight;

	bool _isMove;
	int _derection;

	Sprite* _car;

	Sprite* _background1;
	Sprite* _background2;//�����������

	int _bgSpeed;//���������ٶ�

	Label* _labelScores;
	Vector<Sprite*> _enemyCarVec;

};

#endif // __CarGame_SCENE_H__