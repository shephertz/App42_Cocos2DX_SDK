//
//  TestStorageService.cpp
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#include "TestStorageService.h"
#include "TestHome.h"
#include "ResponseScene.h"

#define GO_HOME 103

USING_NS_CC;

Scene* TestStorageService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestStorageService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}




bool TestStorageService::init()
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
                                                CC_CALLBACK_1(TestStorageService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(origin.x + visibleSize.width/2 ,
                                      origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);

    /**
     * Insert Doc
     */
    auto insertDocLabel = LabelTTF::create("Insert Doc", "Marker Felt", 24);
    insertDocLabel->setColor(Color3B::WHITE);
    auto insertDocItem  = MenuItemLabel::create(insertDocLabel, CC_CALLBACK_1(TestStorageService::insertJsonDocument, this));
    insertDocItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Insert App42Object
     */
    auto insertDocObjectLabel = LabelTTF::create("InsertApp42Object", "Marker Felt", 24);
    insertDocObjectLabel->setColor(Color3B::WHITE);
    auto insertDocObjectItem  = MenuItemLabel::create(insertDocObjectLabel, CC_CALLBACK_1(TestStorageService::insertJsonDocumentWithApp42Object, this));
    y_pos -= button_y_Offset;
    insertDocObjectItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindAllDocuments
     */
    auto findAllDocumentLabel = LabelTTF::create("FindAllDocuments", "Marker Felt", 24);
    findAllDocumentLabel->setColor(Color3B::WHITE);
    auto findAllDocumentItem  = MenuItemLabel::create(findAllDocumentLabel, CC_CALLBACK_1(TestStorageService::findAllDocuments, this));
    y_pos -= button_y_Offset;
    findAllDocumentItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindAllCollections
     */
    auto findAllCollectionsLabel = LabelTTF::create("FindAllCollections", "Marker Felt", 24);
    findAllCollectionsLabel->setColor(Color3B::WHITE);
    auto findAllCollectionsItem  = MenuItemLabel::create(findAllCollectionsLabel, CC_CALLBACK_1(TestStorageService::findAllCollections, this));
    y_pos -= button_y_Offset;
    findAllCollectionsItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindAllDocumentsByPaging
     */
    auto findAllDocumentByPagingLabel = LabelTTF::create("FindAllDocumentsByPaging", "Marker Felt", 24);
    findAllDocumentByPagingLabel->setColor(Color3B::WHITE);
    auto findAllDocumentByPagingItem  = MenuItemLabel::create(findAllDocumentByPagingLabel, CC_CALLBACK_1(TestStorageService::findAllDocumentsByPaging, this));
    y_pos -= button_y_Offset;
    findAllDocumentByPagingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindAllDocumentCount
     */
    auto findAllDocumentCountLabel = LabelTTF::create("FindAllDocumentsCount", "Marker Felt", 24);
    findAllDocumentCountLabel->setColor(Color3B::WHITE);
    auto findAllDocumentCountItem  = MenuItemLabel::create(findAllDocumentCountLabel, CC_CALLBACK_1(TestStorageService::findAllDocumentsCount, this));
    y_pos -= button_y_Offset;
    findAllDocumentCountItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindDocumentID
     */
    auto findDocumentIDLabel = LabelTTF::create("FindDocumentID", "Marker Felt", 24);
    findDocumentIDLabel->setColor(Color3B::WHITE);
    auto findDocumentIDItem  = MenuItemLabel::create(findDocumentIDLabel, CC_CALLBACK_1(TestStorageService::findDocumentById, this));
    y_pos -= button_y_Offset;
    findDocumentIDItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindDocumentsByQuery
     */
    auto findDocumentsByQueryLabel = LabelTTF::create("FindDocumentsByQuery", "Marker Felt", 24);
    findDocumentsByQueryLabel->setColor(Color3B::WHITE);
    auto findDocumentsByQueryItem  = MenuItemLabel::create(findDocumentsByQueryLabel, CC_CALLBACK_1(TestStorageService::findDocumentByQuery, this));
    y_pos -= button_y_Offset;
    findDocumentsByQueryItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindDocumentsByKeyValue
     */
    auto findDocumentsByKeyValueLabel = LabelTTF::create("FindDocumentsByKeyValue", "Marker Felt", 24);
    findDocumentsByKeyValueLabel->setColor(Color3B::WHITE);
    auto findDocumentsByKeyValueItem  = MenuItemLabel::create(findDocumentsByKeyValueLabel, CC_CALLBACK_1(TestStorageService::findDocumentsByKeyValue, this));
    y_pos -= button_y_Offset;
    findDocumentsByKeyValueItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindDocsByKeyValueByOrder
     */
    auto findDocsByKeyValueByOrderLabel = LabelTTF::create("FindDocsByKeyValueByOrder", "Marker Felt", 24);
    findDocsByKeyValueByOrderLabel->setColor(Color3B::WHITE);
    auto findDocsByKeyValueByOrderItem  = MenuItemLabel::create(findDocsByKeyValueByOrderLabel, CC_CALLBACK_1(TestStorageService::findDocsByKeyValueByOrder, this));
    y_pos -= button_y_Offset;
    findDocsByKeyValueByOrderItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindDocumentsByQueryWithPaging
     */
    auto findDocumentsByQueryPagingLabel = LabelTTF::create("FindDocumentsByQueryWithPaging", "Marker Felt", 24);
    findDocumentsByQueryPagingLabel->setColor(Color3B::WHITE);
    auto findDocumentsByQueryPagingItem  = MenuItemLabel::create(findDocumentsByQueryPagingLabel, CC_CALLBACK_1(TestStorageService::findDocumentByQueryWithPaging, this));
    y_pos -= button_y_Offset;
    findDocumentsByQueryPagingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindDocsByQueryWithPagingOrderBy
     */
    auto findDocsByQueryWithPagingOrderByLabel = LabelTTF::create("FindDocsByQueryWithPagingOrderBy", "Marker Felt", 24);
    findDocsByQueryWithPagingOrderByLabel->setColor(Color3B::WHITE);
    auto findDocsByQueryWithPagingOrderByItem  = MenuItemLabel::create(findDocsByQueryWithPagingOrderByLabel, CC_CALLBACK_1(TestStorageService::findDocumentByQueryWithPagingOrderBy, this));
    y_pos -= button_y_Offset;
    findDocsByQueryWithPagingOrderByItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * DeleteDocumentsById
     */
    auto deleteDocumentsByIdLabel = LabelTTF::create("DeleteDocumentsById", "Marker Felt", 24);
    deleteDocumentsByIdLabel->setColor(Color3B::WHITE);
    auto deleteDocumentsByIdItem  = MenuItemLabel::create(deleteDocumentsByIdLabel, CC_CALLBACK_1(TestStorageService::deleteDocumentById, this));
    y_pos -= button_y_Offset;
    deleteDocumentsByIdItem->setPosition(Point(x_pos,y_pos));
    /**
     * DeleteDocumentsByKeyValue
     */
    auto deleteDocumentsByKeyValueLabel = LabelTTF::create("DeleteDocumentsByKeyValue", "Marker Felt", 24);
    deleteDocumentsByKeyValueLabel->setColor(Color3B::WHITE);
    auto deleteDocumentsByKeyValueItem  = MenuItemLabel::create(deleteDocumentsByKeyValueLabel, CC_CALLBACK_1(TestStorageService::deleteDocumentByKeyValue, this));
    y_pos -= button_y_Offset;
    deleteDocumentsByKeyValueItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * DeleteAllDocuments
     */
    auto deleteAllDocumentsLabel = LabelTTF::create("DeleteAllDocuments", "Marker Felt", 24);
    deleteAllDocumentsLabel->setColor(Color3B::WHITE);
    auto deleteAllDocumentsItem  = MenuItemLabel::create(deleteAllDocumentsLabel, CC_CALLBACK_1(TestStorageService::deleteAllDocuments, this));
    y_pos -= button_y_Offset;
    deleteAllDocumentsItem->setPosition(Point(x_pos,y_pos));
    
     y_pos = visibleSize.height-button_y_Offset;
     x_pos = origin.x + 3*visibleSize.width/4;
    
    /**
     * AddOrUpdateKeys
     */
    auto addOrUpdateKeysLabel = LabelTTF::create("AddOrUpdateKeys", "Marker Felt", 24);
    addOrUpdateKeysLabel->setColor(Color3B::WHITE);
    auto addOrUpdateKeysItem  = MenuItemLabel::create(addOrUpdateKeysLabel, CC_CALLBACK_1(TestStorageService::addOrUpdateKeys, this));
    y_pos -= button_y_Offset;
    addOrUpdateKeysItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * AddOrUpdateKeysWithApp42Object
     */
    auto addOrUpdateKeysWithApp42ObjectLabel = LabelTTF::create("AddOrUpdateKeysWithApp42Object", "Marker Felt", 24);
    addOrUpdateKeysWithApp42ObjectLabel->setColor(Color3B::WHITE);
    auto addOrUpdateKeysWithApp42ObjectItem  = MenuItemLabel::create(addOrUpdateKeysWithApp42ObjectLabel, CC_CALLBACK_1(TestStorageService::addOrUpdateKeysWithApp42Object, this));
    y_pos -= button_y_Offset;
    addOrUpdateKeysWithApp42ObjectItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * UpdateDocByKeyValue
     */
    auto updateDocByKeyValueLabel = LabelTTF::create("UpdateDocByKeyValue", "Marker Felt", 24);
    updateDocByKeyValueLabel->setColor(Color3B::WHITE);
    auto updateDocByKeyValueLabelItem  = MenuItemLabel::create(updateDocByKeyValueLabel, CC_CALLBACK_1(TestStorageService::updateDocByKeyValue, this));
    y_pos -= button_y_Offset;
    updateDocByKeyValueLabelItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * UpdateApp42DocByKeyValue
     */
    auto updateApp42DocByKeyValueLabel = LabelTTF::create("UpdateApp42DocByKeyValue", "Marker Felt", 24);
    updateApp42DocByKeyValueLabel->setColor(Color3B::WHITE);
    auto updateApp42DocByKeyValueLabelItem  = MenuItemLabel::create(updateApp42DocByKeyValueLabel, CC_CALLBACK_1(TestStorageService::updateApp42DocByKeyValue, this));
    y_pos -= button_y_Offset;
    updateApp42DocByKeyValueLabelItem->setPosition(Point(x_pos,y_pos));

    /**
     * UpdateDocByDocId
     */
    auto updateDocByDocIDLabel = LabelTTF::create("UpdateDocByDocId", "Marker Felt", 24);
    updateDocByDocIDLabel->setColor(Color3B::WHITE);
    auto updateDocByDocIDItem  = MenuItemLabel::create(updateDocByDocIDLabel, CC_CALLBACK_1(TestStorageService::updateDocByDocID, this));
    y_pos -= button_y_Offset;
    updateDocByDocIDItem->setPosition(Point(x_pos,y_pos));

    /**
     * UpdateApp42DocByDocId
     */
    auto updateApp42DocByDocIDLabel = LabelTTF::create("UpdateApp42DocByDocId", "Marker Felt", 24);
    updateApp42DocByDocIDLabel->setColor(Color3B::WHITE);
    auto updateApp42DocByDocIDItem  = MenuItemLabel::create(updateApp42DocByDocIDLabel, CC_CALLBACK_1(TestStorageService::updateApp42DocByDocId, this));
    y_pos -= button_y_Offset;
    updateApp42DocByDocIDItem->setPosition(Point(x_pos,y_pos));
    
    
    /**
     * SaveOrUpdateApp42DocByKeyValue
     */
    auto saveOrUpdateApp42DocByKeyValueLabel = LabelTTF::create("SaveOrUpdateApp42DocByKeyValue", "Marker Felt", 24);
    saveOrUpdateApp42DocByKeyValueLabel->setColor(Color3B::WHITE);
    auto saveOrUpdateApp42DocByKeyValueItem  = MenuItemLabel::create(saveOrUpdateApp42DocByKeyValueLabel, CC_CALLBACK_1(TestStorageService::saveOrUpdateApp42DocumentByKeyValue, this));
    y_pos -= button_y_Offset;
    saveOrUpdateApp42DocByKeyValueItem->setPosition(Point(x_pos,y_pos));
    
    
    /**
     * SaveOrUpdateDocByKeyValue
     */
    auto saveOrUpdateDocByKeyValueLabel = LabelTTF::create("SaveOrUpdateDocByKeyValue", "Marker Felt", 24);
    saveOrUpdateDocByKeyValueLabel->setColor(Color3B::WHITE);
    auto saveOrUpdateDocByKeyValueItem  = MenuItemLabel::create(saveOrUpdateDocByKeyValueLabel, CC_CALLBACK_1(TestStorageService::saveOrUpdateDocumentByKeyValue, this));
    y_pos -= button_y_Offset;
    saveOrUpdateDocByKeyValueItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * UpdateDocumentByQuery
     */
    auto updateDocumentByQueryLabel = LabelTTF::create("UpdateDocumentByQuery", "Marker Felt", 24);
    updateDocumentByQueryLabel->setColor(Color3B::WHITE);
    auto updateDocumentByQueryItem  = MenuItemLabel::create(updateDocumentByQueryLabel, CC_CALLBACK_1(TestStorageService::updateDocumentByQuery, this));
    y_pos -= button_y_Offset;
    updateDocumentByQueryItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * UpdateDocumentWithApp42ObjectByQuery
     */
    auto updateDocumentWithApp42ObjectByQueryLabel = LabelTTF::create("UpdateDocumentWithApp42ObjectByQuery", "Marker Felt", 24);
    updateDocumentWithApp42ObjectByQueryLabel->setColor(Color3B::WHITE);
    auto updateDocumentWithApp42ObjectByQueryItem  = MenuItemLabel::create(updateDocumentWithApp42ObjectByQueryLabel, CC_CALLBACK_1(TestStorageService::updateDocumentWithApp42ObjectByQuery, this));
    y_pos -= button_y_Offset;
    updateDocumentWithApp42ObjectByQueryItem->setPosition(Point(x_pos,y_pos));
    
    
    /**
     * GrantAccessOnDoc
     */
    auto grantAccessOnDocLabel = LabelTTF::create("GrantAccessOnDoc", "Marker Felt", 24);
    grantAccessOnDocLabel->setColor(Color3B::WHITE);
    auto grantAccessOnDocItem  = MenuItemLabel::create(grantAccessOnDocLabel, CC_CALLBACK_1(TestStorageService::grantAccessOnDoc, this));
    y_pos -= button_y_Offset;
    grantAccessOnDocItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * RevokeAccessOnDoc
     */
    auto revokeAccessOnDocLabel = LabelTTF::create("RevokeAccessOnDoc", "Marker Felt", 24);
    revokeAccessOnDocLabel->setColor(Color3B::WHITE);
    auto revokeAccessOnDocItem  = MenuItemLabel::create(revokeAccessOnDocLabel, CC_CALLBACK_1(TestStorageService::revokeAccessOnDoc, this));
    y_pos -= button_y_Offset;
    revokeAccessOnDocItem->setPosition(Point(x_pos,y_pos));

 	

    /**
     * Create menu, it's an autorelease object
     */
    auto menu = Menu::create(backButtonItem,insertDocItem,
                             findAllDocumentItem,
                             findAllCollectionsItem,
                             findAllDocumentByPagingItem,
                             findAllDocumentCountItem,
                             findDocumentIDItem, NULL);

	auto menu1 = Menu::create(
                             findDocumentsByQueryItem,
                             findDocumentsByKeyValueItem,
                             findDocsByKeyValueByOrderItem,
                             findDocumentsByQueryPagingItem,
                             findDocsByQueryWithPagingOrderByItem,
                             deleteDocumentsByIdItem,
                             deleteDocumentsByKeyValueItem,
                             deleteAllDocumentsItem, NULL);

	auto menu2 = Menu::create(
                             addOrUpdateKeysItem,
                             addOrUpdateKeysWithApp42ObjectItem,
                             insertDocObjectItem,
                             updateDocByKeyValueLabelItem,
                             updateApp42DocByKeyValueLabelItem,
                             updateDocByDocIDItem,
                             updateApp42DocByDocIDItem,
                             saveOrUpdateDocByKeyValueItem, NULL);

	auto menu3 = Menu::create(
                             saveOrUpdateApp42DocByKeyValueItem,
                             updateDocumentByQueryItem,
                             updateDocumentWithApp42ObjectByQueryItem,
                             grantAccessOnDocItem,
                             revokeAccessOnDocItem, NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	menu1->setPosition(Point::ZERO);
    this->addChild(menu1, 1);

	menu2->setPosition(Point::ZERO);
    this->addChild(menu2, 1);

	menu3->setPosition(Point::ZERO);
    this->addChild(menu3, 1);
    
    
    dbName = "jsonDocument2";
    collectionName = "TestingScore";
    docId = "";
    
    App42API::setDbName(dbName);
    
    return true;
}

string getJsonString(string key1, string value1,string key2,string value2)
{
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON_AddStringToObject(bodyJSON, key1.c_str(), value1.c_str());
    cJSON_AddStringToObject(bodyJSON, key2.c_str(), value2.c_str());
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
	string bodyString = cptrFormatted;
    cJSON_Delete(bodyJSON);
	free(cptrFormatted);
    
	return bodyString;
}

void TestStorageService::insertJsonDocument(Ref *sender)
{
/*
  case1: Insert with admin key:
            -use setAdminKey
            - To grant permission user need to setAdminKey
  case2: Insert with session id
            - create user , get session id, and setSessionId in storage service.
            - To grant permission user need to setSessionId
  
  case3: InsertAuth FBAccessToken
            - setFBAccessToken in storageservice instance
            - To grant permission user need to setFBAccessToken
  case4: User can grant permission while inserting the doc by setting defaultApp42ACL.
*/
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
//    const char* dbName = "<Your_DataBase_Name>";
//    const char* collectionName = "<Your_Collection_Name>";
    //const char* jsonDoc ="{\"name\":\"Nick\",\"age\":30,\"phone\":\"xxx-xxx-xxx\"}";
    App42API::setLoggedInUser("RajeevDevice");
    //storageService->setAdminKey(APP_ADMIN_KEY);
    string jsonDoc = "{\"ach_params\":{\"a\":{\"30\":\"1\",\"31\":\"1\",\"32\":\"1\",\"33\":\"1\",\"34\":\"1\",\"35\":\"1\",\"45\":\"1\",\"46\":\"1\",\"47\":\"1\"},\"rep\":false},\"ach_values\":{\"a\":{\"30\":\"1\",\"31\":\"1\",\"32\":\"1\",\"33\":\"2\",\"34\":\"2\",\"35\":\"2\",\"45\":\"1\",\"46\":\"1\",\"47\":\"1\"},\"rep\":false},\"boss\":{\"rep\":false},\"character\":{\"a\":{\"1\":\"124\"},\"rep\":false},\"chieftain\":{\"rep\":false},\"enemy\":{\"a\":{\"4\":\"1\",\"7\":\"1\"},\"rep\":false},\"facebookId\":\"1375652327\",\"inventory\":{\"a\":{\"-1\":\"1\",\"0\":\"8947\",\"10\":\"1\",\"101\":\"1\",\"131\":\"1\",\"161\":\"1\",\"300\":\"1\"},\"rep\":true},\"outfit\":{\"a\":{\"1\":\"131\"},\"rep\":true},\"stats_max\":{\"a\":{\"0\":\"67\",\"2\":\"189\",\"3\":\"197\",\"4\":\"1\"},\"rep\":false},\"stats_total\":{\"a\":{\"0\":\"67\",\"1\":\"1\",\"2\":\"189\",\"3\":\"197\",\"4\":\"1\"},\"rep\":false},\"timestamp\":1408639836,\"version\":1}";//getJsonString("name", "Rajeev Ranjan", "role", "Developer");
    //storageService->InsertJsonDocument(dbName, collectionName, jsonDoc.c_str(), app42callback(TestStorageService::onStorageRequestCompleted, this));
    storageService->InsertJsonDocument(dbName, collectionName, jsonDoc.c_str(), app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::insertJsonDocumentWithApp42Object(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    
    StorageService *storageService = App42API::BuildStorageService();
    App42Object *object = new App42Object();
    object->setObject("name", "Nick");
    object->setObject("age", 30);
    
    storageService->InsertJsonDocument(dbName, collectionName, object, app42callback(TestStorageService::onStorageRequestCompleted, this));
    
    delete object;
    object = nullptr;
}

void TestStorageService::findAllCollections(Ref *sender)
{
    StorageService *storageService = App42API::BuildStorageService();
    storageService->FindAllCollections(dbName, app42callback(TestStorageService::onStorageRequestCompleted, this));
}


void TestStorageService::findAllDocuments(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    storageService->FindAllDocuments(dbName, collectionName,app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::findAllDocumentsByPaging(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    int max = 2;
    int offset = 0;
    storageService->FindAllDocuments(dbName, collectionName,max,offset,app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::findAllDocumentsCount(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    storageService->FindAllDocumentsCount(dbName, collectionName,app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::findDocumentById(Ref *sender)
{
    StorageService *storageService = App42API::BuildStorageService();
    //const char* docId = "";
    storageService->FindDocumentById(dbName, collectionName, docId, app42callback(TestStorageService::onStorageRequestCompleted, this));
}


void TestStorageService::findDocumentByQuery(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* key1 = "name";
    const char* value1 = "Nick";
    const char* key2 = "age";
    const char* value2 = "30";

    Query *query1 = QueryBuilder::BuildQuery(key1, value1, APP42_OP_EQUALS);
    Query *query2 = QueryBuilder::BuildQuery(key2, value2, APP42_OP_GREATER_THAN_EQUALTO);
    Query *query3 = QueryBuilder::CompoundOperator(query1, APP42_OP_OR, query2);
    
    storageService->FindDocumentsByQuery(dbName, collectionName,query3,app42callback(TestStorageService::onStorageRequestCompleted, this));
}
void TestStorageService::findDocumentByQueryWithPaging(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* key1 = "name";
    const char* value1 = "Nick";
    const char* key2 = "age";
    const char* value2 = "30";
    
    Query *query1 = QueryBuilder::BuildQuery(key1, value1, APP42_OP_EQUALS);
    Query *query2 = QueryBuilder::BuildQuery(key2, value2, APP42_OP_GREATER_THAN_EQUALTO);
    Query *query3 = QueryBuilder::CompoundOperator(query1, APP42_OP_OR, query2);
    int max =2;
    int offset = 0;
    storageService->FindDocumentsByQueryWithPaging(dbName, collectionName,query3,max,offset,app42callback(TestStorageService::onStorageRequestCompleted, this));
}
void TestStorageService::findDocumentByQueryWithPagingOrderBy(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* key1 = "name";
    const char* value1 = "Nick";
    const char* key2 = "age";
    const char* value2 = "30";
    
    Query *query1 = QueryBuilder::BuildQuery(key1, value1, APP42_OP_EQUALS);
    Query *query2 = QueryBuilder::BuildQuery(key2, value2, APP42_OP_GREATER_THAN_EQUALTO);
    Query *query3 = QueryBuilder::CompoundOperator(query1, APP42_OP_OR, query2);
    int max =2;
    int offset = 0;

    storageService->FindDocsWithQueryPagingOrderBy(dbName, collectionName,query3,max,offset,key1,APP42_ORDER_ASCENDING,app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::findDocumentsByKeyValue(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* key="name";
    const char* value = "Rajeev Ranjan";
    storageService->FindDocumentByKeyValue(dbName, collectionName,key,value,app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::findDocsByKeyValueByOrder(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    
    map<string,string>otherMetaHeaders;
    otherMetaHeaders["orderByAscending"] = "age";
    const char* key="name";
    const char* value = "Nick";
    storageService->FindDocumentByKeyValue(dbName, collectionName,key,value,app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::deleteDocumentById(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* docId = "538c4fafe4b0b33395a73eef";
    storageService->DeleteDocumentsById(dbName, collectionName,docId,app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::deleteDocumentByKeyValue(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* key = "role";
    const char* value = "Developer";
    storageService->DeleteDocumentsByKeyValue(dbName, collectionName,key,value,app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::deleteAllDocuments(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    storageService->DeleteAllDocuments(dbName, collectionName,app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::addOrUpdateKeys(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    //string jsonDoc = getJsonString("name", "Rajeev Ranjan", "age", "31");
    const char* docId = "docId";
    const char* jsonDoc = "{\"name\":\"Nick\",\"age\":30,\"phone\":\"xxx-xxx-xxx\"}";
    storageService->AddOrUpdateKeys(dbName, collectionName, docId, jsonDoc, app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::addOrUpdateKeysWithApp42Object(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    
    const char* docId = "docId";
    App42Object *object = new App42Object();
    object->setObject("name", "John");
    object->setObject("age", "20");
    storageService->AddOrUpdateKeys(dbName, collectionName, docId, object, app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::updateDocByKeyValue(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    //const char* jsonDoc = getJsonString("name", "Rajeev", "age", "41");

    const char* key = "name";
    const char* value = "Nick";
    const char* jsonDoc = "{\"Company\":\"Shephertz Technologies\"}";
    
    storageService->UpdateDocumentByKeyValue(dbName, collectionName, key, value, jsonDoc, app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::updateApp42DocByKeyValue(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* key = "name";
    const char* value = "Nick";
    App42Object *object = new App42Object();
    object->setObject("name", "John");
    object->setObject("age", "20");
    
    storageService->UpdateDocumentByKeyValue(dbName, collectionName, key, value, object, std::bind(&TestStorageService::onStorageRequestCompleted, this, std::placeholders::_1));
    
    delete object;
    object = nullptr;
}



void TestStorageService::updateDocByDocID(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    //string jsonDoc = getJsonString("name", "Rajeev Ranjan", "age", "31");
    const char* docId = "533e5c89e4b0ae7acf86b1f0";
    const char* jsonDoc = "{\"Company\":\"Shephertz Technologies\"}";
    storageService->UpdateDocumentByDocId(dbName, collectionName, docId, jsonDoc, app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::updateApp42DocByDocId(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* docId = "docId";
    App42Object *object = new App42Object();
    object->setObject("name", "John");
    object->setObject("age", "20");
    
    storageService->UpdateDocumentByDocId(dbName, collectionName, docId, object, app42callback(TestStorageService::onStorageRequestCompleted, this));
    
    delete object;
    object = nullptr;
}

void TestStorageService::saveOrUpdateDocumentByKeyValue(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    //string jsonDoc = getJsonString("name", "Rajeev", "age", "41");
    
    const char* key = "name";
    const char* value = "Nick";
    const char* jsonDoc = "{\"Company\":\"Shephertz Technologies\"}";
    storageService->SaveOrUpdateDocumentByKeyValue(dbName, collectionName, key, value, jsonDoc, app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::saveOrUpdateApp42DocumentByKeyValue(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* key = "name";
    const char* value = "Nick";
    
    App42Object *object = new App42Object();
    object->setObject("name", "John");
    object->setObject("age", "20");
    
    storageService->SaveOrUpdateDocumentByKeyValue(dbName, collectionName, key, value, object, app42callback(TestStorageService::onStorageRequestCompleted, this));
    
    delete object;
    object = nullptr;
}


void TestStorageService::updateDocumentByQuery(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    //string jsonDoc = getJsonString("name", "Rajeev", "age", "41");
    
    const char* key1 = "name";
    const char* value1 = "Nick";
    const char* key2 = "age";
    const char* value2 = "30";
    
    Query *query1 = QueryBuilder::BuildQuery(key1, value1, APP42_OP_EQUALS);
    Query *query2 = QueryBuilder::BuildQuery(key2, value2, APP42_OP_GREATER_THAN_EQUALTO);
    Query *query3 = QueryBuilder::CompoundOperator(query1, APP42_OP_OR, query2);

    const char* jsonDoc = "{\"Company\":\"Shephertz Technologies\"}";
    
    storageService->UpdateDocumentByQuery(dbName, collectionName, query3, jsonDoc, app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::updateDocumentWithApp42ObjectByQuery(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    
    const char* key1 = "name";
    const char* value1 = "Nick";
    const char* key2 = "age";
    const char* value2 = "30";
    
    Query *query1 = QueryBuilder::BuildQuery(key1, value1, APP42_OP_EQUALS);
    Query *query2 = QueryBuilder::BuildQuery(key2, value2, APP42_OP_GREATER_THAN_EQUALTO);
    Query *query3 = QueryBuilder::CompoundOperator(query1, APP42_OP_OR, query2);


    
    App42Object *object = new App42Object();
    object->setObject("name", "Rajeev");
    object->setObject("age", "30");
    
    storageService->UpdateDocumentByQuery(dbName, collectionName, query3, object, app42callback(TestStorageService::onStorageRequestCompleted, this));
    
    delete object;
    object = nullptr;
}


void TestStorageService::grantAccessOnDoc(Ref* sender)
{
    StorageService *storageService = App42API::BuildStorageService();
    const char* docId = "53d226cae4b006982eab6b65";
    vector<App42ACL>App42ACLList;
    App42ACL *App42ACL1 = new App42ACL("Rajeev",R);
    App42ACLList.push_back(*App42ACL1);
    
    App42ACL *App42ACL2 = new App42ACL("Ranjan",W);
    //App42ACLList.push_back(*App42ACL2);
    storageService->setAdminKey(APP_ADMIN_KEY);
    App42API::setLoggedInUser("RajeevDevice");
    storageService->GrantAccessOnDoc(dbName, collectionName, docId, App42ACLList, app42callback(TestStorageService::onStorageRequestCompleted, this));
}

void TestStorageService::revokeAccessOnDoc(Ref* sender)
{
    StorageService *storageService = App42API::BuildStorageService();
    
    const char* docId = "53d226cae4b006982eab6b65";
    vector<App42ACL>App42ACLList;
    App42ACL *App42ACL1 = new App42ACL("Rajeev",R);
    App42ACLList.push_back(*App42ACL1);
    
    App42ACL *App42ACL2 = new App42ACL("Ranjan",W);
    App42ACLList.push_back(*App42ACL2);
    
    storageService->RevokeAccessOnDoc(dbName, collectionName, docId, App42ACLList, app42callback(TestStorageService::onStorageRequestCompleted, this));
}

/***
 * Callbacks
 */

void TestStorageService::onStorageRequestCompleted( void *response)
{
    App42StorageResponse *storageResponse = (App42StorageResponse*)response;
    printf("\ncode=%d",storageResponse->getCode());
    printf("\nResponse Body=%s",storageResponse->getBody().c_str());
    
    string code = StringUtils::format("Code = %d",storageResponse->getCode());
    //layer->loadResponse(code);
    responseArray.push_back(code);
    if (storageResponse->isSuccess)
    {
        printf("\nTotalRecords=%d",storageResponse->getTotalRecords());
        for(std::vector<App42Storage>::iterator it = storageResponse->storages.begin(); it != storageResponse->storages.end(); ++it)
        {
            printf("\n DbName=%s",it->dbName.c_str());
            printf("\n CollectionName=%s",it->collectionName.c_str());
            printf("\n RecordCount=%lf\n",it->recordCount);
            string db = StringUtils::format("DbName = %s....Collection = %s",it->dbName.c_str(),it->collectionName.c_str());
            //layer->loadResponse(db);
            responseArray.push_back(db);
            for(std::vector<JSONDocument>::iterator iit = it->jsonDocArray.begin(); iit != it->jsonDocArray.end(); ++iit)
            {
                docId = iit->getDocId().c_str();
                string createdAt = StringUtils::format("CreatedAt = %s",iit->getCreatedAt().c_str());
                printf("\n CreatedAt=%s",createdAt.c_str());
                //layer->loadResponse(createdAt);
                responseArray.push_back(createdAt);
                
                string documentId = StringUtils::format("DocId = %s",iit->getDocId().c_str());
                //layer->loadResponse(documentId);
                responseArray.push_back(documentId);
                
                printf("\n DocId=%s",iit->getDocId().c_str());
                
                printf("\n Event=%s",iit->getEvent().c_str());
                printf("\n Owner=%s",iit->getOwner().c_str());
                printf("\n UpdatedAt=%s",iit->getUpdatedAt().c_str());
                printf("\n JsonDoc=%s\n",iit->getJsonDoc().c_str());
                string jsonDoc = StringUtils::format("JsonDoc = %s",iit->getJsonDoc().c_str());
                //layer->loadResponse(jsonDoc);
                responseArray.push_back(jsonDoc);
                
                vector<App42ACL>app42ACLList = iit->getApp42ACLList();
                for(std::vector<App42ACL>::iterator app42ACL = app42ACLList.begin(); app42ACL != app42ACLList.end(); ++app42ACL)
                {
                    printf("\n Name=%s",app42ACL->getUserName().c_str());
                   printf("\n Permission=%s",app42ACL->getPermission().c_str());
                }
            }
        }
    }
    else
    {
        printf("\nerrordetails:%s",storageResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",storageResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",storageResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",storageResponse->httpErrorCode);
        string error = StringUtils::format("Error = %s",storageResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",storageResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    
    
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestStorageService::loadResponseScene, this));
    
}

void TestStorageService::loadResponseScene()
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


void TestStorageService::menuCloseCallback(Ref* pSender)
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