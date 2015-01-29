//
//  TestHome.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 02/04/14.
//
//

#include "TestHome.h"
#include "TestUserService.h"
#include "TestPushNotificationService.h"
#include "TestStorageService.h"
#include "TestGameService.h"
#include "TestRewardService.h"
#include "TestScoreboardService.h"
#include "TestEmailService.h"
#include "TestCustomCodeService.h"
#include "TestUploadService.h"
#include "TestSocialService.h"
#include "TestAvatarService.h"
#include "TestSessionService.h"
#include "TestBuddyService.h"
#include "TestTimerService.h"

USING_NS_CC;

#define USER_SERVICE        101
#define PUSH_SERVICE        102
#define STORAGE_SERVICE     103
#define GAME_SERVICE        104
#define SCOREBOARD_SERVICE  105
#define REWARD_SERVICE      106
#define SCORE_SERVICE       107
#define EMAIL_SERVICE       108
#define CUSTOMCODE_SERVICE  109
#define UPLOAD_SERVICE      110
#define SOCIAL_SERVICE      111
#define AVATAR_SERVICE      112
#define SESSION_SERVICE     113
#define BUDDY_SERVICE       114
#define TIMER_SERVICE       115

const time_t sec_per_day = 24*60*60;


Scene* TestHome::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestHome::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


//tm getTime(int day)
//{
//    tm *start_date;
//    
//	time_t diff =0;								// start_date -> time_t type
//	time_t t = time(NULL);                      // number of days -> seconds since
//    
//    start_date = gmtime(&t);
//    //	diff = mktime(start_date);
//    //
//    
//	diff += t-2 * sec_per_day;					// current time_t
//    end_date = gmtime(&diff);
//    
//    string strStartDate = Util::getTimeStamp(start_date);
//    string strEndDate = Util::getTimeStamp(end_date);
//    
//    printf("Start Date: %s\n", strStartDate.c_str());
//    printf("End   Date: %s\n", strEndDate.c_str());
//
//}

// on "init" you need to initialize your instance
bool TestHome::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    /****************************
    
    tm *start_date;
    tm *end_date;
    
	time_t diff =0;								// start_date -> time_t type
	time_t t = time(NULL);                      // number of days -> seconds since
    
    start_date = gmtime(&t);
    tm startDate = *start_date;
    
	diff += t-2 * sec_per_day;					// current time_t
    end_date = gmtime(&diff);
    
    string strStartDate = Util::getTimeStamp(&startDate);
    string strEndDate = Util::getTimeStamp(end_date);
    
    printf("Start Date: %s\n", strStartDate.c_str());
    printf("End   Date: %s\n", strEndDate.c_str());

    
    *****************************/

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    
    float button_y_Offset =30;
    float y_pos = visibleSize.height-button_y_Offset;
    float x_pos = origin.x + visibleSize.width/2;
    
    
    /**
     * User Service Test
     */
    auto userServiceLabel = LabelTTF::create("User Service", "Marker Felt", 24);
    userServiceLabel->setColor(Color3B::WHITE);
    auto userServiceItem  = MenuItemLabel::create(userServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    userServiceItem->setTag(USER_SERVICE);
    userServiceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Storage Service Test
     */
    auto storageServiceLabel = LabelTTF::create("Storage Service", "Marker Felt", 24);
    storageServiceLabel->setColor(Color3B::WHITE);
    auto storageServiceItem  = MenuItemLabel::create(storageServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    storageServiceItem->setTag(STORAGE_SERVICE);
    y_pos -= button_y_Offset;
    storageServiceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Push Service Test
     */
    auto pushServiceLabel = LabelTTF::create("Push Service", "Marker Felt", 24);
    pushServiceLabel->setColor(Color3B::WHITE);
    auto pushServiceItem  = MenuItemLabel::create(pushServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    pushServiceItem->setTag(PUSH_SERVICE);
    y_pos -= button_y_Offset;
    pushServiceItem->setPosition(Point(x_pos,y_pos));

    /**
     * Game Service Test
     */
    auto gameServiceLabel = LabelTTF::create("Game Service", "Marker Felt", 24);
    gameServiceLabel->setColor(Color3B::WHITE);
    auto gameServiceItem  = MenuItemLabel::create(gameServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    gameServiceItem->setTag(GAME_SERVICE);
    y_pos -= button_y_Offset;
    gameServiceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Scoreboard Service Test
     */
    auto scoreboardServiceLabel = LabelTTF::create("Scoreboard Service", "Marker Felt", 24);
    scoreboardServiceLabel->setColor(Color3B::WHITE);
    auto scoreboardServiceItem  = MenuItemLabel::create(scoreboardServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    scoreboardServiceItem->setTag(SCOREBOARD_SERVICE);
    y_pos -= button_y_Offset;
    scoreboardServiceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Reward Service Test
     */
    auto rewardServiceLabel = LabelTTF::create("Reward Service", "Marker Felt", 24);
    rewardServiceLabel->setColor(Color3B::WHITE);
    auto rewardServiceItem  = MenuItemLabel::create(rewardServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    rewardServiceItem->setTag(REWARD_SERVICE);
    y_pos -= button_y_Offset;
    rewardServiceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Email Service Test
     */
    auto emailServiceLabel = LabelTTF::create("Email Service", "Marker Felt", 24);
    emailServiceLabel->setColor(Color3B::WHITE);
    auto emailServiceItem  = MenuItemLabel::create(emailServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    emailServiceItem->setTag(EMAIL_SERVICE);
    y_pos -= button_y_Offset;
    emailServiceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * CustomCode Service Test
     */
    auto customCodeServiceLabel = LabelTTF::create("CustomCode Service", "Marker Felt", 24);
    customCodeServiceLabel->setColor(Color3B::WHITE);
    auto customCodeServiceItem  = MenuItemLabel::create(customCodeServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    customCodeServiceItem->setTag(CUSTOMCODE_SERVICE);
    y_pos -= button_y_Offset;
    customCodeServiceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Upload Service Test
     */
    auto uploadServiceLabel = LabelTTF::create("Upload Service", "Marker Felt", 24);
    uploadServiceLabel->setColor(Color3B::WHITE);
    auto uploadItem  = MenuItemLabel::create(uploadServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    uploadItem->setTag(UPLOAD_SERVICE);
    y_pos -= button_y_Offset;
    uploadItem->setPosition(Point(x_pos,y_pos));

    /**
     * Social Service Test
     */
    auto socialServiceLabel = LabelTTF::create("Social Service", "Marker Felt", 24);
    socialServiceLabel->setColor(Color3B::WHITE);
    auto socialItem  = MenuItemLabel::create(socialServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    socialItem->setTag(SOCIAL_SERVICE);
    y_pos -= button_y_Offset;
    socialItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Avatar Service Test
     */
    auto avatarServiceLabel = LabelTTF::create("Avatar Service", "Marker Felt", 24);
    avatarServiceLabel->setColor(Color3B::WHITE);
    auto avatarItem  = MenuItemLabel::create(avatarServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    avatarItem->setTag(AVATAR_SERVICE);
    y_pos -= button_y_Offset;
    avatarItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Session Service Test
     */
    auto sessionServiceLabel = LabelTTF::create("Session Service", "Marker Felt", 24);
    sessionServiceLabel->setColor(Color3B::WHITE);
    auto sessionServiceItem  = MenuItemLabel::create(sessionServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    sessionServiceItem->setTag(SESSION_SERVICE);
    y_pos -= button_y_Offset;
    sessionServiceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Buddy Service Test
     */
    auto buddyServiceLabel = LabelTTF::create("Buddy Service", "Marker Felt", 24);
    buddyServiceLabel->setColor(Color3B::WHITE);
    auto buddyServiceItem  = MenuItemLabel::create(buddyServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    buddyServiceItem->setTag(BUDDY_SERVICE);
    y_pos -= button_y_Offset;
    buddyServiceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Timer Service Test
     */
    auto timerServiceLabel = LabelTTF::create("Timer Service", "Marker Felt", 24);
    timerServiceLabel->setColor(Color3B::WHITE);
    auto timerServiceItem  = MenuItemLabel::create(timerServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    timerServiceItem->setTag(TIMER_SERVICE);
    y_pos -= button_y_Offset;
    timerServiceItem->setPosition(Point(x_pos,y_pos));

    // create menu, it's an autorelease object
    auto menu = Menu::create(userServiceItem,
                             storageServiceItem,
                             pushServiceItem,
                             gameServiceItem,
                             scoreboardServiceItem,
                             rewardServiceItem,
                             emailServiceItem,
                             customCodeServiceItem,NULL);

	auto menu1 = Menu::create(
                             uploadItem,
                             socialItem,
                             avatarItem,
                             sessionServiceItem,
                             buddyServiceItem,
                             timerServiceItem,NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	menu1->setPosition(Point::ZERO);
    this->addChild(menu1, 1);
    
    
    App42API::Initialize(API_KEY, SECRET_KEY);
    App42API::setIsTraceEnabled(true);
    return true;
}


void TestHome::menuCloseCallback(Ref* pSender)
{
    MenuItem *item = (MenuItem*)pSender;
    int senderTag = item->getTag();
    switch (senderTag)
    {
        case USER_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestUserService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case PUSH_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestPushNotificationService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case STORAGE_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestStorageService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case GAME_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestGameService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case SCOREBOARD_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestScoreboardService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case REWARD_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestRewardService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case SCORE_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestScoreboardService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case EMAIL_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestEmailService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case CUSTOMCODE_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestCustomCodeService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case UPLOAD_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestUploadService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case SOCIAL_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestSocialService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case AVATAR_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestAvatarService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case SESSION_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestSessionService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case BUDDY_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestBuddyService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case TIMER_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestTimerService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        default:
            break;
    }
}



