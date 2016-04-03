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
// 	TextFieldTTF *tf = TextFieldTTF::textFieldWithPlaceHolder("Please input words", "����", 36);
// 	tf->setPosition(visibleSize / 2);
// 	addChild(tf);
// 
// 	auto listener = EventListenerTouchOneByOne::create();                                           //����һ���¼�������
// 	listener->onTouchBegan = [tf](Touch *t, Event *event)
// 	{
// 		if (tf->getBoundingBox().containsPoint(t->getLocation()))            //��ȡ�����㲢�Ҵ������Ƿ���������ı��༭����
// 		{
// 			CCLOG("OPEN IME\n");
// 			tf->attachWithIME();                                      //Ϊ����ؼ��������뷨
// 		}
// 		else
// 		{
// 			CCLOG("CLOSE IME\n");
// 			tf->detachWithIME();
// 		}
// 		return false;
// 	};
// 
// 	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, tf);           //���õ������һ�����¼��ļ�����  
	return true;
}
