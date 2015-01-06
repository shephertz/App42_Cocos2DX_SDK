//
//  StorageService.h
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 21/10/13.
//
//

#ifndef __App42CPPSDK__StorageService__
#define __App42CPPSDK__StorageService__

#include <iostream>
#include "App42Service.h"
#include "cocos2d.h"

using namespace std;

class StorageService : public App42Service, public cocos2d::Node
{
    
private:
    StorageService();
	static StorageService* _instance;
public:
    
	/**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
	
    static StorageService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of UserService.
     *
     * @return UserService - UserService Object
     */
	static StorageService* getInstance();
    
    void InsertJsonDocument(string dbName, string collectionName, string json, Object* pTarget, cocos2d::SEL_CallFuncND pSelector);
    
	void FindAllCollections(string dbName, Object* pTarget, cocos2d::SEL_CallFuncND pSelector);
    
	void FindAllDocuments(string dbName, string collectionName, Object* pTarget, cocos2d::SEL_CallFuncND pSelector);
    
	void FindDocumentById(string dbName, string collectionName, string docId, Object* pTarget, cocos2d::SEL_CallFuncND pSelector);
    
    void FindDocumentByQuery(string dbName, string collectionName, Query *query, Object* pTarget, cocos2d::SEL_CallFuncND pSelector);
    
	void FindDocumentByKeyValue(string dbName, string collectionName, string key,string value, Object* pTarget, cocos2d::SEL_CallFuncND pSelector);
    
    void UpdateDocumentByDocId(string dbName, string collectionName, string docId,string newJsonDoc, Object* pTarget, cocos2d::SEL_CallFuncND pSelector);
    
    void UpdateDocumentByKeyValue(string dbName, string collectionName, string key,string value,string json, Object* pTarget, cocos2d::SEL_CallFuncND pSelector);
    
    void SaveOrUpdateDocumentByKeyValue(string dbName, string collectionName, string key,string value,string json, Object* pTarget, cocos2d::SEL_CallFuncND pSelector);

    void DeleteDocumentsById(string dbName, string collectionName, string docId, Object* pTarget, cocos2d::SEL_CallFuncND pSelector);


};

#endif /* defined(__App42CPPSDK__StorageService__) */
