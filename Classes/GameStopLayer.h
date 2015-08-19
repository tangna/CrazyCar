#ifndef __GameStopLayer_SCENE_H__
#define __GameStopLayer_SCENE_H__

#include "cocos2d.h"

class GameStopLayer : public cocos2d::Layer
{
public:
	//static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameStopLayer);
};

#endif // __GameStopLayer_SCENE_H__
