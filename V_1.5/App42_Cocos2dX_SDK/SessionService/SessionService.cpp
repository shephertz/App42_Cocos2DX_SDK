//
//  SessionService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 16/07/14.
//
//

#include "SessionService.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "Connector.h"
#include "App42API.h"
#include "App42Constants.h"
#include "App42SessionResponse.h"

using namespace App42Network;

// define the static..
SessionService* SessionService::_instance = NULL;

SessionService::SessionService()
{
    
}

SessionService* SessionService::Initialize(string apikey, string secretkey)
{
	if(_instance == NULL)
    {
		_instance = new SessionService();
	}
    _instance->Init(apikey, secretkey);
    return _instance;
}

SessionService* SessionService::getInstance()
{
	return _instance;
}

void SessionService::Terminate()
{
	if(_instance != NULL)
    {
		delete _instance;
		_instance = NULL;
	}
}

string SessionService::buildGetSessionRequest(const char* userName, const char* sessionId)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *sessionJSON = cJSON_CreateObject();
    
    // first construct the user
    if (strlen(userName))
    {
        cJSON_AddStringToObject(sessionJSON, "userName", userName);
    }
    if (strlen(sessionId))
    {
        cJSON_AddStringToObject(sessionJSON, "id", sessionId);
    }
    
    // add session to app42
    cJSON_AddItemReferenceToObject(app42JSON, "session", sessionJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(sessionJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
}

string SessionService::buildSetAttributeRequest(const char* sessionId,const char* attributeName,const char* attributeValue)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *sessionJSON = cJSON_CreateObject();
    
    // first construct the user
    if (strlen(sessionId))
    {
        cJSON_AddStringToObject(sessionJSON, "id", sessionId);
    }
    
    if (strlen(attributeName))
    {
        cJSON_AddStringToObject(sessionJSON, "name", attributeName);
    }
    if (strlen(attributeValue))
    {
        cJSON_AddStringToObject(sessionJSON, "value", attributeValue);
    }
    
    // add session to app42
    cJSON_AddItemReferenceToObject(app42JSON, "session", sessionJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(sessionJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
}


void SessionService::GetSession(const char* userName,App42CallBack* pTarget,SEL_App42CallFuncND pSelector)
{
    App42SessionResponse *response = new App42SessionResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
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
    string requestBody = buildGetSessionRequest(userName,"");
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "session";
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
    Util::executePost(encodedUrl, headers, requestBody.c_str(), response, app42response_selector(App42SessionResponse::onComplete));
}

void SessionService::GetSession(const char* userName, bool isCreate, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42SessionResponse *response = new App42SessionResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
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
    string requestBody = buildGetSessionRequest(userName,"");
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "session";
    if (isCreate)
    {
        resource.append("/true");
    }
    else
    {
        resource.append("/false");
    }
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
    Util::executePost(encodedUrl, headers, requestBody.c_str(), response, app42response_selector(App42SessionResponse::onComplete));
}


void SessionService::Invalidate(const char* sessionId, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42SessionResponse *response = new App42SessionResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(sessionId, "SessionId");
        
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
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
    string requestBody = buildGetSessionRequest("",sessionId);
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "session";
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
    Util::executePut(encodedUrl, headers, requestBody.c_str(), response, app42response_selector(App42SessionResponse::onComplete));
}

void SessionService::SetAttribute(const char* sessionId, const char* attributeName, const char* attributeValue, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42SessionResponse *response = new App42SessionResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(sessionId, "SessionId");
        Util::throwExceptionIfStringNullOrBlank(attributeName, "AttributeName");
        Util::throwExceptionIfStringNullOrBlank(attributeValue, "AttributeValue");

        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
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
    string requestBody = buildSetAttributeRequest("", attributeName, attributeValue);
    signParams["body"] = requestBody;
    signParams["sessionId"] = sessionId;
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "session";
    resource.append("/id/");
    resource.append(sessionId);
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
    Util::executePost(encodedUrl, headers, requestBody.c_str(), response, app42response_selector(App42SessionResponse::onComplete));
}


void SessionService::GetAttribute(const char* sessionId, const char* attributeName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42SessionResponse *response = new App42SessionResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(sessionId, "SessionId");
        Util::throwExceptionIfStringNullOrBlank(attributeName, "AttributeName");
        
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
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
    signParams["sessionId"] = sessionId;
    signParams["name"] = attributeName;

    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "session";
    resource.append("/id/");
    resource.append(sessionId);
    resource.append("/");
    resource.append(attributeName);
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
    Util::executeGet(encodedUrl, headers, response, app42response_selector(App42SessionResponse::onComplete));
}


void SessionService::GetAllAttributes (const char* sessionId, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42SessionResponse *response = new App42SessionResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(sessionId, "SessionId");
        
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
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
    signParams["sessionId"] = sessionId;
    
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "session";
    resource.append("/id/");
    resource.append(sessionId);
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
    Util::executeGet(encodedUrl, headers, response, app42response_selector(App42SessionResponse::onComplete));
}

void SessionService::RemoveAttribute(const char* sessionId, const char* attributeName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42SessionResponse *response = new App42SessionResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(sessionId, "SessionId");
        Util::throwExceptionIfStringNullOrBlank(attributeName, "AttributeName");
        
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
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
    signParams["sessionId"] = sessionId;
    signParams["name"] = attributeName;
    
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "session";
    resource.append("/id/");
    resource.append(sessionId);
    resource.append("/");
    resource.append(attributeName);
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
    Util::executeDelete(encodedUrl, headers, response, app42response_selector(App42SessionResponse::onComplete));
}


void SessionService::RemoveAllAttributes(const char* sessionId, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42SessionResponse *response = new App42SessionResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(sessionId, "SessionId");
        
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
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
    signParams["sessionId"] = sessionId;
    
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "session";
    resource.append("/id/");
    resource.append(sessionId);
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
    Util::executeDelete(encodedUrl, headers, response, app42response_selector(App42SessionResponse::onComplete));
}


