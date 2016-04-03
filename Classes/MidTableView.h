//
//  MidTableView
//  
//  2015/08/20
//  
//	By, Coco
//

#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MidTableView : public Layer, TableViewDataSource, TableViewDelegate
{
public:
	static MidTableView* create()
	{
		MidTableView *view = new MidTableView();
		view->init();
		view->autorelease();
		return view;
	}
	virtual bool init()override;
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);

	void tableCellTouched(TableView* table, TableViewCell* cell);
protected:
private:
};