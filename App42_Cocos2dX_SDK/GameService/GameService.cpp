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
#include "cocos-ext.h"
#include "App42GameResponse.h"
#include "Connector.h"

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


void GameService::CreateGame(string gameName,string description, CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
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
    
    App42GameResponse *response = new App42GameResponse::App42GameResponse(pTarget,pSelector);
    Util::executePost(baseUrl, headers, createGamebody.c_str(), response, callfuncND_selector(App42GameResponse::onComplete));

}

void GameService::GetGamebyName(string gameName,CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
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
    
    App42GameResponse *response = new App42GameResponse::App42GameResponse(pTarget,pSelector);
    Util::executeGet(url,headers, response, callfuncND_selector(App42GameResponse::onComplete));

}

void GameService::GetAllGames(CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
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
    
    App42GameResponse *response = new App42GameResponse::App42GameResponse(pTarget,pSelector);
    Util::executeGet(url,headers, response, callfuncND_selector(App42GameResponse::onComplete));

}
