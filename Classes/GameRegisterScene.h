#ifndef __GameRegister_SCENE_H__
#define __GameRegister_SCENE_H__

#include "cocos2d.h"

class GameRegister : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameRegister);
};

#endif // __GameRegister_SCENE_H__
