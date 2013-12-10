//
//  App42Service.cpp
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 07/10/13.
//
//

#include "App42Service.h"
#include "cJSON.h"
#include "App42Constants.h"
#include "Signing.h"


App42Service::App42Service()
{
    pageMaxRecords = -1;
    pageOffset = -1;
}

App42Service::~App42Service()
{
    
}

void App42Service::Init(string apikey, string secretkey)
{
    apiKey = apikey;
    secretKey = secretkey;
}


void App42Service::populateSignParams(std::map<string, string>& signParamsMap)
{
    signParamsMap["apiKey"] = apiKey;
    signParamsMap["timeStamp"] = Util::getTimeStamp();
    signParamsMap["version"] = VERSION;
}

void App42Service::populateMetaHeaderParams(std::map<string, string>& signParamsMap)
{
    signParamsMap["SDKName"] = "iOS";
}

string App42Service::getBaseUrl(string resource)
{
    string url = "";
    url.append(PROTOCOL);       //"https://"
    url.append(BASE_URL); //"api.shephertz.com"
    url.append(RESOURCE_BASE);  //"/1.0/cloud/"
    url.append(resource);       //"user"
    return url;
}