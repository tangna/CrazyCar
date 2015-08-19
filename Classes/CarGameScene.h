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
	virtual void onEnter();//一进去游戏显示画面
	void updateBackground(float delta);//背景滚动
	void collisionDetection();//碰撞检测
	void carControl();//车子控制，主要是左右方向
	void setCarPosition(bool isMove, int derection);
	void produceEnemyCar();//生成障碍物小车
	//void enemyCarMove();
	void removeEnemyCar();

	void gameOver();
	void showScores();

	CREATE_FUNC(CarGame);
protected:
	int _count;//计数器

	int _screenWidth;
	int _screenHeight;

	bool _isMove;
	int _derection;

	Sprite* _car;

	Sprite* _background1;
	Sprite* _background2;//定义滚动背景

	int _bgSpeed;//背景滚动速度

	Label* _labelScores;
	Vector<Sprite*> _enemyCarVec;

};

#endif // __CarGame_SCENE_H__