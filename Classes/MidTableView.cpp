//
//  MidTableView
//  
//  2015/08/20
//  
//	By, Coco
//

#include "MidTableView.h"


bool MidTableView::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto tableView = new TableView();
	tableView->initWithViewSize(CCSizeMake(250, 280), NULL);
	tableView->autorelease();
	tableView->setDataSource(this);
	tableView->ignoreAnchorPointForPosition(false);
	tableView->setAnchorPoint(Vec2(.5f, .5f));
	//tableView->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->reloadData();
	this->addChild(tableView);
	this->setTouchEnabled(true);

	return true;
}

Size MidTableView::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(260, 60);
}

TableViewCell* MidTableView::tableCellAtIndex(TableView *table, ssize_t idx)
{
	auto cell = table->dequeueCell();
	auto cellSize = this->tableCellSizeForIndex(table, idx);
	if (!cell)
	{
		cell = new TableViewCell();
		cell->autorelease();
	}
	cell->removeAllChildrenWithCleanup(true);

	Sprite *pCellBg = Sprite::create("combineview/cell2.png");
	Label *pNum = Label::createWithTTF("2", "fonts/Marker Felt.ttf", 20);
	Sprite *pIcon = Sprite::create("combineview/plane.png");

	pCellBg->setPosition(Vec2(cellSize.width / 2, cellSize.height / 2));
	cell->addChild(pCellBg);
	pNum->setColor(Color3B(255, 0, 0));
	pNum->setPosition(Vec2(cellSize.width * 0.1, cellSize.height / 2));
	cell->addChild(pNum);
	pIcon->setPosition(Vec2(cellSize.width * 0.85, cellSize.height / 2));
	pIcon->setScale(0.2);
	cell->addChild(pIcon);

	return cell;
}

ssize_t MidTableView::numberOfCellsInTableView(TableView *table)
{
	return 8;
}

void MidTableView::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("tableCellTouched\n");
}
