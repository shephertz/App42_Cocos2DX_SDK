//
//  App42CustomCodeResponse.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 14/05/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__App42CustomCodeResponse__
#define __App42Cocos2dX3_0Sample__App42CustomCodeResponse__

#include <iostream>
#include "cJSON.h"
#include "App42Response.h"

using namespace std;

class App42CustomCodeResponse : public App42Response
{
    public:
    
        App42CustomCodeResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector);
        ~App42CustomCodeResponse();
        void onComplete(void *sender, void *data);
    
    private:
    
        void init();
    
};

#endif /* defined(__App42Cocos2dX3_0Sample__App42CustomCodeResponse__) */
