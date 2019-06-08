#ifndef __UI_NODE_H__
#define __UI_NODE_H__

#include "cocos2d.h"

USING_NS_CC;

class CUINode : public Node {
public:
	CUINode();
	virtual ~CUINode();
	virtual bool init();
	CREATE_FUNC(CUINode);

private:
	void buttonCallFun(Ref* pSender);
	CC_SYNTHESIZE_READONLY(Sprite*, m_pVector, ImgVector);
	CC_SYNTHESIZE_READONLY(Sprite*, m_pFailed, ImgFailed);

private:
	Sprite* m_pLogo;
	MenuItemImage* m_pBtnStart;
	MenuItemImage* m_pBtnReplay;
};

#endif	//__UI_NODE_H__