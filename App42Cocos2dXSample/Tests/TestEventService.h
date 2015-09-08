//
//  TestEventService.h
//  App42Cocos2dXSample
//
//  Created by Rajeev Ranjan on 06/07/15.
//
//

#ifndef __App42Cocos2dXSample__TestEventService__
#define __App42Cocos2dXSample__TestEventService__

#include <stdio.h>
#include "cocos2d.h"
#include "App42API.h"

class TestEventService : public cocos2d::Layer, public App42CallBack
{
public:
    
    TestEventService *eventServiceTemp;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestEventService);
    
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    void loadResponseScene();
    // a selector callback
    void onEventRequestCompleted( void *response);
    void menuCloseCallback(Ref* pSender);
    
    
    void trackEvent(Ref* pSender);
    
private:
    std::string apiKey;
    std::string secretKey;
    cocos2d::LabelTTF *msgLabel;
    vector<string> responseArray;
};

#endif /* defined(__App42Cocos2dXSample__TestEventService__) */
