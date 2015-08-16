//
//  App42UploadResponse.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 04/04/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__App42UploadResponse__
#define __App42Cocos2dX3_0Sample__App42UploadResponse__

#include <iostream>
#include "cJSON.h"
#include "App42Response.h"

using namespace std;

typedef struct App42Upload
{
    string name;
    string userName;
    string type;
    string url;
    string tinyUrl;
    string description;
    string createdOn;
}App42Upload;


class App42UploadResponse : public App42Response
{
public:
    vector<App42Upload> uploadArray;
    App42UploadResponse(const app42CallBack& pSelector);
	~App42UploadResponse();
    void onComplete(void *sender, void *data);
private:
    void init();

};


#endif /* defined(__App42Cocos2dX3_0Sample__App42UploadResponse__) */
