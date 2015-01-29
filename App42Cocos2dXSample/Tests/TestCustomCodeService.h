//
//  TestCustomCodeService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 14/05/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__TestCustomCodeService__
#define __App42Cocos2dX3_0Sample__TestCustomCodeService__

#include <iostream>
#include "cocos2d.h"
#include "App42API.h"

class TestCustomCodeService : public cocos2d::Layer, public App42CallBack
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestCustomCodeService);
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    
    /**
     * APIs Tests
     */
    void runJavaCode(Ref *sender);
    
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    void onCustomCodeServiceRequestCompleted( void *response);
    void loadResponseScene();
    
private:
    std::string apiKey;
    std::string secretKey;
    vector<string> responseArray;
};

#endif /* defined(__App42Cocos2dX3_0Sample__TestCustomCodeService__) */
