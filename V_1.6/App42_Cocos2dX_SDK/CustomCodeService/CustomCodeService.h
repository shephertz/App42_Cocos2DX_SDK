//
//  CustomCodeService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 14/05/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__CustomCodeService__
#define __App42Cocos2dX3_0Sample__CustomCodeService__

#include <iostream>
#include "App42Service.h"
#include "App42Object.h"

using namespace std;

class CustomCodeService : public App42Service
{
    
private:
    CustomCodeService();
	static CustomCodeService* _instance;
    
public:
    
	/**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
	
    static CustomCodeService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of CustomCodeService.
     *
     * @return CustomCodeService - CustomCodeService Object
     */
	static CustomCodeService* getInstance();
    
    /**
     * Runs custom code deployed in the App42 Cloud
     *
     * @param name
     *            - Name of deployed CustomCode Service
     * @param jsonBody
     *            - Request Body in JSON format
     */
    void RunJavaCode(const char* name, App42Object *jsonBody,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

};

#endif /* defined(__App42Cocos2dX3_0Sample__CustomCodeService__) */
