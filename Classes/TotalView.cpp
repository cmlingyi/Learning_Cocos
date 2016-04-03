//
//  TotalView
//  
//  2015/08/20
//  
//	By, Coco
//

#include "TotalView.h"
#include "LeftTableView.h"
#include "MidTableView.h"
#include "RightTableView.h"

Scene * TotalView::create()
{
	auto scene = Scene::create();
	auto pLayer = new TotalView();
	if (scene && pLayer && pLayer->init())
	{
		pLayer->autorelease();
		scene->addChild(pLayer);
		return scene;
	}
	else
	{
		delete pLayer;
		pLayer = NULL;
		return NULL;
	}
}

bool TotalView::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->setTouchEnabled(true);
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();

	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	auto oneTouch = EventListenerTouchOneByOne::create();
	oneTouch->onTouchBegan = CC_CALLBACK_2(TotalView::onTouchBegan, this);
	oneTouch->onTouchMoved = CC_CALLBACK_2(TotalView::onTouchMoved, this);
	oneTouch->onTouchEnded = CC_CALLBACK_2(TotalView::onTouchEnded, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(oneTouch, this);

	__visibleSize = Director::getInstance()->getVisibleSize();

	initTable();

	return true;
}

void TotalView::initTable()
{
	auto bigSprite = Sprite::create("combineview/bg_big.png");
	bigSprite->setPosition(__visibleSize.width / 2, __visibleSize.height / 2);
	addChild(bigSprite, 0);

	auto smallSprite = Sprite::create("combineview/bg_small.png");
	smallSprite->setPosition(__visibleSize.width / 2, __visibleSize.height / 2);
	addChild(smallSprite, 0);

	auto BoxSize = smallSprite->getContentSize();
	auto label = Label::createWithTTF("Test", "fonts/Marker Felt.ttf", 30);
	label->setPosition(__visibleSize.width / 2 + BoxSize.width / 2, __visibleSize.height / 2 + BoxSize.height / 2);
	addChild(label, 2);

	__leftView = LeftTableView::create();
	__midView = MidTableView::create();
	__rightView = RightTableView::create();

	__container = Node::create();
	__container->addChild(__leftView);
	__leftView->setPosition(-250, 0);
	__container->addChild(__midView);
	__midView->setPosition(0, 0);
	__container->addChild(__rightView);
	__rightView->setPosition(250, 0);
	__container->setPosition(__visibleSize/2);

	Rect visibleRect = CCRectMake(0, 0, 250, 340);

// 	ClippingNode* holesClipper = ClippingNode::create();
// 	Node* holesStencil = __midView;
// 	holesClipper->setStencil(holesStencil);
// 	holesClipper->setInverted(false);
// 	holesClipper->setAlphaThreshold(1);
// 	holesClipper->addChild(__container);
	//this->addChild(holesClipper);
	addChild(__container);
	int x = __container->getPositionX();
}

void TotalView::initScroll()
{

}

bool TotalView::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	__originPoint = __container->getPosition();
	__firstTouchPoint = touch->getLocation();
	if (1)
	{
		return true;
	}
	return true;
}

void TotalView::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	Vec2 movePoint = touch->getLocation();
	float distanceX = movePoint.x - __firstTouchPoint.x;
	float distanceY = movePoint.y - __firstTouchPoint.y;
	__firstTouchPoint = movePoint;
	if (fabs(distanceY) >= fabs(distanceX))
		return;
	else
	{	
		if (__container->getPositionX() + distanceX <= (__visibleSize.width / 2 + __tableModelSize.width * 1.5) && 
			__container->getPositionX() + distanceX >= (__visibleSize.width / 2 - __tableModelSize.width * 1.5))
		{
			__container->setPositionX(__container->getPositionX() + distanceX);
		}
	}
}

void TotalView::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	float distance = __originPoint.x - __container->getPositionX();
	float moveArea = int(fabs(distance)) / int(__tableModelSize.width / 2);
	if (moveArea < 0.5)
	{
		//复原
		__container->setPositionX(__originPoint.x);
	}
	else if (moveArea >= 0.5 && moveArea < 1.5)
	{
		//移动一页
		if (distance >= 0)
			__container->setPositionX(__originPoint.x - __tableModelSize.width);
		else
			__container->setPositionX(__originPoint.x + __tableModelSize.width);
	}
	else if (moveArea >= 1.5)
	{
		//移动两页
		if (distance >= 0)
			__container->setPositionX(__originPoint.x - __tableModelSize.width * 2);
		else
			__container->setPositionX(__originPoint.x + __tableModelSize.width * 2);
	}
}
