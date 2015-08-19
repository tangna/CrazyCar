#include "GameAboutScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameAbout::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameAbout::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameAbout::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("AboutScene.csb");

	addChild(rootNode);

	//·µ»Ø°´Å¥
	auto btnBack = (ui::Button*)rootNode->getChildByName("btnBack");
	btnBack->addTouchEventListener([](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->popScene();
		}
	});
	addChild(btnBack);

	return true;
}
