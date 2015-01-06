//
//  TimerService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev on 19/08/14.
//
//

#include "TimerService.h"
#include "App42Constants.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "App42TimerResponse.h"
#include "Connector.h"

using namespace App42Network;
// define the static..
TimerService* TimerService::_instance = NULL;

TimerService* TimerService::Initialize(string apikey, string secretkey)
{
	if(_instance == NULL)
    {
		_instance = new TimerService();
	}
    _instance->Init(apikey, secretkey);
    return _instance;
}

TimerService* TimerService::getInstance()
{
	return _instance;
}

void TimerService::Terminate()
{
	if(_instance != NULL)
    {
		delete _instance;
		_instance = NULL;
	}
}

TimerService::TimerService()
{
    
}

string TimerService::buildCreateTimerBody(const char *timerName, long timeInSeconds)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *timerJSON = cJSON_CreateObject();
    
    // first construct the user
    if (strlen(timerName))
    {
        cJSON_AddStringToObject(timerJSON, "name", timerName);
    }
    
    //cJSON_AddStringToObject(timerJSON, "timeInSeconds", Util::LtoA(timeInSeconds).c_str());
    cJSON_AddNumberToObject(timerJSON, "timeInSeconds", timeInSeconds);
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "timer", timerJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(timerJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}

string TimerService::buildStartTimerBody(const char *timerName, const char * userName)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *timerJSON = cJSON_CreateObject();
    
    // first construct the timer
    if (strlen(timerName))
    {
        cJSON_AddStringToObject(timerJSON, "name", timerName);
    }
    
    if (strlen(timerName))
    {
        cJSON_AddStringToObject(timerJSON, "userName", userName);
    }
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "timer", timerJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(timerJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}


void TimerService::CreateOrUpdateTimer(const char* timerName, long timeInSeconds,const app42CallBack& pSelector)
{
    App42TimerResponse *response = new App42TimerResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(timerName, "Timer Name");
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
    string body = buildCreateTimerBody(timerName, timeInSeconds);
    signParams["body"] = body;
    string signature = Util::signMap(secretKey, signParams);
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string baseUrl = getBaseUrl("timer");
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
    Util::executePost(encodedUrl, headers, body.c_str(), std::bind(&App42TimerResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void TimerService::StartTimer(const char* timerName, const char* userName,const app42CallBack& pSelector)
{
    App42TimerResponse *response = new App42TimerResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(timerName, "Timer Name");
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
    string body = buildStartTimerBody(timerName, userName);
    signParams["body"] = body;
    string signature = Util::signMap(secretKey, signParams);
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string baseUrl = getBaseUrl("timer/startTimer");
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
    Util::executePost(encodedUrl, headers, body.c_str(), std::bind(&App42TimerResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void TimerService::IsTimerActive(const char* timerName, const char* userName,const app42CallBack& pSelector)
{
    App42TimerResponse *response = new App42TimerResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(timerName, "Timer Name");
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
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
    string body = buildStartTimerBody(timerName, userName);
    signParams["body"] = body;
    string signature = Util::signMap(secretKey, signParams);
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string baseUrl = getBaseUrl("timer/isTimerActive");
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
    Util::executePost(encodedUrl, headers, body.c_str(), std::bind(&App42TimerResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void TimerService::CancelTimer(const char* timerName, const char* userName,const app42CallBack& pSelector)
{
    App42TimerResponse *response = new App42TimerResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(timerName, "Timer Name");
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
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
    signParams["name"] = timerName;
    signParams["userName"] = userName;
    string signature = Util::signMap(secretKey, signParams);
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "timer/";
    resource.append(timerName);
    resource.append("/user/");
    resource.append(userName);
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
    Util::executeDelete(encodedUrl, headers, std::bind(&App42TimerResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void TimerService::DeleteTimer(const char* timerName, const app42CallBack& pSelector)
{
    App42TimerResponse *response = new App42TimerResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(timerName, "Timer Name");
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
    signParams["name"] = timerName;
    string signature = Util::signMap(secretKey, signParams);
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "timer/";
    resource.append(timerName);
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
    Util::executeDelete(encodedUrl, headers, std::bind(&App42TimerResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void TimerService::GetCurrentTime(const app42CallBack& pSelector)
{
    App42TimerResponse *response = new App42TimerResponse(pSelector);
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string signature = Util::signMap(secretKey, signParams);
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "timer/currentTime";
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42TimerResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

