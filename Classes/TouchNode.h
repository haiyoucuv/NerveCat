#ifndef __TOUCH_NODE_H__
#define __TOUCH_NODE_H__

#include "cocos2d.h"

USING_NS_CC;

class CTouchNode : public Node
{
public:
	CTouchNode();
	virtual ~CTouchNode();
	virtual bool init();
	CREATE_FUNC(CTouchNode);

private:
	void setTouchListener();	// 设置触摸监听
	bool onTouchBegan(Touch* pTouch, Event* pEvent);
};

#endif // __TOUCH_NODE_H__