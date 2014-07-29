//
//  App42GameResponse.h
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 17/10/13.
//
//

#ifndef __App42CPPSDK__App42GameResponse__
#define __App42CPPSDK__App42GameResponse__

#include <iostream>
#include "cJSON.h"
#include "App42Response.h"
#include "App42Score.h"

using namespace std;

struct App42Game;

class App42GameResponse : public App42Response
{
public:
    
    vector<App42Game> games;
    vector<App42Score> scores;
    
    App42GameResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector);
	~App42GameResponse();
    void onComplete(void *sender, void *data);
private:
    void init();
        
};


typedef struct App42Game
{
    string name;
    string description;
}App42Game;

#endif /* defined(__App42CPPSDK__App42GameResponse__) */
