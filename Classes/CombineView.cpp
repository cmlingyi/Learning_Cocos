#include "CombineView.h"

CombineView::CombineView()
{
	m_scrollView = NULL;
	m_leftTable = NULL;
	m_centerTable = NULL;
	m_rightTable = NULL;
	m_curPage = 0;
	m_firstPoint = Vec2(0,0);
	m_offset = Vec2(0,0);
	m_vertical = false;
	m_horizontal = false;
	m_viewSize = Size(0,0);
}

CombineView::~CombineView()
{
}

cocos2d::Scene * CombineView::create()
{
	auto scene = Scene::create();
	auto pLayer = new CombineView();
	if (scene && pLayer && pLayer->init())
	{
		pLayer->autorelease();
		scene->addChild(pLayer);
		return scene;
	}
	else
	{
		delete pLayer;
		pLayer = NULL;
		return NULL;
	}
}

bool CombineView::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto bgSize = Director::getInstance()->getWinSize();

	auto pBg = Sprite::create("combineview/bg_big.png");
	pBg->setPosition(Vec2(bgSize.width / 2,bgSize.height / 2));
	this->addChild(pBg);

	auto pView = Sprite::create("combineview/bg_small.png");
	pView->setPosition(Vec2(bgSize.width / 2,bgSize.height / 2));
	this->addChild(pView,2);
	
	auto BoxSize = pView->getContentSize();
	m_viewSize = Size(BoxSize.width,BoxSize.height * 0.85);//coco containerSize
	//添加标题
	auto plabel = Label::createWithTTF("CombineView Test","fonts/Marker Felt.ttf",30);
	plabel->setPosition(Vec2(BoxSize.width / 2,BoxSize.height * 0.9));
	pView->addChild(plabel);

	m_scrollView = ScrollView::create();
	m_scrollView->setViewSize(m_viewSize);
	m_scrollView->setContentOffset(Point::ZERO);
	m_scrollView->setDelegate(this);
	m_scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	m_scrollView->setAnchorPoint(Point::ZERO);
	m_scrollView->setPosition(Vec2::ZERO);
	m_scrollView->setTouchEnabled(false);//因为我们不需要scrollview的触摸，因为太糟糕~
	pView->addChild(m_scrollView);
	
	//添加内容
	auto pContainer = Layer::create();
	pContainer->setContentSize(Size(m_viewSize.width * 3,m_viewSize.height));
	pContainer->setAnchorPoint(Point::ZERO);
	pContainer->setPosition(Vec2::ZERO);
	m_scrollView->setContainer(pContainer);

	//添加tabelview
	auto containerSize = pContainer->getContentSize();
	m_leftTable = new TableView();
	m_leftTable->initWithViewSize(m_viewSize, NULL);
	m_leftTable->autorelease();
	m_leftTable->setDataSource(this);
	m_leftTable->setTag(Table_Left);
	m_leftTable->ignoreAnchorPointForPosition(false);
	m_leftTable->setAnchorPoint(Vec2(0.5,0.5));
	m_leftTable->setPosition(Vec2(containerSize.width / 6,containerSize.height / 2));
	m_leftTable->setDirection(ScrollView::Direction::VERTICAL);
	m_leftTable->setDelegate(this);
	m_leftTable->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	m_leftTable->reloadData();
	pContainer->addChild(m_leftTable);

	m_centerTable = new TableView();
	m_centerTable->initWithViewSize(m_viewSize, NULL);
	m_centerTable->autorelease();
	m_centerTable->setDataSource(this);	
	m_centerTable->setTag(Table_Center);
	m_centerTable->ignoreAnchorPointForPosition(false);
	m_centerTable->setAnchorPoint(Vec2(0.5,0.5));
	m_centerTable->setPosition(Vec2(containerSize.width / 2,containerSize.height / 2));
	m_centerTable->setDirection(ScrollView::Direction::VERTICAL);
	m_centerTable->setDelegate(this);
	m_centerTable->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	m_centerTable->reloadData();
	pContainer->addChild(m_centerTable);

	//m_rightTable = TableView::create(this, ViewSize);	
	m_rightTable = new TableView();
	m_rightTable->initWithViewSize(m_viewSize, NULL);
	m_rightTable->autorelease();
	m_rightTable->setDataSource(this);
	m_rightTable->setTag(Table_Right);
	m_rightTable->ignoreAnchorPointForPosition(false);
	m_rightTable->setAnchorPoint(Vec2(0.5,0.5));
	m_rightTable->setPosition(Vec2(containerSize.width / 6 * 5,containerSize.height / 2));
	m_rightTable->setDirection(ScrollView::Direction::VERTICAL);
	m_rightTable->setDelegate(this);
	m_rightTable->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	m_rightTable->reloadData();
	pContainer->addChild(m_rightTable);

	//重写实现scrollview的触摸效果
	auto listenerT = EventListenerTouchOneByOne::create();

	listenerT->onTouchBegan = [=](Touch * touch,Event * pEvent){
		m_firstPoint = touch->getLocation();
		m_offset = m_scrollView->getContentOffset();
		if (!m_scrollView->getBoundingBox().containsPoint(m_firstPoint))
		{
			return false;
		}
		return true;
	};

	listenerT->onTouchMoved = [=](Touch * touch,Event * pEvent){
		auto movePoint = touch->getLocation();
		auto distance = movePoint.x - m_firstPoint.x;

		if ((distance > 0 && this->m_curPage == 0) || (distance < 0 && this->m_curPage == 2))
		{
			return;
		}

		//限制滑动方向，避免scorll和table同时滑动
		if (fabs(movePoint.y - m_firstPoint.y) / fabs(distance) > 0.7 || m_vertical)
		{
			if (!m_horizontal)
			{
				m_vertical = true;
			}
			return;
		}
		else //水平
		{
			if (!m_vertical)
			{
				m_horizontal = true;
			}
		}
		if (m_horizontal)
		{
			this->SetTouch(false);
		}
		m_scrollView->setContentOffset(Vec2(distance + m_offset.x,0));
	};

	listenerT->onTouchEnded = [=](Touch * touch,Event * pEvent){
		auto endPoint = touch->getLocation();
		auto distance = endPoint.x - m_firstPoint.x;
		//优化滑动效果
		bool flag = false;
		if (fabsf(distance) < 60)
		{
			flag = true;
			if (distance < 0)
			{
				m_curPage--;
			}
			else if (distance > 0)
			{
				m_curPage++;
			}
		}

		//限制滑动方向，避免scroll和table同时滑动
		if (m_vertical)
		{
			m_vertical = false;
			if (flag)
			{
				if (distance > 0)
				{
					m_curPage--;
				}
				else if (distance < 0)
				{
					m_curPage++;
				}
			}
			
			return ;
		}
		else
		{
			this->SetTouch(true);
		}

		this->adjustScrollView(distance);
		m_horizontal = false;
	};
	listenerT->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerT,this);

	return true;
}

void CombineView::adjustScrollView(float offset)
{
	if (offset < 0)
	{
		m_curPage++;
	}
	else if (offset > 0)
	{
		m_curPage--;
	}

	if (m_curPage < 0)
	{
		m_curPage = 0;
	}
	else if (m_curPage > 2)
	{
		m_curPage = 2;
	}

	auto adjustPoint = Vec2(-m_viewSize.width * m_curPage,0);
	m_scrollView->setContentOffsetInDuration(adjustPoint,0.1f);
}

Size CombineView::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(260,60);
}

TableViewCell* CombineView::tableCellAtIndex(TableView *table, ssize_t idx)
{
	auto cell = table->dequeueCell();
	auto cellSize = this->tableCellSizeForIndex(table, idx);
	auto tag = table->getTag();

	if (!cell)
	{
		cell = new TableViewCell();
		cell->autorelease();
		Sprite * pCellBg = NULL;
		Label * pNum = NULL;
		Sprite * pIcon = NULL;
		switch (tag)
		{
		case Table_Left:
			{
				pCellBg = Sprite::create("combineview/cell.png");
				pNum = Label::createWithTTF("1","fonts/Marker Felt.ttf",20);
				pIcon = Sprite::create("combineview/book.png");
			}
			break;
		case Table_Center:
			{
				pCellBg = Sprite::create("combineview/cell2.png");
				pNum = Label::createWithTTF("2","fonts/Marker Felt.ttf",20);
				pIcon = Sprite::create("combineview/plane.png");
			}
			break;
		case Table_Right:
			{
				pCellBg = Sprite::create("combineview/cell3.png");
				pNum = Label::createWithTTF("3","fonts/Marker Felt.ttf",20);
				pIcon = Sprite::create("combineview/setting.png");
			}
		default:
			break;
		}
		pCellBg->setPosition(Vec2(cellSize.width / 2,cellSize.height / 2));
		cell->addChild(pCellBg);
		pNum->setColor(Color3B(255,0,0));
		pNum->setPosition(Vec2(cellSize.width * 0.1,cellSize.height / 2));
		cell->addChild(pNum);
		pIcon->setPosition(Vec2(cellSize.width * 0.85,cellSize.height / 2));
		pIcon->setScale(0.2);
		cell->addChild(pIcon);
	}
	return cell;
}
ssize_t CombineView::numberOfCellsInTableView(TableView *table)
{
	return 10;
}

void CombineView::tableCellTouched(TableView* table, TableViewCell* cell)
{

}

void CombineView::scrollViewDidScroll(ScrollView* view)
{

}

void CombineView::scrollViewDidZoom(ScrollView* view)
{

}

void CombineView::SetTouch(bool isTouched)
{
	m_leftTable->setTouchEnabled(isTouched);
	m_centerTable->setTouchEnabled(isTouched);
	m_rightTable->setTouchEnabled(isTouched);
}
