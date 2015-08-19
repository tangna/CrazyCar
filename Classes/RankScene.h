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
	//���а񳡾�
	Button* btnBack;		//���ذ�ť
	LoadingBar* barMyScore;		//�ҵķ���������
	Text* textMyScore;	//�ҵķ����ı�
	Text* textPlayer;		//�����������
	LoadingBar*	barPlayer;		//������ҷ���������
	Text* textScore;		//������ҷ����ı�
	HttpRequest* request;
};

#endif // __RANK_SCENE_H__