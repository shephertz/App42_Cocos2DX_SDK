//
//  TestRewardService.cpp
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#include "TestRewardService.h"
#include "TestHome.h"


#define GO_HOME 106



USING_NS_CC;

Scene* TestRewardService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestRewardService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestRewardService::init()
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
                                                CC_CALLBACK_1(TestRewardService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * Create Reward
     */
    auto createRewardLabel = LabelTTF::create("CreateReward", "Marker Felt", 24);
    createRewardLabel->setColor(Color3B::WHITE);
    auto createRewardItem  = MenuItemLabel::create(createRewardLabel, CC_CALLBACK_1(TestRewardService::createReward, this));
    createRewardItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get All Rewards
     */
    auto getAllRewardsLabel = LabelTTF::create("GetAllRewards", "Marker Felt", 24);
    getAllRewardsLabel->setColor(Color3B::WHITE);
    auto getAllRewardItem  = MenuItemLabel::create(getAllRewardsLabel, CC_CALLBACK_1(TestRewardService::getAllRewards, this));
    y_pos -= button_y_Offset;
    getAllRewardItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get All Rewards By Paging
     */
    auto getAllRewardsByPagingLabel = LabelTTF::create("GetAllRewardsByPaging", "Marker Felt", 24);
    getAllRewardsByPagingLabel->setColor(Color3B::WHITE);
    auto getAllRewardsByPagingItem  = MenuItemLabel::create(getAllRewardsByPagingLabel, CC_CALLBACK_1(TestRewardService::getAllRewardsByPaging, this));
    y_pos -= button_y_Offset;
    getAllRewardsByPagingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get All Rewards Count
     */
    auto getAllRewardsCountLabel = LabelTTF::create("GetAllRewardsCount", "Marker Felt", 24);
    getAllRewardsCountLabel->setColor(Color3B::WHITE);
    auto getAllRewardsCountItem  = MenuItemLabel::create(getAllRewardsCountLabel, CC_CALLBACK_1(TestRewardService::getAllRewardsCount, this));
    y_pos -= button_y_Offset;
    getAllRewardsCountItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Earn Reward
     */
    auto earnRewardLabel = LabelTTF::create("EarnRewards", "Marker Felt", 24);
    earnRewardLabel->setColor(Color3B::WHITE);
    auto earnRewardItem  = MenuItemLabel::create(earnRewardLabel, CC_CALLBACK_1(TestRewardService::earnRewards, this));
    y_pos -= button_y_Offset;
    earnRewardItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Redeem Reward
     */
    auto redeemRewardLabel = LabelTTF::create("RedeemRewards", "Marker Felt", 24);
    redeemRewardLabel->setColor(Color3B::WHITE);
    auto redeemRewardItem  = MenuItemLabel::create(redeemRewardLabel, CC_CALLBACK_1(TestRewardService::redeemRewards, this));
    y_pos -= button_y_Offset;
    redeemRewardItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetGameRewardPointsForUser
     */
    auto getGameRewardPointsForUserLabel = LabelTTF::create("GetGameRewardPointsForUser", "Marker Felt", 24);
    getGameRewardPointsForUserLabel->setColor(Color3B::WHITE);
    auto getGameRewardPointsForUserItem  = MenuItemLabel::create(getGameRewardPointsForUserLabel, CC_CALLBACK_1(TestRewardService::getGameRewardPointsForUser, this));
    y_pos -= button_y_Offset;
    getGameRewardPointsForUserItem->setPosition(Point(x_pos,y_pos));

    /**
     * GetRewardByName
     */
    auto getRewardByNameLabel = LabelTTF::create("GetRewardByName", "Marker Felt", 24);
    getRewardByNameLabel->setColor(Color3B::WHITE);
    auto getRewardByNameItem  = MenuItemLabel::create(getRewardByNameLabel, CC_CALLBACK_1(TestRewardService::getRewardByName, this));
    y_pos -= button_y_Offset;
    getRewardByNameItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetTopNRewardEarners
     */
    auto getTopNRewardEarnersLabel = LabelTTF::create("GetTopNRewardEarners", "Marker Felt", 24);
    getTopNRewardEarnersLabel->setColor(Color3B::WHITE);
    auto getTopNRewardEarnersItem  = MenuItemLabel::create(getTopNRewardEarnersLabel, CC_CALLBACK_1(TestRewardService::getTopNRewardEarners, this));
    y_pos -= button_y_Offset;
    getTopNRewardEarnersItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllRewardsByUser
     */
    auto getAllRewardsByUserLabel = LabelTTF::create("GetAllRewardsByUser", "Marker Felt", 24);
    getAllRewardsByUserLabel->setColor(Color3B::WHITE);
    auto getAllRewardsByUserItem  = MenuItemLabel::create(getAllRewardsByUserLabel, CC_CALLBACK_1(TestRewardService::getAllRewardsByUser, this));
    y_pos -= button_y_Offset;
    getAllRewardsByUserItem->setPosition(Point(x_pos,y_pos));
    
    
    /**
     * GetTopNRewardEarnersByGroup
     */
    auto getTopNRewardEarnersByGroupLabel = LabelTTF::create("GetTopNRewardEarnersByGroup", "Marker Felt", 24);
    getTopNRewardEarnersByGroupLabel->setColor(Color3B::WHITE);
    auto getTopNRewardEarnersByGroupItem  = MenuItemLabel::create(getTopNRewardEarnersByGroupLabel, CC_CALLBACK_1(TestRewardService::getTopNRewardEarnersByGroup, this));
    y_pos -= button_y_Offset;
    getTopNRewardEarnersByGroupItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetUserRankingOnReward
     */
    auto getUserRankingOnRewardLabel = LabelTTF::create("GetUserRankingOnReward", "Marker Felt", 24);
    getUserRankingOnRewardLabel->setColor(Color3B::WHITE);
    auto getUserRankingOnRewardItem  = MenuItemLabel::create(getUserRankingOnRewardLabel, CC_CALLBACK_1(TestRewardService::getUserRankingOnReward, this));
    y_pos -= button_y_Offset;
    getUserRankingOnRewardItem->setPosition(Point(x_pos,y_pos));
    
  
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(backButtonItem,
                             createRewardItem,
                             getAllRewardItem,
                             getAllRewardsByPagingItem,
                             getAllRewardsCountItem,
                             earnRewardItem,
                             redeemRewardItem, NULL);

	auto menu1 = Menu::create(
                             getGameRewardPointsForUserItem,
                             getRewardByNameItem,
                             getTopNRewardEarnersItem,
                             getAllRewardsByUserItem,
                             getTopNRewardEarnersByGroupItem,
                             getUserRankingOnRewardItem, NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	menu1->setPosition(Point::ZERO);
    this->addChild(menu1, 1);
    
    
    gameName = "NinjaJump";
    userName = "Rajeev3243590";
    rewardName = "SilverBag";
    description = "SilverBag Cup";
    return true;
}


void TestRewardService::createReward(Ref *sender)
{
    RewardService *rewardService = App42API::BuildRewardService();
    rewardService->CreateReward(rewardName, description, app42callback(TestRewardService::onRewardRequestCompleted, this));
}

void TestRewardService::getAllRewards(Ref *sender)
{
    RewardService *rewardService = App42API::BuildRewardService();
    rewardService->GetAllRewards(app42callback(TestRewardService::onRewardRequestCompleted, this));
}

void TestRewardService::getAllRewardsByPaging(Ref *sender)
{
    RewardService *rewardService = App42API::BuildRewardService();

    int max =1;
    int offset = 0;
    rewardService->GetAllRewards(max, offset, app42callback(TestRewardService::onRewardRequestCompleted, this));
}

void TestRewardService::getAllRewardsCount(Ref *sender)
{
    RewardService *rewardService = App42API::BuildRewardService();
    rewardService->GetAllRewardsCount(app42callback(TestRewardService::onRewardRequestCompleted, this));
}

void TestRewardService::earnRewards(Ref *sender)
{
    double rewardPoints =200;
    RewardService *rewardService = App42API::BuildRewardService();
    rewardService->EarnRewards(gameName, userName, rewardName, rewardPoints, app42callback(TestRewardService::onRewardRequestCompleted, this));
}

void TestRewardService::redeemRewards(Ref *sender)
{
    double rewardPoints =100;

    RewardService *rewardService = App42API::BuildRewardService();
    rewardService->RedeemRewards(gameName, userName, rewardName, rewardPoints , app42callback(TestRewardService::onRewardRequestCompleted, this));
}

void TestRewardService::getGameRewardPointsForUser(Ref *sender)
{
    RewardService *rewardService = App42API::BuildRewardService();
    rewardService->GetGameRewardPointsForUser(gameName,userName , app42callback(TestRewardService::onRewardRequestCompleted, this));
}

void TestRewardService::getRewardByName(Ref *sender)
{
    RewardService *rewardService = App42API::BuildRewardService();
    rewardService->GetRewardByName(rewardName, app42callback(TestRewardService::onRewardRequestCompleted, this));
}

void TestRewardService::getTopNRewardEarners(Ref *sender)
{
    int max = 5;
    RewardService *rewardService = App42API::BuildRewardService();
    rewardService->GetTopNRewardEarners(gameName, rewardName, max, app42callback(TestRewardService::onRewardRequestCompleted, this));
}

void TestRewardService::getAllRewardsByUser(Ref *sender)
{
    RewardService *rewardService = App42API::BuildRewardService();
    rewardService->GetAllRewardsByUser(userName, rewardName, app42callback(TestRewardService::onRewardRequestCompleted, this));
}

void TestRewardService::getTopNRewardEarnersByGroup(Ref *sender)
{
    RewardService *rewardService = App42API::BuildRewardService();

    std::vector<std::string>userList;
    userList.push_back(userName);
    rewardService->GetTopNRewardEarnersByGroup(gameName, rewardName, userList, app42callback(TestRewardService::onRewardRequestCompleted, this));
}

void TestRewardService::getUserRankingOnReward(Ref *sender)
{
    RewardService *rewardService = App42API::BuildRewardService();
    rewardService->GetUserRankingOnReward(gameName, rewardName, userName, app42callback(TestRewardService::onRewardRequestCompleted, this));
}




/**
 * CallBacks
 */
void TestRewardService::onRewardRequestCompleted( void *response)
{
    App42RewardResponse *rewardResponse = (App42RewardResponse*)response;
    
    string code = StringUtils::format("Code = %d",rewardResponse->getCode());
    responseArray.push_back(code);
    
    printf("\ncode=%d",rewardResponse->getCode());
    printf("\nResponse Body=%s",rewardResponse->getBody().c_str());
    if (rewardResponse->isSuccess)
    {
        printf("\nTotalRecords=%d",rewardResponse->getTotalRecords());
        for(std::vector<App42Reward>::iterator it = rewardResponse->rewards.begin(); it != rewardResponse->rewards.end(); ++it)
        {
            printf("\nReward Name=%s",it->name.c_str());
            printf("\nGame Name=%s",it->gameName.c_str());
            printf("\nUser Name=%s",it->userName.c_str());
            printf("\nRewards Point=%lf",it->points);
            printf("\nRank=%lf",it->rank);
            printf("\nDescription=%s",it->description.c_str());
        }
    }
    else
    {
        printf("\nerrordetails:%s",rewardResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",rewardResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",rewardResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",rewardResponse->httpErrorCode);
        
        string error = StringUtils::format("Error = %s",rewardResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",rewardResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestRewardService::loadResponseScene, this));
    
}

void TestRewardService::loadResponseScene()
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


void TestRewardService::menuCloseCallback(Ref* pSender)
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