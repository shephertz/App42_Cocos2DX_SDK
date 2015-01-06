//
//  App42BuddyResponse.h
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 18/07/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__App42BuddyResponse__
#define __App42Cocos2dX3_0Sample__App42BuddyResponse__

#include <iostream>
#include "cJSON.h"
#include "App42Response.h"
#include "App42Constants.h"
#include "App42GeoPoint.h"

using namespace std;

struct App42BuddyPoint;

typedef struct App42Buddy
{
    string userName;
    string buddyName;
    string groupName;
    string ownerName;
    string message;
    string messageId;
    string sentOn;
    string acceptedOn;
    vector<App42Buddy> buddyList;
    vector<App42GeoPoint> pointList;
    
}App42Buddy;



class App42BuddyResponse : public App42Response
{
public:
    
    vector<App42Buddy> buddyList;

    App42BuddyResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector);
	~App42BuddyResponse();
    void onComplete(void *sender, void *data);
    
private:
    void init();
};

#endif /* defined(__App42Cocos2dX3_0Sample__App42BuddyResponse__) */
