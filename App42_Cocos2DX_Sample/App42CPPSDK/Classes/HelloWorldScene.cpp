#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#define APP_Key "3c1d8c1d23e1dde0d820b06e33e6260e3b9ac0438d522a4ac9d524fc12cb8559"
                //"cad2bfab6310acd9696187b98682925125e469ab0d0d585db0b00609f461b791"
#define SECRET_Key "254964c8a7fcc95cee0362adc2e0e06e0a64ec53c7a9e5279c11b3c4303edf73"
                //"55811709916e7ce4405cde0cdc5a254cf4b506fbafdae05760a73100b8080b67"


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
    
    testUserService();
    
    
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
    
    //testStorageService();
    
    /**
     * Test Push Service
     */
    
    //testPushService();
    
    
    return true;
}

void HelloWorld::testUserService()
{
    Util::setTraceEnabled(true);
    UserService::Initialize(APP_Key, SECRET_Key);
    UserService *user = UserService::getInstance();
    //user->CreateUser("Rajeev3243590", "9934273686", "rajeevabcdegf@gmail.com",this,callfuncND_selector(HelloWorld::onUserRequestCompleted));
    
    //user->Authenticate("Rajeev324359", "9934273686", this, callfuncND_selector(HelloWorld::onUserRequestCompleted));
    //user->GetUser("Rajeev324359", this, callfuncND_selector(HelloWorld::onUserRequestCompleted));
    user->GetAllUsers(this,callfuncND_selector(HelloWorld::onUserRequestCompleted));
}


void HelloWorld::testGameService()
{
    GameService::Initialize(APP_Key, SECRET_Key);
    GameService *gameService = GameService::getInstance();
    //gameService->CreateGame("NinjaJump", "NInja Jump", this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    gameService->GetGamebyName("NinjaJump", this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
}

void HelloWorld::testScoreService()
{
    ScoreService::Initialize(APP_Key, SECRET_Key);
    ScoreService *scoreService = ScoreService::getInstance();
    //scoreService->AddScore("NinjaJump", "Rajeev3243590", 200, this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    scoreService->DeductScore("NinjaJump", "Rajeev3243590", 50, this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
}

void HelloWorld::testScoreBoardService()
{
    ScoreBoardService::Initialize(APP_Key, SECRET_Key);
    ScoreBoardService *scoreService = ScoreBoardService::getInstance();
    //scoreService->SaveUserScore("NinjaJump", "Rajeev3243590", 300, this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    //scoreService->GetHighestScoreByUser("NinjaJump", "Rajeev3243590", this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    //scoreService->GetTopRankings("NinjaJump", this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    //scoreService->GetAverageScoreByUser("NinjaJump", "Rajeev3243590", this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    //scoreService->GetUserRanking("NinjaJump", "Rajeev3243590", this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    scoreService->GetLastScoreByUser("NinjaJump", "Rajeev3243590", this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
}

void HelloWorld::testRewardService()
{
    RewardService::Initialize(APP_Key, SECRET_Key);
    RewardService *rewardService = RewardService::getInstance();
    //rewardService->CreateReward("TestReward", "CReating to test", this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    //rewardService->GetAllRewards(this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    //rewardService->EarnRewards("NinjaJump", "Rajeev3243590", "TestReward", 101, this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    //rewardService->RedeemRewards("NinjaJump", "Rajeev3243590", "TestReward", 60, this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    rewardService->GetGameRewardPointsForUser("NinjaJump", "Rajeev3243590", this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    
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
    StorageService::Initialize(APP_Key, SECRET_Key);
    StorageService *storageService = StorageService::getInstance();
    
    string json = getJsonString("key", "App42 coud api cocos2d-x version testing.");
    
    storageService->InsertJsonDocument("jsonDocument2", "Testing2", json, this, callfuncND_selector(HelloWorld::onStorageRequestCompleted));
    //storageService->FindAllCollections("jsonDocument2", this, callfuncND_selector(HelloWorld::onStorageRequestCompleted));
    //storageService->FindAllDocuments("jsonDocument2", "jsonCollection", this, callfuncND_selector(HelloWorld::onStorageRequestCompleted));
    //storageService->FindDocumentById("jsonDocument2", "jsonCollection", "515bc5b0e4b06691bd02d438", this, callfuncND_selector(HelloWorld::onStorageRequestCompleted));
    //storageService->FindDocumentByKeyValue("jsonDocument2", "jsonCollection", "Version", "2.3", this, callfuncND_selector(HelloWorld::onStorageRequestCompleted));
}

void HelloWorld::testPushService()
{
    PushNotificationService::Initialize(APP_Key, SECRET_Key);
    PushNotificationService *pushService = PushNotificationService::getInstance();
    //pushService->registerDeviceToken("deviceToken", "DhruvC", "iOS", this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    //pushService->sendPushMessageToUser("DhruvC", "Hello From Cocos2d-x", this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    
    map<string, string> messageMap;
    messageMap["alert"] = "Hello, Custom message from channel!";
    messageMap["sound"] = "default";
    messageMap["badge"] = "2";
    
    //pushService->sendPushMessageToUser("DhruvC", messageMap, this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    
    //pushService->subscribeToChannel("Test Channel", "DhruvC", this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    
    pushService->sendPushMessageToChannel("Test Channel", "Hello From Channel!", this, callfuncND_selector(HelloWorld::onPushRequestCompleted));
    //pushService->sendPushMessageToChannel("Test Channel", messageMap, this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
}

void HelloWorld::onPushRequestCompleted(cocos2d::CCNode *sender, void *response)
{
    App42PushNotificationResponse *pushResponse = (App42PushNotificationResponse*)response;
    printf("\ncode=%d",pushResponse->getCode());
    printf("\nResponse Body=%s",pushResponse->getBody().c_str());
    
    for(std::vector<App42PushNotification>::iterator it = pushResponse->notification.begin(); it != pushResponse->notification.end(); ++it)
    {
        printf("\n UserName=%s",it->userName.c_str());
        printf("\n Message=%s\n",it->message.c_str());
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
        printf("\n Message=%s\n",it->email.c_str());
    }
}

void HelloWorld::onStorageRequestCompleted(cocos2d::CCNode *sender, void *response)
{
    App42StorageResponse *storageResponse = (App42StorageResponse*)response;
    printf("\ncode=%d",storageResponse->getCode());
    printf("\nResponse Body=%s",storageResponse->getBody().c_str());
    
    for(std::vector<App42Storage>::iterator it = storageResponse->storages.begin(); it != storageResponse->storages.end(); ++it)
    {
        printf("\n UserName=%s",it->dbName.c_str());
        printf("\n Message=%s\n",it->collectionName.c_str());
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
