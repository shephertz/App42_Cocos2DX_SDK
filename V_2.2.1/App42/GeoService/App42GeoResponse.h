//
//  App42GeoResponse.h
//  App42Cocos2dXSample
//
//  Created by Rajeev Ranjan on 27/04/15.
//
//

#ifndef __App42Cocos2dXSample__App42GeoResponse__
#define __App42Cocos2dXSample__App42GeoResponse__

#include <stdio.h>
#include "cJSON.h"
#include "App42Response.h"
#include "App42Constants.h"
#include "App42GeoPoint.h"

using namespace std;

struct App42Geo;

class App42GeoResponse : public App42Response
{
public:
    App42GeoResponse(const app42CallBack& pSelector);
    vector<App42Geo> geoList;
    ~App42GeoResponse();
    void onComplete(void *sender, void *data);
private:
    void init();
};

typedef struct App42Geo
{
    string storageName;
    double sourceLat;
    double sourceLng;
    double distanceInKM;
    vector<App42GeoPoint> pointList;
    tm createdOn;

}App42Geo;


#endif /* defined(__App42Cocos2dXSample__App42GeoResponse__) */
