//
//  TestPushNotificationService.cpp
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#include "TestPushNotificationService.h"
#include "TestHome.h"
#include "AppDelegate.h"

#define GO_HOME 102

USING_NS_CC;

Scene* TestPushNotificationService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestPushNotificationService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestPushNotificationService::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    channelName = "App42TestPushChannelReturnsss";
    description = "Testing channel";
    userName = "MyiPhone5S";
    deviceToken =  "204b3b21148a2b67b769c331a10c81f789213330d641133848b5e1bb6a4e3b0a";//
    message = "Hello from cocos2d-X!";
    
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
                                                CC_CALLBACK_1(TestPushNotificationService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * Register Device Token
     */
    auto registerDeviceTokenLabel = LabelTTF::create("RegisterDevice", "Marker Felt", 24);
    registerDeviceTokenLabel->setColor(Color3B::WHITE);
    auto registerDeviceTokenItem  = MenuItemLabel::create(registerDeviceTokenLabel, CC_CALLBACK_1(TestPushNotificationService::registerDeviceToken, this));
    //y_pos -= button_y_Offset;
    registerDeviceTokenItem->setPosition(Point(x_pos,y_pos));

    
    /**
     * Create Channel
     */
    auto createChannelLabel = LabelTTF::create("CreateChannel", "Marker Felt", 24);
    createChannelLabel->setColor(Color3B::WHITE);
    auto createChannelItem  = MenuItemLabel::create(createChannelLabel, CC_CALLBACK_1(TestPushNotificationService::createChannel, this));
    y_pos -= button_y_Offset;
    createChannelItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  Subscribe To Channel
     */
    auto subscribeToChannelLabel = LabelTTF::create("SubscribeToChannel", "Marker Felt", 24);
    subscribeToChannelLabel->setColor(Color3B::WHITE);
    auto subscribeToChannelItem  = MenuItemLabel::create(subscribeToChannelLabel, CC_CALLBACK_1(TestPushNotificationService::subscribeToChannel, this));
    y_pos -= button_y_Offset;
    subscribeToChannelItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  Subscribe Device To Channel
     */
    auto subscribeDeviceToChannelLabel = LabelTTF::create("SubscribeDeviceToChannel", "Marker Felt", 24);
    subscribeDeviceToChannelLabel->setColor(Color3B::WHITE);
    auto subscribeDeviceToChannelItem  = MenuItemLabel::create(subscribeDeviceToChannelLabel, CC_CALLBACK_1(TestPushNotificationService::subscribeDeviceToChannel, this));
    y_pos -= button_y_Offset;
    subscribeDeviceToChannelItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  Unsubscribe To Channel
     */
    auto unsubscribeToChannelLabel = LabelTTF::create("UnsubscribeToChannel", "Marker Felt", 24);
    unsubscribeToChannelLabel->setColor(Color3B::WHITE);
    auto unsubscribeToChannelItem  = MenuItemLabel::create(unsubscribeToChannelLabel, CC_CALLBACK_1(TestPushNotificationService::unsubscribeToChannel, this));
    y_pos -= button_y_Offset;
    unsubscribeToChannelItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  Unsubscribe Device To Channel
     */
    auto unsubscribeDeviceToChannelLabel = LabelTTF::create("UnsubscribeDeviceToChannel", "Marker Felt", 24);
    unsubscribeDeviceToChannelLabel->setColor(Color3B::WHITE);
    auto unsubscribeDeviceToChannelItem  = MenuItemLabel::create(unsubscribeDeviceToChannelLabel, CC_CALLBACK_1(TestPushNotificationService::unsubscribeDeviceToChannel, this));
    y_pos -= button_y_Offset;
    unsubscribeDeviceToChannelItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  Delete DeviceToken for user
     */
    auto deleteDeviceTokenLabel = LabelTTF::create("DeleteDeviceToken", "Marker Felt", 24);
    deleteDeviceTokenLabel->setColor(Color3B::WHITE);
    auto deleteDeviceTokenItem  = MenuItemLabel::create(deleteDeviceTokenLabel, CC_CALLBACK_1(TestPushNotificationService::deleteDevice, this));
    y_pos -= button_y_Offset;
    deleteDeviceTokenItem->setPosition(Point(x_pos,y_pos));

    /**
     *  Delete All Devices for user
     */
    auto deleteAllDevicesLabel = LabelTTF::create("DeleteAllDevices", "Marker Felt", 24);
    deleteAllDevicesLabel->setColor(Color3B::WHITE);
    auto deleteAllDevicesItem  = MenuItemLabel::create(deleteAllDevicesLabel, CC_CALLBACK_1(TestPushNotificationService::deleteAllDevices, this));
    y_pos -= button_y_Offset;
    deleteAllDevicesItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  Unsubscribe device
     */
    auto unsubscribeDeviceLabel = LabelTTF::create("UnsubscribeDevice", "Marker Felt", 24);
    unsubscribeDeviceLabel->setColor(Color3B::WHITE);
    auto unsubscribeDeviceItem  = MenuItemLabel::create(unsubscribeDeviceLabel, CC_CALLBACK_1(TestPushNotificationService::unsubscribrDevice, this));
    y_pos -= button_y_Offset;
    unsubscribeDeviceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  Resubscribe device
     */
    auto resubscribeDeviceLabel = LabelTTF::create("ResubscribeDevice", "Marker Felt", 24);
    resubscribeDeviceLabel->setColor(Color3B::WHITE);
    auto resubscribeDeviceItem  = MenuItemLabel::create(resubscribeDeviceLabel, CC_CALLBACK_1(TestPushNotificationService::resubscribeDevice, this));
    y_pos -= button_y_Offset;
    resubscribeDeviceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  SendPushMessageToUser
     */
    auto sendPushToUserLabel = LabelTTF::create("SendPushMessageToUser", "Marker Felt", 24);
    sendPushToUserLabel->setColor(Color3B::WHITE);
    auto sendPushToUserItem  = MenuItemLabel::create(sendPushToUserLabel, CC_CALLBACK_1(TestPushNotificationService::sendPushMessageToUser, this));
    y_pos -= button_y_Offset;
    sendPushToUserItem->setPosition(Point(x_pos,y_pos));
    /**
     *  SendPushJsonToUser
     */
    auto sendPushJsonToUserLabel = LabelTTF::create("SendPushJsonToUser", "Marker Felt", 24);
    sendPushJsonToUserLabel->setColor(Color3B::WHITE);
    auto sendPushJsonToUserItem  = MenuItemLabel::create(sendPushJsonToUserLabel, CC_CALLBACK_1(TestPushNotificationService::sendPushJsonToUser, this));
    y_pos -= button_y_Offset;
    sendPushJsonToUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  SendPushToAll
     */
    auto sendPushToAllLabel = LabelTTF::create("SendPushToAll", "Marker Felt", 24);
    sendPushToAllLabel->setColor(Color3B::WHITE);
    auto sendPushToAllItem  = MenuItemLabel::create(sendPushToAllLabel, CC_CALLBACK_1(TestPushNotificationService::sendPushMessageToAll, this));
    y_pos -= button_y_Offset;
    sendPushToAllItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  SendPushToAllByType
     */
    auto sendPushToAllByTypeLabel = LabelTTF::create("SendPushToAllByType", "Marker Felt", 24);
    sendPushToAllByTypeLabel->setColor(Color3B::WHITE);
    auto sendPushToAllByTypeItem  = MenuItemLabel::create(sendPushToAllByTypeLabel, CC_CALLBACK_1(TestPushNotificationService::sendPushMessageToAllByType, this));
    y_pos -= button_y_Offset;
    sendPushToAllByTypeItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  SendPushToGroup
     */
    auto sendPushToGroupLabel = LabelTTF::create("SendPushToGroup", "Marker Felt", 24);
    sendPushToGroupLabel->setColor(Color3B::WHITE);
    auto sendPushToGroupItem  = MenuItemLabel::create(sendPushToGroupLabel, CC_CALLBACK_1(TestPushNotificationService::sendPushMessageToGroup, this));
    y_pos -= button_y_Offset;
    sendPushToGroupItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  SendPushToTargetUsers
     */
    auto sendPushToTargetUsersLabel = LabelTTF::create("SendPushToTargetUsers", "Marker Felt", 24);
    sendPushToTargetUsersLabel->setColor(Color3B::WHITE);
    auto sendPushToTargetUsersItem  = MenuItemLabel::create(sendPushToTargetUsersLabel, CC_CALLBACK_1(TestPushNotificationService::sendPushMessageToTargetUsers, this));
    y_pos -= button_y_Offset;
    sendPushToTargetUsersItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  ScheduleMessageToUser
     */
    auto scheduleMessageToUserLabel = LabelTTF::create("ScheduleMessageToUser", "Marker Felt", 24);
    scheduleMessageToUserLabel->setColor(Color3B::WHITE);
    auto scheduleMessageToUserItem  = MenuItemLabel::create(scheduleMessageToUserLabel, CC_CALLBACK_1(TestPushNotificationService::scheduleMessageToUser, this));
    y_pos -= button_y_Offset;
    scheduleMessageToUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  SendPushMeassageToChannel
     */
    auto sendPushMeassageToChannelLabel = LabelTTF::create("SendPushMeassageToChannel", "Marker Felt", 24);
    sendPushMeassageToChannelLabel->setColor(Color3B::WHITE);
    auto sendPushMeassageToChannelItem  = MenuItemLabel::create(sendPushMeassageToChannelLabel, CC_CALLBACK_1(TestPushNotificationService::sendPushMeassageToChannel, this));
    y_pos -= button_y_Offset;
    sendPushMeassageToChannelItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  SendPushMeassageToDevice
     */
    auto sendPushMeassageToDeviceLabel = LabelTTF::create("SendPushMeassageToDevice", "Marker Felt", 24);
    sendPushMeassageToDeviceLabel->setColor(Color3B::WHITE);
    auto sendPushMeassageToDeviceItem  = MenuItemLabel::create(sendPushMeassageToDeviceLabel, CC_CALLBACK_1(TestPushNotificationService::sendMessageToDevice, this));
    y_pos -= button_y_Offset;
    sendPushMeassageToDeviceItem->setPosition(Point(x_pos,y_pos));

 	
    /**
     * Create menu, it's an autorelease object
     */
    auto menu = Menu::create(backButtonItem,
                             registerDeviceTokenItem,
                             createChannelItem,
                             subscribeToChannelItem,
                             subscribeDeviceToChannelItem,
                             unsubscribeToChannelItem,
                             unsubscribeDeviceToChannelItem, NULL);

	auto menu1 = Menu::create(
                             deleteDeviceTokenItem,
                             deleteAllDevicesItem,
                             unsubscribeDeviceItem,
                             resubscribeDeviceItem,
                             sendPushToUserItem,
                             sendPushJsonToUserItem,
                             sendPushToAllItem, NULL);

	auto menu2 = Menu::create(
                             sendPushToAllByTypeItem,
                             sendPushToGroupItem,
                             sendPushToTargetUsersItem,
                             scheduleMessageToUserItem,
                             sendPushMeassageToChannelItem,
                             sendPushMeassageToDeviceItem, NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	menu1->setPosition(Point::ZERO);
    this->addChild(menu1, 1);

	menu2->setPosition(Point::ZERO);
    this->addChild(menu2, 1);

    return true;
}



void TestPushNotificationService::registerDeviceToken(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    printf("DeviceToken=%s",deviceToken.c_str());
    pushService->RegisterDeviceToken(deviceToken.c_str(), userName.c_str(), APP42_IOS, app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}

void TestPushNotificationService::createChannel(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->CreateChannel(channelName.c_str(),description.c_str(), app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}

void TestPushNotificationService::subscribeToChannel(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->SubscribeToChannel(channelName.c_str(),userName.c_str(), app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}

void TestPushNotificationService::unsubscribeToChannel(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->UnsubscribeFromChannel(channelName.c_str(),userName.c_str(), app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}

void TestPushNotificationService::deleteDevice(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->DeleteDeviceToken(deviceToken.c_str(),userName.c_str(), app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}

void TestPushNotificationService::deleteAllDevices(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->DeleteAllDevices(userName.c_str(), app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}

void TestPushNotificationService::unsubscribrDevice(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->UnsubscribeDevice(deviceToken.c_str(), userName.c_str(),app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}

void TestPushNotificationService::resubscribeDevice(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    pushService->ResubscribeDevice(deviceToken.c_str(), userName.c_str(),app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}

void TestPushNotificationService::sendPushMessageToUser(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    map<string,string> otherMetaHeaders;
    otherMetaHeaders["dataEncoding"] = "true";
    pushService->setOtherMetaHeaders(otherMetaHeaders);
    pushService->SendPushMessageToUser(userName.c_str(),message.c_str(),app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}

void TestPushNotificationService::sendPushJsonToUser(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    std::map<string,string> messageMap;
    messageMap["alert"]= "Hello! How are you?";
    messageMap["badge"]= "2";
    messageMap["sound"]= "Default";
    pushService->SendPushMessageToUser(userName.c_str(), messageMap,app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}

void TestPushNotificationService::sendPushMessageToAll(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->SendPushMessageToAll(message.c_str(),app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}

void TestPushNotificationService::sendPushMessageToAllByType(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->SendPushMessageToAllByType(message.c_str(),APP42_IOS,app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}

void TestPushNotificationService::subscribeDeviceToChannel(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->SubscribeToChannel(channelName.c_str(),userName.c_str(),deviceToken.c_str(), APP42_IOS, app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}
void TestPushNotificationService::unsubscribeDeviceToChannel(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->UnsubscribeDeviceToChannel(channelName.c_str(),userName.c_str(),deviceToken.c_str(),app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}
void TestPushNotificationService::sendPushMessageToGroup(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    std::vector<std::string>group;
    group.push_back("Nick");
    group.push_back("John");
    pushService->SendPushMessageToGroup(group, message.c_str(), app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}

void TestPushNotificationService::sendPushMessageToTargetUsers(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    const char* dbName = "jsonDocument2";
    const char* collectionName = "TestingScore";
    const char* key = "name";
    const char* value = "Rajeev Ranjan";
    Query *query = QueryBuilder::BuildQuery(key, value, APP42_OP_EQUALS);
    
    pushService->SendPushToTargetUsers(message.c_str(), dbName, collectionName, query, app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}


void TestPushNotificationService::scheduleMessageToUser(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    tm *expiryDate;
    
	time_t t = time(NULL);
    
    expiryDate = gmtime(&t);
    
    pushService->ScheduleMessageToUser(userName.c_str(), message.c_str(), expiryDate, app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}


void TestPushNotificationService::sendPushMeassageToChannel(Ref *sender)
{
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    pushService->SendPushMessageToChannel(channelName.c_str(), message.c_str(), app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}

void TestPushNotificationService::sendMessageToDevice(Ref *sender)
{
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    pushService->SendPushMessageToDevice(deviceToken.c_str(), userName.c_str(), message.c_str(), app42callback(TestPushNotificationService::onPushRequestCompleted, this));
}


/**
 * Callbacks
 */
void TestPushNotificationService::onPushRequestCompleted( void *response)
{
    App42PushNotificationResponse *pushResponse = (App42PushNotificationResponse*)response;
    printf("\ncode=%d",pushResponse->getCode());
    printf("\nResponse Body=%s",pushResponse->getBody().c_str());
    
    string code = StringUtils::format("Code = %d",pushResponse->getCode());
    responseArray.push_back(code);
    if (pushResponse->isSuccess)
    {
        for(std::vector<App42PushNotification>::iterator it = pushResponse->notifications.begin(); it != pushResponse->notifications.end(); ++it)
        {
            printf("\n UserName=%s",it->userName.c_str());
            printf("\n Message=%s\n",it->message.c_str());
            printf("\n Type=%s\n",it->type.c_str());
            printf("\n DeviceToken=%s\n",it->deviceToken.c_str());
            printf("\n Expiry=%s\n",it->expiry.c_str());

            for(std::vector<App42Channel>::iterator channel = it->channelArray.begin(); channel != it->channelArray.end(); ++channel)
            {
                printf("\n Channel Name=%s",channel->channelName.c_str());
                printf("\n Description=%s\n",channel->description.c_str());
            }
        }
    }
    else
    {
        printf("\nerrordetails:%s",pushResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",pushResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",pushResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",pushResponse->httpErrorCode);
        string error = StringUtils::format("Error = %s",pushResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",pushResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestPushNotificationService::loadResponseScene, this));
    
}

void TestPushNotificationService::loadResponseScene()
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


void TestPushNotificationService::menuCloseCallback(Ref* pSender)
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