//
//  App42BuddyResponse.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 18/07/14.
//
//

#include "App42BuddyResponse.h"
#include "Common.h"


App42BuddyResponse::App42BuddyResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector)
:App42Response(pTarget,pSelector)
{
    
}

App42BuddyResponse::~App42BuddyResponse()
{
    buddyList.clear();
}

void App42BuddyResponse::init()
{
    if(_result != 200)
    {
        Util::app42Trace("App42User failed result is %d", _result);
        buildErrorMessage();
        return;
    }
    // parse the body
    cJSON *ptrBody = cJSON_Parse(_body.c_str());
    cJSON* ptrApp42 = Util::getJSONChild("app42", ptrBody);
    cJSON* ptrResponse = Util::getJSONChild("response", ptrApp42);
    cJSON* ptrBuddies = Util::getJSONChild("buddies", ptrResponse);
    
    if (ptrBuddies)
    {
        cJSON* ptrBuddy = Util::getJSONChild("buddy", ptrBuddies);
        
        if (ptrBuddy)
        {
            cJSON* child = ptrBuddy;
            if(child->type == cJSON_Array)
            {
                child = child->child;
            }
            
            while(child != NULL && child->type == cJSON_Object)
            {
                App42Buddy app42Buddy;
                app42Buddy.userName = Util::getJSONString("userName", child);
                app42Buddy.buddyName = Util::getJSONString("buddyName", child);
                app42Buddy.groupName = Util::getJSONString("groupName", child);
                app42Buddy.ownerName = Util::getJSONString("ownerName", child);
                app42Buddy.messageId = Util::getJSONString("messageId", child);
                app42Buddy.message = Util::getJSONString("message", child);
                app42Buddy.sentOn = Util::getJSONString("sendedOn", child);
                app42Buddy.acceptedOn = Util::getJSONString("acceptedOn", child);

                cJSON *ptrPoints = Util::getJSONChild("points", child);
                if (ptrPoints != NULL)
                {
                    cJSON *ptrPoint = Util::getJSONChild("point", ptrPoints);
                    
                    if (ptrPoint != NULL)
                    {
                        //vector<JSONDocument> docArray;
                        cJSON* pointChild = ptrPoint;
                        if (pointChild->type == cJSON_Array)
                        {
                            pointChild = pointChild->child;
                        }
                        while(pointChild != NULL && pointChild->type == cJSON_Object)
                        {
                            App42GeoPoint geoPoint;
                            geoPoint.latitude = Util::getJSONDouble("latitude", pointChild);
                            geoPoint.longitude = Util::getJSONDouble("longitude", pointChild);
                            geoPoint.markerName = Util::getJSONString("markerName", pointChild);
                            geoPoint.createdOn = Util::getJSONString("createdOn", pointChild);
                            app42Buddy.pointList.push_back(geoPoint);
                            pointChild = pointChild->next;
                        }
                        //app42Score.setJsonDocList(docArray);
                    }
                    
                }
                
                buddyList.push_back(app42Buddy);
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

void App42BuddyResponse::onComplete(void *sender, void *data)
{
    App42Response::onComplete(sender, data);
    init();
    
    if (_app42Target && _app42Selector)
    {
        (_app42Target->*_app42Selector)((App42CallBack *)_app42Target, this);
    }
}