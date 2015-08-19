#include "GameLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace ui;

using namespace cocostudio::timeline;

/*
Scene* GameLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
*/
// on "init" you need to initialize your instance
bool GameLayer::init()
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

	return true;
}

void GameLayer::onEnter()
{
	Layer::onEnter();
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
			//暂定游戏，弹出暂停界面
			
		}
	});
	addChild(btnStop);
}

void GameLayer::update(float delta)
{
	_count++;
	updateBackground();
	setCarPosition(_isMove, _derection);
	produceEnemyCar();
	removeEnemyCar();
	collisionDetection();
}

void GameLayer::updateBackground()
{
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

void GameLayer::carControl()
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

void GameLayer::setCarPosition(bool isMove, int derection)
{
	if (isMove)
	{
		switch (derection)
		{
		case -1:
		{
				   _car->setPosition(_car->getPosition() + Vec2(-5, 0)); break;//向左
		}
		case 1:
		{
				  _car->setPosition(_car->getPosition() + Vec2(5, 0)); break;//向右
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

void GameLayer::produceEnemyCar()
{
	if (_count % 70 == 0)
	{
		auto enemyCar = Sprite::create("res/carYellow.png");
		enemyCar->setPosition(Vec2(_screenWidth / 5 + std::rand() % (3 * _screenWidth / 5), std::rand() % (_screenHeight / 4) + _screenHeight + enemyCar->getContentSize().height));

		auto moveTo = MoveTo::create(5, Vec2(enemyCar->getPosition() + Vec2(0, -_screenHeight * 2)));
		enemyCar->runAction(moveTo);

		_enemyCarVec.pushBack(enemyCar);
		addChild(enemyCar);
	}


}

void GameLayer::removeEnemyCar()
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

void GameLayer::collisionDetection()
{
	for (unsigned int i = 0; i < _enemyCarVec.size(); i++)
	{
		auto enemyCar = _enemyCarVec.at(i);
		if (_car->getBoundingBox().intersectsRect(enemyCar->getBoundingBox()))
		{
			removeChild(enemyCar);
			_enemyCarVec.eraseObject(enemyCar);

			gameOver();
		}
	}
}

void GameLayer::gameOver()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/b1.mp3");
}