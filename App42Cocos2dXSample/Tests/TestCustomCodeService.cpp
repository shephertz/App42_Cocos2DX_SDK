//
//  TestCustomCodeService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 14/05/14.
//
//

#include "TestCustomCodeService.h"
#include "TestHome.h"


#define GO_HOME 109



USING_NS_CC;

Scene* TestCustomCodeService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestCustomCodeService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestCustomCodeService::init()
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
                                                CC_CALLBACK_1(TestCustomCodeService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * Run Java Code
     */
    auto runJavaCodeLabel = LabelTTF::create("RunJavaCode", "Marker Felt", 24);
    runJavaCodeLabel->setColor(Color3B::WHITE);
    auto runJavaCodeItem  = MenuItemLabel::create(runJavaCodeLabel, CC_CALLBACK_1(TestCustomCodeService::runJavaCode, this));
    runJavaCodeItem->setPosition(Point(x_pos,y_pos));
    
    

 	

    
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(backButtonItem,
                             runJavaCodeItem,
                              NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}



void TestCustomCodeService::runJavaCode(Ref *sender)
{
    CustomCodeService *customCodeService = App42API::BuildCustomCodeService();

    //App42API::setIsTraceEnabled(true);
    
    const char* name = "DEPLOYED_CUSTOM_CODE_NAME";
    App42Object *object = new App42Object();
    object->setObject("Company", "Shephertz");
    object->setObject("secretKey", SECRET_KEY);
    object->setObject("moduleName", "Demo");
    object->setObject("userName", "Rajeev");
    
    printf("\n%s",object->toString().c_str());
    
    customCodeService->RunJavaCode(name, object, app42callback(TestCustomCodeService::onCustomCodeServiceRequestCompleted, this));
    
    delete object;
    object = nullptr;
}


/**
 * Callback Methods
 */
void TestCustomCodeService::onCustomCodeServiceRequestCompleted( void *response)
{
    App42CustomCodeResponse *customCodeResponse = (App42CustomCodeResponse*)response;
    string code = StringUtils::format("Code = %d",customCodeResponse->getCode());
    responseArray.push_back(code);
    if(customCodeResponse->isSuccess)
    {
        printf("\n code=%d",customCodeResponse->getCode());
        printf("\n isSuccess=%d",customCodeResponse->isSuccess);
        printf("\n Response Body=%s",customCodeResponse->getBody().c_str());
    }
    else
    {
        printf("\nerrordetails:%s",customCodeResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",customCodeResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",customCodeResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",customCodeResponse->httpErrorCode);
        
        string error = StringUtils::format("Error = %s",customCodeResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",customCodeResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestCustomCodeService::loadResponseScene, this));
    
}

void TestCustomCodeService::loadResponseScene()
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

void TestCustomCodeService::menuCloseCallback(Ref* pSender)
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
