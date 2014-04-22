//
//  Connector.h
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 16/10/13.
//
//

#ifndef App42CPPSDK_Connector_h
#define App42CPPSDK_Connector_h

#include "cocos-ext.h"
#include "cocos2d.h"
#include "App42UserResponse.h"
#include "curl/curl.h"
#include "Common.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpClient.h"

using namespace std;
using namespace cocos2d;

namespace Util
{
    
    static const char* url_encode(string &url)
    {
        CURL *curl = curl_easy_init();
        char *str = curl_easy_escape(curl, url.c_str(), url.size());
        return str;
    }
    
    static void printMap(map<std::string, std::string>map)
    {
        std::map<string,string>::iterator it;
        
        for(it=map.begin(); it!=map.end(); ++it)
        {
            printf("\n%s=%s",it->first.c_str(),it->second.c_str());
        }
    }
    
    static void printVector(vector<std::string>vector)
    {
        std::vector<string>::iterator it;
        
        for(it=vector.begin(); it!=vector.end(); ++it)
        {
            printf("\n%s",it->c_str());
        }
    }
    
    static void executePost(string baseUrl,std::vector<std::string> headers, const char* postData,Object* pTarget, cocos2d::network::SEL_HttpResponse pSelector)
    {
        
        cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
        request->setUrl(baseUrl.c_str());
        request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
        
        headers.push_back("Accept: application/json");
        headers.push_back("Content-Type: application/json");
        headers.push_back("SDKName: Cocos2d-X");
        
        request->setHeaders(headers);
        request->setResponseCallback(pTarget, pSelector);
        
        request->setRequestData(postData, strlen(postData));
        
        cocos2d::network::HttpClient::getInstance()->send(request);
        request->release();
        return;
    }
    
    static void executePut(string baseUrl,std::vector<std::string> headers, const char* postData,Object* pTarget, cocos2d::network::SEL_HttpResponse pSelector)
    {
        cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
        request->setUrl(baseUrl.c_str());
        request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
        
        headers.push_back("Accept: application/json");
        headers.push_back("Content-Type: application/json");
        headers.push_back("SDKName: Cocos2d-X");
        headers.push_back("Custom-Headers: PUT");
        request->setHeaders(headers);
        
        request->setResponseCallback(pTarget, pSelector);
        
        request->setRequestData(postData, strlen(postData));
        
        cocos2d::network::HttpClient::getInstance()->send(request);
        request->release();
        return;
    }

    static void executeGet(string baseUrl,std::vector<std::string> headers,Object* pTarget, cocos2d::network::SEL_HttpResponse pSelector)
    {
        cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
        request->setUrl(baseUrl.c_str());
        request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
        
        headers.push_back("Accept: application/json");
        headers.push_back("Content-Type: application/json");
        headers.push_back("SDKName: Cocos2d-X");
        
        request->setHeaders(headers);
        request->setResponseCallback(pTarget, pSelector);
        
        cocos2d::network::HttpClient::getInstance()->send(request);
        request->release();
        return;
    }
    
    static void executeDelete(string baseUrl,std::vector<std::string> headers,Object* pTarget, cocos2d::network::SEL_HttpResponse pSelector)
    {
        cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
        request->setUrl(baseUrl.c_str());
        request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
        
        headers.push_back("Accept: application/json");
        headers.push_back("Content-Type: application/json");
        headers.push_back("SDKName: Cocos2d-X");
        headers.push_back("Custom-Headers:DELETE");
        
        request->setHeaders(headers);
        
        request->setResponseCallback(pTarget, pSelector);
        
        cocos2d::network::HttpClient::getInstance()->send(request);
        request->release();
        return;
    }
    
}



#endif
