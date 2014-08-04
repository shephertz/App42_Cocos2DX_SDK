//
//  App42EmailResponse.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 08/04/14.
//
//

#include "App42EmailResponse.h"
#include "Common.h"


App42EmailResponse::App42EmailResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector)
:App42Response(pTarget,pSelector)
{
    
}

App42EmailResponse::~App42EmailResponse()
{
    
}

void App42EmailResponse::onComplete(void *sender, void *data)
{
    App42Response::onComplete(sender, data);
    init();
    
    if (_app42Target && _app42Selector)
    {
        (_app42Target->*_app42Selector)((App42CallBack *)_app42Target, this);
    }
}

void App42EmailResponse::init()
{
    if(_result != 200)
    {
        Util::app42Trace("App42EmailResult failed result is %d", _result);
        buildErrorMessage();
        return;
    }
    
    // parse the body
    cJSON *ptrBody = cJSON_Parse(_body.c_str());
    cJSON* ptrApp42 = Util::getJSONChild("app42", ptrBody);
    cJSON* ptrResponse = Util::getJSONChild("response", ptrApp42);
    cJSON* ptrEmail = Util::getJSONChild("email", ptrResponse);
    if (ptrEmail)
    {
        from = Util::getJSONString("from", ptrEmail);
        to = Util::getJSONString("to", ptrEmail);
        subject = Util::getJSONString("subject", ptrEmail);
        body = Util::getJSONString("body", ptrEmail);

        cJSON* ptrConfigurations = Util::getJSONChild("configurations", ptrEmail);
        if(ptrConfigurations)
        {
            cJSON* ptrConfig = Util::getJSONChild("config", ptrConfigurations);
            if (ptrConfig)
            {
                cJSON* childConfig = ptrConfig;
                if(childConfig->type == cJSON_Array)
                {
                    childConfig = childConfig->child;
                }
                while(childConfig != NULL && childConfig->type == cJSON_Object)
                {
                    App42Configuration config;
                    
                    config.emailId = Util::getJSONString("emailId", childConfig);
                    config.host = Util::getJSONString("host", childConfig);
                    config.ssl = Util::getJSONBool("ssl", childConfig);
                    config.port = Util::getJSONInt("port", childConfig);
                    
                    configurationArray.push_back(config);
                    childConfig = childConfig->next;
                }
            }
        }
    }
    else
    {
        setTotalRecords();
    }
    
    cJSON_Delete(ptrBody);
}