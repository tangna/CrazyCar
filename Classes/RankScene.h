#ifndef __RANK_SCENE_H__
#define __RANK_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"

using  namespace cocos2d;
using namespace ui;
using namespace cocos2d::network;
using namespace rapidjson;

class RankScene : public cocos2d::Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(RankScene);

	void backScene();
	void RankCallback(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response);
private:
	//排行榜场景
	Button* btnBack;		//返回按钮
	LoadingBar* barMyScore;		//我的分数进度条
	Text* textMyScore;	//我的分数文本
	Text* textPlayer;		//其它玩家名字
	LoadingBar*	barPlayer;		//其它玩家分数进度条
	Text* textScore;		//其它玩家分数文本
	HttpRequest* request;
};

#endif // __RANK_SCENE_H__