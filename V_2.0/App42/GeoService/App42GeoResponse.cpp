//
//  App42GeoResponse.cpp
//  App42Cocos2dXSample
//
//  Created by Rajeev Ranjan on 27/04/15.
//
//

#include "App42GeoResponse.h"
#include "Common.h"


App42GeoResponse::App42GeoResponse(const app42CallBack& pSelector)
:App42Response(pSelector)
{
    
}

App42GeoResponse::~App42GeoResponse()
{
    geoList.clear();
}

void App42GeoResponse::init()
{
    if(_result != 200)
    {
        Util::app42Trace("App42GeoResponse failed result is %d", _result);
        buildErrorMessage();
        return;
    }
    // parse the body
    cJSON *ptrBody = cJSON_Parse(_body.c_str());
    cJSON* ptrApp42 = Util::getJSONChild("app42", ptrBody);
    cJSON* ptrResponse = Util::getJSONChild("response", ptrApp42);
    cJSON* ptrGeo = Util::getJSONChild("geo", ptrResponse);
    if (ptrGeo)
    {
        cJSON* ptrStorage = Util::getJSONChild("storage", ptrGeo);
        
        if (ptrStorage)
        {
            cJSON* child = ptrStorage;
            if(child->type == cJSON_Array)
            {
                child = child->child;
            }
            
            while(child != NULL && child->type == cJSON_Object)
            {
                App42Geo app42Geo;
                app42Geo.storageName = Util::getJSONString("storageName", child);
                app42Geo.sourceLat = Util::getJSONDouble("sourceLat", child);
                app42Geo.sourceLng = Util::getJSONDouble("sourceLng", child);
                app42Geo.distanceInKM = Util::getJSONDouble("distanceInKM", child);
//                app42User.email = Util::getJSONString("email", child);
//                app42User.isAccountLocked = Util::getJSONInt("accountLocked", child);
//                app42User.sessionId = Util::getJSONString("sessionId", child);
//                app42User.createdOn = Util::getJSONString("createdOn", child);
//                app42User.password = Util::getJSONString("password", child);
//                
//                cJSON* ptrUserProfile = Util::getJSONChild("profile", child);
//                if (ptrUserProfile)
//                {
//                    app42User.profile = buildUserProfile(ptrUserProfile);
//                }
                geoList.push_back(app42Geo);
                child = child->next;
            }
        }
    }
    else
    {
        setTotalRecords();
    }
    
    cJSON_Delete(ptrBody);
}



void App42GeoResponse::onComplete(void *sender, void *data)
{
    App42Response::onComplete(sender, data);
    init();
    
    if (_app42Selector)
    {
        _app42Selector(this);
    }
}
