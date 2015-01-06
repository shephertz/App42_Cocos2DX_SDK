//
//  App42API.h
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 07/10/13.
//
//

#ifndef __App42CPPSDK__App42API__
#define __App42CPPSDK__App42API__

#include <iostream>
#include "UserService.h"
#include "GameService.h"
#include "ScoreService.h"
#include "ScoreBoardService.h"
#include "RewardService.h"
#include "StorageService.h"
#include "PushNotificationService.h"
#include "EmailService.h"
#include "UploadService.h"
#include "CustomCodeService.h"

#include "App42CallBack.h"

#include "App42UserResponse.h"
#include "App42GameResponse.h"
#include "App42RewardResponse.h"
#include "App42StorageResponse.h"
#include "App42PushNotificationResponse.h"
#include "App42EmailResponse.h"
#include "App42UploadResponse.h"
#include "App42CustomCodeResponse.h"
#include "Common.h"
#include "Query.h"
#include "QueryBuilder.h"
#include "App42Exception.h"
#include "App42Object.h"

extern bool isTraceEnabled;

class App42API
{
public:
    static string getLoggedInUser();
    static void setLoggedInUser(string _loggedInUser);
        
    static void setIsTraceEnabled(bool _isTraceEnabled);
    
    static void Initialize(string _apiKey, string _secretKey);
    
    
    static UserService * BuildUserService();

    
    static StorageService * BuildStorageService();
    
    
    static GameService * BuildGameService();
    
    
    static ScoreBoardService * BuildScoreBoardService();
    
    
    static ScoreService * BuildScoreService();
    

    static RewardService * BuildRewardService();
    

    static PushNotificationService * BuildPushNotificationService();
    
    static EmailService * BuildEmailService();
    
    static UploadService * BuildUploadService();
    
    static CustomCodeService * BuildCustomCodeService();

};
#endif /* defined(__App42CPPSDK__App42API__) */
