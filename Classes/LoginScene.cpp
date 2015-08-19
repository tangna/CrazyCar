#include "LoginScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameHomeScene.h"
#include "GameRegisterScene.h"
#include "HttpNetConn.h"


USING_NS_CC;
using namespace ui;

using namespace cocostudio::timeline;

Scene* Login::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Login::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Login::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("LoginScene.csb");

	addChild(rootNode);

	//ÕËºÅ¿ò
	auto account = (TextField*)rootNode->getChildByName("textAcc");
	addChild(account);

	//ÃÜÂë¿ò
	auto password = (TextField*)rootNode->getChildByName("textPwd");
	addChild(password);

	//µÇÂ½°´Å¥
	NetConnect* nc = new NetConnect;

	auto btnLogin = (Button*)rootNode->getChildByName("btnLogin");
	addChild(btnLogin);
	btnLogin->addTouchEventListener([=](Ref* pSender,Widget::TouchEventType type){

		if (type==ui::Widget::TouchEventType::ENDED)
		{
			if (account->getString().length()>0&&password->getString().length()>0)
			{
				if (nc->checkLogin(account->getString(), password->getString()))
				{
					Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, GameHome::createScene()));
					//MessageBox("welcome!!!!%s", nc->getUid().c_str());
					//myData::getInstance()->setUid(nc->getUid());
				}
			}
			else
			{
				//MessageBox("please input usename&pwd", "");
			}
			//Director::getInstance()->replaceScene(GameScene::createScene);
		}
	});

	//Íü¼ÇÃÜÂë
	auto btnForgetPassword = (Button*)rootNode->getChildByName("btnForgetPwd");
	addChild(btnForgetPassword);

	//ÓÃ»§×¢²á
	auto btnRegister = (Button*)rootNode->getChildByName("btnRegister");
	btnRegister->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, GameRegister::createScene()));
		}
	});
	addChild(btnRegister);

	return true;
}
