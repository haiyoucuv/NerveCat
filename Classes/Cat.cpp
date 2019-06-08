#include "Cat.h"
#include "GameScene.h"

CCat::CCat() {
}

CCat::~CCat() {
}

//////////////////////////////////////////////////////////////////////////
// 初始化
bool CCat::init() {
	if(!Sprite::initWithSpriteFrameName("stay_1.png")) {
		return false;
	}

	this->setAnchorPoint(Vec2(0.5f, 0.1f));

	this->createAnim();	// 创建动画

	m_nRow = m_nCol = 4;
	m_nState = STATE::NONE;

	this->setCustomListener();	// 设置自定义事件监听

	return true;
}

//////////////////////////////////////////////////////////////////////////
// 改变状态
void CCat::changeState(int nState) {
	if(nState == m_nState) {
		return;
	}
	m_nState = nState;
	AnimationCache* pAnimCache = AnimationCache::getInstance();
	this->stopAllActions();
	if(m_nState == STATE::STAY) {
		Animate* pAnimStay = Animate::create(pAnimCache->getAnimation("CatStay"));
		RepeatForever* pForever = RepeatForever::create(pAnimStay);
		this->runAction(pForever);
	} else if(m_nState == STATE::BESIEGED) {
		Animate* pAnimBesieged = Animate::create(pAnimCache->getAnimation("CatBesieged"));
		RepeatForever* pForever = RepeatForever::create(pAnimBesieged);
		this->runAction(pForever);
	}
}

//////////////////////////////////////////////////////////////////////////
// 创建动画
void CCat::createAnim() {
	SpriteFrameCache* pChche = SpriteFrameCache::getInstance();	// 动画缓存
	AnimationCache* pAnimCache = AnimationCache::getInstance();	// 精灵帧缓存
	char szName[32] = {};

	// 一般状态的动画
	Animation* pAnimStay = Animation::create();
	for(int i = 0; i < 3; i++) {
		sprintf(szName, "stay_%d.png", i);
		pAnimStay->addSpriteFrame(pChche->getSpriteFrameByName(szName));
	}
	pAnimStay->setDelayPerUnit(0.2f);
	pAnimCache->addAnimation(pAnimStay, "CatStay");

	// 被围住的动画
	Animation* pAnimBesieged = Animation::create();
	for(int i = 1; i < 6; i++) {
		sprintf(szName, "besieged_%d.png", i);
		pAnimBesieged->addSpriteFrame(pChche->getSpriteFrameByName(szName));
	}
	pAnimBesieged->setDelayPerUnit(0.2f);
	pAnimCache->addAnimation(pAnimBesieged, "CatBesieged");
}

//////////////////////////////////////////////////////////////////////////
// 设置自定义事件监听
void CCat::setCustomListener() {
	// 游戏开始的自定义触发事件
	EventListenerCustom* pGameStartlistener = EventListenerCustom::create("GAME_START", [=](EventCustom* event) {
		m_nRow = m_nCol = 4;
		this->setPosition(CGameScene::getInstance()->getMap()->getPotByRank(4, 4)->getPosition());
		this->changeState(STATE::STAY);	// 接收到事件时改变状态
	});

	// 游戏结束的自定义触发事件
	EventListenerCustom* pGameOverlistener = EventListenerCustom::create("GAME_OVER", [=](EventCustom* event) {
		this->changeState(STATE::NONE);
	});

	// 被围
	EventListenerCustom* pBesiegedlistener = EventListenerCustom::create("CAT_BESIEGED", [=](EventCustom* event) {
		this->changeState(STATE::BESIEGED);
	});

	// 投递事件
	_eventDispatcher->addEventListenerWithFixedPriority(pGameStartlistener, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(pGameOverlistener, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(pBesiegedlistener, 1);
}

//////////////////////////////////////////////////////////////////////////
// 移动猫
//void CCat::moveCat()
//{
//	// 获取猫的位置
//	int nCol = this->getCol();
//	int nRow = this->getRow();
//
//	CMap* pMap = CGameScene::getInstance()->getMap();
//
//	if (nCol == 0 || nCol == 8 || nRow == 0 || nRow == 8)
//	{ // 猫在边界
//		_eventDispatcher->dispatchCustomEvent("GAME_FAILED");
//		return;
//	}
//
//	Vector<CPot *> VecPot;
//	if (!pMap->potIsBesieged(nCol - 1, nRow))
//	{ // 左
//		VecPot.pushBack(pMap->getPotByRank(nCol - 1, nRow));
//	}
//	if (!pMap->potIsBesieged(nCol + 1, nRow))
//	{ // 右
//		VecPot.pushBack(pMap->getPotByRank(nCol + 1, nRow));
//	}
//
//	if (nRow % 2)
//	{ // 奇数行
//		if (!pMap->potIsBesieged(nCol, nRow + 1))
//		{ // 左上
//			VecPot.pushBack(pMap->getPotByRank(nCol, nRow + 1));
//		}
//		if (!pMap->potIsBesieged(nCol + 1, nRow + 1))
//		{ // 右上
//			VecPot.pushBack(pMap->getPotByRank(nCol + 1, nRow + 1));
//		}
//		if (!pMap->potIsBesieged(nCol, nRow - 1))
//		{ // 左下
//			VecPot.pushBack(pMap->getPotByRank(nCol, nRow - 1));
//		}
//		if (!pMap->potIsBesieged(nCol + 1, nRow - 1))
//		{ // 右下
//			VecPot.pushBack(pMap->getPotByRank(nCol + 1, nRow - 1));
//		}
//	} else
//	{ // 偶数行
//		if (!pMap->potIsBesieged(nCol - 1, nRow + 1))
//		{ // 左上
//			VecPot.pushBack(pMap->getPotByRank(nCol - 1, nRow + 1));
//		}
//		if (!pMap->potIsBesieged(nCol, nRow + 1))
//		{ // 右上
//			VecPot.pushBack(pMap->getPotByRank(nCol, nRow + 1));
//		}
//		if (!pMap->potIsBesieged(nCol - 1, nRow - 1))
//		{ // 左下
//			VecPot.pushBack(pMap->getPotByRank(nCol - 1, nRow - 1));
//		}
//		if (!pMap->potIsBesieged(nCol, nRow - 1))
//		{ // 右下
//			VecPot.pushBack(pMap->getPotByRank(nCol, nRow - 1));
//		}
//	}
//
//	if (VecPot.size() == 0)
//	{ // 猫无处可逃
//		_eventDispatcher->dispatchCustomEvent("GAME_WIN");
//		return;
//	}
//
//	// 随机移动猫
//	int goIndex = rand() % VecPot.size();
//	CPot *pPot = VecPot.at(goIndex);
//	this->setPosition(pPot->getPosition());
//	this->setCol(pPot->getCol());
//	this->setRow(pPot->getRow());
//
//	if (pMap->isBesieged(pPot))
//	{
//		_eventDispatcher->dispatchCustomEvent("CAT_BESIEGED");
//	}
//	for (int i = 0; i < 9; i++)
//	{ // 列
//		for (int j = 0; j < 9; j++)
//		{ // 行
//			pMap->getPotByRank(i, j)->setSearched(false);
//		}
//	}
//}
