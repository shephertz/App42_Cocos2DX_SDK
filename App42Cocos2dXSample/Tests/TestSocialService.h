//
//  TestSocialService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 26/06/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__TestSocialService__
#define __App42Cocos2dX3_0Sample__TestSocialService__

#include <iostream>
#include "cocos2d.h"
#include "App42API.h"

class TestSocialService : public cocos2d::Layer, public App42CallBack
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestSocialService);
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    
    /**
     * APIs Tests
     */
    void linkUserFacebookAccount(Ref *sender);
    void linkUserFacebookAccountWithToken(Ref *sender);
    void updateFBStatus(Ref *sender);
    void getFBFriends(Ref *sender);
    void getFBFriendsForAccessToken(Ref *sender);
    void facebookPublishStream(Ref *sender);
    void facebookLinkPost(Ref *sender);
    void facebookLinkPostWithCustomThumbnail(Ref *sender);
    void getFacebookProfile(Ref *sender);
    void getFacebookProfilesFromIds(Ref *sender);
    
    void linkUserTwitterAccount(Ref *sender);
    void linkUserTwitterAccountAccessCredentials(Ref *sender);
    void updateTWStatus(Ref *sender);
    
    void linkUserLinkedInAccount(Ref *sender);
    void linkUserLinkedInAccountAccessCredentials(Ref *sender);
    void updateLinkedInStatus(Ref *sender);
    void updateSocialStatusForAll(Ref* sender);
    // a selector callback
    void menuCloseCallback(Ref* pSender);//( void *response)
    void onSocialServiceRequestCompleted( void *response);
    
    void loadResponseScene();
private:
    std::string apiKey;
    std::string secretKey;
    vector<string> responseArray;
};

#endif /* defined(__App42Cocos2dX3_0Sample__TestSocialService__) */
