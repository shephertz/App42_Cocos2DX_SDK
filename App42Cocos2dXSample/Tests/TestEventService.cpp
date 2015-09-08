//
//  TestEventService.cpp
//  App42Cocos2dXSample
//
//  Created by Rajeev Ranjan on 06/07/15.
//
//

#include "TestEventService.h"
#include "TestHome.h"


#define GO_HOME 116



USING_NS_CC;

Scene* TestEventService::createScene()
{
    // 'scene' is an autorelease Object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease Object
    auto layer = TestEventService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestEventService::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //geoService = App42API::BuildGeoService();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    float button_y_Offset =30;
    float y_pos = visibleSize.height-button_y_Offset;
    float x_pos = origin.x + visibleSize.width/4;
    
    
    /**
     * Track Event
     */
    auto trackEventLabel = LabelTTF::create("TrackEvent", "Marker Felt", 24);
    trackEventLabel->setColor(Color3B::WHITE);
    auto trackEventItem  = MenuItemLabel::create(trackEventLabel, CC_CALLBACK_1(TestEventService::trackEvent, this));
    trackEventItem->setPosition(Point(x_pos,y_pos));
    
    
    
    /**
     * Back Button
     */
    auto backButtonItem = MenuItemImage::create(
                                                "BackButton.png",
                                                "BackButton.png",
                                                CC_CALLBACK_1(TestEventService::menuCloseCallback, this));
    
    backButtonItem->setPosition(Point(origin.x + visibleSize.width/2 ,
                                      origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    
    
    
    /**
     * Create Menu
     */
    auto menu = Menu::create(trackEventItem,
                             NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void TestEventService::trackEvent(Ref* pSender)
{
    EventService *eventService = App42API::BuildEventService();
    App42API::setLoggedInUser("Rajeev");
    App42Object *app42Object = new App42Object();
    app42Object->setObject("Name", "Rajeev");
    eventService->TrackEvent("Cocos2dxEvent", app42Object, app42callback(TestEventService::onEventRequestCompleted, this));
}


void TestEventService::onEventRequestCompleted( void *response)
{
    App42Response *app42Response = (App42Response*)response;
    printf("\ncode=%d...=%d",app42Response->getCode(),app42Response->isSuccess);
    printf("\nResponse Body=%s",app42Response->getBody().c_str());
    
    string code = StringUtils::format("Code = %d",app42Response->getCode());
    responseArray.push_back(code);
    
    if (app42Response->isSuccess)
    {
        printf("\nTotalRecords=%d",app42Response->getTotalRecords());
    }
    else
    {
        printf("\nerrordetails:%s",app42Response->errorDetails.c_str());
        printf("\nerrorMessage:%s",app42Response->errorMessage.c_str());
        printf("\nappErrorCode:%d",app42Response->appErrorCode);
        printf("\nhttpErrorCode:%d",app42Response->httpErrorCode);
        string error = StringUtils::format("Error = %s",app42Response->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",app42Response->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestEventService::loadResponseScene, this));
}

void TestEventService::loadResponseScene()
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


void TestEventService::menuCloseCallback(Ref* pSender)
{
    MenuItem *item = (MenuItem*)pSender;
    int senderTag = item->getTag();
    switch (senderTag)
    {
        case GO_HOME:
        {
            // create a scene. it's an autorelease Object
            auto scene = TestHome::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        default:
            break;
    }
}
