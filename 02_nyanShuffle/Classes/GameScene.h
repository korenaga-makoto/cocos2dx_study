//
//  GameScene.h
//  nyanshuffle
//
//  Created by cocos2d-x on 14/01/13.
//
//

#ifndef __nyanshuffle__GameScene__
#define __nyanshuffle__GameScene__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public cocos2d::CCLayer
{
protected:
    CCSprite* m_pCat;
    CCMenuItemImage* m_pBox1;
    CCMenuItemImage* m_pBox2;
    CCMenuItemImage* m_pBox3;
    
    void playDroppingSound();
    
    void showCountdown();
    void playCountdownSound();
    void startShuffle();
    
    enum kBoxLocation
    {
        kBoxLocation_Left = 101,
        kBoxLocation_Center,
        kBoxLocation_Right,
    };
    float m_totalShuffleTime;
    CCMenuItemImage* getLeftBox();
    CCMenuItemImage* getCenterBox();
    CCMenuItemImage* getRightBox();
    void shufflePattern1( float time );
    void shufflePattern2( float time );
    void shufflePattern3( float time );
    void shufflePattern4( float time );
    void shufflePattern5( float time );
    void boxesShuffle( float time );
    void afterShuffle();
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC( GameScene );
};

#endif /* defined(__nyanshuffle__GameScene__) */
