//
//  ResponseScene.cpp
//  App42Cocos2dXSample
//
//  Created by Shephertz Technologies Pvt Ltd on 10/09/14.
//
//

#include "ResponseScene.h"
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

Scene* ResponseScene::createScene()
{
    //printf("ResponseScene::loadResponse");
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ResponseScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}




// on "init" you need to initialize your instance
bool ResponseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    //printf("ResponseScene::init");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    float button_y_Offset =30;
    y_pos = origin.y+visibleSize.height-button_y_Offset;
    float x_pos = origin.x + visibleSize.width/2;
    
    /**
     * Back Button
     */
    auto backButtonItem = MenuItemImage::create(
                                                "BackButton.png",
                                                "BackButton.png",
                                                CC_CALLBACK_1(ResponseScene::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(backButtonItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Response Scene", "Marker Felt", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - 20));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    return true;
}

void ResponseScene::loadResponse(string response)
{
   // printf("ResponseScene::loadResponse");
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto label = LabelTTF::create(response, "Marker Felt", 24);
    y_pos -= 40;
    label->setAnchorPoint(Vec2(0,0));
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x+10,y_pos));
    // add the label as a child to this layer
    this->addChild(label, 1);
}

void ResponseScene::menuCloseCallback(Ref* pSender)
{
    switch (serviceId)
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
