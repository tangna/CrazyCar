#ifndef __GameAbout_SCENE_H__
#define __GameAbout_SCENE_H__

#include "cocos2d.h"

class GameAbout : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameAbout);
};

#endif // __GameAbout_SCENE_H__
