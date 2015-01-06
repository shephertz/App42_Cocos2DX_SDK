//
//  App42TimerResponse.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev on 19/08/14.
//
//

#include "App42TimerResponse.h"
#include "Common.h"


App42TimerResponse::App42TimerResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector)
:App42Response(pTarget,pSelector)
{
    
}

App42TimerResponse::~App42TimerResponse()
{
    
}

void App42TimerResponse::onComplete(void *sender, void *data)
{
    App42Response::onComplete(sender, data);
    init();
    
    if (_app42Target && _app42Selector)
    {
        (_app42Target->*_app42Selector)((App42CallBack *)_app42Target, this);
    }
}

void App42TimerResponse::init()
{
    if(_result != 200)
    {
        Util::app42Trace("App42TimerResponse failed result is %d", _result);
        buildErrorMessage();
        return;
    }
    
    // parse the body
    cJSON *ptrBody = cJSON_Parse(_body.c_str());
    cJSON* ptrApp42 = Util::getJSONChild("app42", ptrBody);
    cJSON* ptrResponse = Util::getJSONChild("response", ptrApp42);
    cJSON* ptrTimer = Util::getJSONChild("timer", ptrResponse);
    if (ptrTimer)
    {
        app42Timer.name = Util::getJSONString("name", ptrTimer);
        app42Timer.timeInSeconds = Util::getJSONDouble("timeInSeconds", ptrTimer);
        app42Timer.userName = Util::getJSONString("userName", ptrTimer);
        app42Timer.currentTime = Util::getJSONString("currentTime", ptrTimer);
        app42Timer.startTime = Util::getJSONString("startTime", ptrTimer);
        app42Timer.endTime = Util::getJSONString("endTime", ptrTimer);
        app42Timer.isTimerActive = Util::getJSONBool("isTimerActive", ptrTimer);
    }
    else
    {
        setTotalRecords();
    }
    
    cJSON_Delete(ptrBody);
}