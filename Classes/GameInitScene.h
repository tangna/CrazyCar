#ifndef __GameInit_SCENE_H__
#define __GameInit_SCENE_H__

#include "cocos2d.h"

class GameInit : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void toLoginScene(float delta);
	CREATE_FUNC(GameInit);
};

#endif // __GameInit_SCENE_H__