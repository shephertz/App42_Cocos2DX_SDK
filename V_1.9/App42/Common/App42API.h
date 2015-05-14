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
#include "SocialService.h"
#include "AvatarService.h"
#include "SessionService.h"
#include "BuddyService.h"
#include "TimerService.h"

#include "App42UserResponse.h"
#include "App42GameResponse.h"
#include "App42RewardResponse.h"
#include "App42StorageResponse.h"
#include "App42PushNotificationResponse.h"
#include "App42EmailResponse.h"
#include "App42UploadResponse.h"
#include "App42CustomCodeResponse.h"
#include "App42SocialResponse.h"
#include "App42AvatarResponse.h"
#include "App42SessionResponse.h"
#include "App42BuddyResponse.h"
#include "App42TimerResponse.h"

#include "Common.h"
#include "Query.h"
#include "QueryBuilder.h"
#include "App42Exception.h"
#include "App42Object.h"
#include "App42GeoPoint.h"
#include "App42CallBack.h"
#include "ACL.h"

extern bool isTraceEnabled;

class App42API
{
public:
    
    static vector<App42ACL> getDefaultApp42ACL();
    static void setDefaultApp42ACL(vector<App42ACL> _defaultApp42ACL);
    
    static string getLoggedInUser();
    static void setLoggedInUser(string _loggedInUser);
    static string getInstallId();
    static void setInstallId(string _installId);
    static string getFbAccesToken();
    static void setFbAccesToken(string _fbAccesToken);
    static string getUserSessionId();
    static void setUserSessionId(string _userSessionId);
    static string getDbName();
    static void setDbName(string _dbName);
    static void removeSession();
    
    static void setIsTraceEnabled(bool _isTraceEnabled);
    
    static void Initialize(string _apiKey, string _secretKey);
    
    
    static UserService* BuildUserService();

    static StorageService* BuildStorageService();
    
    static GameService* BuildGameService();
    
    static ScoreBoardService* BuildScoreBoardService();
    
    static ScoreService* BuildScoreService();
    
    static RewardService* BuildRewardService();
    
    static PushNotificationService* BuildPushNotificationService();
    
    static EmailService* BuildEmailService();
    
    static UploadService* BuildUploadService();
    
    static CustomCodeService* BuildCustomCodeService();
    
    static SocialService* BuildSocialService();
    
    static AvatarService* BuildAvatarService();
    
    static SessionService* BuildSessionService();
    
    static BuddyService* BuildBuddyService();

    static TimerService* BuildTimerService();


};
#endif /* defined(__App42CPPSDK__App42API__) */
