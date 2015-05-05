//
//  TestGeoService.cpp
//  App42Cocos2dXSample
//
//  Created by Rajeev Ranjan on 27/04/15.
//
//

#include "TestGeoService.h"
#include "TestHome.h"


#define GO_HOME 116



USING_NS_CC;

Scene* TestGeoService::createScene()
{
    // 'scene' is an autorelease Object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease Object
    auto layer = TestGeoService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestGeoService::init()
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
     * Create GeoPoints
     */
    auto createGeoPointsLabel = LabelTTF::create("Create GeoPoints", "Marker Felt", 24);
    createGeoPointsLabel->setColor(Color3B::WHITE);
    auto createGeoPointsItem  = MenuItemLabel::create(createGeoPointsLabel, CC_CALLBACK_1(TestGeoService::createGeoPoints, this));
    createGeoPointsItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetNearByPointsByMaxDistance
     */
    auto getNearByPointsByMaxDistanceLabel = LabelTTF::create("GetNearByPointsByMaxDistance", "Marker Felt", 24);
    getNearByPointsByMaxDistanceLabel->setColor(Color3B::WHITE);
    auto getNearByPointsByMaxDistanceItem  = MenuItemLabel::create(getNearByPointsByMaxDistanceLabel, CC_CALLBACK_1(TestGeoService::getNearByPointsByMaxDistance, this));
    y_pos = y_pos-button_y_Offset;
    getNearByPointsByMaxDistanceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetNearByPoint
     */
    auto getNearByPointLabel = LabelTTF::create("GetNearByPoint", "Marker Felt", 24);
    getNearByPointLabel->setColor(Color3B::WHITE);
    auto getNearByPointItem  = MenuItemLabel::create(getNearByPointLabel, CC_CALLBACK_1(TestGeoService::getNearByPoint, this));
    y_pos = y_pos-button_y_Offset;
    getNearByPointItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetPointsWithInCircle
     */
    auto getPointsWithInCircleLabel = LabelTTF::create("GetPointsWithInCircle", "Marker Felt", 24);
    getPointsWithInCircleLabel->setColor(Color3B::WHITE);
    auto getPointsWithInCircleItem  = MenuItemLabel::create(getPointsWithInCircleLabel, CC_CALLBACK_1(TestGeoService::getPointsWithInCircle, this));
    y_pos = y_pos-button_y_Offset;
    getPointsWithInCircleItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllStorage
     */
    auto getAllStorageLabel = LabelTTF::create("GetAllStorage", "Marker Felt", 24);
    getAllStorageLabel->setColor(Color3B::WHITE);
    auto getAllStorageItem  = MenuItemLabel::create(getAllStorageLabel, CC_CALLBACK_1(TestGeoService::getAllStorage, this));
    y_pos = y_pos-button_y_Offset;
    getAllStorageItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllStorageByPaging
     */
    auto getAllStorageByPagingLabel = LabelTTF::create("GetAllStorageByPaging", "Marker Felt", 24);
    getAllStorageByPagingLabel->setColor(Color3B::WHITE);
    auto getAllStorageByPagingItem  = MenuItemLabel::create(getAllStorageByPagingLabel, CC_CALLBACK_1(TestGeoService::getAllStorageByPaging, this));
    y_pos = y_pos-button_y_Offset;
    getAllStorageByPagingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * DeleteGeoPoints
     */
    auto deleteGeoPointsLabel = LabelTTF::create("DeleteGeoPoints", "Marker Felt", 24);
    deleteGeoPointsLabel->setColor(Color3B::WHITE);
    auto deleteGeoPointsItem  = MenuItemLabel::create(deleteGeoPointsLabel, CC_CALLBACK_1(TestGeoService::deleteGeoPoints, this));
    y_pos = y_pos-button_y_Offset;
    deleteGeoPointsItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * DeleteStorage
     */
    auto deleteStorageLabel = LabelTTF::create("DeleteStorage", "Marker Felt", 24);
    deleteStorageLabel->setColor(Color3B::WHITE);
    auto deleteStorageItem  = MenuItemLabel::create(deleteStorageLabel, CC_CALLBACK_1(TestGeoService::deleteStorage, this));
    y_pos = y_pos-button_y_Offset;
    deleteStorageItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllPoints
     */
    auto getAllPointsLabel = LabelTTF::create("GetAllPoints", "Marker Felt", 24);
    getAllPointsLabel->setColor(Color3B::WHITE);
    auto getAllPointsItem  = MenuItemLabel::create(getAllPointsLabel, CC_CALLBACK_1(TestGeoService::getAllPoints, this));
    y_pos = y_pos-button_y_Offset;
    getAllPointsItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllPointsByPaging
     */
    auto getAllPointsByPagingLabel = LabelTTF::create("GetAllPointsByPaging", "Marker Felt", 24);
    getAllPointsByPagingLabel->setColor(Color3B::WHITE);
    auto getAllPointsByPagingItem  = MenuItemLabel::create(getAllPointsByPagingLabel, CC_CALLBACK_1(TestGeoService::getAllPointsByPaging, this));
    y_pos = y_pos-button_y_Offset;
    getAllPointsByPagingItem->setPosition(Point(x_pos,y_pos));
    
    
    /**
     * Back Button
     */
    auto backButtonItem = MenuItemImage::create(
                                                "BackButton.png",
                                                "BackButton.png",
                                                CC_CALLBACK_1(TestGeoService::menuCloseCallback, this));
    
    backButtonItem->setPosition(Point(origin.x + visibleSize.width/2 ,
                                      origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    
    
    
    /**
     * Create Menu
     */
    auto menu = Menu::create(createGeoPointsItem,
                             getNearByPointsByMaxDistanceItem,
                             getNearByPointItem,
                             getPointsWithInCircleItem,
                             getAllStorageItem,
                             getAllStorageByPagingItem,
                             deleteGeoPointsItem,
                             deleteStorageItem,
                             getAllPointsItem,
                             getAllPointsByPagingItem,
                             NULL);
    
    /*auto menu1 = Menu::create(
                              getAllUsersCountItem,
                              lockUserItem,
                              unlockUserItem,
                              getAllLockedUsersItem,
                              getLockedUsersPagingItem,
                              getAllLockedUsersCountItem,
                              updateEmailItem,
                              deleteUserItem,
                              deleteUserPermanentItem,NULL);
    
    auto menu2 = Menu::create(
                              changePwdItem,
                              resetPwdItem,
                              profileItem,
                              getUsersByProfileItem,
                              logoutItem,
                              getRolesByUserItem,
                              getUsersByRoleItem,
                              revokeRoleItem,
                              revokeAllRolesItem, NULL);
    
    auto menu3 = Menu::create(
                              getUsersByGroupItem,
                              createUserWithProfileItem,
                              createUserWithCustomDataItem,
                              getUserWithCustomDataItem,
                              getAllUsersWithCustomDataItem,NULL);*/
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    /*menu1->setPosition(Point::ZERO);
    this->addChild(menu1, 1);
    
    menu2->setPosition(Point::ZERO);
    this->addChild(menu2, 1);
    
    menu3->setPosition(Point::ZERO);
    this->addChild(menu3, 1);*/
    
    return true;
}


void TestGeoService::createGeoPoints(Ref* pSender)
{
    GeoService *geoService = App42API::BuildGeoService();
    const char* geoStorageName = "markerstorage";
    
    vector<App42GeoPoint> geoPointsList;
    App42GeoPoint geoPoint;
    geoPoint.latitude = 50.0;
    geoPoint.longitude = 100.0;
    geoPoint.markerName = "New Delhi";
    geoPointsList.push_back(geoPoint);
    
    geoService->CreateGeoPoints(geoStorageName, geoPointsList,app42callback(TestGeoService::onGeoRequestCompleted, this));
}

void TestGeoService::getNearByPointsByMaxDistance(Ref* pSender)
{
    GeoService *geoService = App42API::BuildGeoService();
    const char* geoStorageName = "geolist";
    geoService->GetNearByPointsByMaxDistance(geoStorageName, 22.777777, 55.265865, 22.777777, app42callback(TestGeoService::onGeoRequestCompleted, this));
}

void TestGeoService::getNearByPoint(Ref* pSender)
{
    GeoService *geoService = App42API::BuildGeoService();
    const char* geoStorageName = "geolist";
    geoService->GetNearByPoint(geoStorageName, 22.77777, 55.26586, 10, app42callback(TestGeoService::onGeoRequestCompleted, this));
}

void TestGeoService::getPointsWithInCircle(Ref* pSender)
{
    GeoService *geoService = App42API::BuildGeoService();
    const char* geoStorageName = "geolist";
    geoService->GetPointsWithInCircle(geoStorageName, 22.77777, 55.26586, 100, 10, app42callback(TestGeoService::onGeoRequestCompleted, this));
}

void TestGeoService::getAllStorage(Ref* pSender)
{
    GeoService *geoService = App42API::BuildGeoService();
    geoService->GetAllStorage(app42callback(TestGeoService::onGeoRequestCompleted, this));
}

void TestGeoService::getAllStorageByPaging(Ref* pSender)
{
    GeoService *geoService = App42API::BuildGeoService();
    geoService->GetAllStorageByPaging(5, 0, app42callback(TestGeoService::onGeoRequestCompleted, this));
}

void TestGeoService::deleteGeoPoints(Ref* pSender)
{
    GeoService *geoService = App42API::BuildGeoService();
    const char* geoStorageName = "geolist";
    
    vector<App42GeoPoint> geoPointsList;
    App42GeoPoint geoPoint;
    geoPoint.latitude = 50.0;
    geoPoint.longitude = 100.0;
    geoPoint.markerName = "New Delhi";
    geoPointsList.push_back(geoPoint);
    
    geoService->DeleteGeoPoints(geoStorageName, geoPointsList, app42callback(TestGeoService::onGeoRequestCompleted, this));
}

void TestGeoService::deleteStorage(Ref* pSender)
{
    GeoService *geoService = App42API::BuildGeoService();
    const char* geoStorageName = "geolist";
    geoService->DeleteStorage(geoStorageName, app42callback(TestGeoService::onGeoRequestCompleted, this));
}

void TestGeoService::getAllPoints(Ref* pSender)
{
    GeoService *geoService = App42API::BuildGeoService();
    const char* geoStorageName = "geolist";
    geoService->GetAllPoints(geoStorageName, app42callback(TestGeoService::onGeoRequestCompleted, this));
}

void TestGeoService::getAllPointsByPaging(Ref* pSender)
{
    GeoService *geoService = App42API::BuildGeoService();
    const char* geoStorageName = "geolist";
    geoService->GetAllPointsByPaging(geoStorageName, 5, 0, app42callback(TestGeoService::onGeoRequestCompleted, this));
}

/**
 * Callback Methods
 */
void TestGeoService::onGeoRequestCompleted( void *response)
{
    App42GeoResponse *geoResponse = (App42GeoResponse*)response;
    printf("\ncode=%d...=%d",geoResponse->getCode(),geoResponse->isSuccess);
    printf("\nResponse Body=%s",geoResponse->getBody().c_str());
    
    string code = StringUtils::format("Code = %d",geoResponse->getCode());
    responseArray.push_back(code);
    
    if (geoResponse->isSuccess)
    {
        printf("\nTotalRecords=%d",geoResponse->getTotalRecords());
        
        for(std::vector<App42Geo>::iterator it = geoResponse->geoList.begin(); it != geoResponse->geoList.end(); ++it)
        {
            printf("\n StorageName=%s",it->storageName.c_str());
            printf("\n SourceLat=%lf",it->sourceLat);
            printf("\n SourceLng=%lf",it->sourceLng);
        }
    }
    else
    {
        printf("\nerrordetails:%s",geoResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",geoResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",geoResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",geoResponse->httpErrorCode);
        string error = StringUtils::format("Error = %s",geoResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",geoResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestGeoService::loadResponseScene, this));
    
}

void TestGeoService::loadResponseScene()
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


void TestGeoService::menuCloseCallback(Ref* pSender)
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