//
//  ClippingNode_test
//  
//  2015/08/24
//  
//	By, Coco
//

#pragma once
#include "cocos2d.h"
USING_NS_CC;

class ClippingNode_test : public Layer
{
public:
	static Scene * create();
	virtual bool init();
	void update(float dt);
protected:
private:
	int __updateTimes = 0;
};