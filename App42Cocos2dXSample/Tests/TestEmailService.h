//
//  TestEmailService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 08/04/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__TestEmailService__
#define __App42Cocos2dX3_0Sample__TestEmailService__

#include <iostream>
#include "cocos2d.h"
#include "App42API.h"

class TestEmailService : public cocos2d::Layer, public App42CallBack
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestEmailService);
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    
    /**
     * APIs Tests
     */
    void configureEmail(Ref *sender);
    void removeConfiguration(Ref *sender);
    void getConfiguration(Ref *sender);
    void sendMail(Ref *sender);
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    void onEmailRequestCompleted( void *response);
    void loadResponseScene();
    
private:
    std::string apiKey;
    std::string secretKey;
    vector<string> responseArray;
    
};

#endif /* defined(__App42Cocos2dX3_0Sample__TestEmailService__) */
