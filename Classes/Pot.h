#ifndef __MAP_POT_H__
#define __MAP_POT_H__

#include "cocos2d.h"

USING_NS_CC;

class CPot : public Node {
public:
	CPot();
	~CPot();
	virtual bool init();
	CREATE_FUNC(CPot);

	CC_SYNTHESIZE_READONLY(Sprite*, m_pPot2, Pot2);
	CC_SYNTHESIZE(int, m_nCol, Col);
	CC_SYNTHESIZE(int, m_nRow, Row);

	bool isSearched();
	void setSearched(const bool& isSearched);

	CPot* getNeighborByDir(int nDir);
	void setNeighborByDir(int nDir, CPot* pPot);

	int getDistanceByDir(int nDir);

private:
	bool m_bSearched;	// 是否被搜索过
	CPot* m_ArrNeighbor[6];
	//   1   2
	// 0   x   3
	//   5   4
};

#endif	// __MAP_POT_H__