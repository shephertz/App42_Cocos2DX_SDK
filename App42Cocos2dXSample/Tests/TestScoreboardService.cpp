//
//  TestScoreboardService.cpp
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#include "TestScoreboardService.h"
#include "TestHome.h"
#include "app42base64.h"

#define GO_HOME 105



USING_NS_CC;

Scene* TestScoreboardService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestScoreboardService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestScoreboardService::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    gameName = "TestScore";
    userName1 =  "Rajeev";
    userName2 = "Ranjan";
    dbName = "jsonDocument2";
    collectionName = "TestingScore";
    
    App42API::setDbName(dbName);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    
    float button_y_Offset =30;
    float y_pos = visibleSize.height-button_y_Offset;
    float x_pos = origin.x + visibleSize.width/4;
    
    /**
     * Back Button
     */
    auto backButtonItem = MenuItemImage::create(
                                                "BackButton.png",
                                                "BackButton.png",
                                                CC_CALLBACK_1(TestScoreboardService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(origin.x + visibleSize.width/2 ,
                                      origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * SaveUserScore
     */
    auto saveUserScoreLabel = LabelTTF::create("SaveUserScore", "Marker Felt", 24);
    saveUserScoreLabel->setColor(Color3B::WHITE);
    auto saveUserScoreItem  = MenuItemLabel::create(saveUserScoreLabel, CC_CALLBACK_1(TestScoreboardService::saveUserScore, this));
    //y_pos -= button_y_Offset;
    saveUserScoreItem->setPosition(Point(x_pos,y_pos));
    
    
    /**
     * Edit Score
     */
    auto editScoreLabel = LabelTTF::create("Edit Score", "Marker Felt", 24);
    editScoreLabel->setColor(Color3B::WHITE);
    auto editScoreItem  = MenuItemLabel::create(editScoreLabel, CC_CALLBACK_1(TestScoreboardService::saveUserScore, this));
    y_pos -= button_y_Offset;
    editScoreItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetScoresByUser
     */
    auto getScoresByUserLabel = LabelTTF::create("GetScoresByUser", "Marker Felt", 24);
    getScoresByUserLabel->setColor(Color3B::WHITE);
    auto getScoresByUserItem  = MenuItemLabel::create(getScoresByUserLabel, CC_CALLBACK_1(TestScoreboardService::getScoresByUser, this));
    y_pos -= button_y_Offset;
    getScoresByUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetLowestScoreByUser
     */
    auto getLowestScoreByUserLabel = LabelTTF::create("GetLowestScoreByUser", "Marker Felt", 24);
    getLowestScoreByUserLabel->setColor(Color3B::WHITE);
    auto getLowestScoreByUserItem  = MenuItemLabel::create(getLowestScoreByUserLabel, CC_CALLBACK_1(TestScoreboardService::getLowestScoreByUser, this));
    y_pos -= button_y_Offset;
    getLowestScoreByUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetHighestScoreByUser
     */
    auto getHighestScoreByUserLabel = LabelTTF::create("GetHighestScoreByUser", "Marker Felt", 24);
    getHighestScoreByUserLabel->setColor(Color3B::WHITE);
    auto getHighestScoreByUserItem  = MenuItemLabel::create(getHighestScoreByUserLabel, CC_CALLBACK_1(TestScoreboardService::getHighestScoreByUser, this));
    y_pos -= button_y_Offset;
    getHighestScoreByUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAverageScoreByUser
     */
    auto getAverageScoreByUserLabel = LabelTTF::create("GetAverageScoreByUser", "Marker Felt", 24);
    getAverageScoreByUserLabel->setColor(Color3B::WHITE);
    auto getAverageScoreByUserItem  = MenuItemLabel::create(getAverageScoreByUserLabel, CC_CALLBACK_1(TestScoreboardService::getAverageScoreByUser, this));
    y_pos -= button_y_Offset;
    getAverageScoreByUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetLastScoreByUser
     */
    auto getLastScoreByUserLabel = LabelTTF::create("GetLastScoreByUser", "Marker Felt", 24);
    getLastScoreByUserLabel->setColor(Color3B::WHITE);
    auto getLastScoreByUserItem  = MenuItemLabel::create(getLastScoreByUserLabel, CC_CALLBACK_1(TestScoreboardService::getLastScoreByUser, this));
    y_pos -= button_y_Offset;
    getLastScoreByUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetLastGameScore
     */
    auto getLastGameScoreLabel = LabelTTF::create("GetLastGameScore", "Marker Felt", 24);
    getLastGameScoreLabel->setColor(Color3B::WHITE);
    auto getLastGameScoreItem  = MenuItemLabel::create(getLastGameScoreLabel, CC_CALLBACK_1(TestScoreboardService::getLastScoreByUser, this));
    y_pos -= button_y_Offset;
    getLastGameScoreItem->setPosition(Point(x_pos,y_pos));


    /**
     * GetTopRankings
     */
    auto getTopRankingsLabel = LabelTTF::create("GetTopRankings", "Marker Felt", 24);
    getTopRankingsLabel->setColor(Color3B::WHITE);
    auto getTopRankingsItem  = MenuItemLabel::create(getTopRankingsLabel, CC_CALLBACK_1(TestScoreboardService::getTopRankings, this));
    y_pos -= button_y_Offset;
    getTopRankingsItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetTopRankersByGroup
     */
    auto getTopRankersByGroupLabel = LabelTTF::create("GetTopRankersByGroup", "Marker Felt", 24);
    getTopRankersByGroupLabel->setColor(Color3B::WHITE);
    auto getTopRankersByGroupItem  = MenuItemLabel::create(getTopRankersByGroupLabel, CC_CALLBACK_1(TestScoreboardService::getTopRankersByGroup, this));
    y_pos -= button_y_Offset;
    getTopRankersByGroupItem->setPosition(Point(x_pos,y_pos));

    /**
     * GetTopRankingsByGroup
     */
    auto getTopRankingsByGroupLabel = LabelTTF::create("GetTopRankingsByGroup", "Marker Felt", 24);
    getTopRankingsByGroupLabel->setColor(Color3B::WHITE);
    auto getTopRankingsByGroupItem  = MenuItemLabel::create(getTopRankingsByGroupLabel, CC_CALLBACK_1(TestScoreboardService::getTopRankingsByGroup, this));
    y_pos -= button_y_Offset;
    getTopRankingsByGroupItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetTopNRankings
     */
    auto getTopNRankingsLabel = LabelTTF::create("GetTopNRankings", "Marker Felt", 24);
    getTopNRankingsLabel->setColor(Color3B::WHITE);
    auto getTopNRankingsItem  = MenuItemLabel::create(getTopNRankingsLabel, CC_CALLBACK_1(TestScoreboardService::getTopNRankings, this));
    y_pos -= button_y_Offset;
    getTopNRankingsItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetUsersWithScoreRange
     */
    auto getUsersWithScoreRangeLabel = LabelTTF::create("GetUsersWithScoreRange", "Marker Felt", 24);
    getUsersWithScoreRangeLabel->setColor(Color3B::WHITE);
    auto getUsersWithScoreRangeItem  = MenuItemLabel::create(getUsersWithScoreRangeLabel, CC_CALLBACK_1(TestScoreboardService::getUsersWithScoreRange, this));
    y_pos -= button_y_Offset;
    getUsersWithScoreRangeItem->setPosition(Point(x_pos,y_pos));

    /**
     * GetTopRankingsInDateRange
     */
    auto getTopRankingsInDateRangeLabel = LabelTTF::create("GetTopRankingsInDateRange", "Marker Felt", 24);
    getTopRankingsInDateRangeLabel->setColor(Color3B::WHITE);
    auto getTopRankingsInDateRangeItem  = MenuItemLabel::create(getTopRankingsInDateRangeLabel, CC_CALLBACK_1(TestScoreboardService::getTopRankingsInDateRange, this));
    y_pos -= button_y_Offset;
    getTopRankingsInDateRangeItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetTopNRankers
     */
    auto getTopNRankersLabel = LabelTTF::create("GetTopNRankers", "Marker Felt", 24);
    getTopNRankersLabel->setColor(Color3B::WHITE);
    auto getTopNRankersItem  = MenuItemLabel::create(getTopNRankersLabel, CC_CALLBACK_1(TestScoreboardService::getTopNRankers, this));
    y_pos -= button_y_Offset;
    getTopNRankersItem->setPosition(Point(x_pos,y_pos));
    
    y_pos = visibleSize.height-button_y_Offset;
    x_pos = origin.x + 3*visibleSize.width/4;
    
    /**
     * GetTopNRankersBySorting
     */
    auto getTopNRankersBySortingLabel = LabelTTF::create("GetTopNRankersBySorting", "Marker Felt", 24);
    getTopNRankersBySortingLabel->setColor(Color3B::WHITE);
    auto getTopNRankersBySortingItem  = MenuItemLabel::create(getTopNRankersBySortingLabel, CC_CALLBACK_1(TestScoreboardService::getTopNRankersBySorting, this));
    y_pos -= button_y_Offset;
    getTopNRankersBySortingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetTopNRankersInDateRange
     */
    auto getTopNRankersInDateRangeLabel = LabelTTF::create("GetTopNRankersInDateRange", "Marker Felt", 24);
    getTopNRankersInDateRangeLabel->setColor(Color3B::WHITE);
    auto getTopNRankersInDateRangeItem  = MenuItemLabel::create(getTopNRankersInDateRangeLabel, CC_CALLBACK_1(TestScoreboardService::getTopNRankersInDataRange, this));
    y_pos -= button_y_Offset;
    getTopNRankersInDateRangeItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetUserRanking
     */
    auto getUserRankingLabel = LabelTTF::create("GetUserRanking", "Marker Felt", 24);
    getUserRankingLabel->setColor(Color3B::WHITE);
    auto getUserRankingItem  = MenuItemLabel::create(getUserRankingLabel, CC_CALLBACK_1(TestScoreboardService::getUserRanking, this));
    y_pos -= button_y_Offset;
    getUserRankingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetTopNTargetRankers
     */
    auto getTopNTargetRankersLabel = LabelTTF::create("GetTopNTargetRankers", "Marker Felt", 24);
    getTopNTargetRankersLabel->setColor(Color3B::WHITE);
    auto getTopNTargetRankersItem  = MenuItemLabel::create(getTopNTargetRankersLabel, CC_CALLBACK_1(TestScoreboardService::getTopNTargetRankers, this));
    y_pos -= button_y_Offset;
    getTopNTargetRankersItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetTopNRankersFromFacebook
     */
    auto getTopNRankersFromFacebookLabel = LabelTTF::create("GetTopNRankersFromFacebook", "Marker Felt", 24);
    getTopNRankersFromFacebookLabel->setColor(Color3B::WHITE);
    auto getTopNRankersFromFacebookItem  = MenuItemLabel::create(getTopNRankersFromFacebookLabel, CC_CALLBACK_1(TestScoreboardService::getTopNRankersFromFacebook, this));
    y_pos -= button_y_Offset;
    getTopNRankersFromFacebookItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetTopNRankersFromFacebookInDateRange
     */
    auto getTopNRankersFromFacebookInDateRangeLabel = LabelTTF::create("GetTopNRankersFromFacebookInDateRange", "Marker Felt", 24);
    getTopNRankersFromFacebookInDateRangeLabel->setColor(Color3B::WHITE);
    auto getTopNRankersFromFacebookInDateRangeItem  = MenuItemLabel::create(getTopNRankersFromFacebookInDateRangeLabel, CC_CALLBACK_1(TestScoreboardService::getTopNRankersFromFacebookInDateRange, this));
    y_pos -= button_y_Offset;
    getTopNRankersFromFacebookInDateRangeItem->setPosition(Point(x_pos,y_pos));
    
    
    /**
     * SaveCustomScore
     */
    auto saveCustomScoreLabel = LabelTTF::create("SaveCustomScore", "Marker Felt", 24);
    saveCustomScoreLabel->setColor(Color3B::WHITE);
    auto saveCustomScoreItem  = MenuItemLabel::create(saveCustomScoreLabel, CC_CALLBACK_1(TestScoreboardService::saveCustomUserScore, this));
    y_pos -= button_y_Offset;
    saveCustomScoreItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FetchCustomScore
     */
    auto fetchCustomScoreLabel = LabelTTF::create("FetchCustomScore", "Marker Felt", 24);
    fetchCustomScoreLabel->setColor(Color3B::WHITE);
    auto fetchCustomScoreItem  = MenuItemLabel::create(fetchCustomScoreLabel, CC_CALLBACK_1(TestScoreboardService::getTopNRankersWithCustomScore, this));
    y_pos -= button_y_Offset;
    fetchCustomScoreItem->setPosition(Point(x_pos,y_pos));
    
 	
    
    // create menu, it's an autorelease object
	auto menu = Menu::create(backButtonItem,
                             saveUserScoreItem,
                             editScoreItem,
                             getScoresByUserItem,
                             getLowestScoreByUserItem,
                             getHighestScoreByUserItem,
                             getAverageScoreByUserItem,
                             getLastScoreByUserItem,
                             getLastGameScoreItem, NULL);

	auto menu1 = Menu::create(
                             getTopRankingsItem,
                             getTopRankersByGroupItem,
                             getTopNRankingsItem,
                             getTopRankingsByGroupItem,
                             getUsersWithScoreRangeItem,
                             getTopRankingsInDateRangeItem,
                             getTopNRankersItem,
                             getTopNRankersBySortingItem, NULL);

	auto menu2 = Menu::create(
                             getTopNRankersInDateRangeItem,
                             getUserRankingItem,
                             getTopNTargetRankersItem,
                             getTopNRankersFromFacebookItem,
                             getTopNRankersFromFacebookInDateRangeItem,
                             saveCustomScoreItem,
                             fetchCustomScoreItem, NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	menu1->setPosition(Point::ZERO);
    this->addChild(menu1, 1);

	menu2->setPosition(Point::ZERO);
    this->addChild(menu2, 1);
    
    return true;
}



void TestScoreboardService::saveUserScore(Ref *sender)
{
    /*
     App42Object *object = new App42Object();
     object->setObject("coding", "coding");
     object->setObject("level", 2);
     
     scoreBoardService->AddCustomScore(object, collectionName);
     //const char* userName = "100006181209270";
     */
    
    
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    int score = 400;
    string userName = "汉语";
    string userN = base64_encode((unsigned char const*)userName.c_str(), userName.length());
    scoreBoardService->SaveUserScore(gameName, userN.c_str(), score, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::saveCustomUserScore(Ref* sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();

    App42Object *object = new App42Object();
    object->setObject("game", gameName);// key-value pair
    object->setObject("level", 2);
    scoreBoardService->AddCustomScore(object, collectionName);

    const char* userName = "App42Team";
    int score = 400;
    scoreBoardService->SaveUserScore(gameName, userName, score, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getTopNRankersWithCustomScore(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    
    const char* key = "game";
    const char* value = gameName;
    Query *query = QueryBuilder::BuildQuery(key, value, APP42_OP_EQUALS);
    scoreBoardService->setQuery(collectionName, query);
    
    int max =10;
    scoreBoardService->GetTopNRankers(gameName, max, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::editScoreById(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    const char* scoreId = "MnwIWTcXphhVpIaauoO4lJRWBRk=";
    double score = 200;
    scoreBoardService->EditScoreValueById(scoreId, score, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getScoresByUser(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    scoreBoardService->setQuery(dbName, collectionName);
    scoreBoardService->GetScoresByUser(gameName, userName1, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getLowestScoreByUser(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    scoreBoardService->GetLowestScoreByUser(gameName, userName1, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getHighestScoreByUser(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    scoreBoardService->GetHighestScoreByUser(gameName, userName1, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getAverageScoreByUser(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    scoreBoardService->GetAverageScoreByUser(gameName, userName1, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getLastScoreByUser(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    scoreBoardService->GetLastScoreByUser(gameName, userName1, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getLastGameScore(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    scoreBoardService->GetLastGameScore(userName1, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getTopRankingsByGroup(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    std::vector<string>userList;
    userList.push_back("r12");
    userList.push_back("r1");
    userList.push_back("Rajeev");
    scoreBoardService->GetTopRankingsByGroup(gameName, userList,app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}


void TestScoreboardService::getTopRankersByGroup(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    std::vector<string>userList;
    userList.push_back("r12");
    userList.push_back("r1");
    scoreBoardService->GetTopRankersByGroup(gameName, userList,app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getTopNRankings(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    int max =10;
    scoreBoardService->GetTopNRankings(gameName, max,app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getTopRankings(Ref *sender)
{
    
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    
    scoreBoardService->GetTopRankings(gameName, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getUsersWithScoreRange(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    double minScore =1000;
    double maxScore =1200;
    scoreBoardService->GetUsersWithScoreRange(gameName, minScore, maxScore,app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getTopRankingsInDateRange(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    
    tm start_date;
    tm end_date;
    
	time_t diff =0;
	time_t t = time(NULL);
    
    end_date = *gmtime(&t);
    
	diff += t-60 * sec_per_day;
    start_date = *gmtime(&diff);
    
    string strEndDate = Util::getTimeStamp(&end_date);
    string strStartDate = Util::getTimeStamp(&start_date);
    
    printf("Start Date: %s\n", strStartDate.c_str());
    printf("End   Date: %s\n", strEndDate.c_str());
    scoreBoardService->GetTopRankings(gameName, &start_date, &end_date, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}


void TestScoreboardService::getTopNRankers(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    int max =10;
    scoreBoardService->GetTopNRankers(gameName, max, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getTopNRankersBySorting(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    int max =10;
    map<string,string> otherMetaHeaders;
    otherMetaHeaders["score"] = "orderByAscending"; // Use orderByDescending for Descending or orderByAscending for Ascending
    scoreBoardService->setOtherMetaHeaders(otherMetaHeaders);
    scoreBoardService->GetTopNRankers(gameName, max, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getTopNRankersInDataRange(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    
    tm start_date;
    tm end_date;
    
	time_t diff =0;
	time_t t = time(NULL);
    
    end_date = *gmtime(&t);
    
	diff += t-600 * sec_per_day;
    start_date = *gmtime(&diff);
    
    string strEndDate = Util::getTimeStamp(&end_date);
    string strStartDate = Util::getTimeStamp(&start_date);
    
    printf("Start Date: %s\n", strStartDate.c_str());
    printf("End   Date: %s\n", strEndDate.c_str());
    
    int max =10;
    scoreBoardService->GetTopNRankers(gameName, &start_date, &end_date, max, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getUserRanking(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    scoreBoardService->GetUserRanking(gameName, userName1, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getTopNTargetRankers(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();

    const char* key = "name";
    const char* value = "Nick";
    int max =2;
    Query *query = QueryBuilder::BuildQuery(key, value, APP42_OP_EQUALS);
    
    scoreBoardService->setQuery(dbName, collectionName, query);
    scoreBoardService->GetTopNTargetRankers(gameName, max, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
    
}

void TestScoreboardService::getTopNRankersFromFacebook(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    const char* fbAccessToken = "CAACEdEose0cBAD0e9yYUPzXPCTpqedbBAyShgE3KDGY1nyowqPp9QPh5aMSRjzRnIcRh3J27iGZAypwjMmGR9YaGogq2ZBTBWimZAR8TGkEUUeamqI8L6xslxl67Sk6rSQ55dzsNIff61Bs4jXtL7ABe5j9oZCzi1ylWXFqGswFE1vwrZBhcvd7NHL08e2Yn1ZCuxUFGeqjwZDZD";
    int max = 5;
    scoreBoardService->GetTopNRankersFromFacebook(gameName, fbAccessToken, max, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}

void TestScoreboardService::getTopNRankersFromFacebookInDateRange(Ref *sender)
{
    ScoreBoardService *scoreBoardService = App42API::BuildScoreBoardService();
    const char* fbAccessToken = "CAACEdEose0cBAD0e9yYUPzXPCTpqedbBAyShgE3KDGY1nyowqPp9QPh5aMSRjzRnIcRh3J27iGZAypwjMmGR9YaGogq2ZBTBWimZAR8TGkEUUeamqI8L6xslxl67Sk6rSQ55dzsNIff61Bs4jXtL7ABe5j9oZCzi1ylWXFqGswFE1vwrZBhcvd7NHL08e2Yn1ZCuxUFGeqjwZDZD";
    int max = 5;
    
    tm start_date;
    tm end_date;
    
	time_t diff =0;
	time_t t = time(NULL);
    
    end_date = *gmtime(&t);
    
	diff += t-1 * sec_per_day;
    start_date = *gmtime(&diff);

    
    scoreBoardService->GetTopNRankersFromFacebook(gameName, fbAccessToken, &start_date, &end_date, max, app42callback(TestScoreboardService::onScoreBoardRequestCompleted, this));
}


void TestScoreboardService::onScoreBoardRequestCompleted( void *response)
{
    App42GameResponse *scoreResponse = (App42GameResponse*)response;
    printf("\ncode=%d",scoreResponse->getCode());
    printf("\nResponse Body=%s",scoreResponse->getBody().c_str());
    
    string code = StringUtils::format("Code = %d",scoreResponse->getCode());
    responseArray.push_back(code);
    
    if (scoreResponse->isSuccess)
    {
        vector<App42Score> scores = scoreResponse->scores;
        for(std::vector<App42Score>::iterator it = scores.begin(); it != scores.end(); ++it)
        {
            printf("\n CreatedAt=%s",it->getCreatedOn().c_str());
            printf("\n Rank=%0.0lf\n",it->getRank());
            printf("\n ScoreId=%s\n",it->getScoreId().c_str());
            printf("\n ScoreValue=%f\n",it->getScoreValue());
            printf("\n UserName=%s\n",it->getUserName().c_str());
//            string userName1 = base64_decode(it->getUserName());
//            printf("userName1=%s",userName1.c_str());
            printf("\n Facebook User Name = %s",it->facebookProfile.getName().c_str());
            printf("\n Facebook Id = %s",it->facebookProfile.getFbId().c_str());
            printf("\n Facebook Picture URL = %s",it->facebookProfile.getPicture().c_str());

            
            std::vector<JSONDocument> jsonDocList = it->getJsonDocList();
            for(std::vector<JSONDocument>::iterator it1 = jsonDocList.begin(); it1 != jsonDocList.end(); ++it1)
            {
                
                //printf("\n CreatedAt=%s",it1->getCreatedAt().c_str());
                printf("\n DocId=%s",it1->getDocId().c_str());
                printf("\n Event=%s",it1->getEvent().c_str());
                printf("\n Owner=%s",it1->getOwner().c_str());
                printf("\n UpdatedAt=%s",it1->getUpdatedAt().c_str());
                printf("\n JsonDoc=%s\n",it1->getJsonDoc().c_str());
            }
        }
    }
    else
    {
        printf("\nerrordetails:%s",scoreResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",scoreResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",scoreResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",scoreResponse->httpErrorCode);
        
        string error = StringUtils::format("Error = %s",scoreResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",scoreResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestScoreboardService::loadResponseScene, this));
    
}

void TestScoreboardService::loadResponseScene()
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

void TestScoreboardService::menuCloseCallback(Ref* pSender)
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