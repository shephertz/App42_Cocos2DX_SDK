//
//  App42RewardResponse.h
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 18/10/13.
//
//

#ifndef __App42CPPSDK__App42RewardResponse__
#define __App42CPPSDK__App42RewardResponse__

#include <iostream>
#include "cJSON.h"
#include "App42Response.h"

using namespace std;

struct App42Reward;
class App42RewardResponse : public App42Response
{
public:
    
    vector<App42Reward> rewards;
    App42RewardResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector);
	~App42RewardResponse();
    void onComplete(void *sender, void *data);
private:
    void init();
    
};

typedef struct App42Reward
{
    string name;
    string gameName;
    string userName;
    string description;

	double points;
    double rank;
    
}App42Reward;

#endif /* defined(__App42CPPSDK__App42RewardResponse__) */
