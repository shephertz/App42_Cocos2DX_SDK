//
//  TestAvatarService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 02/07/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__TestAvatarService__
#define __App42Cocos2dX3_0Sample__TestAvatarService__

#include <iostream>
#include "TestHome.h"

class TestAvatarService : public cocos2d::Layer, public App42CallBack
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestAvatarService);
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    
    /**
     * APIs Tests
     */
    void createAvatar(Ref* sender);
    void createAvatarWithFileData(Ref *sender);
    void createAvatarFromFacebook(Ref* sender);
    void createAvatarFromWebUrl(Ref* sender);
    void getAvatarByName(Ref* sender);
    void getAllAvatars(Ref* sender);
    void getCurrentAvatar(Ref *sender);
    void changeCurrentAvatar(Ref *sender);
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    void onAvatarServiceRequestCompleted( void *response);
    void loadResponseScene();
    
private:
    std::string apiKey;
    std::string secretKey;
    vector<string> responseArray;
};

#endif /* defined(__App42Cocos2dX3_0Sample__TestAvatarService__) */
