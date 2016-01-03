//
//  TestTimerService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev on 19/08/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__TestTimerService__
#define __App42Cocos2dX3_0Sample__TestTimerService__

#include <iostream>
#include "TestHome.h"

class TestTimerService : public cocos2d::Layer, public App42CallBack
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestTimerService);
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    /**
     * APIs Tests
     */
    void createOrUpdateTimer(Ref *sender);
    void startTimer(Ref *sender);
    
    
    void loadResponseScene();
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    void onTimerServiceRequestCompleted( void *response);
    
private:
    std::string apiKey;
    std::string secretKey;
    const char* timerName;
    const char* userName;

    vector<string> responseArray;
};
#endif /* defined(__App42Cocos2dX3_0Sample__TestTimerService__) */
