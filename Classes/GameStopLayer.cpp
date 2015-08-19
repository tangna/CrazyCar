#include "GameStopLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "CarGameScene.h"
#include "GameHomeScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace ui;

using namespace cocostudio::timeline;
/*
Scene* GameStopLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameStopLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
*/
// on "init" you need to initialize your instance
bool GameStopLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("StopLayer.csb");

	addChild(rootNode);

	//按钮重新开始
	auto btnRestart = (Button*)rootNode->getChildByName("btnRestart");
	btnRestart->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//
			//Director::getInstance()->replaceScene(GameScene::createScene);
			//Director::getInstance()->end();
			//this->removeFromParent();
			//this->getParent()->removeFromParent();
			Director::getInstance()->resume();
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			this->getParent()->unscheduleUpdate();
			Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, CarGame::createScene()));
			
		}
	});
	addChild(btnRestart);

	//按钮恢复
	auto btnResume = (Button*)rootNode->getChildByName("btnResume");
	btnResume->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//
			//Director::getInstance()->replaceScene(GameScene::createScene);
			Director::getInstance()->resume();
			//removeChildByName("stopLayer",true);
			//_isRemoveStopLayer = true;
			this->removeFromParent();
		}
	});
	addChild(btnResume);

	//按钮返回主界面
	auto btnBackToMenu = (Button*)rootNode->getChildByName("btnBackToMenu");
	btnBackToMenu->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->resume();
			this->getParent()->unscheduleUpdate();
			Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, GameHome::createScene()));
			//Director::getInstance()->replaceScene(GameHome::createScene());
		}
	});
	addChild(btnBackToMenu);

	return true;
}
