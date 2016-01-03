//
//  TestBuddyService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 21/07/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__TestBuddyService__
#define __App42Cocos2dX3_0Sample__TestBuddyService__

#include <iostream>
#include "TestHome.h"

class TestBuddyService : public cocos2d::Layer, public App42CallBack
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestBuddyService);
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    
    /**
     * APIs Tests
     */
    void sendFrndRequest(Ref* sender);
    void getFrndRequest(Ref* sender);
    void acceptFriendRequest(Ref* sender);
    void rejectFriendRequest(Ref* sender);
    void getAllFriends(Ref* sender);
    void createGroup(Ref* sender);
    void addFriendsToGroup(Ref* sender);
    void getAllGroups(Ref* sender);
    void getAllFriendsInGroup(Ref* sender);
    
    void blockFriendRequest(Ref* sender);
    void blockUser(Ref* sender);
    void unblockUser(Ref* sender);
    void sendMessageToGroup(Ref* sender);
    void sendMessageToFriend(Ref* sender);
    void sendMessageToFriends(Ref* sender);
    void getAllMessages(Ref* sender);
    void getAllMessagesFromBuddy(Ref* sender);
    void getAllMessagesFromGroup(Ref* sender);
    void unFriend(Ref* sender);
    void deleteMessageById(Ref* sender);
    void deleteMessageByIds(Ref* sender);
 
    void checkedInGeoLocation(Ref* sender);
    void getFriendsByLocation(Ref* sender);

    
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    void onBuddyServiceRequestCompleted( void *response);
    void loadResponseScene();

private:
    std::string apiKey;
    std::string secretKey;
    const char* groupName;
    const char* ownerName;
    const char* userName;
    const char* buddyName;
    const char* message;
    const char* messageId;
    vector<string> responseArray;
};

#endif /* defined(__App42Cocos2dX3_0Sample__TestBuddyService__) */
