#include "RankScene.h"
//#include "GameScene.h"
#include "GameHomeScene.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/encodings.h"

#include "Network.h"

#define TITLE "赛车游戏提醒您"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;

Scene* RankScene::createScene()
{
	auto scene = Scene::create();
	auto layer = RankScene::create();
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool RankScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("RankScene.csb");

	/*
	btnBack = (Button*)rootNode->getChildByName("btnBack");
	btnBack->addTouchEventListener(this, toucheventselector(RankScene::backScene));
	addChild(btnBack);
	*/
	

	Text* textMyName = (Text*)rootNode->getChildByName("bgRank_1");
	//textMyName->setString("tangna");
	addChild(textMyName);

	barMyScore = (LoadingBar*)rootNode->getChildByName("barMyScore");
	barMyScore->setPercent(40);
	addChild(barMyScore);

	textMyScore = (Text*)rootNode->getChildByName("textMyScore");
	textMyScore->setString("454分");
	addChild(textMyScore);

	/*textPlayer = (Text*)rootNode->getChildByName("textPlayer");
	textPlayer->setString("tangna");
	addChild(textPlayer);

	barPlayer = (LoadingBar*)rootNode->getChildByName("otherLoadingBar");
	barPlayer->setPercent(23);
	addChild(barPlayer);

	textScore = (Text*)rootNode->getChildByName("otherScoreText");
	textScore->setString("978");
	addChild(textScore);
	*/
	addChild(rootNode);

	string urlBase = "http://www.mdnt-cn.com/api/crazycar/";
	Network *net = new Network();
	net->setUrl(urlBase);
	string operate = "RankList.php";
	net->initRank(operate);

	//进行请求
	request = new HttpRequest();
	request->setUrl(net->getUrl().c_str());
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(RankScene::RankCallback, this));
	HttpClient::getInstance()->send(request);

	//返回按钮
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto btBack = Button::create("fanhui.png");
	btBack->setPosition(Vec2(visibleSize.width / 10, 19 * visibleSize.height / 20));
	btBack->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, GameHome::createScene()));
		}
	});
	addChild(btBack);
	
	return true;
}

void RankScene::backScene()
{
	//Director::getInstance()->resume();
	Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f,GameHome::createScene()));
}

void RankScene::RankCallback(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response)
{
	std::vector<char> *data = response->getResponseData();
	data->push_back('\0');

	char *json = nullptr;
	json = (char *)malloc(data->size() + 1);
	memccpy(json, data->data(), 0, data->size() + 1);

	Document jsonDocment;

	jsonDocment.Parse<0>(json);

	int statusCode = jsonDocment["StatusCode"].GetInt();
	const char* message = jsonDocment["Message"].GetString();

	CCLOG("StatusCode:%d Message:%s", statusCode, message);
	if (statusCode == 0)
	{
		int size = jsonDocment["Body"]["Ranks"].Size();
		int maxScore = jsonDocment["Body"]["Ranks"][0]["Rank"].GetInt();
		for (int i = 0; i < size; i++)
		{
			int rank = jsonDocment["Body"]["Ranks"][i]["Rank"].GetInt();
			const char* name = jsonDocment["Body"]["Ranks"][i]["Name"].GetString();
			int score = jsonDocment["Body"]["Ranks"][i]["Score"].GetInt();

			LoadingBar *loadingBar = LoadingBar::create();
			loadingBar->loadTexture("jindutiao-yellow2.png");
			loadingBar->setPercent(score / maxScore);
			
			
			loadingBar->setPosition(ccp(377, 128 + i * 90));
			addChild(loadingBar);

			Text* text = Text::create();
			stringstream ss;
			string str;
			ss << score;
			ss >> str;
			string sscore = "分";
			text->setString(str + sscore);
			text->setContentSize(Size(100, 100));
			text->setFontSize(22);
			text->setPosition(ccp(630, 130 + i * 90));
			addChild(text);

			Text* nameText = Text::create();
			string n(name);
			nameText->setString(n);
			//nameText->setContentSize(Size(150, 150));
			nameText->setFontSize(22);
			nameText->setPosition(ccp(180, 140 + i * 90 + 30));
			addChild(nameText);
		}
	}
	else
	{
		MessageBox("返回出错", TITLE);
		return;
	}
}