//
//  GameController.h
//  TinyFlare
//
//  Created by wang haibo on 15/3/12.
//
//

#ifndef __TinyFlare__GameController__
#define __TinyFlare__GameController__

#include "cocos2d.h"
#include "TwoJoysticks.h"
#include "Player.h"
#include "EnemiesGenerator.h"
#include "MenuUI.h"
#include "MainUI.h"
#include "PauseUI.h"
#include "DeathUI.h"
typedef enum {
    GS_MENU = 0,
    GS_GAME,
    GS_PAUSE,
    GS_DEBUG,
    GS_UNKNOWN
} GameState;

class GameController : public cocos2d::Ref
{
    GameController();
    ~GameController();
public:
    static GameController* getInstance();
    bool init(cocos2d::Layer* pMainLayer);
    void update(float delta);
    void destroy();
    
    void nextStage();
    
    GameState getGameState() const;
    void setGameState(GameState state);
    
    Player* getPlayer() const;
    cocos2d::Layer* getGameLayer() const;
    cocos2d::Camera* getActorCamera() const;
    EnemiesGenerator* getEnemiesGenerator() const;
    
    cocos2d::Size getBoundSize() const;
    
    cocos2d::Vec2 getPlayerPos();
    cocos2d::Vec2 getPlayerOrientation();
    
    void checkBounce(GameActor* actor);
    
    void pause();
    void resume();
    bool isPaused() const;
    void pauseStart();
    void pauseEnd();
    
    void addStardust(ChaosNumber& num);
    void subStardust(ChaosNumber& num);
    
    cocos2d::Vec2 getStardustTargetPos();
    cocos2d::Vec2 getStardustStartPos();
    
    void resetData();

private:
    void onEnterMenu();
    void onExitMenu();
    
    void onEnterGame();
    void onExitGame();
    
    void onEnterPause();
    void onExitPause();
    
    void onEnterDebug();
    void onExitDebug();
    
    void menuStart();
    void menuEnd();
    
    void gameStart();
    void gameEnd();
private:
    cocos2d::Layer*     m_pGameLayer;
    cocos2d::Layer*     m_pUILayer;
    EnemiesGenerator*   m_pEnemiesGenerator;
    cocos2d::Camera*    m_pActorCamera;
    TwoJoysticks*       m_pTwoJoysticks;
    cocos2d::Layer*     m_pMainLayer;
    Player*             m_pPlayer;
    GameState           m_curGameState;
    cocos2d::Size       m_BoundSize;
    
    bool                m_bDebugMode;
    float               m_fRespawnTime;
    
    bool                m_pPaused;
    
    cocos2d::Vec2       m_StardustTargetPos;
    
    MenuUI*             m_pMenuUI;
    MainUI*             m_pMainUI;
    PauseUI*            m_pPauseUI;
    DeathUI*            m_pDeathUI;
};


#endif /* defined(__TinyFlare__GameController__) */