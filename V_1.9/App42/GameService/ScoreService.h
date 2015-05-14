//
//  ScoreService.h
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 18/10/13.
//
//

#ifndef __App42CPPSDK__ScoreService__
#define __App42CPPSDK__ScoreService__

#include <iostream>
#include "App42Service.h"

using namespace std;

class ScoreService: public App42Service
{
private:
	static ScoreService* _instance;
	ScoreService();
public:
    /**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
	
    static ScoreService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of UserService.
     *
     * @return UserService - UserService Object
     */
	static ScoreService* getInstance();
    
    /**
     * Adds game score for the specified user.
     *
     * @param gameName - Name of the game for which scores have to be added.
     * @param userName - The user for whom scores have to be added.
     * @param score - The scores that have to be added.
     * @return app42Result - The result of the request.
     *
     */
    
	void AddScore(const char* gameName, const char* userName, double score, const app42CallBack& pSelector);
	/**
     * Deducts the score from users account for a particular Game
     *
     * @param gameName - Name of the game for which scores have to be deducted
     * @param userName - The user for whom scores have to be deducted
     * @param score - The scores that have to be deducted
     * @return app42Result - The result of the request.
     *
     */
	void DeductScore(const char* gameName, const char* userName, double score, const app42CallBack& pSelector);

};
#endif /* defined(__App42CPPSDK__ScoreService__) */
