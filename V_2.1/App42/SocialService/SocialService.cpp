//
//  SocialService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 26/06/14.
//
//

#include "SocialService.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "Connector.h"
#include "App42API.h"
#include "App42Constants.h"
#include "App42SocialResponse.h"

using namespace App42Network;

// define the static..
SocialService* SocialService::_instance = NULL;

SocialService* SocialService::Initialize(string apikey, string secretkey)
{
	if(_instance == NULL)
    {
		_instance = new SocialService();
	}
    _instance->Init(apikey, secretkey);
    return _instance;
}

SocialService* SocialService::getInstance()
{
	return _instance;
}

void SocialService::Terminate()
{
	if(_instance != NULL)
    {
		delete _instance;
		_instance = NULL;
	}
}

SocialService::SocialService()
{
    
}


string SocialService::buildLinkFacebookAccountRequest(const char* userName, const char* accessToken, const char* appId, const char* appSecret, const char* status)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *socialJSON = cJSON_CreateObject();
    
    // first construct the user
    if (strlen(userName))
    {
        cJSON_AddStringToObject(socialJSON, "userName", userName);
    }
    
    if (strlen(accessToken))
    {
        cJSON_AddStringToObject(socialJSON, "accessToken", accessToken);
    }
    
    if (strlen(appId))
    {
        cJSON_AddStringToObject(socialJSON, "appId", appId);
    }
    
    if (strlen(appSecret))
    {
        cJSON_AddStringToObject(socialJSON, "appSecret", appSecret);
    }
    
    if (strlen(status))
    {
        cJSON_AddStringToObject(socialJSON, "status", status);
    }
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "social", socialJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(socialJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}

string SocialService::buildFacebookLinkPostRequest(const char* accessToken, const char* link, const char* message,const char* pictureUrl,const char* fileName,const char* description)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *socialJSON = cJSON_CreateObject();
    
    // first construct the user
    if (strlen(accessToken))
    {
        cJSON_AddStringToObject(socialJSON, "accessToken", accessToken);
    }
    
    if (strlen(link))
    {
        cJSON_AddStringToObject(socialJSON, "link", link);
    }
    
    if (strlen(message))
    {
        cJSON_AddStringToObject(socialJSON, "message", message);
    }
    
    if (strlen(pictureUrl))
    {
        cJSON_AddStringToObject(socialJSON, "picture", pictureUrl);
    }
    
    if (strlen(fileName))
    {
        cJSON_AddStringToObject(socialJSON, "name", fileName);
    }
    
    if (strlen(description))
    {
        cJSON_AddStringToObject(socialJSON, "description", description);
    }
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "social", socialJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(socialJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}

string SocialService::buildLinkTwitterAccountRequest(const char* userName, const char* consumerKey, const char*consumerSecret, const char* accessToken, const char* accessTokenSecret)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *socialJSON = cJSON_CreateObject();
    
    // first construct the user
    if (strlen(userName))
    {
        cJSON_AddStringToObject(socialJSON, "userName", userName);
    }
    
    if (strlen(consumerKey))
    {
        cJSON_AddStringToObject(socialJSON, "consumerKey", consumerKey);
    }
    
    if (strlen(consumerSecret))
    {
        cJSON_AddStringToObject(socialJSON, "consumerSecret", consumerSecret);
    }
    
    if (strlen(accessToken))
    {
        cJSON_AddStringToObject(socialJSON, "accessToken", accessToken);
    }
    
    if (strlen(accessTokenSecret))
    {
        cJSON_AddStringToObject(socialJSON, "accessTokenSecret", accessTokenSecret);
    }
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "social", socialJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(socialJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}

string SocialService::buildLinkUserLinkedInAccountRequest(const char* userName, const char* linkedInApiKey, const char*linkedInSecretKey, const char* accessToken, const char* accessTokenSecret)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *socialJSON = cJSON_CreateObject();
    
    // first construct the user
    if (strlen(userName))
    {
        cJSON_AddStringToObject(socialJSON, "userName", userName);
    }
    
    if (strlen(linkedInApiKey))
    {
        cJSON_AddStringToObject(socialJSON, "apiKey", linkedInApiKey);
    }
    
    if (strlen(linkedInSecretKey))
    {
        cJSON_AddStringToObject(socialJSON, "secretKey", linkedInSecretKey);
    }
    
    if (strlen(accessToken))
    {
        cJSON_AddStringToObject(socialJSON, "accessToken", accessToken);
    }
    
    if (strlen(accessTokenSecret))
    {
        cJSON_AddStringToObject(socialJSON, "accessTokenSecret", accessTokenSecret);
    }
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "social", socialJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(socialJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}


/******************************************************************************************************/
/*****************************            FACEBOOK RELATED APIS            ****************************/
/******************************************************************************************************/

void SocialService::LinkUserFacebookAccount(const char *userName, const char *accessToken, const char *appId, const char *appSecret, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(accessToken, "AccessToken");
        Util::throwExceptionIfStringNullOrBlank(appId, "AppId");
        Util::throwExceptionIfStringNullOrBlank(appSecret, "AppSecret");

        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestbody = buildLinkFacebookAccountRequest(userName, accessToken, appId, appSecret,"");
    signParams["body"] = requestbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/facebook/linkuser");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, requestbody.c_str(), std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void SocialService::LinkUserFacebookAccount(const char *userName, const char *accessToken, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(accessToken, "AccessToken");
        
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestbody = buildLinkFacebookAccountRequest(userName, accessToken, "", "","");
    signParams["body"] = requestbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/facebook/linkuser/accesscredentials");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, requestbody.c_str(), std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void SocialService::UpdateFacebookStatus(const char *userName, const char *status, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(status, "Status");
        
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestbody = buildLinkFacebookAccountRequest(userName, "", "", "",status);
    signParams["body"] = requestbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/facebook/updatestatus");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, requestbody.c_str(), std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void SocialService::GetFacebookFriendsFromLinkUser(const char *userName, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    signParams["userName"] = userName;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/facebook/friends/");
    resource.append(userName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl, headers, std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void SocialService::GetFacebookFriendsFromAccessToken(const char *accessToken, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(accessToken, "AccessToken");
        
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    signParams["accessToken"] = accessToken;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/facebook/friends/OAuth/");
    resource.append(accessToken);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl, headers, std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void SocialService::FacebookPublishStream(const char *accessToken, const char *fileName, const char *filePath, const char *message, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    try
    {
        Util::throwExceptionIfStringNullOrBlank(fileName, "File Name");
        Util::throwExceptionIfStringNullOrBlank(filePath, "File Path");
        Util::throwExceptionIfStringNullOrBlank(accessToken, "AccessToken");
        Util::throwExceptionIfStringNullOrBlank(message, "Message");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    try
    {
        /**
         * Creating SignParams and signature
         */
        map<string, string> signParams;
        string timestamp = Util::getTimeStamp();
        populateSignParams(signParams);
        signParams["name"] = fileName;
        signParams["accessToken"] = accessToken;
        signParams["message"] = message;
        
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating PostParamsMap
         */
        map<string, string> postParams;
        postParams["name"] = fileName;
        postParams["accessToken"] = accessToken;
        postParams["message"] = message;
        
        /**
         * Creating URL
         */
        string resource = "social";
        resource.append("/facebook/wallpost");
        string baseUrl = getBaseUrl(resource);
        baseUrl.append("?");
        string encodedUrl = url_encode(baseUrl);
        
        /**
         * Creating Headers
         */
        std::vector<std::string> headers;
        map<string, string> metaHeaders;
        populateMetaHeaderParams(metaHeaders);
        Util::BuildHeaders(metaHeaders, headers);
        Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
        
        /**
         * Initiating Http call
         */
        Util::executeMultiPartWithFile("uploadFile",fileName, filePath,postParams, encodedUrl, headers, std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void SocialService::FacebookLinkPost(const char* accessToken, const char* link, const char* message, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(accessToken, "Access Token");
        Util::throwExceptionIfStringNullOrBlank(link, "Link");
        Util::throwExceptionIfStringNullOrBlank(message, "Message");

        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestbody = buildFacebookLinkPostRequest(accessToken, link, message);
    signParams["body"] = requestbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/facebook/publishstream");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, requestbody.c_str(), std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void SocialService::FacebookLinkPostWithCustomThumbnail(const char* accessToken, const char* link, const char* message,const char* pictureUrl, const char* fileName, const char* description, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(accessToken, "Access Token");
        Util::throwExceptionIfStringNullOrBlank(link, "Link");
        Util::throwExceptionIfStringNullOrBlank(message, "Message");
        
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestbody = buildFacebookLinkPostRequest(accessToken, link, message,pictureUrl,fileName,description);
    signParams["body"] = requestbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/facebook/publishstream");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, requestbody.c_str(), std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void SocialService::GetFacebookProfile(const char* accessToken, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(accessToken, "Access Token");
        
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    signParams["accessToken"] = accessToken;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/facebook/me/OAuth/");
    resource.append(accessToken);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl, headers, std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void SocialService::GetFacebookProfilesFromIds(vector<string> facebookIds, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfVectorIsNullOrBlank(facebookIds, "FacebookIds");
        
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/facebook/ids");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    
    string facebookIdsString = "[";
    facebookIdsString.append(Util::GetStringFromVector(facebookIds));
    facebookIdsString.append("]");
    metaHeaders["userList"] = facebookIdsString;
    
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl, headers, std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

/******************************************************************************************************/
/*****************************             TWITTER RELATED APIS            ****************************/
/******************************************************************************************************/

void SocialService::LinkUserTwitterAccount(const char* userName, const char* consumerKey, const char*consumerSecret, const char* accessToken, const char* accessTokenSecret, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(accessToken, "AccessToken");
        Util::throwExceptionIfStringNullOrBlank(accessTokenSecret, "AccessTokenSecret");
        Util::throwExceptionIfStringNullOrBlank(consumerKey, "ConsumerKey");
        Util::throwExceptionIfStringNullOrBlank(consumerSecret, "ConsumerSecret");
        
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestbody = buildLinkTwitterAccountRequest(userName, consumerKey, consumerSecret, accessToken, accessTokenSecret);
    signParams["body"] = requestbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/twitter/linkuser");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, requestbody.c_str(), std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void SocialService::LinkUserTwitterAccount(const char* userName, const char* accessToken, const char* accessTokenSecret, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(accessToken, "AccessToken");
        Util::throwExceptionIfStringNullOrBlank(accessTokenSecret, "AccessTokenSecret");
        
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestbody = buildLinkTwitterAccountRequest(userName, "", "", accessToken, accessTokenSecret);
    signParams["body"] = requestbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/twitter/linkuser/accesscredentials");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, requestbody.c_str(), std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void SocialService::UpdateTwitterStatus(const char* userName, const char* status, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(status, "Status");
        
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestbody = buildLinkFacebookAccountRequest(userName, "", "", "",status);
    signParams["body"] = requestbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/twitter/updatestatus");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, requestbody.c_str(), std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


/******************************************************************************************************/
/*****************************            LINKEDIN RELATED APIS            ****************************/
/******************************************************************************************************/


void SocialService::LinkUserLinkedInAccount(const char* userName, const char* linkedInApiKey, const char* linkedInSecretKey, const char* accessToken, const char* accessTokenSecret, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(accessToken, "AccessToken");
        Util::throwExceptionIfStringNullOrBlank(accessTokenSecret, "AccessTokenSecret");
        Util::throwExceptionIfStringNullOrBlank(linkedInApiKey, "LinkedInApiKey");
        Util::throwExceptionIfStringNullOrBlank(linkedInSecretKey, "LinkedInSecretKey");
        
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestbody = buildLinkUserLinkedInAccountRequest(userName, linkedInApiKey, linkedInSecretKey, accessToken, accessTokenSecret);
    signParams["body"] = requestbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/linkedin/linkuser");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, requestbody.c_str(), std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void SocialService::LinkUserLinkedInAccount(const char* userName, const char* accessToken, const char* accessTokenSecret, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(accessToken, "AccessToken");
        Util::throwExceptionIfStringNullOrBlank(accessTokenSecret, "AccessTokenSecret");
        
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestbody = buildLinkUserLinkedInAccountRequest(userName, "", "", accessToken, accessTokenSecret);
    signParams["body"] = requestbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/linkedin/linkuser/accesscredentials");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, requestbody.c_str(), std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void SocialService::UpdateLinkedInStatus(const char* userName, const char* status, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(status, "Status");
        
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestbody = buildLinkFacebookAccountRequest(userName, "", "", "",status);
    signParams["body"] = requestbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/linkedin/updatestatus");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, requestbody.c_str(), std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void SocialService::UpdateSocialStatusForAll(const char* userName, const char* status, const app42CallBack& pSelector)
{
    App42SocialResponse *response = new App42SocialResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(status, "Status");
        
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestbody = buildLinkFacebookAccountRequest(userName, "", "", "",status);
    signParams["body"] = requestbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "social";
    resource.append("/social/updatestatus/all");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, requestbody.c_str(), std::bind(&App42SocialResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

