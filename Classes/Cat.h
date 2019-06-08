#ifndef __CAT_H__
#define __CAT_H__

#include "cocos2d.h"

USING_NS_CC;

class CCat : public Sprite {
private:
	enum STATE {	// 状态枚举
		NONE,		// 无状态
		STAY,		// 逃脱
		BESIEGED,	// 被围
	};

public:
	CCat();
	virtual ~CCat();
	virtual bool init();
	CREATE_FUNC(CCat);
	CC_SYNTHESIZE(int, m_nRow, Row);
	CC_SYNTHESIZE(int, m_nCol, Col);

	//void moveCat();

private:
	void changeState(int nState);	// 改变状态
	void createAnim();	// 创建动画
	void setCustomListener();	// 设置自定义事件监听

private:
	int m_nState;
};

#endif