//
//  ClippingNode_test
//  
//  2015/08/24
//  
//	By, Coco
//

#include "ClippingNode_test.h"

Scene * ClippingNode_test::create()
{
	auto scene = Scene::create();
	auto pLayer = new ClippingNode_test();
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

bool ClippingNode_test::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->scheduleUpdate();

	static int a = 1;
	std::vector<int> vec(5);
	generate(vec.begin(), vec.end(), []{return a++; });
	auto iter = vec.begin();
	CCLOG("a = %d", a);
	for (; iter != vec.end(); iter++)
	{
		CCLOG("value = %d", (*iter));
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto titleSp = Sprite::create("clippingNode/game_title.png");
	auto sparkSp = Sprite::create("clippingNode/spark.png");
	Size clipSize = titleSp->getContentSize();
	sparkSp->setPositionX(-clipSize.width);

	auto clipper = ClippingNode::create();
	clipper->setStencil(titleSp);
	clipper->setInverted(false);
	clipper->setAlphaThreshold(0.05);
	clipper->addChild(titleSp);
	clipper->addChild(sparkSp);
	clipper->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(clipper);

	Size s = titleSp->getContentSize();
	auto moveAction = MoveBy::create(2.0f, Vec2(clipSize.width * 2, 0));//moveTo() can't use reverse function
	auto moveBackAction = moveAction->reverse();
	sparkSp->runAction(RepeatForever::create(Sequence::create(moveAction, moveBackAction, NULL)));

	return true;
}

void ClippingNode_test::update(float dt)
{
	printf("update time = %d", __updateTimes++);
}

