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
    
    void CreateOrUpdateTimer(const char* timerName, long timeInSeconds,const app42CallBack& pSelector);
    
    void StartTimer(const char* timerName, const char* userName,const app42CallBack& pSelector);
    
    void IsTimerActive(const char* timerName, const char* userName,const app42CallBack& pSelector);
    
    void CancelTimer(const char* timerName, const char* userName,const app42CallBack& pSelector);
    
    void DeleteTimer(const char* timerName, const app42CallBack& pSelector);
    
    void GetCurrentTime(const app42CallBack& pSelector);
};

#endif /* defined(__App42Cocos2dX3_0Sample__TimerService__) */
