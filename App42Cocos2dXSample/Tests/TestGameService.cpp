//
//  TestGameService.cpp
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#include "TestGameService.h"
#include "TestHome.h"

#define GO_HOME 104

#define APPWARP_APP_KEY     "cad2bfab6310acd9696187b98682925125e469ab0d0d585db0b00609f461b791"
#define APPWARP_SECRET_KEY  "55811709916e7ce4405cde0cdc5a254cf4b506fbafdae05760a73100b8080b67"

USING_NS_CC;

Scene* TestGameService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestGameService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestGameService::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    
    float button_y_Offset =30;
    float y_pos = visibleSize.height-button_y_Offset;
    float x_pos = origin.x + visibleSize.width/2;
    
    /**
     * Back Button
     */
    auto backButtonItem = MenuItemImage::create(
                                                "BackButton.png",
                                                "BackButton.png",
                                                CC_CALLBACK_1(TestGameService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * Create Game
     */
    auto createGameLabel = LabelTTF::create("CreateGame", "Marker Felt", 24);
    createGameLabel->setColor(Color3B::WHITE);
    auto createGameItem  = MenuItemLabel::create(createGameLabel, CC_CALLBACK_1(TestGameService::createGame, this));
    createGameItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get Game by Name
     */
    auto getGameLabel = LabelTTF::create("GetGameByName", "Marker Felt", 24);
    getGameLabel->setColor(Color3B::WHITE);
    auto getGameItem  = MenuItemLabel::create(getGameLabel, CC_CALLBACK_1(TestGameService::getGamebyName, this));
    y_pos -= button_y_Offset;
    getGameItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get All Games
     */
    auto getAllGamesLabel = LabelTTF::create("GetAllGames", "Marker Felt", 24);
    getAllGamesLabel->setColor(Color3B::WHITE);
    auto getAllGameItem  = MenuItemLabel::create(getAllGamesLabel, CC_CALLBACK_1(TestGameService::getAllGames, this));
    y_pos -= button_y_Offset;
    getAllGameItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get All Games By Paging
     */
    auto getAllGamesByPagingLabel = LabelTTF::create("GetAllGamesByPaging", "Marker Felt", 24);
    getAllGamesByPagingLabel->setColor(Color3B::WHITE);
    auto getAllGameByPagingItem  = MenuItemLabel::create(getAllGamesByPagingLabel, CC_CALLBACK_1(TestGameService::getAllGamesByPaging, this));
    y_pos -= button_y_Offset;
    getAllGameByPagingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get All Games Count
     */
    auto getAllGamesCountLabel = LabelTTF::create("GetAllGamesCount", "Marker Felt", 24);
    getAllGamesCountLabel->setColor(Color3B::WHITE);
    auto getAllGamesCountItem  = MenuItemLabel::create(getAllGamesCountLabel, CC_CALLBACK_1(TestGameService::getAllGamesCount, this));
    y_pos -= button_y_Offset;
    getAllGamesCountItem->setPosition(Point(x_pos,y_pos));
 	 

    // create menu, it's an autorelease object
    auto menu = Menu::create(backButtonItem,
                             createGameItem,
                             getGameItem,
                             getAllGameItem,
                             getAllGameByPagingItem,
                             getAllGamesCountItem,
                             NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}


void TestGameService::createGame(Ref *sender)
{
    GameService *gameService = App42API::BuildGameService();
    const char* gameName = "NinjaJumpTest";
    const char* description = "Description";
    gameService->CreateGame(gameName, description, app42callback(TestGameService::onGameRequestCompleted, this));
    
}
void TestGameService::getGamebyName(Ref *sender)
{
    GameService *gameService = App42API::BuildGameService();
    const char* gameName = "NinjaJumpTest";
    gameService->GetGamebyName(gameName, app42callback(TestGameService::onGameRequestCompleted, this));
}


void TestGameService::getAllGames(Ref *sender)
{
    GameService *gameService = App42API::BuildGameService();
    gameService->GetAllGames(app42callback(TestGameService::onGameRequestCompleted, this));
}
void TestGameService::getAllGamesByPaging(Ref *sender)
{
    GameService *gameService = App42API::BuildGameService();
    int max = 2;
    int offset = 0;
    gameService->GetAllGames(max,offset,app42callback(TestGameService::onGameRequestCompleted, this));
}

void TestGameService::getAllGamesCount(Ref *sender)
{
    GameService *gameService = App42API::BuildGameService();
    gameService->GetAllGamesCount(app42callback(TestGameService::onGameRequestCompleted, this));
}

void TestGameService::onGameRequestCompleted( void *response)
{
    App42GameResponse *gameResponse = (App42GameResponse*)response;
    printf("\ncode=%d",gameResponse->getCode());
    printf("\nResponse Body=%s",gameResponse->getBody().c_str());
    string code = StringUtils::format("Code = %d",gameResponse->getCode());
    responseArray.push_back(code);
    
    if (gameResponse->isSuccess)
    {
        printf("\nTotalRecords=%d",gameResponse->getTotalRecords());
        for(std::vector<App42Game>::iterator it = gameResponse->games.begin(); it != gameResponse->games.end(); ++it)
        {
            printf("\n Game Name=%s",it->name.c_str());
            printf("\n Description=%s\n",it->description.c_str());
        }
    }
    else
    {
        printf("\nerrordetails:%s",gameResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",gameResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",gameResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",gameResponse->httpErrorCode);
        
        string error = StringUtils::format("Error = %s",gameResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",gameResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestGameService::loadResponseScene, this));
    
}

void TestGameService::loadResponseScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ResponseScene::create();
    layer->serviceId = GO_HOME;
    // add layer as a child to scene
    vector<string>::iterator it;
    
    for (it= responseArray.begin(); it!= responseArray.end(); it++)
    {
        layer->loadResponse(*it);
    }
    scene->addChild(layer);
    // run
    Director::getInstance()->replaceScene(scene);
}


void TestGameService::menuCloseCallback(Ref* pSender)
{
    MenuItem *item = (MenuItem*)pSender;
    int senderTag = item->getTag();
    switch (senderTag)
    {
        case GO_HOME:
        {
            // create a scene. it's an autorelease object
            auto scene = TestHome::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        default:
            break;
    }
}