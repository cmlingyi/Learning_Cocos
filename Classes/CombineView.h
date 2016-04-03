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
	//��scrollview�ĵ���
	void adjustScrollView(float offset);
private:
	ScrollView * m_scrollView;
	TableView * m_leftTable;
	TableView * m_centerTable;
	TableView * m_rightTable;
	//scrollview��ǰ��ʾ��ҳ��
	int m_curPage;
	//��һ��������
	Vec2 m_firstPoint;
	//scrollview��ƫ��
	Vec2 m_offset;
	//�жϵ�һ�λ�������
	bool m_horizontal;
	bool m_vertical;
	//View�Ĵ�С
	Size m_viewSize;
};

#endif // !__COMBINE_VIEW_H__

