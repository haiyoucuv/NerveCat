#include "TouchNode.h"
#include "GameScene.h"

CTouchNode::CTouchNode()
{
}

CTouchNode::~CTouchNode()
{
}

bool CTouchNode::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	this->setTouchListener();
	
	return true;
}

//////////////////////////////////////////////////////////////////////////
// 设置触摸监听
void CTouchNode::setTouchListener()
{
	EventListenerTouchOneByOne *pTouchListener = EventListenerTouchOneByOne::create();
	pTouchListener->onTouchBegan = CC_CALLBACK_2(CTouchNode::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pTouchListener, this);
}

////////////////////////////////////////////////////////////////////////
// 点击开始
bool CTouchNode::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	if (CGameScene::getInstance()->getGameState() != 1)
	{
		return false;
	}

	Vec2 worldPos = pTouch->getLocation(); // 获取世界坐标
	CMap *pMap = CGameScene::getInstance()->getMap();

	for (int i = 0; i < 9; i++)
	{ // 列
		for (int j = 0; j < 9; j++)
		{	// 行
			CPot* pCurPot = pMap->getPotByRank(i, j);
			Vec2 pos = pCurPot->convertToNodeSpaceAR(worldPos);						 // 转换到Pot坐标
			Rect rectPot = static_cast<CPot *>(pCurPot)->getPot2()->getBoundingBox(); // 获取包围盒
			if (rectPot.containsPoint(pos) && !pCurPot->getPot2()->isVisible())
			{	// 判断是否在包围盒内且当前Pot没有围上
				pCurPot->getPot2()->setVisible(true); // 设置为围上（显示橘黄色Pot)
				//CGameScene::getInstance()->getCat()->moveCat();	// 移动猫
				CCat* pCat = CGameScene::getInstance()->getCat();
				int nCatCol = pCat->getCol();
				int nCatRow = pCat->getRow();

				if (nCatRow == 0 || nCatRow == 8 || nCatCol == 0 || nCatCol == 8)
				{
					_eventDispatcher->dispatchCustomEvent("GAME_FAILED");
					return false;
				}

				CPot* pPot = CGameScene::getInstance()->getMap()->getOptimalByRank(nCatCol, nCatRow);

				if (pPot == nullptr)
				{
					_eventDispatcher->dispatchCustomEvent("GAME_WIN");
					return false;
				}

				int nPotCol = pPot->getCol();
				int nPotRow = pPot->getRow();
				
				pCat->setPosition(pPot->getPosition());
				pCat->setCol(nPotCol);
				pCat->setRow(nPotRow);

				return true;
			}
		}
	}
	return true;
}
