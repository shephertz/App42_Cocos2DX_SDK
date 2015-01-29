//
//  TestSessionService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 16/07/14.
//
//

#include "TestSessionService.h"
#include "TestHome.h"


#define GO_HOME 113



USING_NS_CC;

Scene* TestSessionService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestSessionService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestSessionService::init()
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
                                                CC_CALLBACK_1(TestSessionService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * GetSession
     */
    auto getSessionLabel = LabelTTF::create("GetSession", "Marker Felt", 24);
    getSessionLabel->setColor(Color3B::WHITE);
    auto getSessionItem  = MenuItemLabel::create(getSessionLabel, CC_CALLBACK_1(TestSessionService::getSession, this));
    getSessionItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetSessionWithCreateFlag
     */
    auto getSessionWithCreateFlagLabel = LabelTTF::create("GetSessionWithCreateFlag", "Marker Felt", 24);
    getSessionWithCreateFlagLabel->setColor(Color3B::WHITE);
    auto getSessionWithCreateFlagItem  = MenuItemLabel::create(getSessionWithCreateFlagLabel, CC_CALLBACK_1(TestSessionService::getSessionWithCreateFlag, this));
    y_pos -= button_y_Offset;
    getSessionWithCreateFlagItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Invalidate
     */
    auto invalidateLabel = LabelTTF::create("Invalidate", "Marker Felt", 24);
    invalidateLabel->setColor(Color3B::WHITE);
    auto invalidateItem  = MenuItemLabel::create(invalidateLabel, CC_CALLBACK_1(TestSessionService::invalidate, this));
    y_pos -= button_y_Offset;
    invalidateItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * SetAttribute
     */
    auto setAttributeLabel = LabelTTF::create("SetAttribute", "Marker Felt", 24);
    setAttributeLabel->setColor(Color3B::WHITE);
    auto setAttributeItem  = MenuItemLabel::create(setAttributeLabel, CC_CALLBACK_1(TestSessionService::setAttribute, this));
    y_pos -= button_y_Offset;
    setAttributeItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAttribute
     */
    auto getAttributeLabel = LabelTTF::create("GetAttribute", "Marker Felt", 24);
    getAttributeLabel->setColor(Color3B::WHITE);
    auto getAttributeItem  = MenuItemLabel::create(getAttributeLabel, CC_CALLBACK_1(TestSessionService::getAttribute, this));
    y_pos -= button_y_Offset;
    getAttributeItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllAttribute
     */
    auto getAllAttributeLabel = LabelTTF::create("GetAllAttribute", "Marker Felt", 24);
    getAllAttributeLabel->setColor(Color3B::WHITE);
    auto getAllAttributeItem  = MenuItemLabel::create(getAllAttributeLabel, CC_CALLBACK_1(TestSessionService::getAllAttributes, this));
    y_pos -= button_y_Offset;
    getAllAttributeItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * RemoveAttribute
     */
    auto removeAttributeLabel = LabelTTF::create("RemoveAttribute", "Marker Felt", 24);
    removeAttributeLabel->setColor(Color3B::WHITE);
    auto removeAttributeItem  = MenuItemLabel::create(removeAttributeLabel, CC_CALLBACK_1(TestSessionService::removeAttribute, this));
    y_pos -= button_y_Offset;
    removeAttributeItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * RemoveAllAttribute
     */
    auto removeAllAttributeLabel = LabelTTF::create("RemoveAllAttribute", "Marker Felt", 24);
    removeAllAttributeLabel->setColor(Color3B::WHITE);
    auto removeAllAttributeItem  = MenuItemLabel::create(removeAllAttributeLabel, CC_CALLBACK_1(TestSessionService::removeAllAttributes, this));
    y_pos -= button_y_Offset;
    removeAllAttributeItem->setPosition(Point(x_pos,y_pos));

  	
   
    // create menu, it's an autorelease object
    auto menu = Menu::create(backButtonItem,
                             getSessionItem,
                             getSessionWithCreateFlagItem,
                             invalidateItem,
                             setAttributeItem,
                             getAttributeItem,
                             getAllAttributeItem,
                             removeAttributeItem,
                             removeAllAttributeItem,
                             NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    
    attributeName = "environment3";
    attributeValue = "production3";
    sessionId = "7e4595c9-451e-44cf-bf7a-e071789aa16f";
    return true;
}



/**
 * API Methods
 */

void TestSessionService::getSession(Ref* sender)
{
    SessionService *sessionService = App42API::BuildSessionService();
    const char* userName = "Nick19811";
    sessionService->GetSession(userName, app42callback(TestSessionService::onSessionServiceRequestCompleted, this));
}

void TestSessionService::getSessionWithCreateFlag(Ref* sender)
{
    static bool isCreate = true;

    SessionService *sessionService = App42API::BuildSessionService();
    const char* userName = "Nick198111";
    isCreate = !isCreate;
    sessionService->GetSession(userName, isCreate, app42callback(TestSessionService::onSessionServiceRequestCompleted, this));
}

void TestSessionService::invalidate(Ref* sender)
{
    SessionService *sessionService = App42API::BuildSessionService();
    sessionService->Invalidate(sessionId.c_str(), app42callback(TestSessionService::onSessionServiceRequestCompleted, this));

}
void TestSessionService::setAttribute(Ref* sender)
{
    SessionService *sessionService = App42API::BuildSessionService();
    sessionService->SetAttribute(sessionId.c_str(), attributeName, attributeValue, app42callback(TestSessionService::onSessionServiceRequestCompleted, this));
}
void TestSessionService::getAttribute(Ref* sender)
{
    SessionService *sessionService = App42API::BuildSessionService();
    sessionService->GetAttribute(sessionId.c_str(), attributeName, app42callback(TestSessionService::onSessionServiceRequestCompleted, this));
}

void TestSessionService::getAllAttributes(Ref* sender)
{
    SessionService *sessionService = App42API::BuildSessionService();
    sessionService->GetAllAttributes(sessionId.c_str(), app42callback(TestSessionService::onSessionServiceRequestCompleted, this));
}

void TestSessionService::removeAttribute(Ref* sender)
{
    SessionService *sessionService = App42API::BuildSessionService();
    sessionService->RemoveAttribute(sessionId.c_str(), attributeName, app42callback(TestSessionService::onSessionServiceRequestCompleted, this));
}

void TestSessionService::removeAllAttributes(Ref* sender)
{
    SessionService *sessionService = App42API::BuildSessionService();
    sessionService->RemoveAllAttributes(sessionId.c_str(), app42callback(TestSessionService::onSessionServiceRequestCompleted, this));
}

/**
 * Callback Methods
 */
void TestSessionService::onSessionServiceRequestCompleted( void *response)
{
    App42SessionResponse *app42SessionResponse = (App42SessionResponse*)response;
    
    string code = StringUtils::format("Code = %d",app42SessionResponse->getCode());
    responseArray.push_back(code);
    
    if(app42SessionResponse->isSuccess)
    {
        printf("\ncode=%d",app42SessionResponse->getCode());
        printf("\nisSuccess=%d",app42SessionResponse->isSuccess);
        printf("\nResponse Body=%s",app42SessionResponse->getBody().c_str());
        printf("\nUserName=%s",app42SessionResponse->app42Session.userName.c_str());
        printf("\nSessionId=%s",app42SessionResponse->app42Session.sessionId.c_str());
        printf("\nCreatedOn=%s",app42SessionResponse->app42Session.createdOn.c_str());
        printf("\nInvalidatedOn=%s",app42SessionResponse->app42Session.invalidatedOn.c_str());
        //sessionId = app42SessionResponse->app42Session.sessionId;
        
        vector<App42Attribute> attributesArray = app42SessionResponse->app42Session.attributeArray;
        for(std::vector<App42Attribute>::iterator attribute = attributesArray.begin(); attribute != attributesArray.end(); ++attribute)
        {
            printf("\n Name=%s",attribute->name.c_str());
            printf("\n Value=%s\n",attribute->value.c_str());
        }

    }
    else
    {
        printf("\nerrordetails:%s",app42SessionResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",app42SessionResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",app42SessionResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",app42SessionResponse->httpErrorCode);
        
        string error = StringUtils::format("Error = %s",app42SessionResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",app42SessionResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestSessionService::loadResponseScene, this));
    
}

void TestSessionService::loadResponseScene()
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

void TestSessionService::menuCloseCallback(Ref* pSender)
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

