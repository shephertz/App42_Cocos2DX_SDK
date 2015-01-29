//
//  TestUploadService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 04/04/14.
//
//

#include "TestUploadService.h"
#include "TestHome.h"
#include <fstream>

#define GO_HOME 110


USING_NS_CC;

long imageDataLength;

unsigned char* copy_file( const char* srcfilename)
{
    long  len;
    unsigned char* buf = NULL;
    FILE* fp  = NULL;
    
    // Open the source file
    fp = fopen( srcfilename, "rb" );
    if (!fp) return NULL;
    
    // Get its length (in bytes)
    if (fseek( fp, 0, SEEK_END ) != 0)  // This should typically succeed
    {                                 // (beware the 2Gb limitation, though)
        fclose( fp );
        return NULL;
    }
    
    len = ftell( fp );
    rewind( fp );
    
    // Get a buffer big enough to hold it entirely
    buf = (unsigned char*)malloc( len );
    if (!buf)
    {
        fclose( fp );
        return NULL;
    }
    
    // Read the entire file into the buffer
    if (!fread( buf, len, 1, fp ))
    {
        free( buf );
        fclose( fp );
        return NULL;
    }
    
    imageDataLength = len;
    fclose( fp );
    
    //free( buf );
    return buf;
}


Scene* TestUploadService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestUploadService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestUploadService::init()
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
                                                CC_CALLBACK_1(TestUploadService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * UploadFile
     */
    auto uploadFileLabel = LabelTTF::create("UploadFile", "Marker Felt", 24);
    uploadFileLabel->setColor(Color3B::WHITE);
    auto uploadFileItem  = MenuItemLabel::create(uploadFileLabel, CC_CALLBACK_1(TestUploadService::uploadFile, this));
    uploadFileItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * UploadFileData
     */
    auto uploadFileDataLabel = LabelTTF::create("UploadFileData", "Marker Felt", 24);
    uploadFileDataLabel->setColor(Color3B::WHITE);
    auto uploadFileDataItem  = MenuItemLabel::create(uploadFileDataLabel, CC_CALLBACK_1(TestUploadService::uploadFileData, this));
    y_pos -= button_y_Offset;
    uploadFileDataItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllFiles
     */
    auto getAllFilesLabel = LabelTTF::create("GetAllFiles", "Marker Felt", 24);
    getAllFilesLabel->setColor(Color3B::WHITE);
    auto getAllFilesItem  = MenuItemLabel::create(getAllFilesLabel, CC_CALLBACK_1(TestUploadService::getAllFiles, this));
    y_pos -= button_y_Offset;
    getAllFilesItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllFilesCount
     */
    auto getAllFilesCountLabel = LabelTTF::create("GetAllFilesCount", "Marker Felt", 24);
    getAllFilesCountLabel->setColor(Color3B::WHITE);
    auto getAllFilesCountItem  = MenuItemLabel::create(getAllFilesCountLabel, CC_CALLBACK_1(TestUploadService::getAllFilesCount, this));
    y_pos -= button_y_Offset;
    getAllFilesCountItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllFilesByPaging
     */
    auto getAllFilesByPagingLabel = LabelTTF::create("GetAllFilesByPaging", "Marker Felt", 24);
    getAllFilesByPagingLabel->setColor(Color3B::WHITE);
    auto getAllFilesByPagingItem  = MenuItemLabel::create(getAllFilesByPagingLabel, CC_CALLBACK_1(TestUploadService::getAllFilesByPaging, this));
    y_pos -= button_y_Offset;
    getAllFilesByPagingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetFileByUser
     */
    auto getFileByUserLabel = LabelTTF::create("GetFileByUser", "Marker Felt", 24);
    getFileByUserLabel->setColor(Color3B::WHITE);
    auto getFileByUserItem  = MenuItemLabel::create(getFileByUserLabel, CC_CALLBACK_1(TestUploadService::getFileByUser, this));
    y_pos -= button_y_Offset;
    getFileByUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllFilesByUser
     */
    auto getAllFilesByUserLabel = LabelTTF::create("GetAllFilesByUser", "Marker Felt", 24);
    getAllFilesByUserLabel->setColor(Color3B::WHITE);
    auto getAllFilesByUserItem  = MenuItemLabel::create(getAllFilesByUserLabel, CC_CALLBACK_1(TestUploadService::getAllFilesByUser, this));
    y_pos -= button_y_Offset;
    getAllFilesByUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllFilesByUserByPaging
     */
    auto getAllFilesByUserByPagingLabel = LabelTTF::create("GetAllFilesByUserByPaging", "Marker Felt", 24);
    getAllFilesByUserByPagingLabel->setColor(Color3B::WHITE);
    auto getAllFilesByUserByPagingItem  = MenuItemLabel::create(getAllFilesByUserByPagingLabel, CC_CALLBACK_1(TestUploadService::getAllFilesByUserByPaging, this));
    y_pos -= button_y_Offset;
    getAllFilesByUserByPagingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllFilesCountByUser
     */
    auto getAllFilesCountByUserLabel = LabelTTF::create("GetAllFilesCountByUser", "Marker Felt", 24);
    getAllFilesCountByUserLabel->setColor(Color3B::WHITE);
    auto getAllFilesCountByUserItem  = MenuItemLabel::create(getAllFilesCountByUserLabel, CC_CALLBACK_1(TestUploadService::getAllFilesCountByUser, this));
    y_pos -= button_y_Offset;
    getAllFilesCountByUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetFileByName
     */
    auto getFileByNameLabel = LabelTTF::create("GetFileByName", "Marker Felt", 24);
    getFileByNameLabel->setColor(Color3B::WHITE);
    auto getFileByNameItem  = MenuItemLabel::create(getFileByNameLabel, CC_CALLBACK_1(TestUploadService::getFileByName, this));
    y_pos -= button_y_Offset;
    getFileByNameItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * RemoveFileByUser
     */
    auto removeFileByUserLabel = LabelTTF::create("RemoveFileByUser", "Marker Felt", 24);
    removeFileByUserLabel->setColor(Color3B::WHITE);
    auto removeFileByUserItem  = MenuItemLabel::create(removeFileByUserLabel, CC_CALLBACK_1(TestUploadService::removeFileByUser, this));
    y_pos -= button_y_Offset;
    removeFileByUserItem->setPosition(Point(x_pos,y_pos));

    /**
     * RemoveAllFilesByUser
     */
    auto removeAllFilesByUserLabel = LabelTTF::create("RemoveAllFilesByUser", "Marker Felt", 24);
    removeAllFilesByUserLabel->setColor(Color3B::WHITE);
    auto removeAllFilesByUserItem  = MenuItemLabel::create(removeAllFilesByUserLabel, CC_CALLBACK_1(TestUploadService::removeAllFilesByUser, this));
    y_pos -= button_y_Offset;
    removeAllFilesByUserItem->setPosition(Point(x_pos,y_pos));

    /**
     * RemoveFileByName
     */
    auto removeFileByNameLabel = LabelTTF::create("RemoveFileByName", "Marker Felt", 24);
    removeFileByNameLabel->setColor(Color3B::WHITE);
    auto removeFileByNameItem  = MenuItemLabel::create(removeFileByNameLabel, CC_CALLBACK_1(TestUploadService::removeFileByName, this));
    y_pos -= button_y_Offset;
    removeFileByNameItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * RemoveAllFiles
     */
    auto removeAllFilesLabel = LabelTTF::create("RemoveAllFiles", "Marker Felt", 24);
    removeAllFilesLabel->setColor(Color3B::WHITE);
    auto removeAllFilesItem  = MenuItemLabel::create(removeAllFilesLabel, CC_CALLBACK_1(TestUploadService::removeAllFiles, this));
    y_pos -= button_y_Offset;
    removeAllFilesItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetFilesCountByType
     */
    auto getFilesCountByTypeLabel = LabelTTF::create("GetFilesCountByType", "Marker Felt", 24);
    getFilesCountByTypeLabel->setColor(Color3B::WHITE);
    auto getFilesCountByTypeItem  = MenuItemLabel::create(getFilesCountByTypeLabel, CC_CALLBACK_1(TestUploadService::getFilesCountByType, this));
    y_pos -= button_y_Offset;
    getFilesCountByTypeItem->setPosition(Point(x_pos,y_pos));
    
    y_pos = visibleSize.height-button_y_Offset;
    x_pos = origin.x + 3*visibleSize.width/4;
    /**
     * GetFilesByType
     */
    auto getFilesByTypeLabel = LabelTTF::create("GetFilesByType", "Marker Felt", 24);
    getFilesByTypeLabel->setColor(Color3B::WHITE);
    auto getFilesByTypeItem  = MenuItemLabel::create(getFilesByTypeLabel, CC_CALLBACK_1(TestUploadService::getFilesByType, this));
    y_pos -= button_y_Offset;
    getFilesByTypeItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetFilesByTypeByPaging
     */
    auto getFilesByTypeByPagingLabel = LabelTTF::create("GetFilesByTypeByPaging", "Marker Felt", 24);
    getFilesByTypeByPagingLabel->setColor(Color3B::WHITE);
    auto getFilesByTypeByPagingItem  = MenuItemLabel::create(getFilesByTypeByPagingLabel, CC_CALLBACK_1(TestUploadService::getFilesByTypeByPaging, this));
    y_pos -= button_y_Offset;
    getFilesByTypeByPagingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * UploadFileForUser
     */
    auto uploadFileForUserLabel = LabelTTF::create("UploadFileForUser", "Marker Felt", 24);
    uploadFileForUserLabel->setColor(Color3B::WHITE);
    auto uploadFileForUserItem  = MenuItemLabel::create(uploadFileForUserLabel, CC_CALLBACK_1(TestUploadService::uploadFileForUser, this));
    y_pos -= button_y_Offset;
    uploadFileForUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * UploadFileForDataUser
     */
    auto uploadFileDataForUserLabel = LabelTTF::create("UploadFileDataForUser", "Marker Felt", 24);
    uploadFileDataForUserLabel->setColor(Color3B::WHITE);
    auto uploadFileDataForUserItem  = MenuItemLabel::create(uploadFileDataForUserLabel, CC_CALLBACK_1(TestUploadService::uploadFileDataForUser, this));
    y_pos -= button_y_Offset;
    uploadFileDataForUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GrantAccess
     */
    auto grantAccessLabel = LabelTTF::create("GrantAccess", "Marker Felt", 24);
    grantAccessLabel->setColor(Color3B::WHITE);
    auto grantAccessItem  = MenuItemLabel::create(grantAccessLabel, CC_CALLBACK_1(TestUploadService::grantAccess, this));
    y_pos -= button_y_Offset;
    grantAccessItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * RevokeAccess
     */
    auto revokeAccessLabel = LabelTTF::create("RevokeAccess", "Marker Felt", 24);
    revokeAccessLabel->setColor(Color3B::WHITE);
    auto revokeAccessItem  = MenuItemLabel::create(revokeAccessLabel, CC_CALLBACK_1(TestUploadService::revokeAccess, this));
    y_pos -= button_y_Offset;
    revokeAccessItem->setPosition(Point(x_pos,y_pos));

 	   

    
    // create menu, it's an autorelease object
    auto menu = Menu::create(backButtonItem,
                             uploadFileItem,
                             uploadFileDataItem,
                             getAllFilesItem,
                             getAllFilesCountItem,
                             getAllFilesByPagingItem,
                             getFileByUserItem, NULL);

	auto menu1 = Menu::create(
                             getAllFilesByUserItem,
                             getAllFilesCountByUserItem,
                             getAllFilesByUserByPagingItem,
                             getFileByNameItem,
                             removeFileByUserItem,
                             removeAllFilesByUserItem,
                             removeFileByNameItem, NULL);

	auto menu2 = Menu::create(
                             removeAllFilesItem,
                             getFilesCountByTypeItem,
                             getFilesByTypeItem,
                             getFilesByTypeByPagingItem,
                             uploadFileForUserItem,
                             uploadFileDataForUserItem,
                             grantAccessItem,
                             revokeAccessItem, NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	menu1->setPosition(Point::ZERO);
    this->addChild(menu1, 1);

	menu2->setPosition(Point::ZERO);
    this->addChild(menu2, 1);
    
    return true;
}


void TestUploadService::uploadFile(Ref *sender)
{
    UploadService *uploadService = App42API::BuildUploadService();
    uploadService->setAdminKey(APP_ADMIN_KEY);
    string filePath = FileUtils::getInstance()->fullPathForFilename("BackButton.png");
    //App42API::setLoggedInUser("Nick");
    const char* fileName = "BackButton11";//"<Your_file_name>";
    //const char* filePath = "Your Local File Path";
    const char* description = "File Description";
    FileType fileType = IMAGE;
    
    uploadService->UploadFile(fileName, filePath.c_str(), fileType, description, app42callback(TestUploadService::onUploadRequestCompleted, this));
}

void TestUploadService::uploadFileData(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    
    const char* fileName = "BackButtonabcd";
    string filePath = FileUtils::getInstance()->fullPathForFilename("BackButton.png");
    FileType fileType = IMAGE;
    const char* description = "File Description";
    unsigned char* imageData = copy_file(filePath.c_str());
    uploadService->UploadFile(fileName, imageData,imageDataLength, fileType, description, app42callback(TestUploadService::onUploadRequestCompleted, this));
}

void TestUploadService::getAllFiles(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    uploadService->GetAllFiles(app42callback(TestUploadService::onUploadRequestCompleted, this));
}

void TestUploadService::getAllFilesCount(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    uploadService->GetAllFilesCount(app42callback(TestUploadService::onUploadRequestCompleted, this));
}

void TestUploadService::getAllFilesByPaging(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    int max = 2;
    int offset = 0;
    uploadService->GetAllFiles(max, offset,app42callback(TestUploadService::onUploadRequestCompleted, this));
}

void TestUploadService::getFileByUser(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    
    const char* fileName = "BackButton";
    const char* userName = "Nick";
    uploadService->GetFileByUser(fileName, userName,app42callback(TestUploadService::onUploadRequestCompleted, this));
}


void TestUploadService::getAllFilesByUser(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    
    const char* userName = "Nick";
    uploadService->GetAllFilesByUser(userName, app42callback(TestUploadService::onUploadRequestCompleted, this));
}

void TestUploadService::getAllFilesByUserByPaging(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    
    const char* userName = "Nick";
    int max = 2;
    int offset = 0;
    uploadService->GetAllFilesByUser(userName, max,offset, app42callback(TestUploadService::onUploadRequestCompleted, this));
}

void TestUploadService::getAllFilesCountByUser(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    
    const char* userName = "Nick";
    uploadService->GetAllFilesCountByUser(userName,app42callback(TestUploadService::onUploadRequestCompleted, this));
}

void TestUploadService::getFileByName(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    
    const char* fileName = "image2.png";
    uploadService->GetFileByName(fileName,app42callback(TestUploadService::onUploadRequestCompleted, this));
}

void TestUploadService::removeFileByUser(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    
    const char* fileName = "BackButton";
    const char* userName = "Nick";

    uploadService->RemoveFileByUser(fileName,userName,app42callback(TestUploadService::onUploadRequestCompleted, this));
}
void TestUploadService::removeAllFilesByUser(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    
    const char* userName = "userName09";
    uploadService->RemoveAllFilesByUser(userName,app42callback(TestUploadService::onUploadRequestCompleted, this));
}
void TestUploadService::removeFileByName(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    
    const char* fileName = "BackButton11.png";
    uploadService->RemoveFileByName(fileName,app42callback(TestUploadService::onUploadRequestCompleted, this));
}
void TestUploadService::removeAllFiles(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    
    uploadService->RemoveAllFiles(app42callback(TestUploadService::onUploadRequestCompleted, this));
}

void TestUploadService::getFilesCountByType(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    FileType fileType = IMAGE;
    uploadService->GetFilesCountByType(fileType,app42callback(TestUploadService::onUploadRequestCompleted, this));
}
void TestUploadService::getFilesByType(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    FileType fileType = IMAGE;
    uploadService->GetFilesByType(fileType,app42callback(TestUploadService::onUploadRequestCompleted, this));
}
void TestUploadService::getFilesByTypeByPaging(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    int max = 2;
    int offset = 0;
    FileType fileType = IMAGE;
    uploadService->GetFilesByType(fileType,max,offset,app42callback(TestUploadService::onUploadRequestCompleted, this));
}
void TestUploadService::uploadFileForUser(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    //uploadService->setAdminKey(APP_ADMIN_KEY);

    const char* fileName = "BackButton1112";
    const char* userName = "Nick2434";
    App42API::setUserSessionId("1fd666f7-03d1-4553-bed6-a3a9575a7e16");
    
    string filePath = FileUtils::getInstance()->fullPathForFilename("BackButton.png");
    FileType fileType = IMAGE;
    const char* description = "Image file";
    
    printf("\nfilePath=%s\n",filePath.c_str());
    
    uploadService->UploadFileForUser(fileName,userName, filePath.c_str(), fileType, description, app42callback(TestUploadService::onUploadRequestCompleted, this));
}
void TestUploadService::uploadFileDataForUser(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    UploadService *uploadService = App42API::BuildUploadService();
    
    const char* fileName = "BackButton";
    const char* userName = "Nick";
    string filePath = FileUtils::getInstance()->fullPathForFilename("BackButton.png");
    FileType fileType = IMAGE;
    const char* description = "Image file";
    
    unsigned char* imageData = copy_file(filePath.c_str());
    
    printf("dataBytes=%s..size=%zd",imageData,imageDataLength);
    uploadService->UploadFileForUser(fileName,userName, imageData,imageDataLength, fileType, description, app42callback(TestUploadService::onUploadRequestCompleted, this));
}

void TestUploadService::grantAccess(Ref* sender)
{
    UploadService *uploadService = App42API::BuildUploadService();
    
    const char* fileName = "BackButton1112";
    const char* userName = "Nick2434";
    App42API::setUserSessionId("1fd666f7-03d1-4553-bed6-a3a9575a7e16");
    
    vector<App42ACL>App42ACLList;
    App42ACL *App42ACL1 = new App42ACL("Rajeev",R);
    App42ACLList.push_back(*App42ACL1);
    
    uploadService->GrantAccess(fileName, userName, App42ACLList, app42callback(TestUploadService::onUploadRequestCompleted, this));
}
void TestUploadService::revokeAccess(Ref* sender)
{
    UploadService *uploadService = App42API::BuildUploadService();
    
    const char* fileName = "BackButton1112";
    const char* userName = "Nick2434";
    App42API::setUserSessionId("1fd666f7-03d1-4553-bed6-a3a9575a7e16");
    
    vector<App42ACL>App42ACLList;
    App42ACL *App42ACL1 = new App42ACL("Rajeev",R);
    App42ACLList.push_back(*App42ACL1);
    
    //uploadService->setAdminKey(APP_ADMIN_KEY);
    uploadService->RevokeAccess(fileName, userName, App42ACLList, app42callback(TestUploadService::onUploadRequestCompleted, this));
}

/**
 * Callback methods
 */

void TestUploadService::onUploadRequestCompleted( void *response)
{
    App42UploadResponse *uploadResponse = (App42UploadResponse*)response;
    printf("\ncode=%d",uploadResponse->getCode());
    printf("\nResponse Body=%s",uploadResponse->getBody().c_str());
    string code = StringUtils::format("Code = %d",uploadResponse->getCode());
    responseArray.push_back(code);
    if(uploadResponse->isSuccess)
    {
        printf("\nTotalRecords=%d",uploadResponse->getTotalRecords());
        for(std::vector<App42Upload>::iterator it = uploadResponse->uploadArray.begin(); it != uploadResponse->uploadArray.end(); ++it)
        {
            printf("\n Name=%s",it->name.c_str());
            printf("\n UserName=%s",it->userName.c_str());
            printf("\n Type=%s",it->type.c_str());
            printf("\n Description=%s",it->description.c_str());
            printf("\n TinyUrl=%s",it->tinyUrl.c_str());
            printf("\n Url=%s",it->url.c_str());
            printf("\n CreatedOn=%s",it->createdOn.c_str());
        }
    }
    else
    {
        printf("\nerrordetails :%s",uploadResponse->errorDetails.c_str());
        printf("\nerrorMessage :%s",uploadResponse->errorMessage.c_str());
        printf("\nappErrorCode :%d",uploadResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",uploadResponse->httpErrorCode);
        string error = StringUtils::format("Error = %s",uploadResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",uploadResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestUploadService::loadResponseScene, this));
    
}

void TestUploadService::loadResponseScene()
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

void TestUploadService::menuCloseCallback(Ref* pSender)
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