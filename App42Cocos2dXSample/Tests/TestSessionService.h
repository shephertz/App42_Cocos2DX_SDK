//
//  TestSessionService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 16/07/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__TestSessionService__
#define __App42Cocos2dX3_0Sample__TestSessionService__

#include <iostream>
#include "cocos2d.h"
#include "App42API.h"

class TestSessionService : public cocos2d::Layer, public App42CallBack
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestSessionService);
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    
    /**
     * APIs Tests
     */
    void getSession(Ref* sender);
    void getSessionWithCreateFlag(Ref* sender);
    void invalidate(Ref* sender);
    void setAttribute(Ref* sender);
    void getAttribute(Ref* sender);
    void getAllAttributes(Ref* sender);
    void removeAttribute(Ref* sender);
    void removeAllAttributes(Ref* sender);
    
    void loadResponseScene();
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    void onSessionServiceRequestCompleted( void *response);
    
private:
    std::string apiKey;
    std::string secretKey;
    std::string sessionId;
    const char* attributeName;
    const char* attributeValue;
    vector<string> responseArray;
};
#endif /* defined(__App42Cocos2dX3_0Sample__TestSessionService__) */
