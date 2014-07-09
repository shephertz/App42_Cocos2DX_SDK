//
//  ScoreBoardService.h
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 18/10/13.
//
//

#ifndef __App42CPPSDK__ScoreBoardService__
#define __App42CPPSDK__ScoreBoardService__

#include <iostream>
#include "App42Service.h"

using namespace std;
class ScoreBoardService: public App42Service
{
private:
	static ScoreBoardService* _instance;
	ScoreBoardService();
public:
    /**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
	
    static ScoreBoardService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of UserService.
     *
     * @return UserService - UserService Object
     */
	static ScoreBoardService* getInstance();
    
    /**
     * Saves the User score for a game
     *
     * @param gameName - Name of the game for which score has to be saved.
     * @param userName - The user for which score has to be saved.
     * @param score - The score that has to be saved.
     * @return void
     *
     */
	void SaveUserScore(const char* gameName,const char* userName, double score, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Edits the User score for a game
     *
     * @param scoreId - The id for score that has to be edited.
     * @param gameScore - The new score that has to be saved.
     * @return void
     *
     */
    void EditScoreValueById(const char* scoreId, double gameScore, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Retrieves the average game score for the specified user
     *
     * @param gameName - Name of the game for which average score has to be fetched
     * @param userName - The user for which average score has to be fetched
     * @return void.
     *
     */
	void GetAverageScoreByUser(const char* gameName, const char* userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Retrieves the highest game score for the specified user
     *
     * @param gameName - Name of the game for which highest score has to be fetched
     * @param userName - The user for which highest score has to be fetched
     * @return void.
     *
     */
	void GetHighestScoreByUser(const char* gameName,const char* userName , App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * This function returns the top score attained by the specified user in the game.
     *
     * @param gameName - Name of the game
     * @param userName - Name of the user for which score has to retrieve
     * @return app42Result - The result of the request.
     *
     */
	void GetLastScoreByUser(const char* gameName,const char* userName,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
	/**
     * Retrieves the Top Rankings for the specified game
     *
     * @param gameName - Name of the game for which ranks have to be fetched
     * @return void.
     *
     */
	void GetTopRankings(const char* gameName,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Retrieves the Top Rankings for the specified game
     *
     * @param gameName - Name of the game for which ranks have to be fetched
     * @return void.
     *
     */
	void GetTopRankings(const char* gameName, tm *startDate, tm *endDate,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
	/**
     * Retrieves the User Ranking for the specified game
     *
     * @param gameName - Name of the game for which ranks have to be fetched.
     * @param userName - Name of the user for which ranks have to be fetched.
     * @return void.
     *
     */
	void GetUserRanking(const char* gameName, const char* userName,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Retrieves the Top Rankers for the specified game
     *
     * @param gameName - Name of the game for which ranks have to be fetched
     * @param max - maximum number of result need to be fetched
     * @return void.
     *
     */
    void GetTopNRankers(const char* gameName,int max,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Retrieves the Top Rankers for the specified game
     *
     * @param gameName - Name of the game for which ranks have to be fetched
     * @param max - maximum number of result need to be fetched
     * @return void.
     *
     */
    void GetTopNRankers(const char* gameName, tm *startDate, tm *endDate, int max, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Retrieves the scores for a game for the specified name
     *
     * @param gameName
     *            - Name of the game for which score has to be fetched
     * @param userName
     *            - The user for which score has to be fetched
     *
     * @return void
     *
     */

    void GetScoresByUser(const char* gameName,const char* userName,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    /**
     * Retrieves the lowest game score for the specified user
     *
     * @param gameName
     *            - Name of the game for which lowest score has to be fetched
     * @param userName
     *            - The user for which lowest score has to be fetched
     *
     * @return void
     *
     */
    void GetLowestScoreByUser(const char* gameName,const char* userName,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    /**
     * Retrieves the Top N Rankings for the specified game within the
     * given group
     * @param gameName
     *            - Name of the game for which ranks have to be fetched
     * @param group
     *            - array of usernames in the group
     *
     * @return void
     *
     */
    void GetTopRankingsByGroup(const char* gameName,std::vector<std::string>group,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Retrieves the Top Rankers/Scorers for the specified game within the
     * given group
     * @param gameName
     *            - Name of the game for which ranks have to be fetched
     * @param group
     *            - array of usernames in the group
     *
     * @return the Top rankers for a game
     *
     */
    void GetTopRankersByGroup(const char* gameName,std::vector<std::string>group,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    /**
     * Retrieves the last score made by the user in all games
     *
     * @param userName
     *            - Name of the user for which the last score has to be fetched
     *
     * @return the Top rankers for a game
     *
     */

    void GetLastGameScore(const char* userName,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     *
     * @param gameName
     * @param max
     * @return
     * @throws App42Exception
     */
    void GetTopNTargetRankers(const char* gameName,int max,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * Retrieves the Top Rankings for the specified game
     *
     * @param gameName
     *            - Name of the game for which ranks have to be fetched
     * @param max
     *            - Maximum number of records to be fetched
     *
     * @return void
     *
     */
    void GetTopNRankings(const char* gameName,int max,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    /**
     * Retrieves the Users having scores in given range
     * @param gameName
     * @param minScore
     * @param maxScore
     * @return void
     * @throws App42Exception
     */
    void GetUsersWithScoreRange(const char* gameName,double minScore, double maxScore,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
	 * This method helps to fetch the top N rankers from your facebook friends.
	 *
	 * @param gameName
	 *            - Game name for which top N rankers has to fetch.
	 * @param fbAccessToken
	 *            - Fackebook access token of the user who is fetching the
	 *            record.
	 * @param max
	 *            - Max number of rankers to be fetched
	 * @return void
	 * @throws App42Exception
	 */
    void GetTopNRankersFromFacebook(const char* gameName, const char* fbAccessToken, int max, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    /**
     * This function returns the specified number of top rankers among facebook friends in specified
     * range of dates for a specific game.
     *
     * @param gameName
	 *            - Game name for which top N rankers has to fetch.
	 * @param fbAccessToken
	 *            - Fackebook access token of the user who is fetching the record.
     * @param startDate
     * @param endDate
     * @param max
	 *            - Max number of rankers to be fetched
     * @return void
     * @throws App42Exception
     */
    void GetTopNRankersFromFacebook(const char* gameName, const char* fbAccessToken, tm *startDate, tm *endDate, int max, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    
    void AddCustomScore(App42Object *app42Object, const char* collectionName);
    
};

#endif /* defined(__App42CPPSDK__ScoreBoardService__) */
