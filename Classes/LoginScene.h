#ifndef __Login_SCENE_H__
#define __Login_SCENE_H__

#include "cocos2d.h"

class Login : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Login);
};

#endif // __Login_SCENE_H__
