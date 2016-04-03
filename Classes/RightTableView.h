//
//  RightTableView
//  
//  2015/08/21
//  
//	By, Coco
//

#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class RightTableView : public Layer
{
public:
	static RightTableView* create()
	{
		RightTableView *view = new RightTableView();
		view->init();
		view->autorelease();
		return view;
	}
	virtual bool init()override;
protected:
private:
};