//
//  ScoreService.cpp
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 18/10/13.
//
//

#include "ScoreService.h"
#include "App42Constants.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "App42GameResponse.h"
#include "Connector.h"

using namespace App42Network;
// define the static..
ScoreService* ScoreService::_instance = NULL;

ScoreService::ScoreService()
{
    
}

ScoreService* ScoreService::Initialize(string apikey, string secretkey)
{
    if(_instance == NULL)
    {
        _instance = new ScoreService();
    }
    _instance->Init(apikey,secretkey);
    return _instance;
}

ScoreService* ScoreService::getInstance()
{
    return _instance;
}

void ScoreService::Terminate()
{
    if(_instance != NULL)
    {
        delete _instance;
		_instance = NULL;
    }
}

string BuildScoreBody(string gameName, string userName, double score)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *gameJSON = cJSON_CreateObject();
    cJSON *sJSON = cJSON_CreateObject();
    cJSON *scoreJSON = cJSON_CreateObject();
    
    cJSON_AddStringToObject(gameJSON, "name", gameName.c_str());
    cJSON_AddNumberToObject(scoreJSON, "value", score);
    cJSON_AddStringToObject(scoreJSON, "userName", userName.c_str());
    cJSON_AddItemReferenceToObject(sJSON, "score", scoreJSON);
    
    cJSON_AddItemReferenceToObject(app42JSON, "game", gameJSON);
    cJSON_AddItemReferenceToObject(gameJSON, "scores", sJSON);
    
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(gameJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    cJSON_Delete(sJSON);
    cJSON_Delete(scoreJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}


void ScoreService::AddScore(const char* gameName, const char* userName, double score, const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
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

    map<string, string> postMap;
    populateSignParams(postMap);
    string addScoreBody = BuildScoreBody(gameName, userName,score);
    postMap["body"] = addScoreBody;
    
    string signature = Util::signMap(secretKey, postMap);
    
    string baseUrl = getBaseUrl("game/score/add");
    baseUrl.append("?");
    //Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    //Util::app42Trace("\n addScoreBody = %s",addScoreBody.c_str());
    
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    string timestamp = Util::getTimeStamp();
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    Util::executePost(baseUrl, headers, addScoreBody.c_str(), std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}



void ScoreService::DeductScore(const char* gameName, const char* userName, double score, const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
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
    map<string, string> postMap;
    populateSignParams(postMap);
    string deductScoreBody = BuildScoreBody(gameName, userName,score);
    postMap["body"] = deductScoreBody;
    
    string signature = Util::signMap(secretKey, postMap);
    
    string baseUrl = getBaseUrl("game/score/deduct");
    baseUrl.append("?");
   
    
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    string timestamp = Util::getTimeStamp();
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    Util::executePost(baseUrl, headers, deductScoreBody.c_str(), std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


