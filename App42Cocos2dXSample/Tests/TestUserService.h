//
//  TestUserService.h
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#ifndef __App42Cocos2dXSDK_3_0Beta2_Sample__TestUserService__
#define __App42Cocos2dXSDK_3_0Beta2_Sample__TestUserService__

#include <iostream>
#include "cocos2d.h"
#include "App42API.h"

class TestUserService : public cocos2d::Layer, public App42CallBack
{
public:
   
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestUserService);
    
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    
    void createUser(Ref* pSender);
    void createUserWithCustomData(Ref* pSender);
    void createUserWithRoles(Ref* pSender);
    void assignRoles(Ref *sender);
    
    void authenticateUser(Ref* pSender);
    void authenticateUserViaEmail(Ref *sender);
    void getUserWithUserName(Ref* pSender);
    void getUserWithCustomData(Ref* pSender);
    void getUserWithEmailId(Ref* pSender);
    void getUserInfo(Ref *sender);
    void getAllUser(Ref* pSender);
    void getAllUsersByPaging(Ref* pSender);
    void getAllUsersCount(Ref* pSender);
    void lockUser(Ref* pSender);
    void unlockUser(Ref* pSender);
    void getLockedUsers(Ref* pSender);
    void getLockedUsersByPaging(Ref* pSender);
    void getLockedUsersCount(Ref* pSender);
    void updateEmail(Ref* pSender);
    void deleteUser(Ref* pSender);
    void changePassword(Ref* pSender);
    void resetPassword(Ref* pSender);
    void createOrUpdateProfile(Ref* pSender);
    void getUserByProfileData(Ref* pSender);
    void logout(Ref* pSender);
    void getRolesByUser(Ref *sender);
    void deleteUserPermanent(Ref *sender);

    void getUsersByRole(Ref* sender);
    void revokeRole(Ref* sender);
    void revokeAllRoles(Ref* sender);
    void getUsersByGroup(Ref* sender);
    void createUserWithProfile(Ref *sender);
    void getAllUsersWithCustomData(Ref* pSender);
    
    void loadResponseScene();
    // a selector callback
    void onUserRequestCompleted( void *response);
    void menuCloseCallback(Ref* pSender);
private:
    std::string apiKey;
    std::string secretKey;
    cocos2d::LabelTTF *msgLabel;
    vector<string> responseArray;
};
#endif /* defined(__App42Cocos2dXSDK_3_0Beta2_Sample__TestUserService__) */
