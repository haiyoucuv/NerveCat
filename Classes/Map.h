#ifndef __MAP_H__
#define __MAP_H__

#include "cocos2d.h"
#include "Pot.h"

USING_NS_CC;

class CMap : public Node
{
public:
	CMap();
	virtual ~CMap();
	virtual bool init();
	CREATE_FUNC(CMap);

public:
	CPot* getPotByRank(const int& nCol, const int& nRow);
	bool potIsBesieged(const int& nCol, const int& nRow);
	bool isBesieged(CPot* pPot);
	CPot* getOptimalByRank(int nCol, int nRow);

private:
	void createMap();			// 创建地图
	void setPotNeighbor();		// 设置邻居
	void setCustomListener();	// 设置自定义事件监听

private:
	CPot* m_arrPot[9][9];	// m_arrPot[nCol][nRow]

private:
	Size m_PotSize;
	Size m_VisibleSize;
	Vec2 m_Origin;

};

#endif