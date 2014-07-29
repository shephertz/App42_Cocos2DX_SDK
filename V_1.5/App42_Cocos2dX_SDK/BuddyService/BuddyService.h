//
//  BuddyService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 18/07/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__BuddyService__
#define __App42Cocos2dX3_0Sample__BuddyService__

#include <iostream>
#include "App42Service.h"
#include "App42GeoPoint.h"

using namespace std;

class BuddyService : public App42Service
{
    
private:
    BuddyService();
    static BuddyService* _instance;
    string buildSendFriendRequest(const char* userName, const char* buddyName, const char* message,const char* groupName="",const char* ownerName = "");
    string buildAddFriendToGroupRequest(const char* userName, const char* groupName, const char* friends);
    string buildCheckedInUserRequest(const char* userName, const char* points);
    
public:
    
	/**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
	
    static BuddyService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of BuddyService.
     *
     * @return BuddyService - BuddyService Object
     */
	static BuddyService* getInstance();
    
    /**
     * Send friend request allow you to send the buddy request to the user.
     *
     * @param userName
     *            - Name of the user who wanted to send the request to the
     *            buddy.
     * @param buddyName
     *            - Name of buddy for whom you sending the request.
     * @param message
     *            - Message to the user.
     * @return - void
     * @throws App42Exception
     */
    void SendFriendRequest(const char* userName, const char* buddyName, const char* message, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Fetch all the friend request for the user.
     *
     * @param userName
     *      - Name of user for which request has to be fetched.
     * @return void
     * @throws App42Exception
     */
    void GetFriendRequest(const char* userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Accept the friend request of the user.
     *
     * @param userName
     *            - Name of the user who is going to accept the request.
     * @param buddyName
     *            - Name of the buddy whose request has to be accepted.
     * @return - void
     * @throws App42Exception
     */
    void AcceptFriendRequest(const char* userName, const char* buddyName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Reject the friend request of the user
     *
     * @param userName
     *            - Name of user who is rejecting friend request.
     * @param buddyName
     *            - Name of user whose friend request has to reject.
     * @return void
     * @throws App42Exception
     */
    void RejectFriendRequest(const char* userName, const char* buddyName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Creates group for the user
     * @param userName
     *            - Name of the user who want to create the group
     * @param groupName
     *            - Name of the group which is to be create
     * @return void
     * @throws App42Exception
     */
    void CreateGroupByUser(const char* userName, const char* groupName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    /**
     * Fetches all friends of a user
     * @param userName
     *            - Name of the user
     * @return void
     * @throws App42Exception
     */
    void GetAllFriends(const char* userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    /**
     *
     * @param userName
     *            - Name of the user who want to add friend in group
     * @param groupName
     *            - Name of the group in which friend had to be added
     * @param friends
     *            - List of friend which has to be added in group
     * @return Buddy object
     * @throws App42Exception
     */
    void AddFriendsToGroup(const char* userName, const char* groupName, vector<string>friends, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
   
    /**
	 *
	 * @param userName
	 *            - Name of the user who want to checkedIn the geo location
	 * @param point
	 *            - geo points of user which is to checkedIn
	 * @return void
	 * @throws App42Exception
	 */
	void CheckedInGeoLocation(const char* userName, App42GeoPoint* point, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 *
	 * @param userName
	 * @param latitude
	 * @param longitude
	 * @param maxDistance
	 * @param max
	 * @return
	 * @throws App42Exception
	 */
	void GetFriendsByLocation(const char* userName,double latitude, double longitude, double maxDistance,int max, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    
    /**
     * Get All groups created by user
     *
     * @param userName
     *            - Name of the user for which group has to be fetched.
     * @return Buddy object
     * @throws App42Exception
     */
    void GetAllGroups(const char* userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Get All friends in specific group
     *
     * @param userName
     *            : name of user who is frtching the friends in group
     * @param ownerName
     *            : name of group owner
     * @param groupName
     *            : name of group
     * @return void
     * @throws App42Exception
     */
    void GetAllFriendsInGroup(const char* userName, const char* ownerName, const char* groupName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     *
     * @param userName
     *            - Name of the user who is blocking the friend request.
     * @param buddyName
     *            - Name of user whose friend request has to block.
     * @return void
     * @throws App42Exception
     */
    void BlockFriendRequest(const char* userName, const char* buddyName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 * Never get any request by this user
	 *
	 * @param userName
	 *            : name of the user who is blocking.
	 * @param buddyName
	 *            : name of the user to whom to block.
	 * @return void
	 * @throws App42Exception
	 */
	void BlockUser(const char* userName, const char* buddyName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 * Unblock User
	 *
	 * @param userName
	 *            : name of the user who is blocking.
	 * @param buddyName
	 *            : name of the user to whom to block.
	 * @return void
	 * @throws App42Exception
	 */
	void UnblockUser(const char* userName, const char* buddyName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 * Send the message to the group.
	 *
	 * @param userName
	 *            - Name of the user who wan't to send the message.
	 * @param ownerName
	 *            - Name of the user who created the group for which are going
	 *            to send the message
	 * @param groupName
	 *            - Name of the group which is created by the ownerUser.
	 * @param message
	 *            - Message for the receiver.
	 * @return - void
	 * @throws App42Exception
	 */
	void SendMessageToGroup(const char* userName, const char* ownerName, const char* groupName, const char* message, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 *
	 * @param userName
	 *            - Name of the user who want to send message.
	 * @param buddyName
	 *            - Name of buddy to whom message has to send.
	 * @param message
	 * @return void
	 * @throws App42Exception
	 */
	void SendMessageToFriend(const char* userName, const char* buddyName, const char* message, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 *
	 * @param userName
	 *            - Name of the user who want to send message to friends
	 * @param message
	 *            - which message has to send
	 * @return void
	 * @throws App42Exception
	 */
	void SendMessageToFriends(const char* userName, const char* message, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 *
	 * @param userName
	 *            - Name of the user for which message has to fetch.
	 * @return Buddy object
	 * @throws App42Exception
	 */
	void GetAllMessages(const char* userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 *
	 * @param userName
	 *            - Name of the user who want to fetch the message from buddy
	 * @param buddyName
	 *            - Name of Buddy for which message has to fetch.
	 * @return Buddy object
	 * @throws App42Exception
	 */
    
	void GetAllMessagesFromBuddy(const char* userName, const char* buddyName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 *
	 * @param userName
	 *            - Name of the user who want to fetch the message from the
	 *            group
	 * @param groupOwner
	 *            - Name of owner of the group
	 * @param groupName
	 *            - Name of the group from which message has to fetch
	 * @return Buddy object
	 * @throws App42Exception
	 */
	void GetAllMessagesFromGroup(const char* userName, const char* ownerName, const char* groupName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 *
	 * @param userName
	 * @param buddyName
	 * @return
	 * @throws App42Exception
	 */
	void UnFriend(const char* userName, const char* buddyName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 *
	 * @param userName
	 * @param messageId
	 * @return
	 * @throws App42Exception
	 */
	void DeleteMessageById(const char* userName, const char* messageId, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 *
	 * @param userName
	 * @param messageIds
	 * @return
	 * @throws App42Exception
	 */
	
	void DeleteMessageByIds(const char* userName, vector<string> messageIds, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
};
#endif /* defined(__App42Cocos2dX3_0Sample__BuddyService__) */
