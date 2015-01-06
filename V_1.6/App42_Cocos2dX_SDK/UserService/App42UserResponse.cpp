//
//  App42UserResponse.cpp
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 14/10/13.
//
//

#include "App42UserResponse.h"
#include "Common.h"
#include "ACL.h"


App42UserResponse::App42UserResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector)
:App42Response(pTarget,pSelector)
{
    
}

App42UserResponse::~App42UserResponse()
{
	users.clear();
}

void App42UserResponse::init()
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
    cJSON* ptrUsers = Util::getJSONChild("users", ptrResponse);
    if (ptrUsers)
    {
        cJSON* ptrUser = Util::getJSONChild("user", ptrUsers);
        
        if (ptrUser)
        {
            cJSON* child = ptrUser;
            if(child->type == cJSON_Array)
            {
                child = child->child;
            }
            
            while(child != NULL && child->type == cJSON_Object)
            {
                App42User app42User;
                app42User.userName = Util::getJSONString("userName", child);
                app42User.email = Util::getJSONString("email", child);
                app42User.isAccountLocked = Util::getJSONInt("accountLocked", child);
                app42User.sessionId = Util::getJSONString("sessionId", child);
                app42User.createdOn = Util::getJSONString("createdOn", child);
                app42User.password = Util::getJSONString("password", child);

                cJSON* ptrUserProfile = Util::getJSONChild("profile", child);
                if (ptrUserProfile)
                {
                    app42User.profile = buildUserProfile(ptrUserProfile);
                }
                /**
                 * Parsing Roles
                 */
                cJSON* ptrUserRoles = Util::getJSONChild("role", child);
                if (ptrUserRoles)
                {
                    cJSON* childRole = ptrUserRoles;

                    if (childRole->type == cJSON_Array)
                    {
                        int size = cJSON_GetArraySize(childRole);
                        for (int i=0; i<size; i++)
                        {
                            cJSON *item = cJSON_GetArrayItem(childRole, i);
                            if (item->valuestring)
                            {
                                app42User.roleList.push_back(item->valuestring);
                            }
                        }
                    }
                    else if(childRole->type == cJSON_String)
                    {
                        app42User.roleList.push_back(childRole->valuestring);
                    }
                }
                /**
                 * Parsing JsonDocs
                 */
                cJSON* ptrJsonDocs = Util::getJSONChild("jsonDoc", child);
                if(ptrJsonDocs)
                {
                    cJSON* child = ptrJsonDocs;
                    if(child->type == cJSON_Array)
                    {
                        child = child->child;
                    }
                    while(child != NULL && child->type == cJSON_Object)
                    {
                        JSONDocument document;
                        buildJsonDocument(child, &document);
                        
                        app42User.jsonDocArray.push_back(document);
                        child = child->next;
                    }
                }
                users.push_back(app42User);
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

App42UserProfile App42UserResponse::buildUserProfile(cJSON* ptrProfile)
{
    App42UserProfile app42UserProfile;
    
    app42UserProfile.firstName = Util::getJSONString("firstName", ptrProfile);
    app42UserProfile.lastName = Util::getJSONString("lastName", ptrProfile);
    app42UserProfile.mobile = Util::getJSONString("mobile", ptrProfile);
    app42UserProfile.sex = Util::getJSONString("sex", ptrProfile);
    app42UserProfile.line1 = Util::getJSONString("line1", ptrProfile);
    app42UserProfile.line2 = Util::getJSONString("line2", ptrProfile);
    app42UserProfile.city = Util::getJSONString("city", ptrProfile);
    app42UserProfile.state = Util::getJSONString("state", ptrProfile);
    app42UserProfile.country = Util::getJSONString("country", ptrProfile);
    app42UserProfile.pincode = Util::getJSONString("pincode", ptrProfile);
    app42UserProfile.homeLandLine = Util::getJSONString("homeLandLine", ptrProfile);
    app42UserProfile.officeLandLine = Util::getJSONString("officeLandLine", ptrProfile);
    app42UserProfile.dateOfBirth = Util::getJSONString("dateOfBirth", ptrProfile);

    return app42UserProfile;
}

void App42UserResponse::onComplete(void *sender, void *data)
{
    App42Response::onComplete(sender, data);
    init();
    
    if (_app42Target && _app42Selector)
    {
        (_app42Target->*_app42Selector)((App42CallBack *)_app42Target, this);
    }
}

