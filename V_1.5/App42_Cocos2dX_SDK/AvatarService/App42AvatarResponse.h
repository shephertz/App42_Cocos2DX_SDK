//
//  App42AvatarResponse.h
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 02/07/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__App42AvatarResponse__
#define __App42Cocos2dX3_0Sample__App42AvatarResponse__

#include <iostream>
#include "cJSON.h"
#include "App42Response.h"
#include "App42Constants.h"

using namespace std;

struct App42Avatar;

class App42AvatarResponse : public App42Response
{
public:
    App42AvatarResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector);
    vector<App42Avatar> avatars;
	~App42AvatarResponse();
    void onComplete(void *sender, void *data);
    
private:
    void init();
};

typedef struct App42Avatar
{
    string userName;
    string name;
    string url;
    string tinyUrl;
    string description;
    string createdOn;
    bool isCurrent;
    
}App42Avatar;

#endif /* defined(__App42Cocos2dX3_0Sample__App42AvatarResponse__) */
