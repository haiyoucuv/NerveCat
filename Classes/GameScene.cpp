#include "GameScene.h"

CGameScene *CGameScene::m_pInstance = nullptr;

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
}

//////////////////////////////////////////////////////////////////////////
// 获得单例
CGameScene *CGameScene::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = CGameScene::create();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
// 摧毁
void CGameScene::destroy()
{
	m_pInstance = nullptr;
}

//////////////////////////////////////////////////////////////////////////
// 初始化
bool CGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	this->loadRes(); // 加载资源

	m_PotSize = CPot::create()->getPot2()->getContentSize();
	m_VisibleSize = Director::getInstance()->getVisibleSize();
	m_Origin = Director::getInstance()->getVisibleOrigin();

	// 背景
	Sprite *pBg = Sprite::createWithSpriteFrameName("bg.jpg");
	pBg->setPosition(m_Origin.x + m_VisibleSize.width / 2, m_Origin.y + m_VisibleSize.height / 2);
	this->addChild(pBg);

	// 创建地图
	m_pMap = CMap::create();
	this->addChild(m_pMap);

	// 猫
	m_pCat = CCat::create();
	m_pCat->setPosition(m_pMap->getPotByRank(4, 4)->getPosition());
	this->addChild(m_pCat);

	// UI层
	m_pUINode = CUINode::create();
	this->addChild(m_pUINode);

	m_pTouchNode = CTouchNode::create();
	this->addChild(m_pTouchNode);

	// 初始状态
	m_nGameState = GAMESTATE::MENU;

	this->setCustomListener(); // 设置自定义事件监听

	return true;
}

//////////////////////////////////////////////////////////////////////////
// 加载资源
void CGameScene::loadRes()
{
	SpriteFrameCache *pCache = SpriteFrameCache::getInstance();
	pCache->addSpriteFramesWithFile("Image/UI.plist");
	pCache->addSpriteFramesWithFile("Image/stay.plist");
	pCache->addSpriteFramesWithFile("Image/besieged.plist");
}

//////////////////////////////////////////////////////////////////////////
// 设置自定义事件监听
void CGameScene::setCustomListener()
{
	// 游戏开始的自定义触发事件
	EventListenerCustom *pGameStartlistener = EventListenerCustom::create("GAME_START", [=](EventCustom *event)
	{
		m_nGameState = GAMESTATE::GAME;
	});

	// 游戏胜利
	EventListenerCustom *pGameWinlistener = EventListenerCustom::create("GAME_WIN", [=](EventCustom *event)
	{
		m_nGameState = GAMESTATE::WIN;
		m_pUINode->getImgVector()->setVisible(true);
		m_pUINode->getImgFailed()->setVisible(false);
		m_pUINode->setVisible(true);
	});

	// 游戏失败
	EventListenerCustom *pGameFailedlistener = EventListenerCustom::create("GAME_FAILED", [=](EventCustom *event)
	{
		m_nGameState = GAMESTATE::FAILED;
		m_pUINode->getImgVector()->setVisible(false);
		m_pUINode->getImgFailed()->setVisible(true);
		m_pUINode->setVisible(true);
	});

	// 投递事件
	_eventDispatcher->addEventListenerWithFixedPriority(pGameStartlistener, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(pGameWinlistener, 1);
	_eventDispatcher->addEventListenerWithFixedPriority(pGameFailedlistener, 1);
}
