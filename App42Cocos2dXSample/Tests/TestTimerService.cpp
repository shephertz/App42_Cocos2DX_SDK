//
//  TestTimerService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev on 19/08/14.
//
//

#include "TestTimerService.h"
#define GO_HOME 115



USING_NS_CC;


Scene* TestTimerService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestTimerService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestTimerService::init()
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
                                                CC_CALLBACK_1(TestTimerService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * CreateOrUpdateTimer
     */
    auto createOrUpdateTimerLabel = LabelTTF::create("CreateOrUpdateTimer", "Marker Felt", 24);
    createOrUpdateTimerLabel->setColor(Color3B::WHITE);
    auto createOrUpdateTimerItem  = MenuItemLabel::create(createOrUpdateTimerLabel, CC_CALLBACK_1(TestTimerService::createOrUpdateTimer, this));
    createOrUpdateTimerItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * StartTimer
     */
    auto startTimerLabel = LabelTTF::create("StartTimer", "Marker Felt", 24);
    startTimerLabel->setColor(Color3B::WHITE);
    auto startTimerItem  = MenuItemLabel::create(startTimerLabel, CC_CALLBACK_1(TestTimerService::startTimer, this));
    y_pos -= button_y_Offset;
    startTimerItem->setPosition(Point(x_pos,y_pos));

 	

    // create menu, it's an autorelease object
    auto menu = Menu::create(backButtonItem,
                             createOrUpdateTimerItem,
                             startTimerItem,
                             NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    
    timerName = "app42Timer";
    userName  = "Rajeev1981";
    
    return true;
}

/**
 * API Test Methods
 */

void TestTimerService::createOrUpdateTimer(Ref *sender)
{
    TimerService *timerService = App42API::BuildTimerService();
    
    timerService->CreateOrUpdateTimer(timerName,5,app42callback(TestTimerService::onTimerServiceRequestCompleted, this));
}

void TestTimerService::startTimer(Ref *sender)
{
    TimerService *timerService = App42API::BuildTimerService();
    
    timerService->StartTimer(timerName,userName,app42callback(TestTimerService::onTimerServiceRequestCompleted, this));
}



/**
 * Callback Methods
 */
void TestTimerService::onTimerServiceRequestCompleted( void *response)
{
    App42TimerResponse *app42TimerResponse = (App42TimerResponse*)response;
    string code = StringUtils::format("Code = %d",app42TimerResponse->getCode());
    responseArray.push_back(code);
    if(app42TimerResponse->isSuccess)
    {
        printf("\ncode=%d",app42TimerResponse->getCode());
        printf("\nisSuccess=%d",app42TimerResponse->isSuccess);
        printf("\nResponse Body=%s",app42TimerResponse->getBody().c_str());
        
        printf("\n TimerName =%s",app42TimerResponse->app42Timer.name.c_str());
        printf("\n userName =%s",app42TimerResponse->app42Timer.userName.c_str());
        printf("\n currentTime =%s",app42TimerResponse->app42Timer.currentTime.c_str());
        printf("\n startTime =%s",app42TimerResponse->app42Timer.startTime.c_str());
        printf("\n endTime =%s",app42TimerResponse->app42Timer.endTime.c_str());
        printf("\n timeInSeconds=%ld",app42TimerResponse->app42Timer.timeInSeconds);
        printf("\n isTimerActive=%d",app42TimerResponse->app42Timer.isTimerActive);


    }
    else
    {
        printf("\nerrordetails:%s",app42TimerResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",app42TimerResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",app42TimerResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",app42TimerResponse->httpErrorCode);
        string error = StringUtils::format("Error = %s",app42TimerResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",app42TimerResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);

    }
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestTimerService::loadResponseScene, this));
    
}

void TestTimerService::loadResponseScene()
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


void TestTimerService::menuCloseCallback(Ref* pSender)
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
