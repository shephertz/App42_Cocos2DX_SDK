//
//  App42SessionResponse.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 16/07/14.
//
//

#include "App42SessionResponse.h"
#include "Common.h"


App42SessionResponse::App42SessionResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector)
:App42Response(pTarget,pSelector)
{
    
}

App42SessionResponse::~App42SessionResponse()
{
    app42Session.attributeArray.clear();
}

void App42SessionResponse::init()
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
    cJSON* ptrSession = Util::getJSONChild("session", ptrResponse);
    
    if (ptrSession)
    {
        cJSON* child = ptrSession;
        if(child->type == cJSON_Array)
        {
            child = child->child;
        }
        
        while(child != NULL && child->type == cJSON_Object)
        {
            app42Session.userName = Util::getJSONString("userName", child);
            app42Session.sessionId = Util::getJSONString("sessionId", child);
            app42Session.createdOn = Util::getJSONString("createdOn", child);
            app42Session.invalidatedOn = Util::getJSONString("invalidatedOn", child);
            
            cJSON* ptrAttributes = Util::getJSONChild("attributes", child);
            if (ptrAttributes)
            {
                cJSON* ptrAttribute = Util::getJSONChild("attribute", ptrAttributes);
                if (ptrAttribute)
                {
                    cJSON* attributeChild = ptrAttribute;
                    if(attributeChild->type == cJSON_Array)
                    {
                        attributeChild = attributeChild->child;
                    }
                    
                    while(attributeChild != NULL && attributeChild->type == cJSON_Object)
                    {
                        App42Attribute attribute;
                        attribute.name = Util::getJSONString("name", attributeChild);
                        attribute.value = Util::getJSONString("value", attributeChild);
                        app42Session.attributeArray.push_back(attribute);
                        attributeChild = attributeChild->next;
                    }
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

void App42SessionResponse::onComplete(void *sender, void *data)
{
    App42Response::onComplete(sender, data);
    init();
    
    if (_app42Target && _app42Selector)
    {
        (_app42Target->*_app42Selector)((App42CallBack *)_app42Target, this);
    }
}