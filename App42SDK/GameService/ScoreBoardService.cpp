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
#include "cocos-ext.h"
#include "App42GameResponse.h"
#include "Connector.h"

// define the static..
ScoreBoardService* ScoreBoardService::_instance = NULL;

ScoreBoardService::ScoreBoardService()
{
    
}

void ScoreBoardService::Initialize(string apikey, string secretkey)
{
    if(_instance == NULL)
    {
        _instance = new ScoreBoardService();
    }
    _instance->Init(apikey,secretkey);
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

void ScoreBoardService::SaveUserScore(string gameName,string userName, double score, cocos2d::CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
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
    string timestamp = Util::getTimeStamp();
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    App42GameResponse *response = new App42GameResponse::App42GameResponse(pTarget,pSelector);
    Util::executePost(baseUrl, headers, saveScoreBody.c_str(), response, callfuncND_selector(App42GameResponse::onComplete));

}

void ScoreBoardService::GetAverageScoreByUser(string gameName, string userName, cocos2d::CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
    string resource = "game/scoreboard/";
    resource.append(gameName+"/");
    resource.append(userName);
	resource.append("/average");
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
	getMap["name"] = gameName;
    getMap["userName"] = userName;
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    App42GameResponse *response = new App42GameResponse::App42GameResponse(pTarget,pSelector);
    Util::executeGet(url,headers, response, callfuncND_selector(App42GameResponse::onComplete));

}

void ScoreBoardService::GetHighestScoreByUser(string gameName,string userName,cocos2d::CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
    string resource = "game/scoreboard/";
    resource.append(gameName+"/");
    resource.append(userName);
	resource.append("/highest");
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
	getMap["name"] = gameName;
    getMap["userName"] = userName;
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    App42GameResponse *response = new App42GameResponse::App42GameResponse(pTarget,pSelector);
    Util::executeGet(url,headers, response, callfuncND_selector(App42GameResponse::onComplete));

}

void ScoreBoardService::GetLastScoreByUser(string gameName,string userName,cocos2d::CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
    string resource = "game/scoreboard/";
    resource.append(gameName+"/");
    resource.append(userName);
	resource.append("/lastscore");
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
	getMap["name"] = gameName;
    getMap["userName"] = userName;
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    App42GameResponse *response = new App42GameResponse::App42GameResponse(pTarget,pSelector);
    Util::executeGet(url,headers, response, callfuncND_selector(App42GameResponse::onComplete));

}

void ScoreBoardService::GetTopRankings(string gameName,cocos2d::CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
    string resource = "game/scoreboard/";
    resource.append(gameName);
	resource.append("/ranking");
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
	getMap["name"] = gameName;
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    App42GameResponse *response = new App42GameResponse::App42GameResponse(pTarget,pSelector);
    Util::executeGet(url,headers, response, callfuncND_selector(App42GameResponse::onComplete));

}

void ScoreBoardService::GetUserRanking(string gameName, string userName,cocos2d::CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
    string resource = "game/scoreboard/";
    resource.append(gameName+"/");
    resource.append(userName);
	resource.append("/ranking");
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
	getMap["name"] = gameName;
    getMap["userName"] = userName;
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    App42GameResponse *response = new App42GameResponse::App42GameResponse(pTarget,pSelector);
    Util::executeGet(url,headers, response, callfuncND_selector(App42GameResponse::onComplete));

}
