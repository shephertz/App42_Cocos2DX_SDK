//
//  TestBuddyService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 21/07/14.
//
//

#include "TestBuddyService.h"
#define GO_HOME 114




USING_NS_CC;


Scene* TestBuddyService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestBuddyService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestBuddyService::init()
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
    float x_pos = origin.x + visibleSize.width/4;
    
    /**
     * Back Button
     */
    auto backButtonItem = MenuItemImage::create(
                                                "BackButton.png",
                                                "BackButton.png",
                                                CC_CALLBACK_1(TestBuddyService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * SendFriendRequest
     */
    auto sendFrndRequestLabel = LabelTTF::create("SendFriendRequest", "Marker Felt", 24);
    sendFrndRequestLabel->setColor(Color3B::WHITE);
    auto sendFrndRequestItem  = MenuItemLabel::create(sendFrndRequestLabel, CC_CALLBACK_1(TestBuddyService::sendFrndRequest, this));
    sendFrndRequestItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetFriendRequest
     */
    auto getFriendRequestLabel = LabelTTF::create("GetFriendRequest", "Marker Felt", 24);
    getFriendRequestLabel->setColor(Color3B::WHITE);
    auto getFriendRequestItem  = MenuItemLabel::create(getFriendRequestLabel, CC_CALLBACK_1(TestBuddyService::getFrndRequest, this));
    y_pos -= button_y_Offset;
    getFriendRequestItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * AcceptFriendRequest
     */
    auto acceptFriendRequestLabel = LabelTTF::create("AcceptFriendRequest", "Marker Felt", 24);
    acceptFriendRequestLabel->setColor(Color3B::WHITE);
    auto acceptFriendRequestItem  = MenuItemLabel::create(acceptFriendRequestLabel, CC_CALLBACK_1(TestBuddyService::acceptFriendRequest, this));
    y_pos -= button_y_Offset;
    acceptFriendRequestItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * RejectFriendRequest
     */
    auto rejectFriendRequestLabel = LabelTTF::create("RejectFriendRequest", "Marker Felt", 24);
    rejectFriendRequestLabel->setColor(Color3B::WHITE);
    auto rejectFriendRequestItem  = MenuItemLabel::create(rejectFriendRequestLabel, CC_CALLBACK_1(TestBuddyService::rejectFriendRequest, this));
    y_pos -= button_y_Offset;
    rejectFriendRequestItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllFriends
     */
    auto getAllFriendsLabel = LabelTTF::create("GetAllFriends", "Marker Felt", 24);
    getAllFriendsLabel->setColor(Color3B::WHITE);
    auto getAllFriendsItem  = MenuItemLabel::create(getAllFriendsLabel, CC_CALLBACK_1(TestBuddyService::getAllFriends, this));
    y_pos -= button_y_Offset;
    getAllFriendsItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * CreateGroup
     */
    auto createGroupLabel = LabelTTF::create("CreateGroup", "Marker Felt", 24);
    createGroupLabel->setColor(Color3B::WHITE);
    auto createGroupItem  = MenuItemLabel::create(createGroupLabel, CC_CALLBACK_1(TestBuddyService::createGroup, this));
    y_pos -= button_y_Offset;
    createGroupItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * AddFriendsToGroup
     */
    auto addFriendsToGroupLabel = LabelTTF::create("AddFriendsToGroup", "Marker Felt", 24);
    addFriendsToGroupLabel->setColor(Color3B::WHITE);
    auto addFriendsToGroupItem  = MenuItemLabel::create(addFriendsToGroupLabel, CC_CALLBACK_1(TestBuddyService::addFriendsToGroup, this));
    y_pos -= button_y_Offset;
    addFriendsToGroupItem->setPosition(Point(x_pos,y_pos));

    /**
     * GetAllGroup
     */
    auto getAllGroupLabel = LabelTTF::create("GetAllGroup", "Marker Felt", 24);
    getAllGroupLabel->setColor(Color3B::WHITE);
    auto getAllGroupItem  = MenuItemLabel::create(getAllGroupLabel, CC_CALLBACK_1(TestBuddyService::getAllGroups, this));
    y_pos -= button_y_Offset;
    getAllGroupItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllFriendsInGroup
     */
    auto getAllFriendsOfUserLabel = LabelTTF::create("GetAllFriendsInGroup", "Marker Felt", 24);
    getAllFriendsOfUserLabel->setColor(Color3B::WHITE);
    auto getAllFriendsOfUserItem  = MenuItemLabel::create(getAllFriendsOfUserLabel, CC_CALLBACK_1(TestBuddyService::getAllFriendsInGroup, this));
    y_pos -= button_y_Offset;
    getAllFriendsOfUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * BlockFriendRequest
     */
    auto blockFriendRequestLabel = LabelTTF::create("BlockFriendRequest", "Marker Felt", 24);
    blockFriendRequestLabel->setColor(Color3B::WHITE);
    auto blockFriendRequestItem  = MenuItemLabel::create(blockFriendRequestLabel, CC_CALLBACK_1(TestBuddyService::blockFriendRequest, this));
    y_pos -= button_y_Offset;
    blockFriendRequestItem->setPosition(Point(x_pos,y_pos));

    /**
     * BlockUser
     */
    auto blockUserLabel = LabelTTF::create("BlockUser", "Marker Felt", 24);
    blockUserLabel->setColor(Color3B::WHITE);
    auto blockUserItem  = MenuItemLabel::create(blockUserLabel, CC_CALLBACK_1(TestBuddyService::blockUser, this));
    y_pos -= button_y_Offset;
    blockUserItem->setPosition(Point(x_pos,y_pos));

    /**
     * UnblockUser
     */
    auto unblockUserLabel = LabelTTF::create("UnblockUser", "Marker Felt", 24);
    unblockUserLabel->setColor(Color3B::WHITE);
    auto unblockUserItem  = MenuItemLabel::create(unblockUserLabel, CC_CALLBACK_1(TestBuddyService::unblockUser, this));
    y_pos -= button_y_Offset;
    unblockUserItem->setPosition(Point(x_pos,y_pos));
    
    
    
   /**
    * SendMessageToGroup
    */
    auto sendMessageToGroupLabel = LabelTTF::create("SendMessageToGroup", "Marker Felt", 24);
    sendMessageToGroupLabel->setColor(Color3B::WHITE);
    auto sendMessageToGroupItem  = MenuItemLabel::create(sendMessageToGroupLabel, CC_CALLBACK_1(TestBuddyService::sendMessageToGroup, this));
    y_pos -= button_y_Offset;
    sendMessageToGroupItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * SendMessageToFriend
     */
    auto sendMessageToFriendLabel = LabelTTF::create("SendMessageToFriend", "Marker Felt", 24);
    sendMessageToFriendLabel->setColor(Color3B::WHITE);
    auto sendMessageToFriendItem  = MenuItemLabel::create(sendMessageToFriendLabel, CC_CALLBACK_1(TestBuddyService::sendMessageToFriend, this));
    y_pos -= button_y_Offset;
    sendMessageToFriendItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * SendMessageToFriends
     */
    auto sendMessageToFriendsLabel = LabelTTF::create("SendMessageToFriends", "Marker Felt", 24);
    sendMessageToFriendsLabel->setColor(Color3B::WHITE);
    auto sendMessageToFriendsItem  = MenuItemLabel::create(sendMessageToFriendsLabel, CC_CALLBACK_1(TestBuddyService::sendMessageToFriends, this));
    y_pos -= button_y_Offset;
    sendMessageToFriendsItem->setPosition(Point(x_pos,y_pos));
    
    y_pos = visibleSize.height-button_y_Offset;
    x_pos = origin.x + 3*visibleSize.width/4;
    
    /**
     * GetAllMessages
     */
    auto getAllMessagesLabel = LabelTTF::create("GetAllMessages", "Marker Felt", 24);
    getAllMessagesLabel->setColor(Color3B::WHITE);
    auto getAllMessagesItem  = MenuItemLabel::create(getAllMessagesLabel, CC_CALLBACK_1(TestBuddyService::getAllMessages, this));
    y_pos -= button_y_Offset;
    getAllMessagesItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllMessagesFromBuddy
     */
    auto getAllMessagesFromBuddyLabel = LabelTTF::create("GetAllMessagesFromBuddy", "Marker Felt", 24);
    getAllMessagesFromBuddyLabel->setColor(Color3B::WHITE);
    auto getAllMessagesFromBuddyItem  = MenuItemLabel::create(getAllMessagesFromBuddyLabel, CC_CALLBACK_1(TestBuddyService::getAllMessagesFromBuddy, this));
    y_pos -= button_y_Offset;
    getAllMessagesFromBuddyItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllMessagesFromGroup
     */
    auto getAllMessagesFromGroupLabel = LabelTTF::create("GetAllMessagesFromGroup", "Marker Felt", 24);
    getAllMessagesFromGroupLabel->setColor(Color3B::WHITE);
    auto getAllMessagesFromGroupItem  = MenuItemLabel::create(getAllMessagesFromGroupLabel, CC_CALLBACK_1(TestBuddyService::getAllMessagesFromGroup, this));
    y_pos -= button_y_Offset;
    getAllMessagesFromGroupItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * UnFriend
     */
    auto unFriendLabel = LabelTTF::create("UnFriend", "Marker Felt", 24);
    unFriendLabel->setColor(Color3B::WHITE);
    auto unFriendItem  = MenuItemLabel::create(unFriendLabel, CC_CALLBACK_1(TestBuddyService::unFriend, this));
    y_pos -= button_y_Offset;
    unFriendItem->setPosition(Point(x_pos,y_pos));

    /**
     * DeleteMessageById
     */
    auto deleteMessageByIdLabel = LabelTTF::create("DeleteMessageById", "Marker Felt", 24);
    deleteMessageByIdLabel->setColor(Color3B::WHITE);
    auto deleteMessageByIdItem  = MenuItemLabel::create(deleteMessageByIdLabel, CC_CALLBACK_1(TestBuddyService::deleteMessageById, this));
    y_pos -= button_y_Offset;
    deleteMessageByIdItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * DeleteMessageByIds
     */
    auto deleteMessageByIdsLabel = LabelTTF::create("DeleteMessageByIds", "Marker Felt", 24);
    deleteMessageByIdsLabel->setColor(Color3B::WHITE);
    auto deleteMessageByIdsItem  = MenuItemLabel::create(deleteMessageByIdsLabel, CC_CALLBACK_1(TestBuddyService::deleteMessageByIds, this));
    y_pos -= button_y_Offset;
    deleteMessageByIdsItem->setPosition(Point(x_pos,y_pos));

    /**
     * CheckedInGeoLocation
     */
    auto checkedInGeoLocationLabel = LabelTTF::create("CheckedInGeoLocation", "Marker Felt", 24);
    checkedInGeoLocationLabel->setColor(Color3B::WHITE);
    auto checkedInGeoLocationItem  = MenuItemLabel::create(checkedInGeoLocationLabel, CC_CALLBACK_1(TestBuddyService::checkedInGeoLocation, this));
    y_pos -= button_y_Offset;
    checkedInGeoLocationItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetFriendsByLocation
     */
    auto getFriendsByLocationLabel = LabelTTF::create("GetFriendsByLocation", "Marker Felt", 24);
    getFriendsByLocationLabel->setColor(Color3B::WHITE);
    auto getFriendsByLocationItem  = MenuItemLabel::create(getFriendsByLocationLabel, CC_CALLBACK_1(TestBuddyService::getFriendsByLocation, this));
    y_pos -= button_y_Offset;

    getFriendsByLocationItem->setPosition(Point(x_pos,y_pos));
 	 

    // create menu, it's an autorelease object
    auto menu = Menu::create(backButtonItem,
                             sendFrndRequestItem,
                             getFriendRequestItem,
                             acceptFriendRequestItem,
                             rejectFriendRequestItem,
                             getAllFriendsItem,
                             createGroupItem,
                             addFriendsToGroupItem,
                             NULL);

	auto menu1 = Menu::create(
                             getAllGroupItem,
                             getAllFriendsOfUserItem,
                             blockFriendRequestItem,
                             blockUserItem,
                             unblockUserItem,
                             sendMessageToGroupItem,
                             sendMessageToFriendItem,
                             sendMessageToFriendsItem,
                             NULL);

	auto menu2 = Menu::create(
                             getAllMessagesItem,
                             getAllMessagesFromBuddyItem,
                             getAllMessagesFromGroupItem,
                             unFriendItem,
                             deleteMessageByIdItem,
                             deleteMessageByIdsItem,
                             checkedInGeoLocationItem,
                             getFriendsByLocationItem,
                             NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	menu1->setPosition(Point::ZERO);
    this->addChild(menu1, 1);

	menu2->setPosition(Point::ZERO);
    this->addChild(menu2, 1);
    
    
    userName = "Rajeev123";
    buddyName = "Ranjan1234";
    ownerName = "Rajeev123";
    groupName = "Trending";
    message = "Hello";
    messageId = "53cf918fe4b05e4ed335da11";
    return true;
}




/**
 * API Test Cases
 */
void TestBuddyService::sendFrndRequest(Ref* sender)
{
    //static int counter =0;
    BuddyService* buddyService = App42API::BuildBuddyService();
    const char* userName = "Rajeev1231223";
    const char* buddyName = "R";
    const char* message = "Please add me to ur network";
    buddyService->SendFriendRequest(userName, buddyName, message, app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}

void TestBuddyService::getFrndRequest(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    const char* userName = "Ranjan1234";
    buddyService->GetFriendRequest( userName, app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}

void TestBuddyService::acceptFriendRequest(Ref* sender)
{
    static int counter =0;
    
    BuddyService* buddyService = App42API::BuildBuddyService();
    string userName = "R";
    userName.append(Util::ItoA(++counter));
    //const char* userName ="Ranjan1234" ;
    //const char* buddyName = "Rajeev1231223";

    buddyService->AcceptFriendRequest(userName.c_str(), buddyName,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}

void TestBuddyService::rejectFriendRequest(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    const char* userName = "Rajeev123";
    const char* buddyName = "Ranjan123";
    buddyService->RejectFriendRequest(userName, buddyName,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}

void TestBuddyService::getAllFriends(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    const char* userName = "Rajeev123";
    buddyService->GetAllFriends(userName,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}
void TestBuddyService::createGroup(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    const char* userName = "Rajeev1231223";
    const char* groupName = "Trending1234";
   // App42API::setLoggedInUser(userName);
    buddyService->CreateGroupByUser(userName,groupName,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}
void TestBuddyService::addFriendsToGroup(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    vector<string> friends;
    friends.push_back("R1");
    friends.push_back("R2");
    friends.push_back("R3");
    const char* userName = "Rajeev1231223";
    const char* groupName = "Trending1234";
    buddyService->AddFriendsToGroup(userName,groupName, friends,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}

void TestBuddyService::getAllGroups(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    const char* userName = "Rajeev123";
    buddyService->GetAllGroups(userName,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}

void TestBuddyService::getAllFriendsInGroup(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    const char* userName = "Rajeev123";
    const char* groupName = "Trending";
    const char* ownerName = "Rajeev123";
    //App42API::setLoggedInUser(userName);
    buddyService->GetAllFriendsInGroup(userName,ownerName,groupName,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}

void TestBuddyService::blockFriendRequest(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    const char* userName = "Rajeev123";
    const char* buddyName = "R4";
    buddyService->BlockFriendRequest(buddyName,userName,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}
void TestBuddyService::blockUser(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    buddyService->BlockUser(userName,buddyName,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}
void TestBuddyService::unblockUser(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    buddyService->UnblockUser(userName,buddyName,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));

}
void TestBuddyService::sendMessageToGroup(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    buddyService->SendMessageToGroup(userName, ownerName, groupName, message,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));

}
void TestBuddyService::sendMessageToFriend(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    buddyName = "R1";
    buddyService->SendMessageToFriend(userName,buddyName,message,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));

}
void TestBuddyService::sendMessageToFriends(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    
    buddyService->SendMessageToFriends(userName,message,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));

}
void TestBuddyService::getAllMessages(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    buddyService->GetAllMessages(userName,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));

}
void TestBuddyService::getAllMessagesFromBuddy(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    buddyName = "R1";
    buddyService->GetAllMessagesFromBuddy(buddyName,userName,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));

}
void TestBuddyService::getAllMessagesFromGroup(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    buddyService->GetAllMessagesFromGroup(userName, ownerName, groupName,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}

void TestBuddyService::unFriend(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    buddyName = "R1";
    buddyService->UnFriend(userName,buddyName,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}
void TestBuddyService::deleteMessageById(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    buddyService->DeleteMessageById(userName,messageId,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}
void TestBuddyService::deleteMessageByIds(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    
    vector<string> messageIds;
    messageIds.push_back("53cf97a6e4b05e4ed335db0a");
    messageIds.push_back("53cf97b1e4b0a53e3dc82927");

    buddyService->DeleteMessageByIds(userName,messageIds,app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}

void TestBuddyService::checkedInGeoLocation(Ref* sender)
{
    static int counter =0;
    string uName = "R";
    uName.append(Util::ItoA(++counter));
    
    BuddyService* buddyService = App42API::BuildBuddyService();
    App42GeoPoint *geoPoint = new App42GeoPoint();
    geoPoint->latitude = 20.0+counter;
    geoPoint->longitude = 30.0+counter;
    geoPoint->markerName = "Shephertz";
    
    buddyService->CheckedInGeoLocation(userName, geoPoint, app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));

}
void TestBuddyService::getFriendsByLocation(Ref* sender)
{
    BuddyService* buddyService = App42API::BuildBuddyService();
    double latitude = 20.0;
    double longitude = 30.0;
    double maxDistance = 500;
    int max = 5;
    buddyService->GetFriendsByLocation(userName, latitude, longitude, maxDistance, max, app42callback(TestBuddyService::onBuddyServiceRequestCompleted, this));
}

/**
 * Callback Methods
 */
void TestBuddyService::onBuddyServiceRequestCompleted(void *response)
{
    App42BuddyResponse *app42BuddyResponse = (App42BuddyResponse*)response;
    string code = StringUtils::format("Code = %d",app42BuddyResponse->getCode());
    responseArray.push_back(code);

    if(app42BuddyResponse->isSuccess)
    {
        printf("\ncode=%d",app42BuddyResponse->getCode());
        printf("\nisSuccess=%d",app42BuddyResponse->isSuccess);
        printf("\nResponse Body=%s",app42BuddyResponse->getBody().c_str());
        
        for(std::vector<App42Buddy>::iterator it = app42BuddyResponse->buddyList.begin(); it != app42BuddyResponse->buddyList.end(); ++it)
        {
            printf("\n UserName=%s",it->userName.c_str());
            printf("\n BuddyName=%s",it->buddyName.c_str());
            printf("\n Message=%s",it->message.c_str());
            printf("\n MessageId=%s",it->messageId.c_str());
            printf("\n SentOn=%s",it->sentOn.c_str());
            printf("\n AcceptedOn=%s",it->acceptedOn.c_str());
            printf("\n GroupName=%s",it->groupName.c_str());
            printf("\n OwnerName=%s",it->ownerName.c_str());
            
            for(std::vector<App42GeoPoint>::iterator iit = it->pointList.begin(); iit != it->pointList.end(); ++iit)
            {
                printf("\n Latitude=%lf",iit->latitude);
                printf("\n Longitude=%lf\n",iit->longitude);
                printf("\n MarkerName=%s\n",iit->markerName.c_str());
                printf("\n CreatedOn=%s\n",iit->createdOn.c_str());
            }
        }
    }
    else
    {
        printf("\nerrordetails:%s",app42BuddyResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",app42BuddyResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",app42BuddyResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",app42BuddyResponse->httpErrorCode);
        
        string error = StringUtils::format("Error = %s",app42BuddyResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",app42BuddyResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestBuddyService::loadResponseScene, this));
    
}

void TestBuddyService::loadResponseScene()
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

void TestBuddyService::menuCloseCallback(Ref* pSender)
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

