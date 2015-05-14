//
//  App42CustomCodeResponse.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 14/05/14.
//
//

#include "App42CustomCodeResponse.h"
#include "Common.h"


App42CustomCodeResponse::App42CustomCodeResponse(const app42CallBack& pSelector)
:App42Response(pSelector)
{
    
}

App42CustomCodeResponse::~App42CustomCodeResponse()
{
    
}

void App42CustomCodeResponse::onComplete(void *sender, void *data)
{
    App42Response::onComplete(sender, data);
    init();
    
    if (_app42Selector)
    {
        _app42Selector(this);
    }
}

void App42CustomCodeResponse::init()
{
    if(_result != 200)
    {
        Util::app42Trace("\nApp42CustomCodeRequest failed with result code : %d", _result);
        buildErrorMessage();
    }
}