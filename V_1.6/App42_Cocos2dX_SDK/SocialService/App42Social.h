//
//  App42Social.h
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 26/06/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__App42Social__
#define __App42Cocos2dX3_0Sample__App42Social__

#include <iostream>
#include "App42Friend.h"
#include <vector>

class App42Social
{
public:
    
    App42Social();
    
    void setDefaults();
    /**
     * Getters
     */
    std::string getUserName(){return userName;};
    std::string getStatus(){return status;};
    /** Facebook Credentials **/
    std::string getFacebookAppId(){return facebookAppId;};
    std::string getFacebookAppSecret(){return facebookAppSecret;};
    std::string getFacebookAccessToken(){return facebookAccessToken;};
    /** Twitter Credentials **/
    std::string getTwitterConsumerKey(){return twitterConsumerKey;};
    std::string getTwitterConsumerSecret(){return twitterConsumerSecret;};
    std::string getTwitterAccessToken(){return twitterAccessToken;};
    std::string getTwitterAccessTokenSecret(){return twitterAccessTokenSecret;};
    /** LinkedIn Credentials **/
    std::string getLinkedinApiKey(){return linkedinApiKey;};
    std::string getLinkedinSecretKey(){return linkedinSecretKey;};
    std::string getLinkedinAccessToken(){return linkedinAccessToken;};
    std::string getLinkedinAccessTokenSecret(){return linkedinAccessTokenSecret;};
    /**
     * Setters
     */
    
    void setUserName(std::string _userName){ userName=_userName;};
    void setStatus(std::string _status){ status=_status;};
    
    /** Facebook Credentials **/
    void setFacebookAppId(std::string _facebookAppId){ facebookAppId=_facebookAppId;};
    void setFacebookAppSecret(std::string _facebookAppSecret){ facebookAppSecret=_facebookAppSecret;};
    void setFacebookAccessToken(std::string _facebookAccessToken){ facebookAccessToken=_facebookAccessToken;};
    
    /** Twitter Credentials **/
    void setTwitterConsumerKey(std::string _twitterConsumerKey){ twitterConsumerKey=_twitterConsumerKey;};
    void setTwitterConsumerSecret(std::string _twitterConsumerSecret){ twitterConsumerSecret=_twitterConsumerSecret;};
    void setTwitterAccessToken(std::string _twitterAccessToken){ twitterAccessToken=_twitterAccessToken;};
    void setTwitterAccessTokenSecret(std::string _twitterAccessTokenSecret){ twitterAccessTokenSecret=_twitterAccessTokenSecret;};
    
    /** LinkedIn Credentials **/
    void setLinkedinApiKey(std::string _linkedinApiKey){ linkedinApiKey=_linkedinApiKey;};
    void setLinkedinSecretKey(std::string _linkedinSecretKey){ linkedinSecretKey=_linkedinSecretKey;};
    void setLinkedinAccessToken(std::string _linkedinAccessToken){ linkedinAccessToken=_linkedinAccessToken;};
    void setLinkedinAccessTokenSecret(std::string _linkedinAccessTokenSecret){ linkedinAccessTokenSecret=_linkedinAccessTokenSecret;};
    
protected:
    
    std::string userName;
    std::string status;
    std::string facebookAppId;
    std::string facebookAppSecret;
    std::string facebookAccessToken;
    std::string twitterConsumerKey;
    std::string twitterConsumerSecret;
    std::string twitterAccessToken;
    std::string twitterAccessTokenSecret;
    std::string linkedinApiKey;
    std::string linkedinSecretKey;
    std::string linkedinAccessToken;
    std::string linkedinAccessTokenSecret;
private:
};

#endif /* defined(__App42Cocos2dX3_0Sample__App42Social__) */
