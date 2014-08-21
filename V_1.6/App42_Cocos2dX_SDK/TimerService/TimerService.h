//
//  TimerService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev on 19/08/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__TimerService__
#define __App42Cocos2dX3_0Sample__TimerService__

#include <iostream>
#include "App42Service.h"

using namespace std;

class TimerService : public App42Service
{
    
private:
    TimerService();
	static TimerService* _instance;
    string buildCreateTimerBody(const char *timerName, long timerInSeconds);
    string buildStartTimerBody(const char *timerName, const char * userName);

public:
    
	/**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
    static TimerService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of TimerService.
     *
     * @return TimerService - TimerService Object
     */
	static TimerService* getInstance();
    
    void CreateOrUpdateTimer(const char* timerName, long timeInSeconds,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void StartTimer(const char* timerName, const char* userName,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /*New APIs*/
    void CancelTimer(const char* timerName, const char* userName,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void IsTimerActive(const char* timerName, const char* userName,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void DeleteTimer(const char* timerName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void GetCurrentTime(App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
};

#endif /* defined(__App42Cocos2dX3_0Sample__TimerService__) */
