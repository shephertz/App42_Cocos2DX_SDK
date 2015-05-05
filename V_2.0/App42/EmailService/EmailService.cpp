//
//  EmailService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 08/04/14.
//
//

#include "EmailService.h"
#include "App42Constants.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "App42EmailResponse.h"
#include "Connector.h"

using namespace App42Network;
// define the static..
EmailService* EmailService::_instance = NULL;

EmailService* EmailService::Initialize(string apikey, string secretkey)
{
	if(_instance == NULL)
    {
		_instance = new EmailService();
	}
    _instance->Init(apikey, secretkey);
    return _instance;
}

EmailService* EmailService::getInstance()
{
	return _instance;
}

void EmailService::Terminate()
{
	if(_instance != NULL)
    {
		delete _instance;
		_instance = NULL;
	}
}

EmailService::EmailService()
{
    
}

string EmailService::buildSendMailBody(string sendTo, string sendSubject, string sendMsg,string fromEmail, EmailMIME emailMIME)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *emailJSON = cJSON_CreateObject();
    
    // first construct the user
    if (sendTo.length())
    {
        cJSON_AddStringToObject(emailJSON, "to", sendTo.c_str());
    }
    
    if (sendSubject.length())
    {
        cJSON_AddStringToObject(emailJSON, "subject", sendSubject.c_str());
    }
    
    if (sendMsg.length())
    {
        cJSON_AddStringToObject(emailJSON, "msg", sendMsg.c_str());
    }
    
    if (fromEmail.length())
    {
        cJSON_AddStringToObject(emailJSON, "emailId", fromEmail.c_str());
    }
    
    cJSON_AddStringToObject(emailJSON, "mimeType", getEmailMIME(emailMIME));
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "email", emailJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(emailJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}

string EmailService::buildcreateMailConfigurationBody(string emailHost, string emailPort,string emailId, string emailPassword, bool isSSL)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *emailJSON = cJSON_CreateObject();
    
    // first construct the user
    if (emailHost.length())
    {
        cJSON_AddStringToObject(emailJSON, "host", emailHost.c_str());
    }
    
    if (emailPort.length())
    {
        cJSON_AddStringToObject(emailJSON, "port", emailPort.c_str());
    }
    
    if (emailId.length())
    {
        cJSON_AddStringToObject(emailJSON, "emailId", emailId.c_str());
    }
    
    if (emailPassword.length())
    {
        cJSON_AddStringToObject(emailJSON, "password", emailPassword.c_str());
    }
    
    if(isSSL)
    {
        cJSON_AddStringToObject(emailJSON, "ssl", "true");
    }
    else
    {
       cJSON_AddStringToObject(emailJSON, "ssl", "false");
    }
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "email", emailJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(emailJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}



void EmailService::createMailConfiguration(const char* emailHost, int emailPort,const char* emailId, const char* emailPassword, bool isSSL,const app42CallBack& pSelector)
{
    App42EmailResponse *response = new App42EmailResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(emailHost, "Email Host");
        Util::throwExceptionIfStringNullOrBlank(emailPassword, "Email Password");
        Util::throwExceptionIfStringNullOrBlank(emailId, "Email Id");
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
    string createMailConfigurationbody = buildcreateMailConfigurationBody(emailHost, Util::ItoA(emailPort), emailId, emailPassword, isSSL);
    printf("createMailConfigurationbody=%s",createMailConfigurationbody.c_str());
    signParams["body"] = createMailConfigurationbody;
    string signature = Util::signMap(secretKey, signParams);
    /**
     * Creating URL
     */
    string resource = "email";
	resource.append("/configuration");
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
    Util::executePost(encodedUrl, headers, createMailConfigurationbody.c_str(), std::bind(&App42EmailResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
    
}

void EmailService::removeEmailConfiguration(const char* emailId,const app42CallBack& pSelector)
{
    App42EmailResponse *response = new App42EmailResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(emailId, "Email Id");
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
    signParams["emailId"]=emailId;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "email";
	resource.append("/configuration/");
    resource.append(emailId);
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
    Util::executeDelete(encodedUrl, headers, std::bind(&App42EmailResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
    
}

void EmailService::getEmailConfigurations(const app42CallBack& pSelector)
{
    App42EmailResponse *response = new App42EmailResponse(pSelector);
    
    try
    {
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
    string resource = "email";
	resource.append("/configuration");
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42EmailResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
    
}


void EmailService::sendMail(const char* sendTo, const char* sendSubject, const char* sendMsg,const char* fromEmail, EmailMIME emailMIME,const app42CallBack& pSelector)
{
    App42EmailResponse *response = new App42EmailResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(sendTo, "Send To");
        Util::throwExceptionIfStringNullOrBlank(sendSubject, "Send Subject");
        Util::throwExceptionIfStringNullOrBlank(sendMsg, "Message");
        Util::throwExceptionIfStringNullOrBlank(fromEmail, "From Email");
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
    string sendMailbody = buildSendMailBody(sendTo, sendSubject, sendMsg, fromEmail, emailMIME);
    signParams["body"] = sendMailbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "email";
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
    Util::executePost(encodedUrl, headers, sendMailbody.c_str(), std::bind(&App42EmailResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
    
}