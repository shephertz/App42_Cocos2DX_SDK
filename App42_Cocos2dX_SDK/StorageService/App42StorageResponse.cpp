//
//  App42StorageResponse.cpp
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 21/10/13.
//
//

#include "App42StorageResponse.h"
#include "Common.h"


App42StorageResponse::App42StorageResponse(cocos2d::CCObject *pTarget, cocos2d::SEL_CallFuncND pSelector)
:App42Response(pTarget,pSelector)
{
    
}

App42StorageResponse::~App42StorageResponse()
{
    storages.clear();
}

void App42StorageResponse::onComplete(cocos2d::CCNode *sender, void *data)
{
    App42Response::onComplete(sender, data);
    init();
    
    
    if (_pTarget && _pSelector)
    {
        (_pTarget->*_pSelector)((cocos2d::CCNode *)_pTarget, this);
    }
    
}



void App42StorageResponse::init()
{
    if(_result != 200)
    {
        Util::app42Trace("App42StorageResult failed result is %d", _result);
        buildErrorMessage();
        return;
    }
    // parse the body
    cJSON *ptrBody = cJSON_Parse(_body.c_str());
    cJSON* ptrApp42 = Util::getJSONChild("app42", ptrBody);
    cJSON* ptrResponse = Util::getJSONChild("response", ptrApp42);
    cJSON* ptrStorages = Util::getJSONChild("storage", ptrResponse);
    
    cJSON* child = ptrStorages;
    if(child->type == cJSON_Array)
    {
        child = child->child;
    }
    
    while(child != NULL && child->type == cJSON_Object)
    {
        App42Storage app42Storage;
        app42Storage.dbName = Util::getJSONString("dbName", child);
        app42Storage.collectionName = Util::getJSONString("collectionName", child);
        storages.push_back(app42Storage);
        child = child->next;
		
		if(Util::getJSONChild("jsonDoc",ptrStorages))
        {
			cJSON* ptrjsonDocs = Util::getJSONChild("jsonDoc", ptrStorages);
			cJSON* child = ptrjsonDocs;
			if(child->type == cJSON_Array)
            {
				child = child->child;
			}
			while(child != NULL && child->type == cJSON_Object)
            {
				JSONDocument document;
                
				if(Util::getJSONChild("_id",child))
                {
					cJSON* ptrDocId = Util::getJSONChild("_id", child);
					cJSON* child2 = ptrDocId;
					while(child2 != NULL && child2->type == cJSON_Object)
                    {
                        document.setDocId(Util::getJSONString("$oid", child2));
						child2 = child2->next;
					}
					cJSON_DeleteItemFromObject(child, "_id");
				}
                
                if(Util::getJSONChild("_$owner",child))
                {
					cJSON* ptrDocId = Util::getJSONChild("_$owner",child);
					cJSON* child2 = ptrDocId;
					while(child2 != NULL && child2->type == cJSON_Object)
                    {
                        document.setOwner(Util::getJSONString("owner", child2));
						child2 = child2->next;
					}
					cJSON_DeleteItemFromObject(child,"_$owner");
				}
                
				if(Util::getJSONChild("_$updatedAt",child))
                {
                    document.setUpdatedAt(Util::getJSONString("_$updatedAt",child));
					cJSON_DeleteItemFromObject(child, "_$updatedAt");
				}
				if(Util::getJSONChild("_$createdAt",child))
                {
                    document.setCreatedAt(Util::getJSONString("_$createdAt",child));
					cJSON_DeleteItemFromObject(child, "_$createdAt");
				}
                if(Util::getJSONChild("_$event",child))
                {
                    document.setEvent(Util::getJSONString("_$event",child));
					cJSON_DeleteItemFromObject(child, "_$event");
				}
                
				char *doc = cJSON_PrintUnformatted(child);
                document.setJsonDoc(doc);
				free(doc);
				documents.push_back(document);
				child = child->next;
			}
		}
    }
    cJSON_Delete(ptrBody);
}