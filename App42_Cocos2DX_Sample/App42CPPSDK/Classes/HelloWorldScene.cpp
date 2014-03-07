#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#define APP_Key "Application_Key"
#define SECRET_Key "App_Secret_Key"


using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    
    /**
     * Test User Service
     */
    
    //testUserService();
    
    
    /**
     * Test Game Service
     */
    
    //testGameService();
    
    
    /**
     * Test Score Service
     */
    
    //testScoreService();
    
    /**
     * Test Score Board Service
     */
    
    //testScoreBoardService();
    
    /**
     * Test Reward Service
     */
    
     //testRewardService();
    
    
    /**
     * Test Storage Service
     */
    
    testStorageService();
    
    /**
     * Test Push Service
     */
    
    //testPushService();
    
    
    return true;
}

void HelloWorld::testUserService()
{
    std::string userName = "<Enter_your_user_name>";
    std::string password = "Password";
    std::string emailId = "Email_Id";

    UserService::Initialize(APP_Key, SECRET_Key);
    UserService *user = UserService::getInstance();
    user->CreateUser(userName, password, emailId,this,callfuncND_selector(HelloWorld::onUserRequestCompleted));
    
    user->Authenticate(userName, password, this, callfuncND_selector(HelloWorld::onUserRequestCompleted));
    user->GetUser(userName, this, callfuncND_selector(HelloWorld::onUserRequestCompleted));
    user->GetAllUsers(this,callfuncND_selector(HelloWorld::onUserRequestCompleted));
}


void HelloWorld::testGameService()
{
    std::string gameName = "<Enter_your_game_name>";
    std::string description = "Description";

    GameService::Initialize(APP_Key, SECRET_Key);
    GameService *gameService = GameService::getInstance();
    gameService->CreateGame(gameName, description, this, callfuncND_selector(HelloWorld::onGameRequestCompleted));
    gameService->GetGamebyName(gameName, this, callfuncND_selector(HelloWorld::onGameRequestCompleted));
}

void HelloWorld::testScoreService()
{
    std::string gameName = "<Enter_your_game_name>";
    std::string userName = "<Enter_your_user_name>";
    double score = 100;
    ScoreService::Initialize(APP_Key, SECRET_Key);
    ScoreService *scoreService = ScoreService::getInstance();
    scoreService->AddScore(gameName, userName, score, this, callfuncND_selector(HelloWorld::onGameRequestCompleted));
    scoreService->DeductScore(gameName, userName, score, this, callfuncND_selector(HelloWorld::onGameRequestCompleted));
}

void HelloWorld::testScoreBoardService()
{
    std::string gameName = "<Enter_your_game_name>";
    std::string userName = "<Enter_your_user_name>";
    double score = 100;

    ScoreBoardService::Initialize(APP_Key, SECRET_Key);
    ScoreBoardService *scoreService = ScoreBoardService::getInstance();
    scoreService->SaveUserScore(gameName, userName, score, this, callfuncND_selector(HelloWorld::onGameRequestCompleted));
    scoreService->GetHighestScoreByUser(gameName, userName, this, callfuncND_selector(HelloWorld::onGameRequestCompleted));
    scoreService->GetTopRankings(gameName, this, callfuncND_selector(HelloWorld::onGameRequestCompleted));
    scoreService->GetAverageScoreByUser(gameName, userName, this, callfuncND_selector(HelloWorld::onGameRequestCompleted));
    scoreService->GetUserRanking(gameName, userName, this, callfuncND_selector(HelloWorld::onGameRequestCompleted));
    scoreService->GetLastScoreByUser(gameName, userName, this, callfuncND_selector(HelloWorld::onGameRequestCompleted));
}

void HelloWorld::testRewardService()
{
    std::string gameName = "<Enter_your_game_name>";
    std::string userName = "<Enter_your_user_name>";
    std::string rewardName = "<Enter_your_user_name>";
    std::string description = "<Enter_your_user_name>";

    double rewardPoints = 100;
    
    RewardService::Initialize(APP_Key, SECRET_Key);
    RewardService *rewardService = RewardService::getInstance();
    rewardService->CreateReward(rewardName, description, this, callfuncND_selector(HelloWorld::onRewardRequestCompleted));
    rewardService->GetAllRewards(this, callfuncND_selector(HelloWorld::onRewardRequestCompleted));
    rewardService->EarnRewards(gameName, userName, rewardName, rewardPoints, this, callfuncND_selector(HelloWorld::onRewardRequestCompleted));
    rewardService->RedeemRewards(gameName, userName, rewardName, rewardPoints, this, callfuncND_selector(HelloWorld::onRewardRequestCompleted));
    rewardService->GetGameRewardPointsForUser(gameName, userName, this, callfuncND_selector(HelloWorld::onRewardRequestCompleted));
    
}

string getJsonString(string key, string value)
{
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON_AddStringToObject(bodyJSON, key.c_str(), value.c_str());
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
	string bodyString = cptrFormatted;
    cJSON_Delete(bodyJSON);
	free(cptrFormatted);
    
	return bodyString;
}


void HelloWorld::testStorageService()
{
    std::string dbName = "jsonDocument2";
    std::string collectionName = "jsonCollection";
    std::string docId = "52b4378ae4b0f001c5c0e811";
    std::string key = "mykey";//"Version";
    std::string value = "1400";//"2.3";

    StorageService::Initialize(APP_Key, SECRET_Key);
    StorageService *storageService = StorageService::getInstance();
    
    string json = getJsonString("mykey", "1300");
    
    //storageService->InsertJsonDocument(dbName, collectionName, json, this, callfuncND_selector(HelloWorld::onStorageRequestCompleted));
    //storageService->FindAllCollections(dbName, this, callfuncND_selector(HelloWorld::onStorageRequestCompleted));
    //storageService->FindAllDocuments(dbName, collectionName, this, callfuncND_selector(HelloWorld::onStorageRequestCompleted));
    //storageService->FindDocumentById(dbName, collectionName, docId, this, callfuncND_selector(HelloWorld::onStorageRequestCompleted));
    //storageService->FindDocumentByKeyValue(dbName, collectionName, key, value, this, callfuncND_selector(HelloWorld::onStorageRequestCompleted));
    //storageService->UpdateDocumentByDocId(dbName, collectionName, docId, json, this, callfuncND_selector(HelloWorld::onStorageRequestCompleted));
    //storageService->UpdateDocumentByKeyValue(dbName, collectionName, "mykey", "1200", json, this, callfuncND_selector(HelloWorld::onStorageRequestCompleted));
    //storageService->DeleteDocumentsById(dbName, collectionName, docId, this, callfuncND_selector(HelloWorld::onStorageRequestCompleted));
    storageService->SaveOrUpdateDocumentByKeyValue(dbName, collectionName, key, value, json, this, callfuncND_selector(HelloWorld::onStorageRequestCompleted));
}

void HelloWorld::testPushService()
{
    std::string deviceToken = "Enter_device_token";
    std::string userName = "Enter_your_user_name";
    std::string message = "Your_push_message";
    std::string deviceType = "iOS";
    std::string channelName = "Enter_your_channel_name";

    
    PushNotificationService::Initialize(APP_Key, SECRET_Key);
    PushNotificationService *pushService = PushNotificationService::getInstance();
    pushService->registerDeviceToken(deviceToken, userName, deviceType, this, callfuncND_selector(HelloWorld::onPushRequestCompleted));
    pushService->sendPushMessageToUser(userName, message, this, callfuncND_selector(HelloWorld::onPushRequestCompleted));
    
    map<string, string> messageMap;
    messageMap["alert"] = "Hello, Custom message from channel!";
    messageMap["sound"] = "default";
    messageMap["badge"] = "2";
    
    pushService->sendPushMessageToUser(userName, messageMap, this, callfuncND_selector(HelloWorld::onPushRequestCompleted));
    
    pushService->subscribeToChannel(channelName, userName, this, callfuncND_selector(HelloWorld::onPushRequestCompleted));
    
    pushService->sendPushMessageToChannel(channelName, message, this, callfuncND_selector(HelloWorld::onPushRequestCompleted));
    pushService->sendPushMessageToChannel(channelName, messageMap, this, callfuncND_selector(HelloWorld::onPushRequestCompleted));
}



#pragma mark-
#pragma mark- --- Callback methods ---
#pragma mark-

void HelloWorld::onPushRequestCompleted(cocos2d::CCNode *sender, void *response)
{
    App42PushNotificationResponse *pushResponse = (App42PushNotificationResponse*)response;
    printf("\ncode=%d",pushResponse->getCode());
    printf("\nResponse Body=%s",pushResponse->getBody().c_str());
    
    for(std::vector<App42PushNotification>::iterator it = pushResponse->notification.begin(); it != pushResponse->notification.end(); ++it)
    {
        printf("\n UserName=%s",it->userName.c_str());
        printf("\n Message=%s\n",it->message.c_str());
        printf("\n Type=%s\n",it->type.c_str());
        printf("\n Device Token=%s\n",it->deviceToken.c_str());
    }
}

void HelloWorld::onUserRequestCompleted(cocos2d::CCNode *sender, void *response)
{
    App42UserResponse *userResponse = (App42UserResponse*)response;
    printf("\ncode=%d",userResponse->getCode());
    printf("\nResponse Body=%s",userResponse->getBody().c_str());
    
    for(std::vector<App42User>::iterator it = userResponse->users.begin(); it != userResponse->users.end(); ++it)
    {
        printf("\n UserName=%s",it->userName.c_str());
        printf("\n Email=%s\n",it->email.c_str());
    }
}

void HelloWorld::onStorageRequestCompleted(cocos2d::CCNode *sender, void *response)
{
    App42StorageResponse *storageResponse = (App42StorageResponse*)response;
    printf("\ncode=%d",storageResponse->getCode());
    printf("\nResponse Body=%s",storageResponse->getBody().c_str());
    
    for(std::vector<App42Storage>::iterator it = storageResponse->storages.begin(); it != storageResponse->storages.end(); ++it)
    {
        printf("\n DBName=%s",it->dbName.c_str());
        printf("\n CollectionName=%s\n",it->collectionName.c_str());
    }
    
    for(std::vector<JSONDocument>::iterator it = storageResponse->documents.begin(); it != storageResponse->documents.end(); ++it)
    {
        printf("\n DocId=%s",it->getDocId().c_str());
        printf("\n Json =%s\n",it->getJsonDoc().c_str());
    }
    
}

void HelloWorld::onGameRequestCompleted(cocos2d::CCNode *sender, void *response)
{
    App42GameResponse *gameResponse = (App42GameResponse*)response;
    printf("\ncode=%d",gameResponse->getCode());
    printf("\nResponse Body=%s",gameResponse->getBody().c_str());
    
    for(std::vector<App42Game>::iterator it = gameResponse->games.begin(); it != gameResponse->games.end(); ++it)
    {
        printf("\n Game Name=%s",it->name.c_str());
        printf("\n Description=%s\n",it->description.c_str());
    }
    
    for(std::vector<App42Score>::iterator it = gameResponse->scores.begin(); it != gameResponse->scores.end(); ++it)
    {
        printf("\n User Name=%s",it->getUserName().c_str());
        printf("\n Score Id=%s\n",it->getScoreId().c_str());
        printf("\n Value=%f\n",it->getScoreValue());

    }
}

void HelloWorld::onRewardRequestCompleted(cocos2d::CCNode *sender, void *response)
{
    App42RewardResponse *rewardResponse = (App42RewardResponse*)response;
    printf("\ncode=%d",rewardResponse->getCode());
    printf("\nResponse Body=%s",rewardResponse->getBody().c_str());
    
    for(std::vector<App42Reward>::iterator it = rewardResponse->rewards.begin(); it != rewardResponse->rewards.end(); ++it)
    {
        printf("\n Reward Name=%s",it->name.c_str());
        printf("\n Game Name=%s\n",it->gameName.c_str());
        printf("\n Points=%f\n",it->points);
        printf("\n Description=%s\n",it->description.c_str());

    }
}


void HelloWorld::onHttpRequestCompleted(cocos2d::CCNode *sender, void *response)
{
    App42Response *storageResponse = (App42Response*)response;
    printf("\ncode=%d",storageResponse->getCode());
    printf("\nResponse Body=%s",storageResponse->getBody().c_str());
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
