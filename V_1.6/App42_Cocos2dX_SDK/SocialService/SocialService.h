//
//  SocialService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 26/06/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__SocialService__
#define __App42Cocos2dX3_0Sample__SocialService__

#include <iostream>
#include "App42Service.h"

using namespace std;


class SocialService : public App42Service
{
    
private:
    SocialService();
    static SocialService* _instance;
    string buildLinkFacebookAccountRequest(const char* userName, const char* accessToken, const char* appId, const char* appSecret, const char* status);
    string buildFacebookLinkPostRequest(const char* accessToken, const char* link, const char* message,const char* pictureUrl="",const char* fileName="",const char* description="");
    string buildLinkTwitterAccountRequest(const char* userName, const char* consumerKey, const char*consumerSecret, const char* accessToken, const char* accessTokenSecret);
    string buildLinkUserLinkedInAccountRequest(const char* userName, const char* linkedInApiKey, const char*linkedInSecretKey, const char* accessToken, const char* accessTokenSecret);
public:
    
    
	/**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
	
    static SocialService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of SocialService.
     *
     * @return SocialService - SocialService Object
     */
	static SocialService* getInstance();
    
    /******************************************************************************************************/
    /*****************************            FACEBOOK RELATED APIS            ****************************/
    /******************************************************************************************************/

    /**
     * Links the User Facebook access credentials to the App User account.
     *
     * @param userName
     *            - Name of the user whose Facebook account to be linked
     * @param accessToken
     *            - Facebook Access Token that has been received after
     *            authorization
     * @param appId
     *            - Facebook App Id
     * @param appSecret
     *            - Facebook App Secret
     *
     * @returns The App42SocialResponse object
     *
     */
    void LinkUserFacebookAccount(const char *userName, const char *accessToken, const char *appId, const char *appSecret, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Links the User Facebook access credentials to the App User account.
     *
     * @param userName
     *            - Name of the user whose Facebook account to be linked
     * @param accessToken
     *            - Facebook Access Token that has been received after
     *            authorization
     *
     * @returns The App42SocialResponse object
     *
     */
    void LinkUserFacebookAccount(const char *userName, const char *accessToken, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Updates the Facebook status of the specified user.
     *
     * @param userName
     *            - Name of the user for whom the status needs to be updated
     * @param status
     *            - status that has to be updated
     *
     * @returns The App42SocialResponse object
     *
     */
    void UpdateFacebookStatus(const char *userName, const char *status, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * This function returns a list of facebook friends of the specified user by
     * accessing the facebook account.
     *
     * @param userName
     *            - Name of the user whose Facebook friends account has to be
     *            retrieve
     * @return App42SocialResponse Object
     * @throws App42Exception
     */
    void GetFacebookFriendsFromLinkUser(const char *userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * This function returns a list of facebook friends of the specified user
     * using a given authorization token. To get the friend list here, user
     * needs not to log into the facebook account.
     *
     * @param accessToken
     *            - Facebook Access Token that has been received after authorization
     * @return App42SocialResponse Object
     * @throws App42Exception
     */
    void GetFacebookFriendsFromAccessToken(const char *accessToken, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     *
     * Share binary files on your facebook wall with custom message.
     *
     * @param accessToken
     *            - Facebook Access Token that has been received after
     *            authorization
     * @param name
     *            - name of the file which has to be share.
     * @param filePath
     *            - file path of your local machiene
     * @param message
     *            - Message which has to be post with Link.
     * @return App42SocialResponse Object
     * @throws App42Exception
     */
    void FacebookPublishStream(const char *accessToken, const char *fileName, const char *filePath, const char *message, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     *
     * Share your link on facebook based on access token.
     *
     * @param accessToken
     *            - Facebook Access Token that has been received after
     *            authorization.
     * @param link
     *            - Link which has to be post on facebook wall.
     * @param message
     *            - Message which has to be post with Link.
     * @return App42SocialResponse Object
     * @throws App42Exception
     */
    void FacebookLinkPost(const char* accessToken, const char* link, const char* message, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     *
     * Share your link on facebook based on custom image and message.
     *
     * @param accessToken
     *            -Facebook Access Token that has been received after
     *            authorization
     * @param link
     *            - Link which has to be share on facebook.
     * @param message
     *            - Message which has to be share with Link.
     * @param pictureUrl
     *            - Your Thumbnail image url which you want to share on
     *            facebook.
     * @param name
     *            - Name of your File.
     * @param description
     *            - Description about your link.
     * @return App42SocialResponse Object
     * @throws App42Exception
     */
    void FacebookLinkPostWithCustomThumbnail(const char* accessToken, const char* link, const char* message,const char* pictureUrl, const char* fileName, const char* description, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Fetch the profile info like profile pic ,facebookID and user name based
     * on facebook access token.
     *
     * @param accessToken
     *            -Facebook Access Token for which Profile Info has to be
     *            fetched.
     * @return App42SocialResponse Object
     * @throws App42Exception
     */
    void GetFacebookProfile(const char* accessToken, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Get the facebook profile info for the gives IDs
     *
     * @param facebookIds
     *            - facebook id(s) of the user(s) for which facebook profile
     *            info is to fetch.
     * @return App42SocialResponse object
     * @throws App42Exception
     */
    void GetFacebookProfilesFromIds(vector<string> facebookIds, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /******************************************************************************************************/
    /*****************************             TWITTER RELATED APIS            ****************************/
    /******************************************************************************************************/
    
    /**
     * Links the User Twitter access credentials to the App User account.
     *
     * @param userName
     *            - Name of the user whose Twitter account to be linked
     * @param consumerKey
     *            - Twitter App Consumer Key
     * @param consumerSecret
     *            - Twitter App Consumer Secret
     * @param accessToken
     *            - Twitter Access Token that has been received after
     *            authorization
     * @param accessTokenSecret
     *            - Twitter Access Token Secret that has been received after
     *            authorization
     *
     * @returns The App42SocialResponse object
     */
    void LinkUserTwitterAccount(const char* userName, const char* consumerKey, const char*consumerSecret, const char* accessToken, const char* accessTokenSecret, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    /**
     * Links the User Twitter access credentials to the App User account.
     *
     * @param userName
     *            - Name of the user whose Twitter account to be linked
     * @param accessToken
     *            - Twitter Access Token that has been received after
     *            authorization
     * @param accessTokenSecret
     *            - Twitter Access Token Secret that has been received after
     *            authorization
     *
     * @returns The App42SocialResponse object
     *
     */
    void LinkUserTwitterAccount(const char* userName, const char* accessToken, const char* accessTokenSecret, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Updates the Twitter status of the specified user.
     *
     * @param userName
     *            - Name of the user for whom the status needs to be updated
     * @param status
     *            - status that has to be updated
     *
     * @returns The App42SocialResponse object
     */
    void UpdateTwitterStatus(const char* userName, const char* status, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /******************************************************************************************************/
    /*****************************            LINKEDIN RELATED APIS            ****************************/
    /******************************************************************************************************/
    
    /**
     * Links the User LinkedIn access credentials to the App User account.
     *
     * @param userName
     *            - Name of the user whose LinkedIn account to be linked
     * @param apiKey
     *            - LinkedIn App API Key
     * @param secretKey
     *            - LinkedIn App Secret Key
     * @param accessToken
     *            - LinkedIn Access Token that has been received after
     *            authorization
     * @param accessTokenSecret
     *            - LinkedIn Access Token Secret that has been received after
     *            authorization
     *
     * @returns The App42SocialResponse object
     *
     */
    void LinkUserLinkedInAccount(const char* userName, const char* linkedInApiKey, const char* linkedInSecretKey, const char* accessToken, const char* accessTokenSecret, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Links the User LinkedIn access credentials to the App User account.
     *
     * @param userName
     *            - Name of the user whose LinkedIn account to be linked
     * @param accessToken
     *            - LinkedIn Access Token that has been received after
     *            authorization
     * @param accessTokenSecret
     *            - LinkedIn Access Token Secret that has been received after
     *            authorization
     *
     * @returns The Social object
     *
     */
    void LinkUserLinkedInAccount(const char* userName, const char* accessToken, const char* accessTokenSecret, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Updates the LinkedIn status of the specified user.
     *
     * @param userName
     *            - Name of the user for whom the status needs to be updated
     * @param status
     *            - status that has to be updated
     *
     * @returns The Social object
     *
     */
    void UpdateLinkedInStatus(const char* userName, const char* status, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    /**
     * Updates the status for all linked social accounts of the specified user.
     *
     * @param userName
     *            - Name of the user for whom the status needs to be updated
     * @param status
     *            - status that has to be updated
     *
     * @returns The Social object
     *
     */
    void UpdateSocialStatusForAll(const char* userName, const char* status, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

};
#endif /* defined(__App42Cocos2dX3_0Sample__SocialService__) */
