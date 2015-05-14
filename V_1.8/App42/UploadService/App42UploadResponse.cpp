//
//  App42UploadResponse.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 04/04/14.
//
//

#include "App42UploadResponse.h"
#include "Common.h"


App42UploadResponse::App42UploadResponse(const app42CallBack& pSelector)
:App42Response(pSelector)
{
    
}

App42UploadResponse::~App42UploadResponse()
{
    
}

void App42UploadResponse::onComplete(void *sender, void *data)
{
    App42Response::onComplete(sender, data);
    init();
    
    if (_app42Selector)
    {
        _app42Selector(this);
    }
}

void App42UploadResponse::init()
{
    if(_result != 200)
    {
        Util::app42Trace("App42UploadResponse failed result is %d", _result);
        buildErrorMessage();
        return;
    }
    
    // parse the body
    cJSON *ptrBody = cJSON_Parse(_body.c_str());
    cJSON* ptrApp42 = Util::getJSONChild("app42", ptrBody);
    cJSON* ptrResponse = Util::getJSONChild("response", ptrApp42);
    cJSON* ptrUpload = Util::getJSONChild("upload", ptrResponse);
    if (ptrUpload)
    {
        cJSON* ptrFiles = Util::getJSONChild("files", ptrUpload);
        if (ptrFiles)
        {
            cJSON* ptrFile = Util::getJSONChild("file", ptrFiles);
            if (ptrFile)
            {
                cJSON* child = ptrFile;
                if(child->type == cJSON_Array)
                {
                    child = child->child;
                }
                while(child != NULL && child->type == cJSON_Object)
                {
                    App42Upload app42Upload;
                    app42Upload.name = Util::getJSONString("name", child);
                    app42Upload.userName = Util::getJSONString("userName", child);
                    app42Upload.type = Util::getJSONString("type", child);
                    app42Upload.url = Util::getJSONString("url", child);
                    app42Upload.tinyUrl = Util::getJSONString("tinyUrl", child);
                    app42Upload.description = Util::getJSONString("description", child);
                    app42Upload.createdOn = Util::getJSONString("createdOn", child);
                    uploadArray.push_back(app42Upload);
                    child = child->next;
                }
            }
        }
    }
    else
    {
        setTotalRecords();
    }
    cJSON_Delete(ptrBody);
}