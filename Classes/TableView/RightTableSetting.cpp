//
//  RightTableSetting
//  
//  2015/08/21
//  
//	By, Coco
//

#include "RightTableSetting.h"


Size RightTableSetting::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(260, 60);
}

TableViewCell* RightTableSetting::tableCellAtIndex(TableView *table, ssize_t idx)
{
	auto cell = table->dequeueCell();
	auto cellSize = this->tableCellSizeForIndex(table, idx);
	if (!cell)
	{
		cell = new TableViewCell();
		cell->autorelease();
	}
	cell->removeAllChildrenWithCleanup(true);

	Sprite *pCellBg = Sprite::create("combineview/cell3.png");
	Label *pNum;
	switch (idx)
	{
		case 0:
			pNum = Label::createWithTTF("3-1", "fonts/Marker Felt.ttf", 20);
			break;
		case 1:
			pNum = Label::createWithTTF("3-2", "fonts/Marker Felt.ttf", 20);
			break;
		case 2:
			pNum = Label::createWithTTF("3-3", "fonts/Marker Felt.ttf", 20);
			break;
		case 3:
			pNum = Label::createWithTTF("3-4", "fonts/Marker Felt.ttf", 20);
			break;
		case 4:
			pNum = Label::createWithTTF("3-5", "fonts/Marker Felt.ttf", 20);
			break;
		case 5:
			pNum = Label::createWithTTF("3-6", "fonts/Marker Felt.ttf", 20);
			break;
		default:
			break;
	}
// 	Label *pNum = Label::createWithTTF("3", "fonts/Marker Felt.ttf", 20);
	Sprite *pIcon = Sprite::create("combineview/setting.png");

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

ssize_t RightTableSetting::numberOfCellsInTableView(TableView *table)
{
	return 6;
}

void RightTableSetting::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("tableCellTouched\n");
}
