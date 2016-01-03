//
//  GeoService.cpp
//  App42Cocos2dXSample
//
//  Created by Rajeev Ranjan on 27/04/15.
//
//

#include "GeoService.h"
#include "App42GeoResponse.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "Connector.h"
#include "App42API.h"

using namespace App42Network;


// define the static..
GeoService* GeoService::_instance = NULL;

GeoService::GeoService()
{
    
}

GeoService* GeoService::Initialize(string apikey, string secretkey)
{
    if(_instance == NULL)
    {
        _instance = new GeoService();
    }
    _instance->Init(apikey, secretkey);
    return _instance;
}

GeoService* GeoService::getInstance()
{
    return _instance;
}

void GeoService::Terminate()
{
    if(_instance != NULL)
    {
        delete _instance;
        _instance = NULL;
    }
}


string GeoService::getJsonStringFromVector(vector<App42GeoPoint>list)
{
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *pointJSON = cJSON_CreateArray();
    
    std::vector<App42GeoPoint>::iterator it;
    
    for(it=list.begin(); it!=list.end(); ++it)
    {
        cJSON_AddItemToArray(pointJSON, it->getJson());
    }
    cJSON_AddItemReferenceToObject(bodyJSON, "point", pointJSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(pointJSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}

string GeoService::buildCreateGeoPointBody(const char *storageName, const char *points)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *geoJSON = cJSON_CreateObject();
    cJSON *storageJSON = cJSON_CreateObject();

    // first construct the user
    if (strlen(storageName))
    {
        cJSON_AddStringToObject(storageJSON, "storageName", storageName);
    }
    
    if (strlen(points))
    {
        cJSON_AddStringToObject(storageJSON, "points", points);
    }
    
    // add to storage
    cJSON_AddItemReferenceToObject(geoJSON, "storage", storageJSON);
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "geo", geoJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(storageJSON);
    cJSON_Delete(geoJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}


void GeoService::CreateGeoPoints(const char *geoStorageName, vector<App42GeoPoint> geoPointsList, const app42CallBack& pSelector)
{
    App42GeoResponse *response = new App42GeoResponse(pSelector);
    try
    {
        Util::throwExceptionIfStringNullOrBlank(geoStorageName, "Geo Storage Name");
        //Util::throwExceptionIfVectorIsNullOrBlank(geoPointsList, "Geo Points List");
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
    string createGeoPointsbody = buildCreateGeoPointBody(geoStorageName, getJsonStringFromVector(geoPointsList).c_str());
    signParams["body"] = createGeoPointsbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "geo";
    resource.append("/createGeoPoints");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n baseUrl = %s\n",baseUrl.c_str());
    //Util::app42Trace("\n createUserbody = %s",createGeoPointsbody.c_str());
    Util::printMap(signParams);
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
    Util::executePost(encodedUrl, headers, createGeoPointsbody.c_str(), std::bind(&App42GeoResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void GeoService::GetNearByPointsByMaxDistance(const char *geoStorageName,double lat, double lng, double distanceInKM, const app42CallBack& pSelector)
{
    App42GeoResponse *response = new App42GeoResponse(pSelector);
    try
    {
        Util::throwExceptionIfStringNullOrBlank(geoStorageName, "Geo Storage Name");
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
    signParams["storageName"] = geoStorageName;
    signParams["lat"] = Util::DtoA(lat);
    signParams["lng"] = Util::DtoA(lng);
    signParams["distanceInKM"] = Util::DtoA(distanceInKM);
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "geo";
    resource.append("/getNearByPoints/storageName/");
    resource.append(geoStorageName);
    resource.append("/lat/");
    resource.append(Util::DtoA(lat));
    resource.append("/lng/");
    resource.append(Util::DtoA(lng));
    resource.append("/distanceInKM/");
    resource.append(Util::DtoA(distanceInKM));
    
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n baseUrl = %s\n",baseUrl.c_str());
    //Util::app42Trace("\n createUserbody = %s",createGeoPointsbody.c_str());
    Util::printMap(signParams);
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42GeoResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void GeoService::GetNearByPoint(const char *geoStorageName,double lat, double lng, int resultLimit, const app42CallBack& pSelector)
{
    App42GeoResponse *response = new App42GeoResponse(pSelector);
    try
    {
        Util::throwExceptionIfStringNullOrBlank(geoStorageName, "Geo Storage Name");
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
    signParams["storageName"] = geoStorageName;
    signParams["lat"] = Util::DtoA(lat);
    signParams["lng"] = Util::DtoA(lng);
    signParams["resultLimit"] = Util::ItoA(resultLimit);
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "geo";
    resource.append("/getNearByPoint/storageName/");
    resource.append(geoStorageName);
    resource.append("/lat/");
    resource.append(Util::DtoA(lat));
    resource.append("/lng/");
    resource.append(Util::DtoA(lng));
    resource.append("/limit/");
    resource.append(Util::ItoA(resultLimit));
    
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n baseUrl = %s\n",baseUrl.c_str());
    Util::printMap(signParams);
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42GeoResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void GeoService::GetPointsWithInCircle(const char *geoStorageName,double lat, double lng, double radiusInKM, int resultLimit, const app42CallBack& pSelector)
{
    App42GeoResponse *response = new App42GeoResponse(pSelector);
    try
    {
        Util::throwExceptionIfStringNullOrBlank(geoStorageName, "Geo Storage Name");
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
    signParams["storageName"] = geoStorageName;
    signParams["lat"] = Util::DtoA(lat);
    signParams["lng"] = Util::DtoA(lng);
    signParams["radiusInKM"] = Util::DtoA(radiusInKM);
    signParams["resultLimit"] = Util::ItoA(resultLimit);
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "geo";
    resource.append("/getPointsWithInCircle/storageName/");
    resource.append(geoStorageName);
    resource.append("/lat/");
    resource.append(Util::DtoA(lat));
    resource.append("/lng/");
    resource.append(Util::DtoA(lng));
    resource.append("/radiusInKM/");
    resource.append(Util::DtoA(radiusInKM));
    resource.append("/limit/");
    resource.append(Util::ItoA(resultLimit));
    
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n baseUrl = %s\n",baseUrl.c_str());
    Util::printMap(signParams);
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42GeoResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void GeoService::GetAllStorage(const app42CallBack& pSelector)
{
    App42GeoResponse *response = new App42GeoResponse(pSelector);
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
    string resource = "geo";
    resource.append("/storage");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n baseUrl = %s\n",baseUrl.c_str());
    Util::printMap(signParams);
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42GeoResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void GeoService::GetAllStorageByPaging(int max, int offset, const app42CallBack& pSelector)
{
    App42GeoResponse *response = new App42GeoResponse(pSelector);
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
    signParams["max"] = Util::ItoA(max);
    signParams["offset"] = Util::ItoA(offset);
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "geo";
    resource.append("/paging/");
    resource.append(Util::ItoA(max));
    resource.append("/");
    resource.append(Util::ItoA(offset));
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n baseUrl = %s\n",baseUrl.c_str());
    Util::printMap(signParams);
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42GeoResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void GeoService::DeleteGeoPoints(const char *geoStorageName, vector<App42GeoPoint> geoPointsList, const app42CallBack& pSelector)
{
    App42GeoResponse *response = new App42GeoResponse(pSelector);
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
    string geoPointsbody = buildCreateGeoPointBody("", getJsonStringFromVector(geoPointsList).c_str());
    signParams["geoPoints"] = geoPointsbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "geo";
    resource.append("/points/");
    resource.append(geoStorageName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    
    /**
     * Creating Query Params
     */
    //map<string, string> queryParams;
    //queryParams["userName"] = userName;
    string queryString = buildQueryString(signParams);
    baseUrl.append(queryString);
    
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n baseUrl = %s\n",baseUrl.c_str());
    Util::printMap(signParams);
    
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
    Util::executeDelete(encodedUrl, headers, std::bind(&App42GeoResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void GeoService::DeleteStorage(const char *geoStorageName, const app42CallBack& pSelector)
{
    App42GeoResponse *response = new App42GeoResponse(pSelector);
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
    signParams["storageName"] = geoStorageName;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "geo";
    resource.append("/storage/");
    resource.append(geoStorageName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n baseUrl = %s\n",baseUrl.c_str());
    Util::printMap(signParams);
    
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
    Util::executeDelete(encodedUrl, headers, std::bind(&App42GeoResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void GeoService::GetAllPoints(const char *geoStorageName, const app42CallBack& pSelector)
{
    App42GeoResponse *response = new App42GeoResponse(pSelector);
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
    signParams["storageName"] = geoStorageName;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "geo";
    resource.append("/points/");
    resource.append(geoStorageName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n baseUrl = %s\n",baseUrl.c_str());
    Util::printMap(signParams);
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42GeoResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void GeoService::GetAllPointsByPaging(const char *geoStorageName, int max, int offset, const app42CallBack& pSelector)
{
    App42GeoResponse *response = new App42GeoResponse(pSelector);
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
    signParams["storageName"] = geoStorageName;
    signParams["max"] = Util::ItoA(max);
    signParams["offset"] = Util::ItoA(offset);
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "geo";
    resource.append("/paging/points/");
    resource.append(geoStorageName);
    resource.append("/");
    resource.append(Util::ItoA(max));
    resource.append("/");
    resource.append(Util::ItoA(offset));
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n baseUrl = %s\n",baseUrl.c_str());
    Util::printMap(signParams);
    
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
    Util::executeGet(encodedUrl, headers, std::bind(&App42GeoResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

