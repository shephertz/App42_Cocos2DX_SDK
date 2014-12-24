//
//  UploadService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 04/04/14.
//
//

#include "UploadService.h"
#include "App42Constants.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "App42UploadResponse.h"
#include "Connector.h"

using namespace App42Network;

// define the static..
UploadService* UploadService::_instance = NULL;

UploadService* UploadService::Initialize(string apikey, string secretkey)
{
	if(_instance == NULL)
    {
		_instance = new UploadService();
	}
    _instance->Init(apikey, secretkey);
    return _instance;
}

UploadService* UploadService::getInstance()
{
	return _instance;
}

void UploadService::Terminate()
{
	if(_instance != NULL)
    {
		delete _instance;
		_instance = NULL;
	}
}

UploadService::UploadService()
{
    
}

void UploadService::UploadFile(const char * fileName, unsigned char* inputStream,int fileDataSize,FileType fileType, const char * description, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(fileName, "File Name");
        Util::throwExceptionIfStringNullOrBlank(description, "Description");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    try {
        /**
         * Creating SignParams and signature
         */
        map<string, string> signParams;
        string timestamp = Util::getTimeStamp();
        populateSignParams(signParams);
        signParams["name"] = fileName;
        signParams["type"] = getUploadFileType(fileType);
        signParams["description"] = description;
        
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating PostParamsMap
         */
        map<string, string> postParams;
        postParams["name"] = fileName;
        postParams["type"] = getUploadFileType(fileType);
        postParams["description"] = description;
        
        /**
         * Creating URL
         */
        string resource = "upload";
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
		Util::executeMultiPartWithFileData("uploadFile", fileName, inputStream, fileDataSize, postParams, encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));

        
    }
    catch (exception *e)
    {
        throw e;
    }
}


void UploadService::UploadFile(const char * fileName, const char * filePath,FileType fileType, const char * description,SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
        Util::throwExceptionIfStringNullOrBlank(fileName, "File Name");
        Util::throwExceptionIfStringNullOrBlank(filePath, "File Path");
        Util::throwExceptionIfStringNullOrBlank(description, "Description");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pSelector)
        {
            pSelector(response);
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
        signParams["type"] = getUploadFileType(fileType);
        signParams["description"] = description;
        
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating PostParamsMap
         */
        map<string, string> postParams;
        postParams["name"] = fileName;
        postParams["type"] = getUploadFileType(fileType);
        postParams["description"] = description;

        /**
         * Creating URL
         */
        string resource = "upload";
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
		Util::executeMultiPartWithFile("uploadFile", fileName, filePath, postParams, encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::GetAllFiles(SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pSelector)
        {
            pSelector(response);
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
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload";
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
		Util::executeGet(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::GetAllFilesCount(SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pSelector)
        {
            pSelector(response);
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
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload";
        resource.append("/count");
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
		Util::executeGet(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::GetAllFiles(int max, int offset, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
        Util::throwExceptionIfMaxIsNotValid(max, "Max");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pSelector)
        {
            pSelector(response);
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
        signParams["max"] = Util::ItoA(max);
        signParams["offset"]=Util::ItoA(offset);
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload";
        resource.append("/paging/");
        resource.append(Util::ItoA(max) + "/");
        resource.append(Util::ItoA(offset));

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
		Util::executeGet(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::GetFileByUser(const char * fileName, const char * userName, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
        Util::throwExceptionIfStringNullOrBlank(fileName, "File Name");
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
        if (pSelector)
        {
            pSelector(response);
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
        signParams["userName"]= userName;
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload/";
        resource.append(userName);
        resource.append("/");
        resource.append(fileName);
        
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
		Util::executeGet(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::GetAllFilesByUser(const char * userName, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
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
        if (pSelector)
        {
            pSelector(response);
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
        signParams["userName"]= userName;
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload";
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
		Util::executeGet(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::GetAllFilesByUser(const char * userName, int max, int offset, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
        Util::throwExceptionIfMaxIsNotValid(max, "Max");
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
        if (pSelector)
        {
            pSelector(response);
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
        signParams["userName"]= userName;
        signParams["max"] = Util::ItoA(max);
        signParams["offset"]=Util::ItoA(offset);
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload";
        resource.append("/user/");
        resource.append(userName);
        resource.append("/" + Util::ItoA(max) + "/");
        resource.append(Util::ItoA(offset));
        
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
		Util::executeGet(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}


void UploadService::GetAllFilesCountByUser(const char * userName, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
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
        if (pSelector)
        {
            pSelector(response);
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
        signParams["userName"]= userName;
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload";
        resource.append("/user/");
        resource.append(userName);
        resource.append("/count");
        
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
		Util::executeGet(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::GetFileByName(const char * fileName, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
        Util::throwExceptionIfStringNullOrBlank(fileName, "File Name");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pSelector)
        {
            pSelector(response);
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
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload/";
        resource.append(fileName);
        
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
		Util::executeGet(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::RemoveFileByUser(const char * fileName, const char * userName, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
        Util::throwExceptionIfStringNullOrBlank(fileName, "File Name");
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
        if (pSelector)
        {
            pSelector(response);
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
        signParams["userName"]= userName;
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload/";
        resource.append(userName);
        resource.append("/");
        resource.append(fileName);
        
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
		Util::executeDelete(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::RemoveAllFilesByUser(const char * userName, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
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
        if (pSelector)
        {
            pSelector(response);
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
        signParams["userName"]= userName;
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload";
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
		Util::executeDelete(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::RemoveFileByName(const char * fileName, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
        Util::throwExceptionIfStringNullOrBlank(fileName, "File Name");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pSelector)
        {
            pSelector(response);
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
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload/";
        resource.append(fileName);
        
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
		Util::executeDelete(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::RemoveAllFiles(SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pSelector)
        {
            pSelector(response);
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
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload";
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
		Util::executeDelete(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}


void UploadService::GetFilesCountByType(FileType fileType, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
        //Util::throwExceptionIfStringNullOrBlank(fileName, "File Name");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pSelector)
        {
            pSelector(response);
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
        signParams["type"] = getUploadFileType(fileType);
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload";
        resource.append("/type/");
        resource.append(getUploadFileType(fileType));
        resource.append("/count");
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
		Util::executeGet(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::GetFilesByType(FileType fileType, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
        //Util::throwExceptionIfStringNullOrBlank(fileName, "File Name");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pSelector)
        {
            pSelector(response);
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
        signParams["type"] = getUploadFileType(fileType);
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload";
        resource.append("/type/");
        resource.append(getUploadFileType(fileType));
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
		Util::executeGet(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::GetFilesByType(FileType fileType, int max, int offset, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
        //Util::throwExceptionIfStringNullOrBlank(fileName, "File Name");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pSelector)
        {
            pSelector(response);
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
        signParams["type"] = getUploadFileType(fileType);
        signParams["max"] = Util::ItoA(max);
        signParams["offset"]=Util::ItoA(offset);
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "upload";
        resource.append("/type/");
        resource.append(getUploadFileType(fileType));
        resource.append("/" + Util::ItoA(max) + "/");
        resource.append(Util::ItoA(offset));
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
		Util::executeGet(encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::UploadFileForUser(const char * fileName, const char * userName, unsigned char* inputStream,int fileDataSize,FileType fileType, const char * description, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(fileName, "File Name");
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(description, "Description");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    try {
        /**
         * Creating SignParams and signature
         */
        map<string, string> signParams;
        string timestamp = Util::getTimeStamp();
        populateSignParams(signParams);
        signParams["name"] = fileName;
        signParams["userName"] = userName;
        signParams["type"] = getUploadFileType(fileType);
        signParams["description"] = description;
        
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating PostParamsMap
         */
        map<string, string> postParams;
        postParams["name"] = fileName;
        postParams["userName"] = userName;
        postParams["type"] = getUploadFileType(fileType);
        postParams["description"] = description;
        
        /**
         * Creating URL
         */
        string resource = "upload/";
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
		Util::executeMultiPartWithFileData("uploadFile", fileName, inputStream, fileDataSize, postParams, encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}

void UploadService::UploadFileForUser(const char * fileName, const char * userName, const char * filePath,FileType fileType, const char * description, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse(pSelector);
    try
    {
        Util::throwExceptionIfStringNullOrBlank(fileName, "File Name");
        Util::throwExceptionIfStringNullOrBlank(filePath, "File Path");
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(description, "Description");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pSelector)
        {
            pSelector(response);
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
        signParams["userName"] = userName;
        signParams["type"] = getUploadFileType(fileType);
        signParams["description"] = description;
        
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating PostParamsMap
         */
        map<string, string> postParams;
        postParams["name"] = fileName;
        postParams["userName"] = userName;
        postParams["type"] = getUploadFileType(fileType);
        postParams["description"] = description;
        
        /**
         * Creating URL
         */
        string resource = "upload/";
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
		Util::executeMultiPartWithFile("uploadFile", fileName, filePath, postParams, encodedUrl, headers, std::bind(&App42UploadResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}