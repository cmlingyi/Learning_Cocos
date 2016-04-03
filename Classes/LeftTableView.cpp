//
//  LeftTableView
//  
//  2015/08/20
//  
//	By, Coco
//

#include "LeftTableView.h"


bool LeftTableView::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();

	auto tableView = new TableView();
	tableView->initWithViewSize(CCSizeMake(250, 280), NULL);
	tableView->autorelease();
	tableView->setDataSource(this);
	tableView->ignoreAnchorPointForPosition(false);
	tableView->setAnchorPoint(Vec2(0.5, 0.5));
	//tableView->setPosition(ccp(size.width / 2.0f -  250, size.height / 2.0f));
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->reloadData();
	this->addChild(tableView);
	this->setTouchEnabled(true);

	return true;
}

Size LeftTableView::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(260, 60);
}

TableViewCell* LeftTableView::tableCellAtIndex(TableView *table, ssize_t idx)
{
	auto cell = table->dequeueCell();
	auto cellSize = this->tableCellSizeForIndex(table, idx);
	if (!cell)
	{
		cell = new TableViewCell();
		cell->autorelease();
	}
	cell->removeAllChildrenWithCleanup(true);

	Sprite *pCellBg = Sprite::create("combineview/cell.png");
	Label *pNum = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 20);
	Sprite *pIcon = Sprite::create("combineview/book.png");

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

ssize_t LeftTableView::numberOfCellsInTableView(TableView *table)
{
	return 10;
}

void LeftTableView::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("tableCellTouched\n");
}

