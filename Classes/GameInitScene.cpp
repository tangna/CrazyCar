#include "GameInitScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "LoginScene.h"

USING_NS_CC;
using namespace ui;

using namespace cocostudio::timeline;

Scene* GameInit::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameInit::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameInit::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("InitScene.csb");

	addChild(rootNode);
	
	scheduleOnce(schedule_selector(GameInit::toLoginScene),1.2f);
	/*
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event){
		return true;
	};
	listener->onTouchEnded = [](Touch* touch, Event* event){
		Director::getInstance()->replaceScene(Login::createScene());
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	*/
	return true;
}
void GameInit::toLoginScene(float delta)
{
	Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f,Login::createScene()));
}