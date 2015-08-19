#include "GameRankScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameHomeScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameRank::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameRank::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameRank::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("RankScene.csb");

	addChild(rootNode);

	//¹ØÓÚ°´Å¥
	auto btnBack = (ui::Button*)rootNode->getChildByName("btnBack");
	btnBack->addTouchEventListener([](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, GameHome::createScene()));
			//Director::getInstance()->popScene();
		}
	});
	addChild(btnBack);
	return true;
}
