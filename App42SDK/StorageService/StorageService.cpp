//
//  StorageService.cpp
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 21/10/13.
//
//

#include "StorageService.h"
#include "App42Constants.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "cocos-ext.h"
#include "App42StorageResponse.h"
#include "Connector.h"

// define the static..
StorageService* StorageService::_instance = NULL;

void StorageService::Initialize(string apikey, string secretkey)
{
	if(_instance == NULL)
    {
		_instance = new StorageService();
	}
    _instance->Init(apikey, secretkey);
}

StorageService* StorageService::getInstance()
{
	return _instance;
}

void StorageService::Terminate()
{
	if(_instance != NULL)
    {
		delete _instance;
		_instance = NULL;
	}
}

StorageService::StorageService()
{
    
}

string BuildStorageBody(string json)
{
	cJSON *bodyJSON = cJSON_CreateObject();
	cJSON *app42JSON = cJSON_CreateObject();
	cJSON *storageJSON = cJSON_CreateObject();
    
	cJSON_AddStringToObject(storageJSON, "jsonDoc", json.c_str());
	cJSON_AddItemReferenceToObject(app42JSON, "storage", storageJSON);
    
	cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
	char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
	string bodyString = cptrFormatted;
    
	cJSON_Delete(storageJSON);
	cJSON_Delete(app42JSON);
	cJSON_Delete(bodyJSON);
	free(cptrFormatted);
    
	return bodyString;
    
}


void StorageService::InsertJsonDocument(string dbName, string collectionName, string json, CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
    
    map<string, string> postMap;
    string timestamp = Util::getTimeStamp();
    populateSignParams(postMap);
    postMap["dbName"] = dbName;
	postMap["collectionName"] = collectionName;
    
    
    string storageBody = BuildStorageBody(json);
    postMap["body"] = storageBody;
    
    
    string signature = Util::signMap(secretKey, postMap);
    
    string resource = "storage/insert/dbName/";
    resource.append(dbName + "/collectionName/");
	resource.append(collectionName);
    string baseUrl = getBaseUrl(resource);
    
    baseUrl.append("?");
    //Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    //Util::app42Trace("\n createRewardbody = %s",storageBody.c_str());
    
    std::vector<std::string> headers;
    
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    Util::executePost(baseUrl, headers, storageBody.c_str(), response, callfuncND_selector(App42StorageResponse::onComplete));
}


void StorageService::FindAllCollections(string dbName, CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
    string resource = "storage/findCollections/dbName/";
    resource.append(dbName);
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
    getMap["dbName"] = dbName;
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    Util::executeGet(url,headers, response, callfuncND_selector(App42StorageResponse::onComplete));
}

void StorageService::FindAllDocuments(string dbName, string collectionName, CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
    string resource = "storage/findAll/dbName/";
	resource.append(dbName+ "/collectionName/");
	resource.append(collectionName);
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
    getMap["dbName"] = dbName;
    getMap["collectionName"] = collectionName;
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    Util::executeGet(url,headers, response, callfuncND_selector(App42StorageResponse::onComplete));

}

void StorageService::FindDocumentById(string dbName, string collectionName, string docId, CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
    string resource = "storage/findDocById/dbName/";
	resource.append(dbName + "/collectionName/");
	resource.append(collectionName + "/docId/");
	resource.append(docId);
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
    getMap["dbName"] = dbName;
    getMap["collectionName"] = collectionName;
    getMap["docId"] = docId;
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    Util::executeGet(url,headers, response, callfuncND_selector(App42StorageResponse::onComplete));

}

void StorageService::FindDocumentByKeyValue(string dbName, string collectionName, string key,string value, CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
{
    string resource = "storage/findDocByKV/dbName/";
	resource.append(dbName+ "/collectionName/");
	resource.append(collectionName+ "/");
	resource.append(key+ "/");
	resource.append(value+ "/");
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
    getMap["dbName"] = dbName;
    getMap["collectionName"] = collectionName;
    getMap["key"] = key;
	getMap["value"] = value;
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    Util::executeGet(url,headers, response, callfuncND_selector(App42StorageResponse::onComplete));

}