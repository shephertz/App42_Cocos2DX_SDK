//
//  CustomCodeService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 14/05/14.
//
//

#include "CustomCodeService.h"
#include "App42Constants.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "Connector.h"
#include "App42CustomCodeResponse.h"

using namespace App42Network;
// define the static..
CustomCodeService* CustomCodeService::_instance = NULL;

CustomCodeService* CustomCodeService::Initialize(string apikey, string secretkey)
{
	if(_instance == NULL)
    {
		_instance = new CustomCodeService();
	}
    _instance->Init(apikey, secretkey);
    return _instance;
}

CustomCodeService* CustomCodeService::getInstance()
{
	return _instance;
}

void CustomCodeService::Terminate()
{
	if(_instance != NULL)
    {
		delete _instance;
		_instance = NULL;
	}
}

CustomCodeService::CustomCodeService()
{
    
}

void CustomCodeService::RunJavaCode(const char* name, App42Object *jsonBody,const app42CallBack& pSelector)
{
    App42CustomCodeResponse *response = new App42CustomCodeResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(name, "File Name");
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
    string resource = "run/java/";
    resource.append(name);
	string baseUrl = getCustomCodeUrl(resource);
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
    Util::executePost(encodedUrl, headers, jsonBody->toString().c_str(), std::bind(&App42Response::onComplete, response, std::placeholders::_1, std::placeholders::_2));
    
}

void CustomCodeService::RunJavaCode(const char* name, const char* jsonString, const app42CallBack& pSelector)
{
    App42CustomCodeResponse *response = new App42CustomCodeResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(name, "File Name");
        Util::throwExceptionIfStringNullOrBlank(jsonString, "Json Body");
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
    string resource = "run/java/";
    resource.append(name);
    string baseUrl = getCustomCodeUrl(resource);
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
    Util::executePost(encodedUrl, headers, jsonString, std::bind(&App42Response::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}
