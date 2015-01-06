//
//  App42SocialResponse.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 26/06/14.
//
//

#include "App42SocialResponse.h"
#include "Common.h"


App42SocialResponse::App42SocialResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector)
:App42Response(pTarget,pSelector)
{
    
}

App42SocialResponse::~App42SocialResponse()
{
	friendsList.clear();
    publicProfile.clear();
}

void App42SocialResponse::init()
{
    if(_result != 200)
    {
        Util::app42Trace("App42User failed result is %d", _result);
        buildErrorMessage();
        return;
    }
    // parse the body
    cJSON *ptrBody = cJSON_Parse(_body.c_str());
    cJSON* ptrApp42 = Util::getJSONChild("app42", ptrBody);
    cJSON* ptrResponse = Util::getJSONChild("response", ptrApp42);
    cJSON* ptrSocial = Util::getJSONChild("social", ptrResponse);
    social.setDefaults();
    if (ptrSocial)
    {
        cJSON* child = ptrSocial;
        if(child->type == cJSON_Array)
        {
            child = child->child;
        }
        
        while(child != NULL && child->type == cJSON_Object)
        {            
            social.setUserName(Util::getJSONString("userName", child));
            social.setStatus(Util::getJSONString("status", child));
            social.setFacebookAccessToken(Util::getJSONString("facebookAccessToken", child));
            social.setFacebookAppId(Util::getJSONString("facebookAppId", child));
            printf("\n%s",Util::getJSONString("facebookAppId", child).c_str());
            social.setFacebookAppSecret(Util::getJSONString("facebookAppSecret", child));
            
            cJSON* ptrFriends = Util::getJSONChild("friends",child);
            if(ptrFriends)
            {
                cJSON* friendsJson = ptrFriends;
                if(friendsJson->type == cJSON_Array)
                {
                    friendsJson = friendsJson->child;
                }
                while(friendsJson != NULL && friendsJson->type == cJSON_Object)
                {
                    App42Friend app42Friend;
                    app42Friend.setName(Util::getJSONString("name", friendsJson));
                    app42Friend.setFriendId(Util::getJSONString("id", friendsJson));
                    app42Friend.setPicture(Util::getJSONString("picture", friendsJson));
                    app42Friend.setInstalled(Util::getJSONBool("installed", friendsJson));

                    friendsList.push_back(app42Friend);
                    friendsJson = friendsJson->next;
                }
            }
            
            cJSON* ptrMe = Util::getJSONChild("me",child);
            if(ptrMe)
            {
                
                facebookProfile.setName(Util::getJSONString("name", ptrMe));
                facebookProfile.setFbId(Util::getJSONString("id", ptrMe));
                facebookProfile.setPicture(Util::getJSONString("picture", ptrMe));
            }
            
            cJSON* ptrFriendsProfile = Util::getJSONChild("profile",child);
            if(ptrFriendsProfile)
            {
                cJSON* friendsProfileJson = ptrFriendsProfile;
                if(friendsProfileJson->type == cJSON_Array)
                {
                    friendsProfileJson = friendsProfileJson->child;
                }
                while(friendsProfileJson != NULL && friendsProfileJson->type == cJSON_Object)
                {
                    App42PublicProfile app42FriendProfile;
                    app42FriendProfile.setName(Util::getJSONString("name", friendsProfileJson));
                    app42FriendProfile.setFbId(Util::getJSONString("id", friendsProfileJson));
                    app42FriendProfile.setPicture(Util::getJSONString("picture", friendsProfileJson));
                    
                    publicProfile.push_back(app42FriendProfile);
                    friendsProfileJson = friendsProfileJson->next;
                }
            }
            
            child = child->next;
        }
    }
    else
    {
        setTotalRecords();
    }
    
    cJSON_Delete(ptrBody);
}


void App42SocialResponse::onComplete(void *sender, void *data)
{
    App42Response::onComplete(sender, data);
    init();
    
    if (_app42Target && _app42Selector)
    {
        (_app42Target->*_app42Selector)((App42CallBack *)_app42Target, this);
    }
}