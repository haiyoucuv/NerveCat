#include "Map.h"

CMap::CMap()
{
}

CMap::~CMap()
{
}

bool CMap::init()
{
	if (!Node::init())
	{
		return false;
	}

	m_PotSize = CPot::create()->getPot2()->getContentSize();
	m_VisibleSize = Director::getInstance()->getVisibleSize();
	m_Origin = Director::getInstance()->getVisibleOrigin();

	this->setCustomListener();
	this->createMap();
	this->setPotNeighbor();

	return true;
}

//////////////////////////////////////////////////////////////////////////
// 通过列行获得Pot
CPot* CMap::getPotByRank(const int& nCol, const int& nRow)
{
	return m_arrPot[nCol][nRow];
}

//////////////////////////////////////////////////////////////////////////
// 获取这个Pot是否被围
bool CMap::potIsBesieged(const int& nCol, const int& nRow)
{
	return m_arrPot[nCol][nRow]->getPot2()->isVisible();
}

//////////////////////////////////////////////////////////////////////////
// 判断是否被围上
bool CMap::isBesieged(CPot* pPot)
{
	int nRow = pPot->getRow();
	int nCol = pPot->getCol();

	if (nCol == 0 || nCol == 8 || nRow == 0 || nRow == 8)
	{
		return false;
	}
	pPot->setSearched(true);
	bool bLeft = true;
	bool bRight = true;
	bool bLeftUp = true;
	bool bLeftDown = true;
	bool bRightUp = true;
	bool bRightDown = true;
	CPot *pCurPot = m_arrPot[nCol - 1][nRow];
	if (!pCurPot->getPot2()->isVisible() && !pCurPot->isSearched())
	{ // 左
		bLeft = isBesieged(pCurPot);
	}

	pCurPot = m_arrPot[nCol + 1][nRow];
	if (!pCurPot->getPot2()->isVisible() && !pCurPot->isSearched())
	{ // 右
		bRight = isBesieged(pCurPot);
	}

	if (nRow % 2)
	{ // 奇数行
		pCurPot = m_arrPot[nCol][nRow + 1];
		if (!pCurPot->getPot2()->isVisible() && !pCurPot->isSearched())
		{ // 左上
			bLeftUp = isBesieged(pCurPot);
		}

		pCurPot = m_arrPot[nCol + 1][nRow + 1];
		if (!pCurPot->getPot2()->isVisible() && !pCurPot->isSearched())
		{ // 右上
			bLeftDown = isBesieged(pCurPot);
		}

		pCurPot = m_arrPot[nCol][nRow - 1];
		if (!pCurPot->getPot2()->isVisible() && !pCurPot->isSearched())
		{ // 左下
			bRightUp = isBesieged(pCurPot);
		}

		pCurPot = m_arrPot[nCol + 1][nRow - 1];
		if (!pCurPot->getPot2()->isVisible() && !pCurPot->isSearched())
		{ // 右下
			bRightDown = isBesieged(pCurPot);
		}
	}
	else
	{ // 偶数行
		pCurPot = m_arrPot[nCol - 1][nRow + 1];
		if (!pCurPot->getPot2()->isVisible() && !pCurPot->isSearched())
		{ // 左上
			bLeftUp = isBesieged(pCurPot);
		}

		pCurPot = m_arrPot[nCol][nRow + 1];
		if (!pCurPot->getPot2()->isVisible() && !pCurPot->isSearched())
		{ // 右上
			bLeftDown = isBesieged(pCurPot);
		}

		pCurPot = m_arrPot[nCol - 1][nRow - 1];
		if (!pCurPot->getPot2()->isVisible() && !pCurPot->isSearched())
		{ // 左下
			bRightUp = isBesieged(pCurPot);
		}

		pCurPot = m_arrPot[nCol][nRow - 1];
		if (!pCurPot->getPot2()->isVisible() && !pCurPot->isSearched())
		{ // 右下
			bRightDown = isBesieged(pCurPot);
		}
	}

	if (bLeft && bRight && bLeftUp && bLeftDown && bRightUp && bRightDown)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////
// 创建地图
void CMap::createMap()
{
	float cutWidth = m_VisibleSize.width - (m_PotSize.width + 3) * 9.0f;
	for (int i = 0; i < 9; i++)
	{ // 列
		for (int j = 0; j < 9; j++)
		{ // 行
			CPot *pPot = CPot::create();
			this->addChild(pPot);
			if (j % 2)
			{ // 奇数行
				pPot->setPositionX(cutWidth / 2.0f + m_PotSize.width * 0.5f + i * (m_PotSize.width + 3));
			}
			else
			{ // 偶数行
				pPot->setPositionX(cutWidth / 2.0f + i * (m_PotSize.width + 3));
			}
			pPot->setPositionY(m_Origin.x + m_VisibleSize.height / 8 + j * (m_PotSize.height - 2));
			pPot->setCol(i);
			pPot->setRow(j);
			m_arrPot[i][j] = pPot; // 存入数组
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 设置邻居
void CMap::setPotNeighbor()
{
	for (int nCol = 0; nCol < 9; nCol++)
	{ // 列
		for (int nRow = 0; nRow < 9; nRow++)
		{ // 行
			CPot *pPot = m_arrPot[nCol][nRow];
			if (nCol == 0)
			{ // 左
				pPot->setNeighborByDir(0, nullptr);
			}
			else
			{
				pPot->setNeighborByDir(0, m_arrPot[nCol - 1][nRow]);
			}

			if (nCol == 8)
			{ // 右
				pPot->setNeighborByDir(3, nullptr);
			}
			else
			{
				pPot->setNeighborByDir(3, m_arrPot[nCol + 1][nRow]);
			}
			if (nRow % 2 == 1) // 奇数行
			{
				if (nCol == 8)
				{
					pPot->setNeighborByDir(2, nullptr);	// 右上
					pPot->setNeighborByDir(4, nullptr);	// 右下
				}
				else
				{
					pPot->setNeighborByDir(2, m_arrPot[nCol + 1][nRow + 1]);	// 右上
					pPot->setNeighborByDir(4, m_arrPot[nCol + 1][nRow - 1]);	// 右下
				}
				pPot->setNeighborByDir(1, m_arrPot[nCol][nRow + 1]);// 左上
				pPot->setNeighborByDir(5, m_arrPot[nCol][nRow - 1]);// 左下
			}
			else // 偶数行
			{
				if (nCol == 0)
				{
					if (nRow == 8)	// 上
					{
						pPot->setNeighborByDir(2, nullptr);	// 右上
						pPot->setNeighborByDir(4, m_arrPot[nCol][nRow - 1]);	// 右下
					}
					else if (nRow == 0)
					{
						pPot->setNeighborByDir(2, m_arrPot[nCol][nRow + 1]);	// 右上
						pPot->setNeighborByDir(4, nullptr);	// 右下
					}
					else
					{
						pPot->setNeighborByDir(2, m_arrPot[nCol][nRow + 1]);	// 右上
						pPot->setNeighborByDir(4, m_arrPot[nCol][nRow - 1]);	// 右下
					}
					pPot->setNeighborByDir(1, nullptr);	// 左上
					pPot->setNeighborByDir(5, nullptr);// 左下
				}
				else if (nCol == 8)
				{
					if (nRow == 8)	// 上
					{
						pPot->setNeighborByDir(1, nullptr);	// 左上
						pPot->setNeighborByDir(2, nullptr);	// 右上
						pPot->setNeighborByDir(5, m_arrPot[nCol - 1][nRow - 1]);// 左下
						pPot->setNeighborByDir(4, m_arrPot[nCol][nRow - 1]);	// 右下
					}
					else if (nRow == 0)
					{
						pPot->setNeighborByDir(1, m_arrPot[nCol - 1][nRow + 1]);// 左上
						pPot->setNeighborByDir(2, m_arrPot[nCol][nRow + 1]);	// 右上
						pPot->setNeighborByDir(4, nullptr);	// 右下
						pPot->setNeighborByDir(5, nullptr); // 左下
					}
				}
				else
				{
					if (nRow == 8)	// 上
					{
						pPot->setNeighborByDir(2, nullptr);	// 右上
						pPot->setNeighborByDir(1, nullptr);	// 左上
						pPot->setNeighborByDir(5, m_arrPot[nCol - 1][nRow - 1]);// 左下
						pPot->setNeighborByDir(4, m_arrPot[nCol][nRow - 1]);	// 右下
					}
					else if (nRow == 0)
					{
						pPot->setNeighborByDir(1, m_arrPot[nCol - 1][nRow + 1]);// 左上
						pPot->setNeighborByDir(2, m_arrPot[nCol][nRow + 1]);	// 右上
						pPot->setNeighborByDir(5, nullptr);// 左下
						pPot->setNeighborByDir(4, nullptr);	// 右下
					}
					else
					{
						pPot->setNeighborByDir(1, m_arrPot[nCol - 1][nRow + 1]);// 左上
						pPot->setNeighborByDir(2, m_arrPot[nCol][nRow + 1]);	// 右上
						pPot->setNeighborByDir(5, m_arrPot[nCol - 1][nRow - 1]);// 左下
						pPot->setNeighborByDir(4, m_arrPot[nCol][nRow - 1]);	// 右下
					}
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 设置自定义监听事件
void CMap::setCustomListener()
{
	// 游戏开始的自定义触发事件
	EventListenerCustom *pGameStartlistener = EventListenerCustom::create("GAME_START", [=](EventCustom *event)
	{
		// 清空被围上的Pot
		for (int i = 0; i < 9; i++)
		{ // 列
			for (int j = 0; j < 9; j++)
			{ // 行
				m_arrPot[i][j]->getPot2()->setVisible(false);
			}
		}

		// 随机增加一些围上的Pot
		for (int i = 0; i < rand() % 5 + 10; i++)
		{
			int nRow = 4;
			int nCol = 4;
			while (nRow == 4 && nCol == 4)
			{
				nRow = rand() % 9;
				nCol = rand() % 9;
			}
			m_arrPot[nRow][nCol]->getPot2()->setVisible(true);
		}
	});

	// 投递事件
	_eventDispatcher->addEventListenerWithFixedPriority(pGameStartlistener, 1);
}


CPot* CMap::getOptimalByRank(int nCol, int nRow)
{
	CPot* pPot = m_arrPot[nCol][nRow];

	int arrCounts[6];
	for (int i = 0; i < 6; i++)	// 获取六个方向的通路长度
	{
		arrCounts[i] = pPot->getDistanceByDir(i);
	}

	bool bFailed = true;	// 是否失败

	for (int i = 0; i < 6; i++)	// 判断是否全为-1
	{
		if (arrCounts[i] != -1)	// 有一个不等于-1则表示没有失败
		{
			bFailed = false;
			break;
		}
	}

	if (bFailed)	// 如果失败则返回空
	{
		return nullptr;
	}

	bool bMinus = true;	// 是否全为负数

	for (int i = 0; i < 6; i++)	// 判断是否全为负数
	{
		if (arrCounts[i] >= 0)
		{
			bMinus = false;
			break;
		}
	}

	int nDir = 0;
	int nCount = 10;

	if (bMinus == true)	// 如果全为负数
	{
		int nCount = arrCounts[0];
		for (int i = 0; i < 6; i++)
		{
			if (arrCounts[i] < nCount)	// 求最小
			{
				nDir = i;
				nCount = arrCounts[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			if (arrCounts[i] >= 0 && arrCounts[i] < nCount)	// 求最小
			{
				nDir = i;
				nCount = arrCounts[i];
			}
		}
	}

	if (this->isBesieged(pPot))
	{
		_eventDispatcher->dispatchCustomEvent("CAT_BESIEGED");
	}

	for (int i = 0; i < 9; i++)
	{ // 列
		for (int j = 0; j < 9; j++)
		{ // 行
			m_arrPot[i][j]->setSearched(false);
		}
	}

	return pPot->getNeighborByDir(nDir);
}