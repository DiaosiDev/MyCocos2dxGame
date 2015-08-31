//
//  Player.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/26.
//
//

#include "Player.h"
USING_NS_CC;

Player::Player()
{
    m_pIdleAnimation        = nullptr;
    m_pRunAnimation         = nullptr;
    m_pJumpAnimation        = nullptr;
    m_pSuperJumpAnimation   = nullptr;
    m_pShakeHeadAnimation   = nullptr;
    m_pTurnBackAnimation    = nullptr;
    m_pBackIdleAnimation    = nullptr;
    m_pBackFireRunAnimation     = nullptr;
    m_pBackJumpAnimation        = nullptr;
    m_pBackSuperJumpAnimation   = nullptr;
    m_pBackForwardRunAnimation  = nullptr;
    m_pSquatAnimation           = nullptr;
    
    m_PlayerType = PT_UNKNOWN;
    m_PlayerState = PS_UNKNOWN;
    m_PlayerDirection = PD_RIGHT;
    m_PlayerLastDirection = PD_RIGHT;
    
    m_bAcceptInput = true;
    m_bEquipedGun = false;
}
Player::~Player()
{
}
void Player::setPlayerState(PlayerState state)
{
    if (m_PlayerState == state)
        return;
    
    ///处理上一个状态退出逻辑
    switch (m_PlayerState) {
        case PS_IDLE:
            onExitIdleState();
            break;
        case PS_RUN:
            onExitRunState();
            break;
        case PS_JUMP:
            onExitJumpState();
            break;
        case PS_SUPERJUMP:
            onExitSuperJumpState();
            break;
        case PS_SHAKEHEAD:
            onExitShakeHead();
            break;
        case PS_TURNBACK:
            onExitTurnBackState();
            break;
        case PS_TURNFRONT:
            onExitTurnFrontState();
            break;
        case PS_BACKFORWARDRUN:
            onExitBackforwardRunState();
            break;
        case PS_SQUAT:
            onExitSquatState();
            break;
        case PS_DEATH:
            onExitDeathState();
            break;
        default:
            break;
    }
    
    m_PlayerState = state;
    ///处理下一个状态进入逻辑
    switch (m_PlayerState) {
        case PS_IDLE:
            onEnterIdleState();
            break;
        case PS_RUN:
            onEnterRunState();
            break;
        case PS_JUMP:
            onEnterJumpState();
            break;
        case PS_SUPERJUMP:
            onEnterSuperJumpState();
            break;
        case PS_SHAKEHEAD:
            onEnterShakeHead();
            break;
        case PS_TURNBACK:
            onEnterTurnBackState();
            break;
        case PS_TURNFRONT:
            onEnterTurnFrontState();
            break;
        case PS_BACKFORWARDRUN:
            onEnterBackforwardRunState();
            break;
        case PS_SQUAT:
            onEnterSquatState();
            break;
        case PS_DEATH:
            onEnterDeathState();
            break;
        default:
            break;
    }
}
void Player::setPlayerDirection(PLayerDirection direction)
{
    if(m_PlayerDirection == direction)
        return;
    m_PlayerLastDirection = m_PlayerDirection;
    m_PlayerDirection = direction;
    if(m_PlayerDirection == PD_LEFT)
        m_pSprite->setFlippedX(true);
    else if(m_PlayerDirection == PD_RIGHT)
        m_pSprite->setFlippedX(false);
}
void Player::onEnterIdleState()
{
    if(!m_pSprite)
        return;
    Animate* action = nullptr;
    switch (m_PlayerDirection) {
        case PD_LEFT:
        case PD_RIGHT:
            action = Animate::create(m_pIdleAnimation);
            m_pSprite->runAction(RepeatForever::create(Sequence::create(action, DelayTime::create(3.0f), NULL)));
            break;
        case PD_BACK:
            action = Animate::create(m_pBackIdleAnimation);
            m_pSprite->runAction(RepeatForever::create(action));
            break;
        default:
            break;
    }
}
void Player::onExitIdleState()
{
    m_pSprite->stopAllActions();
}

void Player::onEnterRunState()
{
    if(!m_pSprite)
        return;
    Animate* action = nullptr;
    switch (m_PlayerDirection) {
        case PD_LEFT:
        case PD_RIGHT:
            action = Animate::create(m_pRunAnimation);
            break;
        case PD_BACK:
            action = Animate::create(m_pBackFireRunAnimation);
            break;
        default:
            break;
    }
    m_pSprite->runAction(RepeatForever::create(action));
}
void Player::onExitRunState()
{
     m_pSprite->stopAllActions();
}

void Player::onEnterJumpState()
{
    if(!m_pSprite)
        return;
    Animate* action = nullptr;
    switch (m_PlayerDirection) {
        case PD_LEFT:
        case PD_RIGHT:
            action = Animate::create(m_pJumpAnimation);
            break;
        case PD_BACK:
            action = Animate::create(m_pBackJumpAnimation);
            break;
        default:
            break;
    }
    m_pSprite->runAction(action);
}
void Player::onExitJumpState()
{
    m_pSprite->stopAllActions();
}

void Player::onEnterSuperJumpState()
{
    if(!m_pSprite)
        return;
    Animate* action = nullptr;
    switch (m_PlayerDirection) {
        case PD_LEFT:
        case PD_RIGHT:
            action = Animate::create(m_pSuperJumpAnimation);
            break;
        case PD_BACK:
            action = Animate::create(m_pBackSuperJumpAnimation);
            break;
        default:
            break;
    }
    m_pSprite->runAction(action);
}
void Player::onExitSuperJumpState()
{
    m_pSprite->stopAllActions();
}

void Player::onEnterShakeHead()
{
    if(!m_pSprite)
        return;
    Animate* action = Animate::create(m_pShakeHeadAnimation);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Player::setPlayerState, this, PS_IDLE));
    Sequence* sequence = Sequence::create(action, callback, NULL);
    m_pSprite->runAction(sequence);
}
void Player::onExitShakeHead()
{
    m_pSprite->stopAllActions();
}

void Player::onEnterTurnBackState()
{
    if(!m_pSprite)
        return;
    Animate* action = Animate::create(m_pTurnBackAnimation);
    CallFunc* callback1 = CallFunc::create(CC_CALLBACK_0(Player::setPlayerDirection, this, PD_BACK));
    CallFunc* callback2 = CallFunc::create(CC_CALLBACK_0(Player::setPlayerState, this, PS_IDLE));
    Sequence* sequence = Sequence::create(action, callback1, callback2, NULL);
    m_pSprite->runAction(sequence);
}
void Player::onExitTurnBackState()
{
     m_pSprite->stopAllActions();
}

void Player::onEnterTurnFrontState()
{
    if(!m_pSprite)
        return;
    Animate* action = Animate::create(m_pTurnBackAnimation);
    CallFunc* callback1 = nullptr;
    if(m_PlayerLastDirection == PD_RIGHT)
        callback1 =CallFunc::create(CC_CALLBACK_0(Player::setPlayerDirection, this, PD_RIGHT));
    else if(m_PlayerLastDirection == PD_LEFT)
        callback1 =CallFunc::create(CC_CALLBACK_0(Player::setPlayerDirection, this, PD_LEFT));
    CallFunc* callback2 = CallFunc::create(CC_CALLBACK_0(Player::setPlayerState, this, PS_IDLE));
    Sequence* sequence = Sequence::create(action->reverse(), callback1, callback2, NULL);
    m_pSprite->runAction(sequence);

}
void Player::onExitTurnFrontState()
{
    m_pSprite->stopAllActions();
}
void Player::onEnterBackforwardRunState()
{
    if(!m_pSprite)
        return;
    Animate* action = Animate::create(m_pBackForwardRunAnimation);
    m_pSprite->runAction(RepeatForever::create(action));
}
void Player::onExitBackforwardRunState()
{
    m_pSprite->stopAllActions();
}
void Player::onEnterSquatState()
{
    if(!m_pSprite)
        return;
    Animate* action = Animate::create(m_pSquatAnimation);
    m_pSprite->runAction(RepeatForever::create(action));
}
void Player::onExitSquatState()
{
    m_pSprite->stopAllActions();
}
void Player::onEnterDeathState()
{
    disableAcceptInput();
}
void Player::onExitDeathState()
{
    enableAcceptInput();
}