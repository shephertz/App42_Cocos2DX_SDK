//
//  App42AvatarResponse.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 02/07/14.
//
//

#include "App42AvatarResponse.h"
#include "Common.h"


App42AvatarResponse::App42AvatarResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector)
:App42Response(pTarget,pSelector)
{
    
}

App42AvatarResponse::~App42AvatarResponse()
{
	avatars.clear();
}

void App42AvatarResponse::init()
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
    cJSON* ptrAvatars = Util::getJSONChild("avatars", ptrResponse);
    
    if (ptrAvatars)
    {
        cJSON* ptrAvatar = Util::getJSONChild("avatar", ptrAvatars);
        
        if (ptrAvatar)
        {
            cJSON* child = ptrAvatar;
            if(child->type == cJSON_Array)
            {
                child = child->child;
            }
            
            while(child != NULL && child->type == cJSON_Object)
            {
                App42Avatar app42Avatar;
                app42Avatar.userName = Util::getJSONString("userName", child);
                app42Avatar.name = Util::getJSONString("name", child);
                app42Avatar.url = Util::getJSONString("url", child);
                app42Avatar.tinyUrl = Util::getJSONString("tinyUrl", child);
                app42Avatar.description = Util::getJSONString("description", child);
                app42Avatar.createdOn = Util::getJSONString("createdOn", child);
                app42Avatar.isCurrent = Util::getJSONBool("isCurrent", child);

                avatars.push_back(app42Avatar);
                child = child->next;
            }
        }
    }
    else
    {
        setTotalRecords();
    }
    
    cJSON_Delete(ptrBody);
}

void App42AvatarResponse::onComplete(void *sender, void *data)
{
    App42Response::onComplete(sender, data);
    init();
    
    if (_app42Target && _app42Selector)
    {
        (_app42Target->*_app42Selector)((App42CallBack *)_app42Target, this);
    }
}