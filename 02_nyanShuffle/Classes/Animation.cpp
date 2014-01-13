//
//  Animation.cpp
//  nyanshuffle
//
//  Created by cocos2d-x on 14/01/13.
//
//

#include "Animation.h"

#define WIN_WIDTH CCDirector::sharedDirector()->getWinSize().width
#define WIN_HEIGHT CCDirector::sharedDirector()->getWinSize().height

#define BOX_LOC_LEFT ccp( WIN_WIDTH * 0.2, WIN_HEIGHT * 0.5 )
#define BOX_LOC_CENTER ccp( WIN_WIDTH * 0.5, WIN_HEIGHT * 0.5 )
#define BOX_LOC_RIGHT ccp( WIN_WIDTH * 0.8, WIN_HEIGHT * 0.5 )

#define CONTROL_POINT_X1 WIN_WIDTH * 0.25
#define CONTROL_POINT_X2 WIN_WIDTH * 0.45
#define CONTROL_POINT_X3 WIN_WIDTH * 0.55
#define CONTROL_POINT_X4 WIN_WIDTH * 0.75

#define CONTROL_POINT_Y1 WIN_WIDTH * 0.8
#define CONTROL_POINT_Y2 WIN_WIDTH * 0.2
#define CONTROL_POINT_Y3 WIN_WIDTH * 0.65
#define CONTROL_POINT_Y4 WIN_WIDTH * 0.35

CCFiniteTimeAction* Animation::catStartAction()
{
    CCSkewTo* skew1 = CCSkewTo::create( 0.2, 1, 0 );
    CCSkewTo* skew2 = CCSkewTo::create( 0.2, -1, 0 );
    CCSequence* seq = CCSequence::createWithTwoActions( skew1, skew2 );
    CCRepeat* repeat = CCRepeat::create( seq, 10 );
    
    return repeat;
}

CCFiniteTimeAction* Animation::vibrationAnimation()
{
    CCMoveBy* move1 = CCMoveBy::create( 0.03, ccp( -5, 0 ) );
    CCMoveBy* move2 = CCMoveBy::create( 0.06, ccp( 10, 0 ) );
    CCMoveBy* move3 = CCMoveBy::create( 0.03, ccp( -5, 0 ) );
    CCSequence* moves = CCSequence::create( move1, move2, move3, NULL );
    
    return CCRepeat::create( moves, 2 );
}

CCFiniteTimeAction* Animation::boxesStartAction( CCObject* target, SEL_CallFunc selector )
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    int random = rand();
    
    float delayTime = 1;
    
    switch ( random % 5 )
    {
        case 0:
            delayTime = delayTime * 0.90;
            break;
        case 1:
            delayTime = delayTime * 0.95;
            break;
        case 2:
            delayTime = delayTime * 1.05;
            break;
        case 3:
            delayTime = delayTime * 1.10;
            break;
        default:
            break;
    }
    
    CCDelayTime* delay1 = CCDelayTime::create( delayTime );
    CCMoveBy* move1 = CCMoveBy::create( 1, ccp( 0, - size.height ) );
    CCEaseIn* ease1 = CCEaseIn::create( move1, 10 );
    
    CCDelayTime* delay2 = CCDelayTime::create( 0.9 );
    CCCallFunc* func = CCCallFunc::create( target, selector );
    CCFiniteTimeAction* seq = CCSequence::createWithTwoActions( delay2, func );
    
    CCSpawn* spawn = CCSpawn::createWithTwoActions( ease1, seq );
    
    return CCSequence::createWithTwoActions( delay1, spawn );
}

CCFiniteTimeAction* Animation::boxesStartActionWithVibration( CCObject* target, SEL_CallFunc selector )
{
    CCFiniteTimeAction* action1 = boxesStartAction( target, selector );
    CCFiniteTimeAction* action2 = Animation::vibrationAnimation();
    
    return CCSequence::createWithTwoActions( action1, action2 );
}

CCFiniteTimeAction* Animation::num3Animation()
{
    CCDelayTime* delay1 = CCDelayTime::create( 0.5 );
    CCScaleTo* scaleUp = CCScaleTo::create( 0.1, 1 );
    CCDelayTime* delay2 = CCDelayTime::create( 0.3 );
    CCScaleTo* scaleDown = CCScaleTo::create( 0.1, 0 );
    
    return CCSequence::create( delay1, scaleUp, delay2, scaleDown, NULL );
}

CCFiniteTimeAction* Animation::num2Animation()
{
    CCDelayTime* delay = CCDelayTime::create( 1 );
    
    return CCSequence::create( delay, Animation::num3Animation(), NULL );
}

CCFiniteTimeAction* Animation::num1Animation()
{
    CCDelayTime* delay = CCDelayTime::create( 2 );
    
    return CCSequence::create( delay, Animation::num3Animation(), NULL );
}

CCFiniteTimeAction* Animation::num0Animation( CCObject* target, SEL_CallFunc selector )
{
    CCDelayTime* delay = CCDelayTime::create( 3 );
    CCCallFunc* func = CCCallFunc::create( target, selector );
    
    return CCSequence::create( delay, Animation::num3Animation(), func, NULL );
}

CCFiniteTimeAction* Animation::moveFromLeftToCenter( float time )
{
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp( CONTROL_POINT_X1, CONTROL_POINT_Y1 );
    bezier.controlPoint_2 = ccp( CONTROL_POINT_X2, CONTROL_POINT_Y1 );
    bezier.endPosition = BOX_LOC_CENTER;
    
    CCFiniteTimeAction* action = CCBezierTo::create( time, bezier );
    action->setTag( TAG_ACTION );
    
    return action;
}

CCFiniteTimeAction* Animation::moveFromLeftToRight( float time )
{
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp( CONTROL_POINT_X1, CONTROL_POINT_Y1 );
    bezier.controlPoint_2 = ccp( CONTROL_POINT_X4, CONTROL_POINT_Y1 );
    bezier.endPosition = BOX_LOC_RIGHT;
    
    CCFiniteTimeAction* action = CCBezierTo::create( time, bezier );
    action->setTag( TAG_ACTION );
    
    return action;
}

CCFiniteTimeAction* Animation::moveFromCenterToLeft( float time )
{
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp( CONTROL_POINT_X2, CONTROL_POINT_Y2 );
    bezier.controlPoint_2 = ccp( CONTROL_POINT_X1, CONTROL_POINT_Y2 );
    bezier.endPosition = BOX_LOC_LEFT;
    
    CCFiniteTimeAction* action = CCBezierTo::create( time, bezier );
    action->setTag( TAG_ACTION );
    
    return action;
}

CCFiniteTimeAction* Animation::moveFromCenterToRight( float time )
{
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp( CONTROL_POINT_X3, CONTROL_POINT_Y2 );
    bezier.controlPoint_2 = ccp( CONTROL_POINT_X4, CONTROL_POINT_Y1 );
    bezier.endPosition = BOX_LOC_RIGHT;
    
    CCFiniteTimeAction* action = CCBezierTo::create( time, bezier );
    action->setTag( TAG_ACTION );
    
    return action;
}

CCFiniteTimeAction* Animation::moveFromRightToLeft( float time )
{
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp( CONTROL_POINT_X4, CONTROL_POINT_Y2 );
    bezier.controlPoint_2 = ccp( CONTROL_POINT_X1, CONTROL_POINT_Y2 );
    bezier.endPosition = BOX_LOC_LEFT;
    
    CCFiniteTimeAction* action = CCBezierTo::create( time, bezier );
    action->setTag( TAG_ACTION );
    
    return action;
}

CCFiniteTimeAction* Animation::moveFromRightToCenter( float time )
{
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp( CONTROL_POINT_X4, CONTROL_POINT_Y2 );
    bezier.controlPoint_2 = ccp( CONTROL_POINT_X3, CONTROL_POINT_Y2 );
    bezier.endPosition = BOX_LOC_CENTER;
    
    CCFiniteTimeAction* action = CCBezierTo::create( time, bezier );
    action->setTag( TAG_ACTION );
    
    return action;
}

