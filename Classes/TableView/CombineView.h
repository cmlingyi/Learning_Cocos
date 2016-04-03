#ifndef __COMBINE_VIEW_H__
#define __COMBINE_VIEW_H__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

enum Table
{
	Table_Left = 0,
	Table_Center,
	Table_Right
};

class CombineView : public Layer,TableViewDataSource,TableViewDelegate
{
public:
	CombineView();
	~CombineView();

	virtual bool init();
	static cocos2d::Scene * create();

	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);

	virtual void scrollViewDidScroll(ScrollView* view);
	virtual void scrollViewDidZoom(ScrollView* view);

public:
	void SetTouch(bool isTouched);
	//对scrollview的调整
	void adjustScrollView(float offset);
private:
	ScrollView * m_scrollView;
	TableView * m_leftTable;
	TableView * m_centerTable;
	TableView * m_rightTable;
	//scrollview当前显示的页数
	int m_curPage;
	//第一个触摸点
	Vec2 m_firstPoint;
	//scrollview的偏移
	Vec2 m_offset;
	//判断第一次滑动方向
	bool m_horizontal;
	bool m_vertical;
	//View的大小
	Size m_viewSize;
};

#endif // !__COMBINE_VIEW_H__

