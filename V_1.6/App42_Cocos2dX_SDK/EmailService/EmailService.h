//
//  EmailService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 08/04/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__EmailService__
#define __App42Cocos2dX3_0Sample__EmailService__

#include <iostream>
#include "App42Service.h"

using namespace std;

typedef enum EmailMIME
{
    PLAIN_TEXT_MIME_TYPE,
    HTML_TEXT_MIME_TYPE,
}EmailMIME;

class EmailService : public App42Service
{
    
private:
    EmailService();
	static EmailService* _instance;
    
    inline const char *getEmailMIME(EmailMIME emailMIME)
    {
        const char *strings[] = {"text/plain", "text/html"};
        
        return strings[emailMIME];
    }
    
    string buildcreateMailConfigurationBody(string emailId);
    string buildcreateMailConfigurationBody(string emailHost, string emailPort,string emailId, string emailPassword, bool isSSL);
    string buildSendMailBody(string sendTo, string sendSubject, string sendMsg,string fromEmail, EmailMIME emailMIME);
public:
    
	/**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
	
    static EmailService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of EmailService.
     *
     * @return EmailService - EmailService Object
     */
	static EmailService* getInstance();

    void createMailConfiguration(const char* emailHost, int emailPort,const char* mailId, const char* emailPassword, bool isSSL,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void removeEmailConfiguration(const char* emailId,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void getEmailConfigurations(App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    void sendMail(const char* sendTo, const char* sendSubject, const char* sendMsg,const char* fromEmail, EmailMIME emailMIME,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
};

#endif /* defined(__App42Cocos2dX3_0Sample__EmailService__) */
