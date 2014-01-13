//
//  GameScene.h
//  nyan25
//
//  Created by cocos2d-x on 14/01/12.
//
//

#ifndef __nyan25__GameScene__
#define __nyan25__GameScene__

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
private:
    int nextNumber;
    float gametime;
    bool pauseFlag;
    
    void makeBackground();
    void makeCards();
    void measureGametime( float fDelta );
    void showGametimeLabel();
    void makeRetryButton();
    void makePauseButton();
    void tapRetryButton( CCNode *node );
    void tapPauseButton( CCNode *node );
    void showHighScoreLabel();
    void pause();
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC( GameScene );
    
    virtual bool ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );
    virtual void ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );
};

#endif /* defined(__nyan25__GameScene__) */
