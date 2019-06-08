#include "Pot.h"

CPot::CPot() {
}

CPot::~CPot() {
}

bool CPot::init() {
	if(!Node::init()) {
		return false;
	}

	for (int i = 0; i < 6; i++)
	{
		m_ArrNeighbor[i] = nullptr;
	}

	Sprite* pPot1 = Sprite::createWithSpriteFrameName("pot1.png");
	this->addChild(pPot1);

	m_pPot2 = Sprite::createWithSpriteFrameName("pot2.png");
	m_pPot2->setVisible(false);
	this->addChild(m_pPot2);

	m_bSearched = false;

	return true;
}

bool CPot::isSearched() {
	return m_bSearched;
}

void CPot::setSearched(const bool& isSearched) {
	m_bSearched = isSearched;
}

//////////////////////////////////////////////////////////////////////////
// 根据方向获取邻居
// 0为左，顺时针方向
CPot* CPot::getNeighborByDir(int nDir)
{
	return m_ArrNeighbor[nDir];
}

//////////////////////////////////////////////////////////////////////////
// 根据方向设置邻居
// 0为左，顺时针方向
void CPot::setNeighborByDir(int nDir, CPot* pPot)
{
	m_ArrNeighbor[nDir] = pPot;
}

int CPot::getDistanceByDir(int nDir)
{
	CPot* pPot = getNeighborByDir(nDir);
	int nDistance = 1;
	while (pPot != nullptr)
	{
		if (pPot->getPot2()->isVisible() == true)
		{
			return -nDistance;
		}

		nDistance++;

		pPot = pPot->getNeighborByDir(nDir);
	}
	return nDistance;
}

