//
//  GameService.cpp
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 17/10/13.
//
//

#include "GameService.h"
#include "App42Constants.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "Connector.h"
#include "Exceptions.h"

using namespace App42Network;
// define the static..
GameService* GameService::_instance = NULL;

GameService* GameService::Initialize(string apikey, string secretkey)
{
	if(_instance == NULL)
    {
		_instance = new GameService();
	}
    _instance->Init(apikey, secretkey);
    return _instance;
}

GameService* GameService::getInstance()
{
	return _instance;
}

void GameService::Terminate()
{
	if(_instance != NULL)
    {
		delete _instance;
		_instance = NULL;
	}
}

GameService::GameService()
{
    
}

string BuildCreateGameBody(string gameName, string descrption)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *gameJSON = cJSON_CreateObject();
    
    // first construct the user
    cJSON_AddStringToObject(gameJSON, "name", gameName.c_str());
    cJSON_AddStringToObject(gameJSON, "description", descrption.c_str());
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "game", gameJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(gameJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}


void GameService::CreateGame(const char* gameName,const char* description, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42GameResponse *response = new App42GameResponse(pTarget,pSelector);
    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
        Util::throwExceptionIfStringNullOrBlank(description, "Description");
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
    map<string, string> postMap;
    populateSignParams(postMap);
    string createGamebody = BuildCreateGameBody(gameName, description);
    postMap["body"] = createGamebody;
    
    string signature = Util::signMap(secretKey, postMap);
    
    string baseUrl = getBaseUrl("game");
    baseUrl.append("?");
    //Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    //Util::app42Trace("\n createGamebody = %s",createGamebody.c_str());
    
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    string timestamp = Util::getTimeStamp();
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    
    Util::executePost(baseUrl, headers, createGamebody.c_str(), response, app42response_selector(App42GameResponse::onComplete));
}

void GameService::GetGamebyName(const char* gameName,App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42GameResponse *response = new App42GameResponse(pTarget,pSelector);

    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
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
    
    string resource = "game/";
	resource.append(gameName);
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
	getMap["name"] = gameName;
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    Util::executeGet(url,headers, response, app42response_selector(App42GameResponse::onComplete));
}

void GameService::GetAllGames(App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42GameResponse *response = new App42GameResponse(pTarget,pSelector);

    try
    {
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
    
    string resource = "game/";
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    Util::executeGet(url,headers, response, app42response_selector(App42GameResponse::onComplete));

}

void GameService::GetAllGames(int max, int offset, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42GameResponse *response = new App42GameResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfMaxIsNotValid(max, "Max");
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
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signParams);
    signParams["max"] = Util::ItoA(max);
    signParams["offset"] = Util::ItoA(offset);
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "game/";
    resource.append("paging/");
    resource.append(Util::ItoA(max) + "/");
    resource.append(Util::ItoA(offset));
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);
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
    Util::executeGet(encodedUrl,headers, response, app42response_selector(App42GameResponse::onComplete));
    
}

void GameService::GetAllGamesCount(App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42GameResponse *response = new App42GameResponse(pTarget,pSelector);
    
    try
    {
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
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signParams);
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "game/";
    resource.append("count");
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);
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
    Util::executeGet(encodedUrl,headers, response, app42response_selector(App42GameResponse::onComplete));
    
}
