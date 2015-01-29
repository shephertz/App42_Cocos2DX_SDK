//
//  TestAvatarService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 02/07/14.
//
//

#include "TestAvatarService.h"


#define GO_HOME 112



USING_NS_CC;

long fileDataLength;

unsigned char* copyfile( const char* srcfilename)
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
    
    fileDataLength = len;
    fclose( fp );
    
    //free( buf );
    return buf;
}


Scene* TestAvatarService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestAvatarService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestAvatarService::init()
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
                                                CC_CALLBACK_1(TestAvatarService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * CreateAvatar
     */
    auto createAvatarLabel = LabelTTF::create("CreateAvatar", "Marker Felt", 24);
    createAvatarLabel->setColor(Color3B::WHITE);
    auto createAvatarItem  = MenuItemLabel::create(createAvatarLabel, CC_CALLBACK_1(TestAvatarService::createAvatar, this));
    createAvatarItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * CreateAvatarFromFileData
     */
    auto createAvatarFromFileDataLabel = LabelTTF::create("CreateAvatarFromFileData", "Marker Felt", 24);
    createAvatarFromFileDataLabel->setColor(Color3B::WHITE);
    auto createAvatarFromFileDataItem  = MenuItemLabel::create(createAvatarFromFileDataLabel, CC_CALLBACK_1(TestAvatarService::createAvatarWithFileData, this));
    y_pos -= button_y_Offset;
    createAvatarFromFileDataItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * CreateAvatarFromFacebook
     */
    auto createAvatarFromFacebookLabel = LabelTTF::create("CreateAvatarFromFacebook", "Marker Felt", 24);
    createAvatarFromFacebookLabel->setColor(Color3B::WHITE);
    auto createAvatarFromFacebookItem  = MenuItemLabel::create(createAvatarFromFacebookLabel, CC_CALLBACK_1(TestAvatarService::createAvatarFromFacebook, this));
    y_pos -= button_y_Offset;
    createAvatarFromFacebookItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * CreateAvatarFromWebUrl
     */
    auto createAvatarFromWebUrlLabel = LabelTTF::create("CreateAvatarFromWebUrl", "Marker Felt", 24);
    createAvatarFromWebUrlLabel->setColor(Color3B::WHITE);
    auto createAvatarFromWebUrlItem  = MenuItemLabel::create(createAvatarFromWebUrlLabel, CC_CALLBACK_1(TestAvatarService::createAvatarFromWebUrl, this));
    y_pos -= button_y_Offset;
    createAvatarFromWebUrlItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAvatarByName
     */
    auto getAvatarByNameLabel = LabelTTF::create("GetAvatarByName", "Marker Felt", 24);
    getAvatarByNameLabel->setColor(Color3B::WHITE);
    auto getAvatarByNameItem  = MenuItemLabel::create(getAvatarByNameLabel, CC_CALLBACK_1(TestAvatarService::getAvatarByName, this));
    y_pos -= button_y_Offset;
    getAvatarByNameItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetAllAvatars
     */
    auto getAllAvatarsLabel = LabelTTF::create("GetAllAvatars", "Marker Felt", 24);
    getAvatarByNameLabel->setColor(Color3B::WHITE);
    auto getAllAvatarsItem  = MenuItemLabel::create(getAllAvatarsLabel, CC_CALLBACK_1(TestAvatarService::getAllAvatars, this));
    y_pos -= button_y_Offset;
    getAllAvatarsItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetCurrentAvatar
     */
    auto getCurrentAvatarLabel = LabelTTF::create("GetCurrentAvatar", "Marker Felt", 24);
    getCurrentAvatarLabel->setColor(Color3B::WHITE);
    auto getCurrentAvatarItem  = MenuItemLabel::create(getCurrentAvatarLabel, CC_CALLBACK_1(TestAvatarService::getCurrentAvatar, this));
    y_pos -= button_y_Offset;
    getCurrentAvatarItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * ChangeCurrentAvatar
     */
    auto changeCurrentAvatarLabel = LabelTTF::create("ChangeCurrentAvatar", "Marker Felt", 24);
    changeCurrentAvatarLabel->setColor(Color3B::WHITE);
    auto changeCurrentAvatarItem  = MenuItemLabel::create(changeCurrentAvatarLabel, CC_CALLBACK_1(TestAvatarService::changeCurrentAvatar, this));
    y_pos -= button_y_Offset;
    changeCurrentAvatarItem->setPosition(Point(x_pos,y_pos));

	

    // create menu, it's an autorelease object
    auto menu = Menu::create(backButtonItem,
                             createAvatarItem,
                             createAvatarFromFileDataItem,
                             createAvatarFromFacebookItem,
                             createAvatarFromWebUrlItem,
                             getAvatarByNameItem,
                             getAllAvatarsItem,
                             getCurrentAvatarItem,
                             changeCurrentAvatarItem,NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void TestAvatarService::createAvatar(Ref* sender)
{
    AvatarService *avatarService = App42API::BuildAvatarService();
    string filePath = FileUtils::getInstance()->fullPathForFilename("BackButton.png");
    const char* avatarName = "Shephertz Nick1";
    const char* userName = "Nick";
    //const char* filePath = "Your File Path";
    const char* description = "My Profile Pic";

    avatarService->CreateAvatar(avatarName, userName, filePath.c_str(), description, app42callback(TestAvatarService::onAvatarServiceRequestCompleted, this));
}



void TestAvatarService::createAvatarWithFileData(Ref *sender)
{
    AvatarService *avatarService = App42API::BuildAvatarService();
    
    const char* avatarName = "Shephertz Nick";
    const char* userName = "Nick";
    string filePath = FileUtils::getInstance()->fullPathForFilename("BackButton.png");;
    const char* description = "Testing create avatar from cocos2d-x sdk";
    
    FileExtension fileExtension = PNG;
    unsigned char* imageData = copyfile(filePath.c_str());
    
    avatarService->CreateAvatar(avatarName, userName, imageData, fileDataLength, description, fileExtension, app42callback(TestAvatarService::onAvatarServiceRequestCompleted, this));
    
}

void TestAvatarService::createAvatarFromFacebook(Ref* sender)
{
    AvatarService *avatarService = App42API::BuildAvatarService();
    
    const char* avatarName = "Ranjan009";
    const char* userName = "Rajeev";
    const char* description = "Testing create avatar from cocos2d-x sdk";
    const char* accessToken = "CAACEdEose0cBAB9Uv1WI9PVsZBOStXZB0VZBmBiMcdg92rw79iMjw0QzCiXdLCZCtHd0qZBVDJZBYncJr69rUf7X6w1UKFAdHHsaGlLwxvctSHxQOb53Cz5I60ZAth0kUbZBZCKmv7rJygZATfDPUnhp1rl4rCF1iFwc8DuLfRzYZC17w1WAum0V6NM4vauzJgqgAq37N3zChMSXAZDZD";
    avatarService->CreateAvatarFromFacebook(avatarName, userName, accessToken, description, app42callback(TestAvatarService::onAvatarServiceRequestCompleted, this));
}

void TestAvatarService::createAvatarFromWebUrl(Ref* sender)
{
    AvatarService *avatarService = App42API::BuildAvatarService();
    
    const char* avatarName = "Ranjan";
    const char* userName = "Rajeev";
    const char* webUrl = "http://tinyurl.com/kzkverz";
    const char* description = "Testing create avatar from cocos2d-x sdk";
    
    avatarService->CreateAvatarFromWebURL(avatarName, userName, webUrl, description, app42callback(TestAvatarService::onAvatarServiceRequestCompleted, this));
}

void TestAvatarService::getAvatarByName(Ref* sender)
{
    AvatarService *avatarService = App42API::BuildAvatarService();
    
    const char* avatarName = "Shephertz Nick";
    const char* userName = "Nick";
    
    avatarService->GetAvatarByName(avatarName, userName, app42callback(TestAvatarService::onAvatarServiceRequestCompleted, this));
}

void TestAvatarService::getAllAvatars(Ref* sender)
{
    AvatarService *avatarService = App42API::BuildAvatarService();
    
    const char* userName = "Rajeev";
    avatarService->GetAllAvatars(userName, app42callback(TestAvatarService::onAvatarServiceRequestCompleted, this));
}

void TestAvatarService::getCurrentAvatar(Ref *sender)
{
    AvatarService *avatarService = App42API::BuildAvatarService();
    
    const char* userName = "Rajeev";
    avatarService->GetCurrentAvatar(userName, app42callback(TestAvatarService::onAvatarServiceRequestCompleted, this));
}

void TestAvatarService::changeCurrentAvatar(Ref *sender)
{
    AvatarService *avatarService = App42API::BuildAvatarService();
    
    const char* avatarName = "Ranjan";
    const char* userName = "Rajeev";
    avatarService->ChangeCurrentAvatar(avatarName, userName, app42callback(TestAvatarService::onAvatarServiceRequestCompleted, this));
}

/**
 * Callback Methods
 */
void TestAvatarService::onAvatarServiceRequestCompleted( void *response)
{
    App42AvatarResponse *app42AvatarResponse = (App42AvatarResponse*)response;
    string code = StringUtils::format("Code = %d",app42AvatarResponse->getCode());
    responseArray.push_back(code);
    
    if(app42AvatarResponse->isSuccess)
    {
        printf("\ncode=%d",app42AvatarResponse->getCode());
        printf("\nisSuccess=%d",app42AvatarResponse->isSuccess);
        printf("\nResponse Body=%s",app42AvatarResponse->getBody().c_str());
        
        for(std::vector<App42Avatar>::iterator it = app42AvatarResponse->avatars.begin(); it != app42AvatarResponse->avatars.end(); ++it)
        {
            printf("\n UserName=%s",it->userName.c_str());
            printf("\n AvatarName=%s\n",it->name.c_str());
            printf("\n URL=%s\n",it->url.c_str());
            printf("\n TinyURL=%s\n",it->tinyUrl.c_str());
            printf("\n CreatedOn=%s\n",it->createdOn.c_str());
            printf("\n Description=%s\n",it->description.c_str());
            printf("\n isCurrent=%d\n",it->isCurrent);
        }
    }
    else
    {
        printf("\nerrordetails:%s",app42AvatarResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",app42AvatarResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",app42AvatarResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",app42AvatarResponse->httpErrorCode);
        string error = StringUtils::format("Error = %s",app42AvatarResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",app42AvatarResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestAvatarService::loadResponseScene, this));
    
}

void TestAvatarService::loadResponseScene()
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

void TestAvatarService::menuCloseCallback(Ref* pSender)
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

