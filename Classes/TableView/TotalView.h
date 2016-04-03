//
//  TotalView
//  
//  2015/08/20
//  
//	By, Coco
//

#pragma once
#include "cocos2d.h"
#include "LeftTableView.h"
#include "MidTableView.h"
#include "RightTableView.h"
USING_NS_CC;

class TotalView : public Layer
{
public:
	static Scene * create();
	virtual bool init()override;

	void initTable();
	void initScroll();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)override;
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)override;
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)override;
	
protected:
private:
	Size				__visibleSize;
	Node*				__container;
	Size				__tableModelSize{ 250, 280 };

	LeftTableView*		__leftView;
	MidTableView*		__midView;
	RightTableView*		__rightView;

	Vec2				__originPoint;
	Vec2				__firstTouchPoint;
};