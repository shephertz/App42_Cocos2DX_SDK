//
//  App42Service.h
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 07/10/13.
//
//

#ifndef __App42CPPSDK__App42Service__
#define __App42CPPSDK__App42Service__

#include <iostream>
#include <map>

class App42Service
{
public:
    
    App42Service();
    ~App42Service();
    
    void Init(std::string apikey, std::string secretkey);
    
    std::string apiKey;
    std::string secretKey;
    std::string appVersion;
    std::string sessionId;
    std::string adminKey;
    
    int pageOffset;
    int pageMaxRecords;

    std::string getSessionId(){return sessionId;}
    std::string getBaseUrl(std::string resource);

    void populateSignParams(std::map<std::string, std::string>& signParamsMap);
    void populateMetaHeaderParams(std::map<std::string, std::string>& signParamsMap);
    
protected:
    
private:
    
};

#endif /* defined(__App42CPPSDK__App42Service__) */
