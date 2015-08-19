#include "GameHomeScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CarGameScene.h"
#include "GameRankScene.h"
#include "GameAboutScene.h"
#include "RankScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;

Scene* GameHome::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameHome::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameHome::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("MenuScene.csb");

	addChild(rootNode);
	
	//��ʼ��Ϸ��ť
	auto btnStart= (Button*)rootNode->getChildByName("btnPlay");
	btnStart->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, CarGame::createScene()));	
		}
	});
	addChild(btnStart);

	//���а�ť
	auto btnRank = (Button*)rootNode->getChildByName("btnRank");
	btnRank->addTouchEventListener([](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, GameRank::createScene()));
			//Director::getInstance()->pushScene(GameRank::createScene());
			Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, RankScene::createScene()));
		}
	});
	addChild(btnRank);

	//���ð�ť
	auto btnSet = (Button*)rootNode->getChildByName("btnSetting");
	btnSet->addTouchEventListener([](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
		}
	});
	addChild(btnSet);

	//���ڰ�ť
	auto btnAbout = (Button*)rootNode->getChildByName("btnAbout");
	btnAbout->addTouchEventListener([](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, GameAbout::createScene()));
			Director::getInstance()->pushScene(GameAbout::createScene());
		}
	});
	addChild(btnAbout);

	return true;
}
