//
//  BuddyService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 18/07/14.
//
//

#include "BuddyService.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "Connector.h"
#include "App42API.h"
#include "App42Constants.h"
#include "App42BuddyResponse.h"

using namespace App42Network;

// define the static..
BuddyService* BuddyService::_instance = NULL;

BuddyService::BuddyService()
{
    
}

BuddyService* BuddyService::Initialize(string apikey, string secretkey)
{
	if(_instance == NULL)
    {
		_instance = new BuddyService();
	}
    _instance->Init(apikey, secretkey);
    return _instance;
}

BuddyService* BuddyService::getInstance()
{
	return _instance;
}

void BuddyService::Terminate()
{
	if(_instance != NULL)
    {
		delete _instance;
		_instance = NULL;
	}
}



string BuddyService::buildAddFriendToGroupRequest(const char* userName, const char* groupName, const char* friends)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *buddyJSON = cJSON_CreateObject();
    
    // first construct the user
    if (strlen(userName))
    {
        cJSON_AddStringToObject(buddyJSON, "userName", userName);
    }
   
    if (strlen(groupName))
    {
        cJSON_AddStringToObject(buddyJSON, "groupName", groupName);
    }
    
    if (strlen(friends))
    {
        cJSON_AddStringToObject(buddyJSON, "friends", friends);
    }
    // add buddy to app42
    cJSON_AddItemReferenceToObject(app42JSON, "buddy", buddyJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(buddyJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
}


string BuddyService::buildCheckedInUserRequest(const char* userName, const char* points)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *buddyJSON = cJSON_CreateObject();
    
    // first construct the user
    if (strlen(userName))
    {
        cJSON_AddStringToObject(buddyJSON, "userName", userName);
    }

    if (strlen(points))
    {
        cJSON_AddStringToObject(buddyJSON, "points", points);
    }
    // add buddy to app42
    cJSON_AddItemReferenceToObject(app42JSON, "buddy", buddyJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(buddyJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
}

string BuddyService::buildSendFriendRequest(const char* userName, const char* buddyName, const char* message,const char* groupName,const char* ownerName)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *buddyJSON = cJSON_CreateObject();
    
    // first construct the user
    if (strlen(userName))
    {
        cJSON_AddStringToObject(buddyJSON, "userName", userName);
    }
    if (strlen(buddyName))
    {
        cJSON_AddStringToObject(buddyJSON, "buddyName", buddyName);
    }
    if (strlen(message))
    {
        cJSON_AddStringToObject(buddyJSON, "message", message);
    }
    
    if (strlen(groupName))
    {
        cJSON_AddStringToObject(buddyJSON, "groupName", groupName);
    }
    
    if (strlen(ownerName))
    {
        cJSON_AddStringToObject(buddyJSON, "ownerName", ownerName);
    }
    // add session to app42
    cJSON_AddItemReferenceToObject(app42JSON, "buddy", buddyJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(buddyJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
}

void BuddyService::SendFriendRequest(const char* userName, const char* buddyName, const char* message, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(buddyName, "Buddy Name");
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
    string requestBody = buildSendFriendRequest(userName, buddyName, message);
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    Util::app42Trace("\n RequestBody = %s",requestBody.c_str());
    
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
    Util::executePost(encodedUrl, headers, requestBody.c_str(), std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::GetFriendRequest(const char* userName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
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
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy/";
    resource.append(userName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::AcceptFriendRequest(const char* userName, const char* buddyName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(buddyName, "Buddy Name");
        
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
    string requestBody = buildSendFriendRequest(userName, buddyName, "");
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    Util::app42Trace("\n RequestBody = %s",requestBody.c_str());
    
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
    Util::executePut(encodedUrl, headers, requestBody.c_str(), std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::RejectFriendRequest(const char* userName, const char* buddyName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(buddyName, "Buddy Name");

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
    signParams["buddyName"] = buddyName;

    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/userName/");
    resource.append(userName);
    resource.append("/buddyName/");
    resource.append(buddyName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executeDelete(encodedUrl, headers, std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::CreateGroupByUser(const char* userName, const char* groupName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(groupName, "Group Name");
        
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
    string requestBody = buildSendFriendRequest(userName, "", "",groupName);
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    Util::printMap(signParams);
    
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/group");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    Util::app42Trace("\n RequestBody = %s",requestBody.c_str());
    
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
    Util::executePost(encodedUrl, headers, requestBody.c_str(), std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::GetAllFriends(const char* userName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
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
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/friends/");
    resource.append(userName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void BuddyService::AddFriendsToGroup(const char* userName, const char* groupName, vector<string>friends, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(groupName, "Group Name");
        Util::throwExceptionIfVectorIsNullOrBlank(friends, "Friends");
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
    string friendsString = getJsonStringFromVector(friends);
    string requestBody = buildAddFriendToGroupRequest(userName, groupName, friendsString.c_str());
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    Util::printMap(signParams);
    
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/group/friends");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    Util::app42Trace("\n RequestBody = %s",requestBody.c_str());
    
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
    Util::executePost(encodedUrl, headers, requestBody.c_str(), std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void BuddyService::GetAllGroups(const char* userName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
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
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/groupall/");
    resource.append(userName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::GetAllFriendsInGroup(const char* userName, const char* ownerName, const char* groupName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(groupName, "Group Name");
        Util::throwExceptionIfStringNullOrBlank(ownerName, "Owner Name");

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
    signParams["groupName"] = groupName;
    signParams["ownerName"] = ownerName;

    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/friends/");
    resource.append(userName);
    resource.append("/group/");
    resource.append(ownerName);
    resource.append("/");
    resource.append(groupName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::BlockFriendRequest(const char* userName, const char* buddyName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(buddyName, "Buddy Name");
        
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
    signParams["buddyName"] = buddyName;
    
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/block/userName/");
    resource.append(userName);
    resource.append("/buddyName/");
    resource.append(buddyName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executeDelete(encodedUrl, headers, std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void BuddyService::BlockUser(const char* userName, const char* buddyName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(buddyName, "Buddy Name");
        
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
    string requestBody = buildSendFriendRequest(userName, buddyName, "");
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/block");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executePost(encodedUrl, headers, requestBody.c_str(),std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::UnblockUser(const char* userName, const char* buddyName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(buddyName, "Buddy Name");
        
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
    string requestBody = buildSendFriendRequest(userName, buddyName, "");
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/unblock");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executePut(encodedUrl, headers, requestBody.c_str(),std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::SendMessageToGroup(const char* userName, const char* ownerName, const char* groupName, const char* message, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(ownerName, "Owner Name");
        Util::throwExceptionIfStringNullOrBlank(groupName, "Group Name");
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
    string requestBody = buildSendFriendRequest(userName, "", message,groupName,ownerName);
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/groupmessage");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executePost(encodedUrl, headers, requestBody.c_str(),std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::SendMessageToFriend(const char* userName, const char* buddyName, const char* message, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(buddyName, "Buddy Name");
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
    string requestBody = buildSendFriendRequest(userName, buddyName, message,"","");
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/friendmessage");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executePost(encodedUrl, headers, requestBody.c_str(),std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::SendMessageToFriends(const char* userName, const char* message, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
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
    string requestBody = buildSendFriendRequest(userName, "", message,"","");
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/messageAll");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executePost(encodedUrl, headers, requestBody.c_str(),std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::GetAllMessages(const char* userName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
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
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/message/");
    resource.append(userName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::GetAllMessagesFromBuddy(const char* userName, const char* buddyName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(buddyName, "Buddy Name");

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
    signParams["buddyName"] = buddyName;

    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/buddyMessage/");
    resource.append(userName);
    resource.append("/");
    resource.append(buddyName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::GetAllMessagesFromGroup(const char* userName, const char* ownerName, const char* groupName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(ownerName, "Owner Name");
        Util::throwExceptionIfStringNullOrBlank(groupName, "Group Name");

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
    signParams["ownerName"] = ownerName;
    signParams["groupName"] = groupName;
    
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy/";
    resource.append(userName);
    resource.append("/groupMassaage/");
    resource.append(ownerName);
    resource.append("/");
    resource.append(groupName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::UnFriend(const char* userName, const char* buddyName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(buddyName, "Buddy Name");
        
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
    signParams["buddyName"] = buddyName;
    
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/unfriend/userName/");
    resource.append(userName);
    resource.append("/buddyName/");
    resource.append(buddyName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executeDelete(encodedUrl, headers, std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::DeleteMessageById(const char* userName, const char* messageId, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(messageId, "MessageId");
        
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
    
    cJSON *jsonArray = cJSON_CreateArray();
    cJSON *jsonString = cJSON_CreateString(messageId);
    cJSON_AddItemToArray(jsonArray, jsonString);
    char *cptrFormatted = cJSON_PrintUnformatted(jsonArray);
    string messageIds = cptrFormatted;
    
    cJSON_Delete(jsonArray);
    free(cptrFormatted);

    signParams["messageIds"] = messageIds;
    
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/deleteMessageById/");
    resource.append(userName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
    /**
     * Creating Query Params
     */
    map<string, string> queryParams;
    queryParams["messageIds"] = messageIds;
    string queryString = buildQueryString(queryParams);
    baseUrl.append(queryString);
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
    Util::executeDelete(encodedUrl, headers, std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void BuddyService::DeleteMessageByIds(const char* userName, vector<string> messageIds, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfVectorIsNullOrBlank(messageIds, "MessageIds");
        
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
    signParams["messageIds"] = getJsonStringFromVector(messageIds);
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/deleteMessageById/");
    resource.append(userName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
    /**
     * Creating Query Params
     */
    map<string, string> queryParams;
    queryParams["messageIds"] = getJsonStringFromVector(messageIds);
    string queryString = buildQueryString(queryParams);
    baseUrl.append(queryString);
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
    Util::executeDelete(encodedUrl, headers, std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}



void BuddyService::CheckedInGeoLocation(const char* userName, App42GeoPoint* point, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfObjectIsNull(point, "Point");
        
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
    string points = "{\"point\":";
    points.append(point->toString());
    points.append("}");
    string requestBody = buildCheckedInUserRequest(userName, points.c_str());
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/checkedIn");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executePost(encodedUrl, headers, requestBody.c_str(),std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}
void BuddyService::GetFriendsByLocation(const char* userName,double latitude, double longitude, double maxDistance,int max, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
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
    signParams["maxDistance"] = Util::DtoA(maxDistance);
    signParams["latitude"] = Util::DtoA(latitude);
    signParams["longitude"] = Util::DtoA(longitude);
    signParams["max"] = Util::ItoA(max);

    
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/friends/location/");
    resource.append(userName);
    resource.append("/");
    resource.append(Util::DtoA(maxDistance));
    resource.append("/");
    resource.append(Util::DtoA(latitude));
    resource.append("/");
    resource.append(Util::DtoA(longitude));
    resource.append("/");
    resource.append(Util::ItoA(max));
    
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void BuddyService::DeleteUser(const char* userName, const app42CallBack& pSelector)
{
    App42BuddyResponse *response = new App42BuddyResponse(pSelector);
    
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
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "buddy";
    resource.append("/delete/");
    resource.append(userName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
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
    Util::executeDelete(encodedUrl, headers, std::bind(&App42BuddyResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}
