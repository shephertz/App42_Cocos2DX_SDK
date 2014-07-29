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



using namespace std;

class StorageService : public App42Service
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
    
    void InsertJsonDocument(const char* dbName, const char* collectionName, const char* json, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void InsertJsonDocument(const char* dbName, const char* collectionName, App42Object *app42Object, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    
	void FindAllCollections(const char* dbName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
	void FindAllDocuments(const char* dbName, const char* collectionName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void FindAllDocuments(const char* dbName, const char* collectionName,int max, int offset, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void FindAllDocumentsCount(const char* dbName, const char* collectionName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
	void FindDocumentById(const char* dbName, const char* collectionName, const char* docId, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    //Deprecated---Use "FindDocumentsByQuery"
    void FindDocumentByQuery(const char* dbName, const char* collectionName, Query *query, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void FindDocumentsByQuery(const char* dbName, const char* collectionName, Query *query, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void FindDocumentsByQueryWithPaging(const char* dbName, const char* collectionName, Query *query, int max, int offset, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void FindDocsWithQueryPagingOrderBy(const char* dbName, const char* collectionName, Query *query, int max, int offset,const char* orderByKey,const char* orderByType, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
	void FindDocumentByKeyValue(const char* dbName, const char* collectionName, const char* key,const char* value, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void UpdateDocumentByDocId(const char* dbName, const char* collectionName, const char* docId,const char* newJsonDoc, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void UpdateDocumentByDocId(const char* dbName, const char* collectionName, const char* docId, App42Object *app42Object, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void UpdateDocumentByKeyValue(const char* dbName, const char* collectionName, const char* key,const char* value,const char* json, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void UpdateDocumentByKeyValue(const char* dbName, const char* collectionName, const char* key,const char* value,App42Object *app42Object, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void SaveOrUpdateDocumentByKeyValue(const char* dbName, const char* collectionName, const char* key,const char* value,const char* json, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void SaveOrUpdateDocumentByKeyValue(const char* dbName, const char* collectionName, const char* key,const char* value,App42Object *app42Object, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    void DeleteDocumentsById(const char* dbName, const char* collectionName, const char* docId, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void DeleteDocumentsByKeyValue(const char* dbName, const char* collectionName, const char* key, const char* value, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    void DeleteAllDocuments(const char* dbName, const char* collectionName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void AddOrUpdateKeys(const char* dbName, const char* collectionName, const char* docId,const char* json, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void AddOrUpdateKeys(const char* dbName, const char* collectionName, const char* docId,App42Object *app42Object, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void UpdateDocumentByQuery(const char* dbName, const char* collectionName, Query *query, const char* json, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void UpdateDocumentByQuery(const char* dbName, const char* collectionName, Query *query, App42Object *app42Object, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 *
	 * @param dbName
	 * @param collectionName
	 * @param docId
	 * @param aclList
	 * @return
	 * @throws App42Exception
	 */
	void GrantAccessOnDoc(const char* dbName, const char* collectionName,
                          const char* docId, vector<ACL> aclList, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 *
	 * @param dbName
	 * @param collectionName
	 * @param docId
	 * @param aclList
	 * @return
	 * @throws App42Exception
	 */
	void RevokeAccessOnDoc(const char* dbName, const char* collectionName,
                           const char* docId, vector<ACL> aclList, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
};

#endif /* defined(__App42CPPSDK__StorageService__) */
