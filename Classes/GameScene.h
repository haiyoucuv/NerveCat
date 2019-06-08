#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "UINode.h"
#include "Pot.h"
#include "Cat.h"
#include "Map.h"
#include "TouchNode.h"

USING_NS_CC;

class CGameScene : public Scene {
private:
	enum GAMESTATE {
		MENU,
		GAME,
		WIN,
		FAILED,
	};

public:
	CGameScene();
	virtual ~CGameScene();
	static CGameScene* getInstance();
	static void destroy();
	virtual bool init();
	CREATE_FUNC(CGameScene);

	CC_SYNTHESIZE(int, m_nGameState, GameState);
	CC_SYNTHESIZE_READONLY(CCat*, m_pCat, Cat);
	CC_SYNTHESIZE_READONLY(CMap*, m_pMap, Map);

private:
	void loadRes();		// 加载资源
	void setCustomListener();	// 设置自定义事件监听

private:
	static CGameScene* m_pInstance;
	CUINode* m_pUINode;
	CTouchNode* m_pTouchNode;

private:
	Size m_PotSize;
	Size m_VisibleSize;
	Vec2 m_Origin;
};
#endif	// __GAME_SCENE_H__
