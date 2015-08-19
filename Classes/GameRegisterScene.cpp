#include "GameRegisterScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "HttpNetConn.h"
#include "GameHomeScene.h"

#include "LoginScene.h"
USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;

Scene* GameRegister::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameRegister::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameRegister::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("RegisterScene.csb");

	addChild(rootNode);

	//ÕËºÅÊäÈë¿ò
	auto account = (TextField*)rootNode->getChildByName("textAcc");
	addChild(account);

	//ÃÜÂëÊäÈë¿ò
	auto password = (TextField*)rootNode->getChildByName("textPwd");
	addChild(password);

	//ÃÜÂëÈ·ÈÏ¿ò
	auto confirmpw = (TextField*)rootNode->getChildByName("textConfirmPwd");
	addChild(confirmpw);

	//×¢²á°´Å¥¿ò
	NetConnect* nc = new NetConnect;

	auto btnRegister = (Button*)rootNode->getChildByName("btnRegsiter");
	btnRegister->addTouchEventListener([=](Ref* pSender,ui::Widget::TouchEventType type){
		if (type==ui::Widget::TouchEventType::ENDED)
		{
			if (nc->registerNewUser(account->getString(), password->getString(), confirmpw->getString()))
			{
				Director::getInstance()->replaceScene( GameHome::createScene());
			}
			else{
				MessageBox("´´½¨Ê§°Ü", "");
			}
			
		}
	});
	addChild(btnRegister);
	//·µ»Ø¿ò
	auto btnback = (Button*)rootNode->getChildByName("btnBack");
	btnback->addTouchEventListener([](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, Login::createScene()));
		}
	});
	addChild(btnback);

	return true;
}
