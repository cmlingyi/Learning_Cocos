//
//  TextFiledTTFView
//  
//  2015/08/26
//  
//	By, Coco
//

#include "TextFiledTTFView.h"
#include "CursorTextField.h"

Scene* TextFiledTTFView::create()
{
	auto scene = Scene::create();
	auto pLayer = new TextFiledTTFView();
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

bool TextFiledTTFView::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	CursorTextField *m_pCursorInputLayer = CursorTextField::textFieldWithPlaceHolder(this, "click and input",
																					 "fonts/Marker Felt.ttf", 40);
	m_pCursorInputLayer->setAnchorPoint(ccp(0.0f, 0.0f));
	m_pCursorInputLayer->setInputWidth(visibleSize.width);
	Vec2 posi(0, visibleSize.height / 2);
	m_pCursorInputLayer->setPosition(posi);
	this->addChild(m_pCursorInputLayer, 1);

// 	Size visibleSize = Director::getInstance()->getVisibleSize();
// 	TextFieldTTF *tf = TextFieldTTF::textFieldWithPlaceHolder("Please input words", "宋体", 36);
// 	tf->setPosition(visibleSize / 2);
// 	addChild(tf);
// 
// 	auto listener = EventListenerTouchOneByOne::create();                                           //设立一个事件监听器
// 	listener->onTouchBegan = [tf](Touch *t, Event *event)
// 	{
// 		if (tf->getBoundingBox().containsPoint(t->getLocation()))            //获取触摸点并且触摸点是否包含在在文本编辑框内
// 		{
// 			CCLOG("OPEN IME\n");
// 			tf->attachWithIME();                                      //为这个控件启用输入法
// 		}
// 		else
// 		{
// 			CCLOG("CLOSE IME\n");
// 			tf->detachWithIME();
// 		}
// 		return false;
// 	};
// 
// 	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, tf);           //利用导演添加一个对事件的监听器  
	return true;
}
