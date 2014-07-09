//
//  RewardService.h
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 18/10/13.
//
//

#ifndef __App42CPPSDK__RewardService__
#define __App42CPPSDK__RewardService__

#include <iostream>
#include "App42Service.h"

using namespace std;
class RewardService: public App42Service
{
private:
	static RewardService* _instance;
	RewardService();
public:
    /**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
	
    static RewardService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of RewardService.
     *
     * @return RewardService - RewardService Object
     */
	static RewardService* getInstance();
    
    /**
     * Creates Reward. Reward can be Sword, Energy etc. When Reward Points have
     * to be added the Reward name created using this method has to be
     * specified.
     *
     * @param rewardName - The reward that has to be created
     * @param description - The description of the reward to be created.
     * @return app42Result - The result of the request.
     *
     */
	void CreateReward(const char* rewardName,const char* description, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
	/**
     * Fetches all the Rewards
     *
     * @return app42Result - The result of the request.
     *
     */
	void GetAllRewards(App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    /**
     * Fetches all the Rewards by paging.
     *
     * @param max
     *            - Maximum number of records to be fetched
     * @param offset
     *            - From where the records are to be fetched
     *
     * @return List of Reward objects containing all the rewards of the App
     *
     */
    void GetAllRewards(int max, int offset, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Fetches all the Rewards
     *
     * @return app42Result - The result of the request.
     *
     */
	void GetAllRewardsCount(App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
	/**
     * Adds the reward points to an users account. Reward Points can be earned
     * by the user which can be redeemed later.
     *
     * @param gameName - Name of the game for which reward points have to be added
     * @param userName - The user for whom reward points have to be added
     * @param rewardName - The rewards for which reward points have to be added
     * @param rewardPoints - The points that have to be added
     * @return app42Result - The result of the request.
     *
     */
	void EarnRewards(const char* gameName, const char* userName, const char* rewardName, double rewardPoints,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
	/**
     * Deducts the reward points from the earned rewards by a user.
     *
     * @param gameName - Name of the game for which reward points have to be deducted
     * @param userName - The user for whom reward points have to be deducted
     * @param rewardName - The rewards for which reward points have to be deducted
     * @param rewardPoints - The points that have to be deducted
     * @return app42Result - The result of the request.
     *
     */
	void RedeemRewards(const char* gameName, const char* userName, const char* rewardName, double rewardPoints,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
	/**
     * Fetches the reward points for a particular user
     *
     * @param gameName - Name of the game for which reward points have to be fetched
     * @param userName - The user for whom reward points have to be fetched
     * @return app42Result - The result of the request.
     * 
     */
	void GetGameRewardPointsForUser(const char* gameName, const char* userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Retrieves the reward for the specified name
     *
     * @param rewardName
     *            - Name of the reward that has to be fetched
     *
     * @return Reward object containing the reward based on the rewardName
     *
     */
     void GetRewardByName(const char* rewardName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * This function provides a list of specified number of top reward earners
     * for a specific game.
     *
     * @param gameName
     *            - Name of the game for which reward earners are to be fetched
     * @param rewardName
     *            - Name of the reward for which list of earners is to be
     *            fetched
     * @param max
     *            - Specifies the number of top earners to be fetched
     * @return ArrayList of Reward object
     * @throws App42Exception
     */
    void GetTopNRewardEarners(const char* gameName, const char* rewardName, int max, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * This function returns you the details of all the specific rewards earned
     * by the specified user.
     *
     * @param userName
     *            - Name of the user whose rewards are to be fetched
     * @param rewardName
     *            - Name of the reward for which details are to be fetched
     * @return ArrayList of Reward object
     * @throws App42Exception
     */
    void GetAllRewardsByUser(const char* userName, const char* rewardName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * This function returns you a list of group wise users who earned the top
     * rewards in the specified game .
     *
     * @param gameName
     *            - Name of the game for which top reward earners are to be
     *            fetched
     * @param rewardName
     *            - Name of the reward for which top earners are to be listed
     * @param userList
     *            - List of group wise users earning specified rewards
     * @return ArrayList of Reward object
     * @throws App42Exception
     */
    void GetTopNRewardEarnersByGroup(const char* gameName, const char* rewardName, vector<std::string>userList, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * This function returns you a list of group wise users who earned the top
     * rewards in the specified game .
     *
     * @param gameName
     *            - Name of the game for which top reward earners are to be
     *            fetched
     * @param rewardName
     *            - Name of the reward for which top earners are to be listed
     * @param userName
     *            - Name of the user whose rewards are to be fetched
     * @return Reward object containing the ranking for the specified user
     * @throws App42Exception
     */
    void GetUserRankingOnReward(const char* gameName, const char* rewardName, const char* userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    
};
#endif /* defined(__App42CPPSDK__RewardService__) */
