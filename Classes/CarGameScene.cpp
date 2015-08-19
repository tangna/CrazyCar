#include "CarGameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "GameRankScene.h"
#include "GameHomeScene.h"
#include "HttpNetConn.h"
#include "RankScene.h"


USING_NS_CC;
using namespace ui;

using namespace cocostudio::timeline;


Scene* CarGame::createScene()
{
// 'scene' is an autorelease object
auto scene = Scene::create();

// 'layer' is an autorelease object
auto layer = CarGame::create();

// add layer as a child to scene
scene->addChild(layer);

// return the scene
return scene;
}

// on "init" you need to initialize your instance
bool CarGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_screenWidth = visibleSize.width;
	_screenHeight = visibleSize.height;

	_count = 0;
	_bgSpeed = 5;
	_isMove = false;
	_derection = 0;

	carControl();

	this->scheduleUpdate();
	//this->schedule(schedule_selector(CarGame::updateBackground));
	Device::setAccelerometerEnabled(true);
	return true;
}

void CarGame::onEnter()
{
	Layer::onEnter();

	//背景音乐
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgmusic.mp3");

	_background1 = Sprite::create("res/roadOne.png");
	_background1->setAnchorPoint(Vec2::ZERO);
	_background1->getTexture()->setAliasTexParameters();
	addChild(_background1);

	_background2 = Sprite::create("res/roadOne.png");
	_background2->setPosition(Vec2(0, _screenHeight));
	_background2->setAnchorPoint(Vec2::ZERO);
	_background2->getTexture()->setAliasTexParameters();
	addChild(_background2);

	//以下代码随机不同颜色的车,随机数函数有问题，重写一下*******************************！！！！！！！
	std::string carName;
	switch ((int)std::rand() % 4)
	{
	case 0:carName = "res/carYellow.png"; break;
	case 1:carName = "res/carBlue.png"; break;
	case 2:carName = "res/carRed.png"; break;
	case 3:carName = "res/carGreen.png"; break;
	default:carName = "res/carYellow.png"; break;
		break;
	}
	_car = Sprite::create(carName);
	_car->setPosition(Vec2(_screenWidth / 2, _screenHeight / 4));
	addChild(_car);

	//暂停按钮
	auto btnStop = Button::create("btnStop.png");
	btnStop->setPosition(Vec2(_screenWidth * 4 / 5 + btnStop->getContentSize().width, _screenHeight * 9 / 10));
	btnStop->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//暂定游戏
			Director::getInstance()->pause();
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
			//_isRemoveStopLayer = false;
			//弹出暂停界面
			//addChild(_stopLayer);
			auto ly = GameStopLayer::create();
			addChild(ly);
			
		}
	});
	addChild(btnStop);

	//分数面板
	_labelScores = Label::createWithTTF("Your Scores:", "fonts/Marker Felt.ttf", 30);
	_labelScores->setPosition(Vec2(_screenWidth/8,_screenHeight*9/10));
	_labelScores->setColor(Color3B(255,0,0));
	addChild(_labelScores);
}

void CarGame::update(float delta)
{
	_count++;
	updateBackground( delta);
	setCarPosition(_isMove, _derection);
	produceEnemyCar();
	removeEnemyCar();
	collisionDetection();
	showScores();
}

void CarGame::updateBackground(float delta)
{
	//下面的有问题
	if (_count>400)
	{
		//_bgSpeed =( _bgSpeed<10 )?( _bgSpeed++) : 10;
		
		_bgSpeed = 10;
	}
	if (_count>600)
	{
		//_bgSpeed =( _bgSpeed<20) ?( _bgSpeed++ ): 20;
		_bgSpeed = 20;
		
	}
	if (_count > 800)
	{
		//_bgSpeed = (_bgSpeed<30) ?( _bgSpeed++ ): 30;
		_bgSpeed = 30;
		
	}
	CCLOG("AAAAAAAAA%d %d",_count,_bgSpeed);
	Vec2 p1 = _background1->getPosition();
	p1.y -= _bgSpeed;
	if (p1.y <= -_background1->getContentSize().height)
	{
		p1.y = _background1->getContentSize().height;
	}
	_background1->setPosition(p1);

	Vec2 p2 = _background2->getPosition();
	p2.y -= _bgSpeed;
	if (p2.y <= -_background2->getContentSize().height)
	{
		p2.y = _background2->getContentSize().height;
	}
	_background2->setPosition(p2);

}

void CarGame::carControl()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event){
		Vec2 touchPosition = touch->getLocation();
		CCLOG("AAAAAAAAAAAAAA");
		_isMove = true;
		if (touchPosition.x - _car->getPosition().x > 3)
		{
			_derection = 1;
		}
		else if (touchPosition.x - _car->getPosition().x < -3)
		{
			_derection = -1;
		}
		else{
			_derection = 0;
		}

		return true;
	};
	listener->onTouchEnded = [=](Touch* touch, Event* event){
		_isMove = false;

	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void CarGame::setCarPosition(bool isMove, int derection)
{
	if (isMove)
	{
		switch (derection)
		{
		case -1:
		{
				   _car->setPosition(_car->getPosition() + Vec2(-10, 0)); break;//向左
		}
		case 1:
		{
				  _car->setPosition(_car->getPosition() + Vec2(10, 0)); break;//向右
		}
		default:
			break;
		}
	}
	if (_car->getPosition().x<_screenWidth / 5 + _car->getContentSize().width / 2)
	{
		_car->setPosition(Vec2(_screenWidth / 5 + _car->getContentSize().width / 2, _car->getPosition().y));
	}
	if (_car->getPosition().x > 4 * _screenWidth / 5 - _car->getContentSize().width / 2)
	{
		_car->setPosition(Vec2(4 * _screenWidth / 5 - _car->getContentSize().width / 2, _car->getPosition().y));
	}
}

void CarGame::produceEnemyCar()
{
	if (_count % 70 == 0)
	{
		std::string fileName;
		switch (std::rand()%3)
		{
		case 0:fileName = "res/carYellow.png"; break;
		case 1:fileName = "res/carRed.png"; break;
		case 2:fileName = "res/carGreen.png"; break;
		default:fileName = "res/carRed.png"; break;
		}
		auto enemyCar = Sprite::create(fileName);
		enemyCar->setPosition(Vec2(_screenWidth / 5 + std::rand() % (3 * _screenWidth / 5), std::rand() % (_screenHeight / 4) + _screenHeight + enemyCar->getContentSize().height));

		//设置速度
		int speed;
		if (_bgSpeed<11)
		{
			speed = 5;
		}
		else if (_bgSpeed < 21){
			speed = 3;
		}
		else if (_bgSpeed < 31){
			speed = 2.5;
		}
		auto moveTo = MoveTo::create(speed, Vec2(enemyCar->getPosition() + Vec2(0, -_screenHeight * 2)));
		enemyCar->runAction(moveTo);

		_enemyCarVec.pushBack(enemyCar);
		addChild(enemyCar);
	}


}

void CarGame::removeEnemyCar()
{

	for (unsigned int i = 0; i < _enemyCarVec.size(); i++)
	{
		auto enemyCar = _enemyCarVec.at(i);
		if (enemyCar->getPosition().y <= -enemyCar->getContentSize().height)
		{
			removeChild(enemyCar);
			_enemyCarVec.eraseObject(enemyCar);
		}
	}

}

void CarGame::collisionDetection()
{
	for (unsigned int i = 0; i < _enemyCarVec.size(); i++)
	{
		auto enemyCar = _enemyCarVec.at(i);
		if (_car->getBoundingBox().intersectsRect(enemyCar->getBoundingBox()))
		{
			this->unscheduleUpdate();
			
			//障碍物小车运动
			ccBezierConfig tr0;
			tr0.endPosition = ccp(enemyCar->getPosition().x +20, enemyCar->getPosition().y +300);
			tr0.controlPoint_1 = ccp(enemyCar->getPosition().x + 30, enemyCar->getPosition().y +130);
			tr0.controlPoint_2 = ccp(enemyCar->getPosition().x + 70, enemyCar->getPosition().y + 270);
			auto action = BezierTo::create(3.5f, tr0);
			enemyCar->stopAllActions();
			auto rotate = RotateBy::create(1.5f, -45);
			enemyCar->runAction(Spawn::create(rotate,action,nullptr));
			/*
			removeChild(enemyCar);
			_enemyCarVec.eraseObject(enemyCar);
			*/
			//爆炸图片
			auto bomb = Sprite::create("bomb.png");
			bomb->setPosition(Vec2(enemyCar->getPosition()+Vec2(0,20)));
			addChild(bomb);
			bomb->runAction(FadeOut::create(1.0f));
			gameOver();
		}
	}
}

void CarGame::gameOver()
{
	//停止背景音乐
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/b1.mp3");
	
	//提交分数
	//NetConnect* nc = new NetConnect;
	//nc->sendRank(/*myData::getInstance()->getUid()*/,_count/100);

	//车子做简单漂移运动
	ccBezierConfig tr0;
	tr0.endPosition = ccp(_car->getPosition().x + 100, _car->getPosition().y + 100);
	tr0.controlPoint_1 = ccp(_car->getPosition().x + 30, _car->getPosition().y + 30);
	tr0.controlPoint_2 = ccp(_car->getPosition().x + 70, _car->getPosition().y + 70);
	auto action = BezierTo::create(1.5f, tr0);
	auto rotate = RotateBy::create(1.5f,45);
	auto blink = Blink::create(2, 5);
	_car->runAction(Spawn::create(blink,rotate, action,nullptr));
	//_car->runAction(Sequence::create(rotate, action, nullptr));

	//游戏结束弹出菜单
	//按钮重新开始
	auto btnRestart = Button::create("res/btnRestart.png");
	btnRestart->setPosition(Vec2(_screenWidth * 2 / 5-btnRestart->getContentSize().width/2, _screenHeight / 2));
	btnRestart->addTouchEventListener([](Ref* pSender, ui::Widget::TouchEventType type){
		if (type==ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, CarGame::createScene()));
		}
	});
	addChild(btnRestart);

	//按钮回主页面
	auto btnBackHome = Button::create("res/btnBackHome.png");
	btnBackHome->setPosition(Vec2(_screenWidth * 3 / 5 - btnBackHome->getContentSize().width / 2, _screenHeight / 2));
	btnBackHome->addTouchEventListener([](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, GameHome::createScene()));
		}
	});
	addChild(btnBackHome);
	//排行榜页面
	auto btnRank = Button::create("res/butTopUp.png");
	btnRank->setPosition(Vec2(_screenWidth * 4 / 5 - btnRank->getContentSize().width / 2, _screenHeight / 2));
	btnRank->addTouchEventListener([](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(TransitionSlideInL::create(1.0f, RankScene::createScene()));
		}
	});
	addChild(btnRank);
}

void CarGame::showScores()
{
	_labelScores->setString("Your Scores:"+StringUtils::format("  %d",_count/100));
	//_labelScores->
}