//
//  RightTableView
//  
//  2015/08/21
//  
//	By, Coco
//

#include "RightTableView.h"
#include "RightTableSetting.h"

bool RightTableView::init()
{
	if (!Layer::init())
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();

	RightTableSetting *tableSetting = new RightTableSetting();

	auto tableView = new TableView();
	tableView->initWithViewSize(CCSizeMake(250, 280), NULL);
	tableView->autorelease();
	tableView->setDataSource(tableSetting);
	tableView->ignoreAnchorPointForPosition(false);
	tableView->setAnchorPoint(Vec2(.5f, .5f));
	//tableView->setPosition(Vec2(visibleSize.width / 2 + 250, visibleSize.height / 2));
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	//tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->reloadData();
	this->addChild(tableView);
	this->setTouchEnabled(true);

	return true;
}
