//
//  App42API.cpp
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 07/10/13.
//
//

#include "App42API.h"

static string apiKey="";
static string secretKey="";
static string loggedInUser = "";
bool isTraceEnabled = false;

string App42API::getLoggedInUser()
{
    return loggedInUser;
}
void App42API::setLoggedInUser(string _loggedInUser)
{
    loggedInUser=_loggedInUser;
}

void App42API::setIsTraceEnabled(bool _isTraceEnabled)
{
    isTraceEnabled = _isTraceEnabled;
}

void App42API::Initialize(string _apiKey, string _secretKey)
{
    apiKey = _apiKey;
    secretKey = _secretKey;
    isTraceEnabled = false;
}

UserService * App42API::BuildUserService()
{
    UserService *userService = UserService::Initialize(apiKey, secretKey);
    return userService;
}

StorageService * App42API::BuildStorageService()
{
    StorageService *storageService = StorageService::Initialize(apiKey, secretKey);
    return storageService;
}

GameService * App42API::BuildGameService()
{
    GameService *gameService = GameService::Initialize(apiKey, secretKey);
    return gameService;
}

ScoreBoardService * App42API::BuildScoreBoardService()
{
    ScoreBoardService *scoreBoardService = ScoreBoardService::Initialize(apiKey, secretKey);
    return scoreBoardService;
}

ScoreService * App42API::BuildScoreService()
{
    ScoreService *scoreService = ScoreService::Initialize(apiKey, secretKey);
    return scoreService;
}

RewardService * App42API::BuildRewardService()
{
    RewardService *rewardService = RewardService::Initialize(apiKey, secretKey);
    return rewardService;
}

PushNotificationService * App42API::BuildPushNotificationService()
{
    PushNotificationService *pushNotificationService = PushNotificationService::Initialize(apiKey, secretKey);
    return pushNotificationService;
}

EmailService * App42API::BuildEmailService()
{
    EmailService *emailService = EmailService::Initialize(apiKey, secretKey);
    return emailService;
}

UploadService * App42API::BuildUploadService()
{
    UploadService *uploadService = UploadService::Initialize(apiKey, secretKey);
    return uploadService;
}

CustomCodeService * App42API::BuildCustomCodeService()
{
    CustomCodeService *customCodeService = CustomCodeService::Initialize(apiKey, secretKey);
    return customCodeService;
}
