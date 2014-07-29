//
//  App42EmailResponse.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 08/04/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__App42EmailResponse__
#define __App42Cocos2dX3_0Sample__App42EmailResponse__

#include <iostream>
#include "cJSON.h"
#include "App42Response.h"

using namespace std;

typedef struct App42Configuration
{
    string emailId;
    string host;
    int port;
    bool ssl;
}App42Configuration;


class App42EmailResponse : public App42Response
{
public:
    vector<App42Configuration> configurationArray;
    string from;
    string to;
    string subject;
    string body;
    
    App42EmailResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector);
	~App42EmailResponse();
    void onComplete(void *sender, void *data);
private:
    void init();
    
};

#endif /* defined(__App42Cocos2dX3_0Sample__App42EmailResponse__) */
