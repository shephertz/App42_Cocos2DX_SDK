//
//  TestEmailService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 08/04/14.
//
//

#include "TestEmailService.h"
#include "TestHome.h"


#define GO_HOME 108



USING_NS_CC;

Scene* TestEmailService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestEmailService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestEmailService::init()
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
                                                CC_CALLBACK_1(TestEmailService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * ConfigureMail
     */
    auto configureMailLabel = LabelTTF::create("ConfigureMail", "Marker Felt", 24);
    configureMailLabel->setColor(Color3B::WHITE);
    auto configureMailItem  = MenuItemLabel::create(configureMailLabel, CC_CALLBACK_1(TestEmailService::configureEmail, this));
    configureMailItem->setPosition(Point(x_pos,y_pos));

    
    /**
     * RemoveConfiguration
     */
    auto removeConfigurationLabel = LabelTTF::create("RemoveConfiguration", "Marker Felt", 24);
    removeConfigurationLabel->setColor(Color3B::WHITE);
    auto removeConfigurationItem  = MenuItemLabel::create(removeConfigurationLabel, CC_CALLBACK_1(TestEmailService::removeConfiguration, this));
    y_pos -= button_y_Offset;
    removeConfigurationItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetConfigurations
     */
    auto getConfigurationLabel = LabelTTF::create("GetConfigurations", "Marker Felt", 24);
    getConfigurationLabel->setColor(Color3B::WHITE);
    auto getConfigurationItem  = MenuItemLabel::create(getConfigurationLabel, CC_CALLBACK_1(TestEmailService::getConfiguration, this));
    y_pos -= button_y_Offset;
    getConfigurationItem->setPosition(Point(x_pos,y_pos));
    
    
    /**
     * SendMail
     */
    auto sendMailLabel = LabelTTF::create("SendMail", "Marker Felt", 24);
    sendMailLabel->setColor(Color3B::WHITE);
    auto sendMailItem  = MenuItemLabel::create(sendMailLabel, CC_CALLBACK_1(TestEmailService::sendMail, this));
    y_pos -= button_y_Offset;
    sendMailItem->setPosition(Point(x_pos,y_pos));
    
 	

    // create menu, it's an autorelease object
    auto menu = Menu::create(backButtonItem,
                             configureMailItem,
                             removeConfigurationItem,
                             getConfigurationItem,
                             sendMailItem, NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}



void TestEmailService::configureEmail(Ref *sender)
{

    EmailService *emailService = App42API::BuildEmailService();
    
    string emailHost = "smtp.gmail.com";
    int emailPort = 465;
    string emailId = "rajeev.ranjan@shephertz.co.in";
    string password = "9934273686r";
    bool isSSL = true;

    emailService->createMailConfiguration(emailHost.c_str(), emailPort, emailId.c_str(), password.c_str(), isSSL, app42callback(TestEmailService::onEmailRequestCompleted, this));
}

void TestEmailService::removeConfiguration(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    EmailService *emailService = App42API::BuildEmailService();
    string emailId = "rajeev.ranjan@shephertz.co.in";
    
    emailService->removeEmailConfiguration(emailId.c_str(),app42callback(TestEmailService::onEmailRequestCompleted, this));
}

void TestEmailService::getConfiguration(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    EmailService *emailService = App42API::BuildEmailService();
    emailService->getEmailConfigurations(app42callback(TestEmailService::onEmailRequestCompleted, this));
}

void TestEmailService::sendMail(Ref *sender)
{
    //App42API::setIsTraceEnabled(true);
    EmailService *emailService = App42API::BuildEmailService();
    
    string sendTo = "john@shephertz.co.in";
    string senderEmailId = "nick@gmail.com";
    string sendSubject = "Feedback";
    string sendMsg = "Your message";
    EmailMIME emailMime = PLAIN_TEXT_MIME_TYPE;
    emailService->sendMail(sendTo.c_str(), sendSubject.c_str(), sendMsg.c_str(),senderEmailId.c_str(),emailMime,app42callback(TestEmailService::onEmailRequestCompleted, this));
}

/**
 * Callback Methods
 */
void TestEmailService::onEmailRequestCompleted( void *response)
{
    App42EmailResponse *emailResponse = (App42EmailResponse*)response;
    printf("\ncode=%d...%d",emailResponse->getCode(),emailResponse->isSuccess);
    printf("\nResponse Body=%s",emailResponse->getBody().c_str());
    string code = StringUtils::format("Code = %d",emailResponse->getCode());
    responseArray.push_back(code);

    if(emailResponse->isSuccess)
    {
        printf("\n From=%s",emailResponse->from.c_str());
        printf("\n To=%s",emailResponse->to.c_str());
        printf("\n Subject=%s",emailResponse->subject.c_str());
        printf("\n Body=%s",emailResponse->body.c_str());
        for(std::vector<App42Configuration>::iterator it = emailResponse->configurationArray.begin(); it != emailResponse->configurationArray.end(); ++it)
        {
            printf("\n EmailId=%s",it->emailId.c_str());
            printf("\n Host=%s\n",it->host.c_str());
            printf("\n Port=%d\n",it->port);
            printf("\n SSL=%d\n",it->ssl);
        }
    }
    
    else
    {
        printf("\nerrordetails:%s",emailResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",emailResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",emailResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",emailResponse->httpErrorCode);
        
        string error = StringUtils::format("Error = %s",emailResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",emailResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestEmailService::loadResponseScene, this));
    
}

void TestEmailService::loadResponseScene()
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


void TestEmailService::menuCloseCallback(Ref* pSender)
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


/**** Remove Configuration

 void TestEmailService::onEmailRequestCompleted( void *response)
 {
     App42EmailResponse *emailResponse = (App42EmailResponse*)response;
     printf("\ncode=%d...%d",emailResponse->getCode(),emailResponse->isSuccess);
     printf("\nResponse Body=%s",emailResponse->getBody().c_str());
     
     if(emailResponse->isSuccess)
     {
         for(std::vector<App42Configuration>::iterator it = emailResponse->configurationArray.begin(); it != emailResponse->configurationArray.end(); ++it)
         {
             printf("\n EmailId=%s",it->emailId.c_str());
             printf("\n Host=%s\n",it->host.c_str());
             printf("\n Port=%d\n",it->port);
             printf("\n SSL=%d\n",it->ssl);
         }
     }
     else
     {
 
         printf("\nerrordetails:%s",emailResponse->errorDetails.c_str());
         printf("\nerrorMessage:%s",emailResponse->errorMessage.c_str());
         printf("\nappErrorCode:%d",emailResponse->appErrorCode);
         printf("\nhttpErrorCode:%d",emailResponse->httpErrorCode);
     }
 }
*****/