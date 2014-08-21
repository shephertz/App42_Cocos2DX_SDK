//
//  SessionService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 16/07/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__SessionService__
#define __App42Cocos2dX3_0Sample__SessionService__

#include <iostream>
#include "App42Service.h"


using namespace std;

class SessionService : public App42Service
{
    
private:
    SessionService();
    static SessionService* _instance;
    string buildGetSessionRequest(const char* userName, const char* sessionId);
    string buildSetAttributeRequest(const char* sessionId,const char* attributeName,const char* attributeValue);
public:
    
	/**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
	
    static SessionService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of SessionService.
     *
     * @return SessionService - SessionService Object
     */
	static SessionService* getInstance();
    
    /**
     * Gets Session for the User. If the session does not exist it will create
     * a new session
     *
     * @param uName
     *            - UserName for which the session has to be fetched/created.
     *
     * @return void
     *
     */
    void GetSession(const char* userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Create User Session based on the isCreate boolean parameter. If isCreate
     * is true and there is an existing session for the user, the existing
     * session is returned. If there is no existing session for the user a new
     * one is created. If isCreate is false and there is an existing session,
     * the existing session is returned if there is no existing session new one
     * is not created
     *
     * @param uName
     *            - UserName for which the session has to be created.
     * @param isCreate
     *            - A boolean value for specifying if an existing session is not
     *            there, should a new one is to be created or not.
     *
     * @return Session object containing the session id of the created session.
     *         This id has to be used for storing or retrieving attributes.
     *
     */
    void GetSession(const char* userName, bool isCreate, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Invalidate a session based on the session id. All the attributes store in
     * the session will be lost.
     *
     * @param sessionId
     *            - The session id for which the session has to be invalidated.
     *
     * @return void
     *
     */
    void Invalidate(const char* sessionId, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Sets attribute in a session whose session id is provided. Attributes are
     * stored in a key value pair.
     *
     * @param sessionId
     *            - Session id for which the attribute has to be saved.
     * @param attributeName
     *            - The attribute key that needs to be stored
     * @param attributeValue
     *            - The attribute value that needs to be stored
     *
     * @return void
     *
     */
    void SetAttribute(const char* sessionId, const char* attributeName, const char* attributeValue, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Gets the attribute value in a session whose session id is provided.
     *
     * @param sessionId
     *            - The session id for which the attribute has to be fetched
     * @param attributeName
     *            - The attribute key that has to be fetched
     *
     * @return void
     *
     */
    void GetAttribute(const char* sessionId, const char* attributeName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Get all the attributes for a given session id
     *
     * @param sessionId
     *            - The session id for which the attribute has to be fetched
     *
     * @return void
     *
     */
    void GetAllAttributes(const char* sessionId, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Removes the attribute from a session whose session id is provided.
     *
     * @param sessionId
     *            - The session id for which the attribute has to be removed
     * @param attributeName
     *            - The attribute key that has to be removed
     *
     * @return App42Response if removed successfully
     *
     */
    void RemoveAttribute(const char* sessionId, const char* attributeName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Removes all the attributes for a given session id
     *
     * @param sessionId
     *            - The session id for which the attributes has to be removed
     *
     * @return void
     *
     */
    void RemoveAllAttributes(const char* sessionId, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

};
#endif /* defined(__App42Cocos2dX3_0Sample__SessionService__) */
