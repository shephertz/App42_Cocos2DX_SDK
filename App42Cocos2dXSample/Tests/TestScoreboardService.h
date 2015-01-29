//
//  TestScoreboardService.h
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#ifndef __App42Cocos2dXSDK_3_0Beta2_Sample__TestScoreboardService__
#define __App42Cocos2dXSDK_3_0Beta2_Sample__TestScoreboardService__

#include <iostream>
#include "cocos2d.h"
#include "App42API.h"

class TestScoreboardService : public cocos2d::Layer, public App42CallBack
{
public:
    
    const char* gameName;
    const char* userName1;
    const char* userName2;
    const char* dbName;
    const char* collectionName;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestScoreboardService);
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    
    
    
    void saveUserScore(Ref *sender);
    void saveCustomUserScore(Ref* sender);
    void editScoreById(Ref *sender);
    void getScoresByUser(Ref *sender);
    void getLowestScoreByUser(Ref *sender);
    void getHighestScoreByUser(Ref *sender);
    void getAverageScoreByUser(Ref *sender);
    void getLastScoreByUser(Ref *sender);
    void getLastGameScore(Ref *sender);
    void getTopRankings(Ref *sender);
    void getTopRankingsByGroup(Ref *sender);
    void getTopRankersByGroup(Ref *sender);
    void getTopNRankings(Ref *sender);
    void getUsersWithScoreRange(Ref *sender);
    void getTopNRankers(Ref *sender);
    void getTopRankingsInDateRange(Ref *sender);
    void getTopNRankersInDataRange(Ref *sender);
    void getUserRanking(Ref *sender);
    void getTopNTargetRankers(Ref *sender);
    void getTopNRankersBySorting(Ref *sender);
    void getTopNRankersFromFacebook(Ref *sender);
    void getTopNRankersFromFacebookInDateRange(Ref *sender);
     void getTopNRankersWithCustomScore(Ref *sender);
    // a selector callback
    void onScoreBoardRequestCompleted( void *response);
    void menuCloseCallback(Ref* pSender);
    
    void loadResponseScene();
private:
    std::string apiKey;
    std::string secretKey;
    vector<string> responseArray;
    
};

#endif /* defined(__App42Cocos2dXSDK_3_0Beta2_Sample__TestScoreboardService__) */
