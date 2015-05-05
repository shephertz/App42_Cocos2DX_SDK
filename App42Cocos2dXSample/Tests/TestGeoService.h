//
//  TestGeoService.h
//  App42Cocos2dXSample
//
//  Created by Rajeev Ranjan on 27/04/15.
//
//

#ifndef __App42Cocos2dXSample__TestGeoService__
#define __App42Cocos2dXSample__TestGeoService__

#include <stdio.h>
#include "cocos2d.h"
#include "App42API.h"

class TestGeoService : public cocos2d::Layer, public App42CallBack
{
public:
    
    TestGeoService *geoServiceTemp;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestGeoService);
    
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    void loadResponseScene();
    // a selector callback
    void onGeoRequestCompleted( void *response);
    void menuCloseCallback(Ref* pSender);
    
    
    void createGeoPoints(Ref* pSender);
    void getNearByPointsByMaxDistance(Ref* pSender);
    void getNearByPoint(Ref* pSender);
    void getPointsWithInCircle(Ref* pSender);
    void getAllStorage(Ref* pSender);
    void getAllStorageByPaging(Ref* pSender);
    void deleteGeoPoints(Ref* pSender);
    void deleteStorage(Ref* pSender);
    void getAllPoints(Ref* pSender);
    void getAllPointsByPaging(Ref* pSender);
    
private:
    std::string apiKey;
    std::string secretKey;
    cocos2d::LabelTTF *msgLabel;
    vector<string> responseArray;
};
#endif /* defined(__App42Cocos2dXSample__TestGeoService__) */
