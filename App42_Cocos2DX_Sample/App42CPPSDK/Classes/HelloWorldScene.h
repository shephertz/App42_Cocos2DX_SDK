#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "App42API.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void onPushRequestCompleted(cocos2d::CCNode *sender, void *response);
    void onUserRequestCompleted(cocos2d::CCNode *sender, void *response);
    void onStorageRequestCompleted(cocos2d::CCNode *sender, void *response);
    void onGameRequestCompleted(cocos2d::CCNode *sender, void *response);
    void onRewardRequestCompleted(cocos2d::CCNode *sender, void *response);
    void onScoreBoardRequestCompleted(cocos2d::CCNode *sender, void *response);
    void onHttpRequestCompleted(cocos2d::CCNode *sender, void *response);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
    void testGameService();
    void testUserService();
    void testScoreService();
    void testScoreBoardService();
    void testRewardService();
    void testStorageService();
    void testPushService();
};

#endif // __HELLOWORLD_SCENE_H__
