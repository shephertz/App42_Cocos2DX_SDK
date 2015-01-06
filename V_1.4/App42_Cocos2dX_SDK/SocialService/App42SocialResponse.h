//
//  App42SocialResponse.h
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 26/06/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__App42SocialResponse__
#define __App42Cocos2dX3_0Sample__App42SocialResponse__

#include <iostream>
#include "cJSON.h"
#include "App42Response.h"
#include "JSONDocument.h"
#include "App42Friend.h"
#include "App42PublicProfile.h"
#include "App42FacebookProfile.h"
#include "App42Social.h"

using namespace std;

class App42SocialResponse : public App42Response
{
public:
    App42Social social;
    App42FacebookProfile facebookProfile;
    vector<App42Friend> friendsList;
    vector<App42PublicProfile> publicProfile;
    
    App42SocialResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector);
	~App42SocialResponse();
    void onComplete(void *sender, void *data);
private:
    void init();
    
};

#endif /* defined(__App42Cocos2dX3_0Sample__App42SocialResponse__) */
