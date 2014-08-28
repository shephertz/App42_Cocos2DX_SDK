//
//  App42TimerResponse.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev on 19/08/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__App42TimerResponse__
#define __App42Cocos2dX3_0Sample__App42TimerResponse__

#include <iostream>
#include "cJSON.h"
#include "App42Response.h"

using namespace std;

typedef struct App42Timer
{
    string name;
    string userName;
    string currentTime;
    string startTime;
    string endTime;
    long timeInSeconds;
    bool isTimerActive;
}App42Timer;


class App42TimerResponse : public App42Response
{
public:
    App42Timer app42Timer;
    App42TimerResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector);
	~App42TimerResponse();
    void onComplete(void *sender, void *data);
private:
    void init();
    
};

#endif /* defined(__App42Cocos2dX3_0Sample__App42TimerResponse__) */
