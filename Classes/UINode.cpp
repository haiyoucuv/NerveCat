#include "UINode.h"

CUINode::CUINode() {
}

CUINode::~CUINode() {
}

bool CUINode::init() {
	if(!Node::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();

	// Logo
	m_pLogo = Sprite::createWithSpriteFrameName("logo.png");
	m_pLogo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(m_pLogo);

	// 胜利UI
	m_pVector = Sprite::createWithSpriteFrameName("victory.png");
	m_pVector->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	m_pVector->setVisible(false);
	this->addChild(m_pVector);

	// 失败UI
	m_pFailed = Sprite::createWithSpriteFrameName("failed.png");
	m_pFailed->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	m_pFailed->setVisible(false);
	this->addChild(m_pFailed);

	// 开始按钮
	m_pBtnStart = MenuItemImage::create();
	m_pBtnStart->setNormalSpriteFrame(pCache->getSpriteFrameByName("btn_start.png"));
	m_pBtnStart->setSelectedSpriteFrame(pCache->getSpriteFrameByName("btn_start.png"));
	m_pBtnStart->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 5);
	m_pBtnStart->setCallback(CC_CALLBACK_1(CUINode::buttonCallFun, this));

	// 再来一次按钮
	m_pBtnReplay = MenuItemImage::create();
	m_pBtnReplay->setNormalSpriteFrame(pCache->getSpriteFrameByName("btn_replay.png"));
	m_pBtnReplay->setSelectedSpriteFrame(pCache->getSpriteFrameByName("btn_replay.png"));
	m_pBtnReplay->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 5);
	m_pBtnReplay->setCallback(CC_CALLBACK_1(CUINode::buttonCallFun, this));
	m_pBtnReplay->setVisible(false);

	// 菜单层
	Menu* pMenu = Menu::create(m_pBtnStart, m_pBtnReplay, nullptr);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu);

	return true;
}

void CUINode::buttonCallFun(Ref* pSender) {
	if(pSender == m_pBtnStart){
		m_pLogo->setVisible(false);
		m_pBtnStart->setVisible(false);
		m_pBtnReplay->setVisible(true);
	}
	this->setVisible(false);
	_eventDispatcher->dispatchCustomEvent("GAME_START");	// 投递游戏开始的自定义事件
}
