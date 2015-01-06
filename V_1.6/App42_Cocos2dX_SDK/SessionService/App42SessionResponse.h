//
//  App42SessionResponse.h
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 16/07/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__App42SessionResponse__
#define __App42Cocos2dX3_0Sample__App42SessionResponse__

#include <iostream>
#include "cJSON.h"
#include "App42Response.h"
#include "App42Constants.h"

using namespace std;

struct App42Attribute;

typedef struct App42Session
{
    string userName;
    string sessionId;
    string invalidatedOn;
    string createdOn;
    vector<App42Attribute> attributeArray;
    
}App42Session;

typedef struct App42Attribute
{
    string name;
    string value;
}App42Attribute;


class App42SessionResponse : public App42Response
{
public:
    App42SessionResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector);
    App42Session app42Session;
	~App42SessionResponse();
    void onComplete(void *sender, void *data);
    
private:
    void init();
};



#endif /* defined(__App42Cocos2dX3_0Sample__App42SessionResponse__) */
