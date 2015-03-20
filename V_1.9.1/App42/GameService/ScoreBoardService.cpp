//
//  ScoreBoardService.cpp
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 18/10/13.
//
//

#include "ScoreBoardService.h"
#include "App42Constants.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "App42GameResponse.h"
#include "Connector.h"
#include "App42API.h"

using namespace App42Network;
// define the static..
ScoreBoardService* ScoreBoardService::_instance = NULL;

ScoreBoardService::ScoreBoardService()
{
    
}

ScoreBoardService* ScoreBoardService::Initialize(string apikey, string secretkey)
{
    if(_instance == NULL)
    {
        _instance = new ScoreBoardService();
    }
    _instance->Init(apikey,secretkey);
    return _instance;
}

ScoreBoardService* ScoreBoardService::getInstance()
{
    return _instance;
}

void ScoreBoardService::Terminate()
{
    if(_instance != NULL)
    {
        delete _instance;
		_instance = NULL;
    }
}

string BuildSaveUserScoreBody(string gameName, string userName, double score)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *gameJSON = cJSON_CreateObject();
    cJSON *sJSON = cJSON_CreateObject();
    cJSON *scoreJSON = cJSON_CreateObject();
    
    cJSON_AddNumberToObject(scoreJSON, "value", score);
    cJSON_AddStringToObject(scoreJSON, "userName", userName.c_str());
    cJSON_AddItemReferenceToObject(sJSON, "score", scoreJSON);
    
    cJSON_AddItemReferenceToObject(gameJSON, "scores", sJSON);
    cJSON_AddStringToObject(gameJSON, "name", gameName.c_str());

    cJSON_AddItemReferenceToObject(app42JSON, "game", gameJSON);
    
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

string BuildEditUserScoreBody(string scoreId, double score)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *gameJSON = cJSON_CreateObject();
    cJSON *sJSON = cJSON_CreateObject();
    cJSON *scoreJSON = cJSON_CreateObject();
    
    cJSON_AddNumberToObject(scoreJSON, "value", score);
    cJSON_AddStringToObject(scoreJSON, "scoreId", scoreId.c_str());
    cJSON_AddItemReferenceToObject(sJSON, "score", scoreJSON);
    
    cJSON_AddItemReferenceToObject(gameJSON, "scores", sJSON);

    cJSON_AddItemReferenceToObject(app42JSON, "game", gameJSON);
    
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(gameJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    cJSON_Delete(sJSON);
    cJSON_Delete(scoreJSON);
   //"{"app42":{"game":{"scores":{"score":{"value":1100,"scoreId":"oHBMmGocgkwwTPl02oMsAKtrHVc="}}}}}"
    free(cptrFormatted);
    
    return bodyString;
    
}


void ScoreBoardService::SaveUserScore(const char* gameName,const char* userName, double score, const app42CallBack& pSelector)
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
    string saveScoreBody = BuildSaveUserScoreBody(gameName, userName,score);
    postMap["body"] = saveScoreBody;
    
    string signature = Util::signMap(secretKey, postMap);
    
    string baseUrl = getBaseUrl("game/scoreboard");
    baseUrl.append("?");
    //Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    //Util::app42Trace("\n addScoreBody = %s",saveScoreBody.c_str());
    
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    string timestamp = Util::getTimeStamp();
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    Util::executePost(baseUrl, headers, saveScoreBody.c_str(), std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));

}

void ScoreBoardService::EditScoreValueById(const char* scoreId, double gameScore, const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(scoreId, "Score ID");
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
    string saveScoreBody = BuildEditUserScoreBody(scoreId, gameScore);
    postMap["body"] = saveScoreBody;
    
    string signature = Util::signMap(secretKey, postMap);
    
    string baseUrl = getBaseUrl("game/scoreboard/editscore");
    baseUrl.append("?");
    
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    string timestamp = Util::getTimeStamp();
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    Util::executePut(baseUrl, headers, saveScoreBody.c_str(), std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
    
}

void ScoreBoardService::GetAverageScoreByUser(const char* gameName, const char* userName, const app42CallBack& pSelector)
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

    string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    signParams["name"] = gameName;
    signParams["userName"] = userName;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
    resource.append("/");
    resource.append(userName);
    resource.append("/average");
    string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));

}

void ScoreBoardService::GetHighestScoreByUser(const char* gameName,const char* userName,const app42CallBack& pSelector)
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

    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    signParams["name"] = gameName;
    signParams["userName"] = userName;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
    resource.append("/");
    resource.append(userName);
    resource.append("/highest");
    string url = getBaseUrl(resource);
    string timestamp = Util::getTimeStamp();
    url.append("?");
    
    /**
     * Creating Headers
     */
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));

}

void ScoreBoardService::GetLastScoreByUser(const char* gameName,const char* userName,const app42CallBack& pSelector)
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

    
    string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    signParams["name"] = gameName;
    signParams["userName"] = userName;
    string signature = Util::signMap(secretKey, signParams);
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
    resource.append("/");
    resource.append(userName);
    resource.append("/lastscore");
    string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));

}

void ScoreBoardService::GetTopRankings(const char* gameName, tm *startDate, tm *endDate,const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
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
	populateSignParams( signParams);
	signParams["name"] = gameName;
    
    string strStartDate = Util::getTimeStamp(startDate);
    string strEndDate = Util::getTimeStamp(endDate);

    signParams["startDate"] = strStartDate;
	signParams["endDate"] = strEndDate;
	string signature = Util::signMap(secretKey, signParams);

    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
	resource.append("/ranking/");
    resource.append(strStartDate + "/");
    resource.append(strEndDate);
	string url = getBaseUrl(resource);
    url.append("?");
    
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
    
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
    
}

void ScoreBoardService::GetTopRankings(const char* gameName,const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
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
    signParams["name"] = gameName;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
    resource.append("/ranking");
    string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));

}

void ScoreBoardService::GetTopNRankers(const char* gameName, tm *startDate, tm *endDate, int max, const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
        Util::throwExceptionIfMaxIsNotValid(max, "Max");
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
	populateSignParams( signParams);
	signParams["name"] = gameName;
    signParams["max"]=Util::ItoA(max);
    
    string strStartDate = Util::getTimeStamp(startDate);
    string strEndDate = Util::getTimeStamp(endDate);
    
    signParams["startDate"] = strStartDate;
	signParams["endDate"] = strEndDate;

	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
	resource.append("/rankers/");
    resource.append(strStartDate + "/");
    resource.append(strEndDate + "/");
    resource.append(Util::ItoA(max));
    
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
    Util::executeGet(encodedUrl,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void ScoreBoardService::GetTopNRankers(const char* gameName,int max,const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
        Util::throwExceptionIfMaxIsNotValid(max, "Max");
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

    string resource = "game/scoreboard/";
    resource.append(gameName);
	resource.append("/rankers/");
    resource.append(Util::ItoA(max));
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	populateSignParams( getMap);
	getMap["name"] = gameName;
    getMap["max"]=Util::ItoA(max);
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void ScoreBoardService::GetUserRanking(const char* gameName, const char* userName,const app42CallBack& pSelector)
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

    string resource = "game/scoreboard/";
    resource.append(gameName);
    resource.append("/");
    resource.append(userName);
	resource.append("/ranking");
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	populateSignParams( getMap);
	getMap["name"] = gameName;
    getMap["userName"] = userName;
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));

}

void ScoreBoardService::GetScoresByUser(const char* gameName,const char* userName,const app42CallBack& pSelector)
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

	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
	populateSignParams( signParams);
	signParams["name"] = gameName;
    signParams["userName"] = userName;
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
    resource.append("/");
    resource.append(userName);
	string url = getBaseUrl(resource);
    url.append("?");
    
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
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
    
}


void ScoreBoardService::GetLowestScoreByUser(const char* gameName,const char* userName,const app42CallBack& pSelector)
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

	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
	populateSignParams( signParams);
	signParams["name"] = gameName;
    signParams["userName"] = userName;
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
    resource.append("/");
    resource.append(userName);
    resource.append("/lowest");
	string url = getBaseUrl(resource);
    url.append("?");
    
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
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
    
}

void ScoreBoardService::GetTopRankingsByGroup(const char* gameName,std::vector<std::string>group,const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
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
	populateSignParams( signParams);
    
    string groupString = "[";
    groupString.append(Util::GetStringFromVector(group));
    groupString.append("]");
    signParams["userList"] = groupString;
    
    string queryString = buildQueryString(signParams);
    
    signParams["name"] = gameName;
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
    resource.append("/group");
	string url = getBaseUrl(resource);
    url.append("?");
    url.append(queryString);
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
    Util::executeGet(encodedUrl,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void ScoreBoardService::GetTopRankersByGroup(const char* gameName,std::vector<std::string>group,const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
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
	populateSignParams( signParams);
    
    string groupString = "[";
    groupString.append(Util::GetStringFromVector(group));
    groupString.append("]");
    signParams["userList"] = groupString;
    
    string queryString = buildQueryString(signParams);

    signParams["name"] = gameName;
	string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
    resource.append("/");
    resource.append("rankers/group");
	string url = getBaseUrl(resource);
    url.append("?");
    url.append(queryString);
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
    Util::executeGet(encodedUrl,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
    
}

void ScoreBoardService::GetLastGameScore(const char* userName,const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
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
	populateSignParams( signParams);
    signParams["userName"] = userName;
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(userName);
    resource.append("/lastgame");
	string url = getBaseUrl(resource);
    url.append("?");
    
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
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
    
}

void ScoreBoardService::GetTopNTargetRankers(const char* gameName,int max,const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
        Util::throwExceptionIfMaxIsNotValid(max, "Max");
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
	populateSignParams( signParams);
	signParams["name"] = gameName;
    signParams["max"] = Util::ItoA(max);
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
    resource.append("/targetedrankers/");
    resource.append(Util::ItoA(max));
	string url = getBaseUrl(resource);
    url.append("?");
    
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
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void ScoreBoardService::GetTopNRankings(const char* gameName,int max,const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
        Util::throwExceptionIfMaxIsNotValid(max, "Max");
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
	populateSignParams( signParams);
	signParams["name"] = gameName;
    signParams["max"] = Util::ItoA(max);
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
    resource.append("/ranking/");
    resource.append(Util::ItoA(max));
	string url = getBaseUrl(resource);
    url.append("?");
    
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
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void ScoreBoardService::GetUsersWithScoreRange(const char* gameName,double minScore, double maxScore,const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
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
	populateSignParams( signParams);
	signParams["name"] = gameName;
    signParams["minScore"] = Util::DtoA(minScore);
    signParams["maxScore"] = Util::DtoA(maxScore);
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
    resource.append("/range/");
    resource.append(Util::DtoA(minScore) + "/");
    resource.append(Util::DtoA(maxScore));
	string url = getBaseUrl(resource);
    url.append("?");
    
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
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void ScoreBoardService::GetTopNRankersFromFacebook(const char* gameName, const char* fbAccessToken, int max, const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
        Util::throwExceptionIfStringNullOrBlank(fbAccessToken, "Access Token");
        Util::throwExceptionIfMaxIsNotValid(max, "Max");
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
    setFbAccessToken(fbAccessToken);
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
	populateSignParams(signParams);
	signParams["name"] = gameName;
    signParams["max"] = Util::ItoA(max);
	string signature = Util::signMap(secretKey, signParams);
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
    resource.append("/rankers/facebook/");
    resource.append(Util::ItoA(max));
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(signParams, headers);
    Util::BuildHeaders("", "", "", signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void ScoreBoardService::GetTopNRankersFromFacebook(const char* gameName, const char* fbAccessToken, tm *startDate, tm *endDate, int max, const app42CallBack& pSelector)
{
    App42GameResponse *response = new App42GameResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(gameName, "Game Name");
        Util::throwExceptionIfStringNullOrBlank(fbAccessToken, "Access Token");
        Util::throwExceptionIfMaxIsNotValid(max, "Max");
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
    setFbAccessToken(fbAccessToken);
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
	populateSignParams(signParams);
	signParams["name"] = gameName;
    signParams["max"] = Util::ItoA(max);
    
    string strStartDate = Util::getTimeStamp(startDate);
    string strEndDate = Util::getTimeStamp(endDate);
    
    signParams["startDate"] = strStartDate;
	signParams["endDate"] = strEndDate;
    
	string signature = Util::signMap(secretKey, signParams);
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "game/scoreboard/";
    resource.append(gameName);
    resource.append("/rankers/facebook/");
    resource.append(strStartDate + "/");
    resource.append(strEndDate + "/");
    resource.append(Util::ItoA(max));
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(signParams, headers);
    Util::BuildHeaders("", "", "", signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(url,headers, std::bind(&App42GameResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void ScoreBoardService::AddCustomScore(App42Object *app42Object, const char* collectionName)
{
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
        Util::throwExceptionIfStringNullOrBlank(App42API::getDbName().c_str(), "Collection Name");
    }
    catch (App42Exception *e)
    {
        throw e;
    }
    
    this->dbName = App42API::getDbName();
    this->collectionName = collectionName;
    this->jsonObject = app42Object->toString();
}