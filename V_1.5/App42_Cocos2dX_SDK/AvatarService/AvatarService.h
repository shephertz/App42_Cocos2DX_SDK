//
//  AvatarService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 02/07/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__AvatarService__
#define __App42Cocos2dX3_0Sample__AvatarService__

#include <iostream>
#include "App42Service.h"


using namespace std;

typedef enum FileExtension
{
    PNG,
    JPG,
    GIF,
}FileExtension;


class AvatarService : public App42Service
{
    
private:
    AvatarService();
    static AvatarService* _instance;
    
    string buildCreateAvatarFromFacebookRequest(const char* userName, const char* avatarName, const char* accessToken, const char* webUrl, const char* description);
    
    inline const char *getFileExtension(FileExtension fileExtension)
    {
        const char *strings[] = {"png","jpg","gif"};
        
        return strings[fileExtension];
    }
    
public:
    
    
	/**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
	
    static AvatarService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of UserService.
     *
     * @return UserService - UserService Object
     */
	static AvatarService* getInstance();
    
    /**
     * Upload your own avatar from binary.
     *
     * @param avatarName
     *            - Name of avatar to be created.
     * @param userName
     *            - Name of the user who is creating avatar
     * @param filePath
     *            - The local path for the file
     * @param description
     *            - Description of the avatar
     * @return App42AvatarResponse Object
     * @throws App42Exception
     */
    void CreateAvatar(const char* avatarName, const char* userName, const char* filePath, const char* description, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     *kartik.khamesra@sh
     * @param avatarName
     * @param userName
     * @param fileData
     * @param description
     * @param extension
     * @return
     * @throws App42Exception
     */
    void CreateAvatar(const char* avatarName, const char* userName, unsigned char* fileData, int fileDataSize, const char* description,FileExtension extension, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Import your avatar from Facebook based of given access token.
     *
     * @param avatarName
     *            - Name of avatar to be created.
     * @param userName
     *            - Name of the user who is creating avatar
     * @param accessToken
     *            - Facebook Access Token that has been received after
     *            authorization
     * @param description
     *            - Description of the avatar
     * @return App42AvatarResponse Object
     * @throws App42Exception
     */
    void CreateAvatarFromFacebook(const char* avatarName, const char* userName, const char* accessToken, const char* description, App42CallBack* pTarget,SEL_App42CallFuncND pSelector);

    /**
     * Create avatar from any web media using URL
     *
     * @param avatarName
     *            - Name of avatar to be created
     * @param userName
     *            - Name of the user who is creating avatar
     * @param webUrl
     *            - WebURL of photo which you want to create
     * @param description
     *            - Description of the avatar
     * @return App42AvatarResponse Object
     * @throws App42Exception
     */
    void CreateAvatarFromWebURL(const char* avatarName, const char* userName, const char* webUrl, const char* description, App42CallBack* pTarget,SEL_App42CallFuncND pSelector);
    
    /**
     * Get detail description of avatar
     *
     * @param userName
     *            - Name of the user for which avatar is to fetched
     * @param avatarName
     *            - Name of the avatar is to be fetched
     * @return Avatar Object
     * @throws App42Exception
     */
    void GetAvatarByName(const char* avatarName, const char* userName, App42CallBack* pTarget,SEL_App42CallFuncND pSelector);
    
    /**
     * View all avatars.
     *
     * @param userName
     *            - Name of the user for which avatar is to fetched
     * @return Array of Avatar Objects
     * @throws App42Exception
     */
    void GetAllAvatars(const char* userName, App42CallBack* pTarget,SEL_App42CallFuncND pSelector);
    
    /**
     * View the latest avatar uploaded by user.
     *
     *
     * @param userName
     *            - Name of the user for which current avatar is to fetch
     * @return Avatar Object
     * @throws App42Exception
     */
    void GetCurrentAvatar(const char* userName, App42CallBack* pTarget,SEL_App42CallFuncND pSelector);
    
    /**
     * Change your current avatar from existing avatars in app.
     *
     * @param userName
     *            - Name of the user for which avatar is to updated.
     * @param avatarName
     *            - Name of the avatar to be updated.
     * @return Avatar Object
     * @throws App42Exception
     */
    void ChangeCurrentAvatar(const char* avatarName, const char* userName, App42CallBack* pTarget,SEL_App42CallFuncND pSelector);
    

};
#endif /* defined(__App42Cocos2dX3_0Sample__AvatarService__) */
