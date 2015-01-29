//
//  TestSocialService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 26/06/14.
//
//

#include "TestSocialService.h"

#include "TestHome.h"


#define GO_HOME 111



USING_NS_CC;

Scene* TestSocialService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestSocialService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestSocialService::init()
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
                                                CC_CALLBACK_1(TestSocialService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * LinkUserFacebookAccount
     */
    auto linkUserFacebookAccountLabel = LabelTTF::create("LinkUserFacebookAccount", "Marker Felt", 24);
    linkUserFacebookAccountLabel->setColor(Color3B::WHITE);
    auto linkUserFacebookAccountItem  = MenuItemLabel::create(linkUserFacebookAccountLabel, CC_CALLBACK_1(TestSocialService::linkUserFacebookAccount, this));
    linkUserFacebookAccountItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * LinkUserFacebookAccountWithToken
     */
    auto linkUserFacebookAccountWithTokenLabel = LabelTTF::create("LinkUserFacebookAccountWithToken", "Marker Felt", 24);
    linkUserFacebookAccountWithTokenLabel->setColor(Color3B::WHITE);
    auto linkUserFacebookAccountWithTokenItem  = MenuItemLabel::create(linkUserFacebookAccountWithTokenLabel, CC_CALLBACK_1(TestSocialService::linkUserFacebookAccountWithToken, this));
    y_pos -= button_y_Offset;
    linkUserFacebookAccountWithTokenItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * UpdateFBStatus
     */
    auto updateFBStatusLabel = LabelTTF::create("UpdateFBStatus", "Marker Felt", 24);
    updateFBStatusLabel->setColor(Color3B::WHITE);
    auto updateFBStatusItem  = MenuItemLabel::create(updateFBStatusLabel, CC_CALLBACK_1(TestSocialService::updateFBStatus, this));
    y_pos -= button_y_Offset;
    updateFBStatusItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetFBFriends
     */
    auto getFBFriendsLabel = LabelTTF::create("GetFBFriends", "Marker Felt", 24);
    getFBFriendsLabel->setColor(Color3B::WHITE);
    auto getFBFriendsItem  = MenuItemLabel::create(getFBFriendsLabel, CC_CALLBACK_1(TestSocialService::getFBFriends, this));
    y_pos -= button_y_Offset;
    getFBFriendsItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetFBFriendsWithAccessToken
     */
    auto getFBFriendsWithAccessTokenLabel = LabelTTF::create("GetFBFriendsWithAccessToken", "Marker Felt", 24);
    getFBFriendsWithAccessTokenLabel->setColor(Color3B::WHITE);
    auto getFBFriendsWithAccessTokenItem  = MenuItemLabel::create(getFBFriendsWithAccessTokenLabel, CC_CALLBACK_1(TestSocialService::getFBFriendsForAccessToken, this));
    y_pos -= button_y_Offset;
    getFBFriendsWithAccessTokenItem->setPosition(Point(x_pos,y_pos));

    /**
     * FacebookPublishStream
     */
    auto facebookPublishStreamLabel = LabelTTF::create("FacebookPublishStream", "Marker Felt", 24);
    facebookPublishStreamLabel->setColor(Color3B::WHITE);
    auto facebookPublishStreamLabelItem  = MenuItemLabel::create(facebookPublishStreamLabel, CC_CALLBACK_1(TestSocialService::facebookPublishStream, this));
    y_pos -= button_y_Offset;
    facebookPublishStreamLabelItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FacebookLinkPost
     */
    auto facebookLinkPostLabel = LabelTTF::create("FacebookLinkPost", "Marker Felt", 24);
    facebookLinkPostLabel->setColor(Color3B::WHITE);
    auto facebookLinkPostItem  = MenuItemLabel::create(facebookLinkPostLabel, CC_CALLBACK_1(TestSocialService::facebookLinkPost, this));
    y_pos -= button_y_Offset;
    facebookLinkPostItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FacebookLinkPostWithCustomThumbnail
     */
    auto facebookLinkPostWithCustomThumbnailLabel = LabelTTF::create("FacebookLinkPostWithCustomThumbnail", "Marker Felt", 24);
    facebookLinkPostWithCustomThumbnailLabel->setColor(Color3B::WHITE);
    auto facebookLinkPostWithCustomThumbnailItem  = MenuItemLabel::create(facebookLinkPostWithCustomThumbnailLabel, CC_CALLBACK_1(TestSocialService::facebookLinkPostWithCustomThumbnail, this));
    y_pos -= button_y_Offset;
    facebookLinkPostWithCustomThumbnailItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetFacebookProfile
     */
    auto getFacebookProfileLabel = LabelTTF::create("GetFacebookProfile", "Marker Felt", 24);
    getFacebookProfileLabel->setColor(Color3B::WHITE);
    auto getFacebookProfileItem  = MenuItemLabel::create(getFacebookProfileLabel, CC_CALLBACK_1(TestSocialService::getFacebookProfile, this));
    y_pos -= button_y_Offset;
    getFacebookProfileItem->setPosition(Point(x_pos,y_pos));

    /**
     * GetFacebookProfilesFromIds
     */
    auto getFacebookProfilesFromIdsLabel = LabelTTF::create("GetFacebookProfilesFromIds", "Marker Felt", 24);
    getFacebookProfilesFromIdsLabel->setColor(Color3B::WHITE);
    auto getFacebookProfilesFromIdsItem  = MenuItemLabel::create(getFacebookProfilesFromIdsLabel, CC_CALLBACK_1(TestSocialService::getFacebookProfilesFromIds, this));
    y_pos -= button_y_Offset;
    getFacebookProfilesFromIdsItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * LinkUserTwitterAccount
     */
    auto linkUserTwitterAccountLabel = LabelTTF::create("LinkUserTwitterAccount", "Marker Felt", 24);
    linkUserTwitterAccountLabel->setColor(Color3B::WHITE);
    auto linkUserTwitterAccountItem  = MenuItemLabel::create(linkUserTwitterAccountLabel, CC_CALLBACK_1(TestSocialService::linkUserTwitterAccount, this));
    y_pos -= button_y_Offset;
    linkUserTwitterAccountItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * LinkUserTwitterAccountWithAccessCredentials
     */
    auto linkUserTwitterAccountAccessCredentialsLabel = LabelTTF::create("LinkUserTwitterAccountWithAccessCredentials", "Marker Felt", 24);
    linkUserTwitterAccountAccessCredentialsLabel->setColor(Color3B::WHITE);
    auto linkUserTwitterAccountAccessCredentialsItem  = MenuItemLabel::create(linkUserTwitterAccountAccessCredentialsLabel, CC_CALLBACK_1(TestSocialService::linkUserTwitterAccountAccessCredentials, this));
    y_pos -= button_y_Offset;
    linkUserTwitterAccountAccessCredentialsItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * UpdateTWStatus
     */
    auto updateTWStatusLabel = LabelTTF::create("UpdateTWStatus", "Marker Felt", 24);
    updateTWStatusLabel->setColor(Color3B::WHITE);
    auto updateTWStatusItem  = MenuItemLabel::create(updateTWStatusLabel, CC_CALLBACK_1(TestSocialService::updateTWStatus, this));
    y_pos -= button_y_Offset;
    updateTWStatusItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * LinkUserLinkedInAccount
     */
    auto linkUserLinkedInAccountLabel = LabelTTF::create("LinkUserLinkedInAccount", "Marker Felt", 24);
    linkUserLinkedInAccountLabel->setColor(Color3B::WHITE);
    auto linkUserLinkedInAccountItem  = MenuItemLabel::create(linkUserLinkedInAccountLabel, CC_CALLBACK_1(TestSocialService::linkUserLinkedInAccount, this));
    y_pos -= button_y_Offset;
    linkUserLinkedInAccountItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * LinkUserLinkedInAccountWithAccessCredentials
     */
    auto linkUserLinkedInAccountAccessCredentialsLabel = LabelTTF::create("LinkUserLinkedInAccountWithAccessCredentials", "Marker Felt", 24);
    linkUserLinkedInAccountAccessCredentialsLabel->setColor(Color3B::WHITE);
    auto linkUserLinkedInAccountAccessCredentialsItem  = MenuItemLabel::create(linkUserLinkedInAccountAccessCredentialsLabel, CC_CALLBACK_1(TestSocialService::linkUserLinkedInAccountAccessCredentials, this));
    y_pos -= button_y_Offset;
    linkUserLinkedInAccountAccessCredentialsItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * UpdateLinkedInStatus
     */
    auto updateLinkedInStatusLabel = LabelTTF::create("UpdateLinkedInStatus", "Marker Felt", 24);
    updateLinkedInStatusLabel->setColor(Color3B::WHITE);
    auto updateLinkedInStatusItem  = MenuItemLabel::create(updateLinkedInStatusLabel, CC_CALLBACK_1(TestSocialService::updateLinkedInStatus, this));
    y_pos -= button_y_Offset;
    updateLinkedInStatusItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * UpdateSocialStatusForAll
     */
    auto updateSocialStatusForAllLabel = LabelTTF::create("UpdateSocialStatusForAll", "Marker Felt", 24);
    updateSocialStatusForAllLabel->setColor(Color3B::WHITE);
    auto updateSocialStatusForAllItem  = MenuItemLabel::create(updateSocialStatusForAllLabel, CC_CALLBACK_1(TestSocialService::updateSocialStatusForAll, this));
    y_pos -= button_y_Offset;
    updateSocialStatusForAllItem->setPosition(Point(x_pos,y_pos));

 	
    // create menu, it's an autorelease object
    auto menu = Menu::create(backButtonItem,
                             linkUserFacebookAccountItem,
                             linkUserFacebookAccountWithTokenItem,
                             updateFBStatusItem,
                             getFBFriendsItem,
                             getFBFriendsWithAccessTokenItem,
                             facebookPublishStreamLabelItem,
                             facebookLinkPostItem,NULL);

	auto menu1 = Menu::create(
                             facebookLinkPostWithCustomThumbnailItem,
                             getFacebookProfileItem,
                             getFacebookProfilesFromIdsItem,
                             linkUserTwitterAccountItem,
                             linkUserTwitterAccountAccessCredentialsItem,
                             updateTWStatusItem,
                             linkUserLinkedInAccountItem,
                             linkUserLinkedInAccountAccessCredentialsItem,
                             updateLinkedInStatusItem,
                             updateSocialStatusForAllItem,NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	menu1->setPosition(Point::ZERO);
    this->addChild(menu1, 1);
    
    return true;
}




/**
 * API Methods
 */
void TestSocialService::linkUserFacebookAccount(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    
    const char* userName = "Rajeev";
    const char* accessToken = "CAADBZBGAg6a4BADCKRiZC2AcHASiURUmLSNOO285G8FZAwfvN2FBnVW2eWL4SNZBBjti7QdguIGZAyc6C4wr4jwvVTZCMgig9dGnGZA4VJZCTdZAxsooytojGSjowtqPeDZBtyg7hMjEqPHPvm1znxLDdzZAnlZB2MepwONkzaZAxFrL9mR34cEzlHN8ZA3LMJVJP8B4g33qIZAsKZBwmAZDZD";
    const char* appId = "213272508819886";
    const char* appSecret = "aff71134807bdc000a72d6c7fb9b8297";
    
    socialService->LinkUserFacebookAccount(userName, accessToken, appId, appSecret, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

void TestSocialService::linkUserFacebookAccountWithToken(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    
    const char* userName = "Rajeev";
    const char* accessToken = "CAACEdEose0cBAOFz6pJZA74LxWzaZBYTi18KQZCLU4BIeR89rlNaZBYnx5S2kkK02ofX5Gl24SjAm9kfTMNRPZCFZCdTblLprtjhcyezJglqeffodC1JPRU8KjXooaptR7OizMi7m4O5lepU1pl7Yl9O4RZB1r120WAHgO7EP8jsfiDT8TUK4jsX8EdZByDd4kfhWg1PNi2ChwZDZD";
    
    socialService->LinkUserFacebookAccount(userName, accessToken, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

void TestSocialService::updateFBStatus(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    
    const char* userName = "Rajeev";
    const char* status = "Hello there!";
    
    socialService->UpdateFacebookStatus(userName, status, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

void TestSocialService::getFBFriends(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    
    const char* userName = "Rajeev";
    
    socialService->GetFacebookFriendsFromLinkUser(userName, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

void TestSocialService::getFBFriendsForAccessToken(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    
    const char* accessToken = "CAACEdEose0cBAOFz6pJZA74LxWzaZBYTi18KQZCLU4BIeR89rlNaZBYnx5S2kkK02ofX5Gl24SjAm9kfTMNRPZCFZCdTblLprtjhcyezJglqeffodC1JPRU8KjXooaptR7OizMi7m4O5lepU1pl7Yl9O4RZB1r120WAHgO7EP8jsfiDT8TUK4jsX8EdZByDd4kfhWg1PNi2ChwZDZD";
    
    socialService->GetFacebookFriendsFromAccessToken(accessToken, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

void TestSocialService::facebookPublishStream(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    
    string filePath = FileUtils::getInstance()->fullPathForFilename("BackButton.png");
    
    const char* fileName = "BackButtonSocial.png";
    const char* message ="Hi";
    const char* accessToken = "CAACEdEose0cBAOFz6pJZA74LxWzaZBYTi18KQZCLU4BIeR89rlNaZBYnx5S2kkK02ofX5Gl24SjAm9kfTMNRPZCFZCdTblLprtjhcyezJglqeffodC1JPRU8KjXooaptR7OizMi7m4O5lepU1pl7Yl9O4RZB1r120WAHgO7EP8jsfiDT8TUK4jsX8EdZByDd4kfhWg1PNi2ChwZDZD";
    
    socialService->FacebookPublishStream(accessToken, fileName, filePath.c_str(), message, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

void TestSocialService::facebookLinkPost(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    
    const char* link = "http://blogs.shephertz.com/2012/12/27/writing-custom-code-your-code-our-cloud-2/";
    const char* message ="Hi";
    const char* accessToken = "CAACEdEose0cBAOFz6pJZA74LxWzaZBYTi18KQZCLU4BIeR89rlNaZBYnx5S2kkK02ofX5Gl24SjAm9kfTMNRPZCFZCdTblLprtjhcyezJglqeffodC1JPRU8KjXooaptR7OizMi7m4O5lepU1pl7Yl9O4RZB1r120WAHgO7EP8jsfiDT8TUK4jsX8EdZByDd4kfhWg1PNi2ChwZDZD";
   
    socialService->FacebookLinkPost(accessToken, link, message, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

void TestSocialService::facebookLinkPostWithCustomThumbnail(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    
    const char* link = "http://blogs.shephertz.com/2012/12/27/writing-custom-code-your-code-our-cloud-2/";
    const char* message ="Hi";
    const char* accessToken = "CAACEdEose0cBAOFz6pJZA74LxWzaZBYTi18KQZCLU4BIeR89rlNaZBYnx5S2kkK02ofX5Gl24SjAm9kfTMNRPZCFZCdTblLprtjhcyezJglqeffodC1JPRU8KjXooaptR7OizMi7m4O5lepU1pl7Yl9O4RZB1r120WAHgO7EP8jsfiDT8TUK4jsX8EdZByDd4kfhWg1PNi2ChwZDZD";
    
    const char* pictureUrl = "http://50.112.110.36/wp-content/uploads/2012/12/custom_code_bg2.png";
    const char* fileName = "cloud1.png";
    const char* description = "CustomCloud";
    socialService->FacebookLinkPostWithCustomThumbnail(accessToken, link, message,pictureUrl,fileName,description, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

void TestSocialService::getFacebookProfile(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    const char* accessToken = "CAACEdEose0cBAOFz6pJZA74LxWzaZBYTi18KQZCLU4BIeR89rlNaZBYnx5S2kkK02ofX5Gl24SjAm9kfTMNRPZCFZCdTblLprtjhcyezJglqeffodC1JPRU8KjXooaptR7OizMi7m4O5lepU1pl7Yl9O4RZB1r120WAHgO7EP8jsfiDT8TUK4jsX8EdZByDd4kfhWg1PNi2ChwZDZD";
    
    socialService->GetFacebookProfile(accessToken, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

void TestSocialService::getFacebookProfilesFromIds(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();

    vector<string> facebookIds;
    facebookIds.push_back("100006181209270");
    facebookIds.push_back("100005374989098");

    socialService->GetFacebookProfilesFromIds(facebookIds, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}


void TestSocialService::linkUserTwitterAccount(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    
    const char* userName = "Rajeev";
    const char* twitterConsumerKey = "6lFvyAd515aKrFDwL8DA";
	const char* twitterConsumerSecret = "uFQ4QBr1fxcTthcB7bE5yvnaq8Jv3EUD4bAQRk8vNs";
	const char* twitterAccessToken = "448838959-m67CV2QqqizC6tKwS88R8K7YxTts54HPmUv4EfJC";
	const char* twitterAccessTokenSecret = "mgyFruxAopBkJdQAOS3zSBqn8SqjkRpgw8oJJZKV9vg";
    socialService->LinkUserTwitterAccount(userName, twitterConsumerKey, twitterConsumerSecret, twitterAccessToken, twitterAccessTokenSecret, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

void TestSocialService::linkUserTwitterAccountAccessCredentials(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    const char* userName = "Rajeev";
	const char* twitterAccessToken = "448838959-m67CV2QqqizC6tKwS88R8K7YxTts54HPmUv4EfJC";
	const char* twitterAccessTokenSecret = "mgyFruxAopBkJdQAOS3zSBqn8SqjkRpgw8oJJZKV9vg";
    socialService->LinkUserTwitterAccount(userName, twitterAccessToken, twitterAccessTokenSecret, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

void TestSocialService::updateTWStatus(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    const char* userName = "Rajeev";
    const char* status = "Hello";
    socialService->UpdateTwitterStatus(userName, status, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

void TestSocialService::linkUserLinkedInAccount(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    const char* userName = "Rajeev";
    const char* linkedinApiKey = "gdsxb5wr6bow";
	const char* linkedinSecretKey = "YQ345Y4AqI2WSMjp";
	const char* linkedinAccessToken = "56a813dd-5b61-48f4-8cd6-cb49b40081f6";
	const char* linkedinAccessTokenSecret = "7d81cb5b-d9ee-4ebb-8750-2f822ebd8aa2";
    socialService->LinkUserLinkedInAccount(userName, linkedinApiKey, linkedinSecretKey, linkedinAccessToken, linkedinAccessTokenSecret, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

void TestSocialService::linkUserLinkedInAccountAccessCredentials(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    const char* userName = "Rajeev";
	const char* linkedinAccessToken = "56a813dd-5b61-48f4-8cd6-cb49b40081f6";
	const char* linkedinAccessTokenSecret = "7d81cb5b-d9ee-4ebb-8750-2f822ebd8aa2";
    socialService->LinkUserLinkedInAccount(userName, linkedinAccessToken, linkedinAccessTokenSecret, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));

}

void TestSocialService::updateLinkedInStatus(Ref *sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    const char* userName = "Rajeev";
    const char* status = "Hi";
    socialService->UpdateLinkedInStatus(userName, status, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

void TestSocialService::updateSocialStatusForAll(Ref* sender)
{
    SocialService *socialService = App42API::BuildSocialService();
    const char* userName = "Rajeev";
    const char* status = "ReTweeted";
    socialService->UpdateSocialStatusForAll(userName, status, app42callback(TestSocialService::onSocialServiceRequestCompleted, this));
}

/**
 * Callback Methods
 */
void TestSocialService::onSocialServiceRequestCompleted( void *response)
{
    App42SocialResponse *app42SocialResponse = (App42SocialResponse*)response;
    
    string code = StringUtils::format("Code = %d",app42SocialResponse->getCode());
    responseArray.push_back(code);
    
    if(app42SocialResponse->isSuccess)
    {
        printf("\ncode=%d",app42SocialResponse->getCode());
        printf("\nisSuccess=%d",app42SocialResponse->isSuccess);
        printf("\nResponse Body=%s",app42SocialResponse->getBody().c_str());
        printf("\nUserName=%s",app42SocialResponse->social.getUserName().c_str());
        printf("\nStatus=%s",app42SocialResponse->social.getStatus().c_str());
        
        printf("\nFBAccessToken=%s",app42SocialResponse->social.getFacebookAccessToken().c_str());
        printf("\nFBAppId=%s",app42SocialResponse->social.getFacebookAppId().c_str());
        printf("\nFBAppSecret=%s",app42SocialResponse->social.getFacebookAppSecret().c_str());
        
        printf("\nTWAccessToken=%s",app42SocialResponse->social.getTwitterAccessToken().c_str());
        printf("\nTWAccessTokenSecret=%s",app42SocialResponse->social.getTwitterAccessTokenSecret().c_str());
        printf("\nTWConsumerKey=%s",app42SocialResponse->social.getTwitterConsumerKey().c_str());
        printf("\nTWConsumerSecret=%s",app42SocialResponse->social.getTwitterConsumerSecret().c_str());

        printf("\nLinkedInAccessToken=%s",app42SocialResponse->social.getLinkedinAccessToken().c_str());
        printf("\nLinkedInAccessTokenSecret=%s",app42SocialResponse->social.getLinkedinAccessTokenSecret().c_str());
        printf("\nLinkedinApiKey=%s",app42SocialResponse->social.getLinkedinApiKey().c_str());
        printf("\nLinkedinSecretKey=%s",app42SocialResponse->social.getLinkedinSecretKey().c_str());


        /**
         * Getting personel facebook profile
         */
        
        printf("\nName=%s", app42SocialResponse->facebookProfile.getName().c_str());
        printf("\nFbId=%s", app42SocialResponse->facebookProfile.getFbId().c_str());
        printf("\nPicture=%s", app42SocialResponse->facebookProfile.getPicture().c_str());

        
        /**
         * Getting friends
         */
        vector<App42Friend> friends = app42SocialResponse->friendsList;
        for(std::vector<App42Friend>::iterator it = friends.begin(); it != friends.end(); ++it)
        {
            printf("\nFriendId=%s",it->getFriendId().c_str());
            printf("\nName=%s\n",it->getName().c_str());
            printf("\nPictureUrl=%s\n",it->getPicture().c_str());
            printf("\nInstalled=%d\n",it->getInstalled());
        }
        
        /**
         * Getting friend's public profile
         */
        vector<App42PublicProfile> publicProfile = app42SocialResponse->publicProfile;
        
        for(std::vector<App42PublicProfile>::iterator it = publicProfile.begin(); it != publicProfile.end(); ++it)
        {
            printf("\nFriendId=%s",it->getFbId().c_str());
            printf("\nName=%s\n",it->getName().c_str());
            printf("\nPictureUrl=%s\n",it->getPicture().c_str());
        }
    }
    else
    {
        printf("\nerrordetails:%s",app42SocialResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",app42SocialResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",app42SocialResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",app42SocialResponse->httpErrorCode);
        string error = StringUtils::format("Error = %s",app42SocialResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",app42SocialResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestSocialService::loadResponseScene, this));
    
}

void TestSocialService::loadResponseScene()
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

void TestSocialService::menuCloseCallback(Ref* pSender)
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
