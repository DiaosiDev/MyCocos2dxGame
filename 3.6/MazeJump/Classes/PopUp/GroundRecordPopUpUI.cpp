//
//  GroundRecordPopUpUI.cpp
//
//
//
//

#include "GroundRecordPopUpUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "UIManager.h"
#include "GameController.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

GroundRecordPopUpUI* GroundRecordPopUpUI::create()
{
    GroundRecordPopUpUI *pRet = new(std::nothrow) GroundRecordPopUpUI();
    if (pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

GroundRecordPopUpUI::GroundRecordPopUpUI()
{
}
GroundRecordPopUpUI::~GroundRecordPopUpUI()
{
}

void GroundRecordPopUpUI::onEnter()
{
    BasePopUpUI::onEnter();
    init();
}
void GroundRecordPopUpUI::onExit()
{
    BasePopUpUI::onExit();
}
bool GroundRecordPopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;

    m_popupBgLayer = cocos2d::ui::ImageView::create(UtilityHelper::getLocalString("UI_GROUND_HELP_PANEL"),cocos2d::ui::TextureResType::PLIST);
    m_popupBgLayer->setPosition(Vec2(size.width*0.5,size.height*0.5));
    m_popupBgLayer->setScale(scale);
    m_dialogLayer->addChild(m_popupBgLayer);
    
    
    cocos2d::ui::Button* reviveBtn = cocos2d::ui::Button::create(UtilityHelper::getLocalString("UI_GROUND_BTN_SUC_BACK"),"","",cocos2d::ui::TextureResType::PLIST);
    reviveBtn->setScale(scale);
    reviveBtn->setPosition(Vec2(size.width*0.5,size.height*0.47));
    m_dialogLayer->addChild(reviveBtn);
    
    reviveBtn->addClickEventListener(CC_CALLBACK_1(GroundRecordPopUpUI::onBack, this));
    return true;
}
void GroundRecordPopUpUI::onBack(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->hidePopUp(true,CC_CALLBACK_0(GroundRecordPopUpUI::onHidePopUpEnd, this));
}
void GroundRecordPopUpUI::onHidePopUpEnd()
{
    if (GameController::getInstance()->getMazeMode() == GameController::MAZE) {
        
        GameController::getInstance()->changeToMap(false, Value(localStorageGetItem(USER_MAZE_LEVEL)).asInt());
        
    }else if (GameController::getInstance()->getMazeMode() == GameController::NORAML)
    {
        GameController::getInstance()->switchToRainbowRun();
    }
}
