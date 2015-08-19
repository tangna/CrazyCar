#ifndef __GameRank_SCENE_H__
#define __GameRank_SCENE_H__

#include "cocos2d.h"

class GameRank : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameRank);
};

#endif // __GameRank_SCENE_H__
