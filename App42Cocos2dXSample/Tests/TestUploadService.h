//
//  TestUploadService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 04/04/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__TestUploadService__
#define __App42Cocos2dX3_0Sample__TestUploadService__

#include <iostream>
#include "cocos2d.h"
#include "App42API.h"

class TestUploadService : public cocos2d::Layer, public App42CallBack
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestUploadService);
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    
    /**
     * API Tests
     */
    void uploadFile(Ref *sender);
    void uploadFileData(Ref *sender);
    void getAllFiles(Ref *sender);
    void getAllFilesByPaging(Ref *sender);
    void getAllFilesCount(Ref *sender);
    void getFileByUser(Ref *sender);
    void getAllFilesByUser(Ref *sender);
    void getAllFilesByUserByPaging(Ref *sender);
    void getAllFilesCountByUser(Ref *sender);
    void getFileByName(Ref *sender);
    
    void removeFileByUser(Ref *sender);
    void removeAllFilesByUser(Ref *sender);
    void removeFileByName(Ref *sender);
    void removeAllFiles(Ref *sender);
    void getFilesCountByType(Ref *sender);
    void getFilesByType(Ref *sender);
    void getFilesByTypeByPaging(Ref *sender);
    void uploadFileForUser(Ref *sender);
    void uploadFileDataForUser(Ref *sender);
    void grantAccess(Ref* sender);
    void revokeAccess(Ref* sender);
    
    void loadResponseScene();
    /**
     * A selector callback
     */
    void onUploadRequestCompleted( void *response);
    void menuCloseCallback(Ref* pSender);
private:
    std::string apiKey;
    std::string secretKey;
    vector<string> responseArray;
};

#endif /* defined(__App42Cocos2dX3_0Sample__TestUploadService__) */
