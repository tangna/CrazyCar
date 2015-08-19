#ifndef __GameHome_SCENE_H__
#define __GameHome_SCENE_H__

#include "cocos2d.h"

class GameHome : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameHome);
};

#endif // __GameHome_SCENE_H__
