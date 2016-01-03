//
//  GeoService.h
//  App42Cocos2dXSample
//
//  Created by Rajeev Ranjan on 27/04/15.
//
//

#ifndef __App42Cocos2dXSample__GeoService__
#define __App42Cocos2dXSample__GeoService__

#include <stdio.h>
#include <vector>
#include "App42Service.h"
#include "App42Constants.h"
#include "App42GeoPoint.h"

using namespace std;

class GeoService : public App42Service
{
    
private:
    GeoService();
    
    string getJsonStringFromVector(vector<App42GeoPoint>list);
    string buildCreateGeoPointBody(const char *storageName, const char *points);
    /*string getJsonStringFromVector(vector<string>roles);
    string buildCreateUserBody(const char *username, const char *password, const char *email,const char *roleList);
    string buildChangePasswordBody(string username, string oldPwd, string newPwd);
    string buildCreateOrUpdateProfileBody(App42User *user);
    string buildProfileData(App42UserProfile *profile);
    string buildLogoutBody(string sessionId);
    string buildCreateUserWithProfileBody(const char* userName, const char* password, const char* emailAddress,App42UserProfile *user);*/
    static GeoService* _instance;

public:
    
    /**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
    
    static GeoService* Initialize(string apikey, string secretkey);
    
    static void Terminate();
    
    /**
     * Builds the instance of GeoService.
     *
     * @return GeoService - GeoService Object
     */
    static GeoService* getInstance();
    
    /**
     * Stores the geo points with unique handler on the cloud. Geo point data
     * contains lat, lng and marker of the point.
     *
     * @param geoStorageName
     *            - Unique handler for storage name
     * @param geoPointsList
     *            - List of Geo Points to be saved
     *
     * @return void
     */
    void CreateGeoPoints(const char *geoStorageName, vector<App42GeoPoint> geoPointsList, const app42CallBack& pSelector);
    
    /**
     * Search the near by point in given range(In KM) from specified source
     * point. Points to be searched should already be stored on cloud using
     * unique storage name handler.
     *
     * @param storageName
     *            - Unique handler for storage name
     * @param lat
     *            - Latitude of source point
     * @param lng
     *            - Longitude of source point
     * @param distanceInKM
     *            - Range in KM
     *
     * @return Geo object containing the target points in ascending order of
     *         distance from source point.
     * 
     */
    void GetNearByPointsByMaxDistance(const char *geoStorageName,double lat, double lng, double distanceInKM, const app42CallBack& pSelector);
    
    /**
     * Search the near by point from specified source point. Points to be
     * searched should already be stored on cloud using unique storage name
     * handler.
     *
     * @param storageName
     *            - Unique handler for storage name
     * @param lat
     *            - Latitude of source point
     * @param lng
     *            - Longitude of source point
     * @param resultLimit
     *            - Maximum number of results to be retrieved
     *
     * @return Geo object containing the target points in ascending order of
     *         distance from source point.
     *
     */
    void GetNearByPoint(const char *geoStorageName,double lat, double lng, int resultLimit, const app42CallBack& pSelector);
    
    /**
     * Search the near by point from specified source point with in specified
     * radius. Points to be searched should already be stored on cloud using
     * unique storage name handler.
     *
     * @param storageName
     *            - Unique handler for storage name
     * @param lat
     *            - Lattitude of source point
     * @param lng
     *            - Longitude of source point
     * @param radiusInKM
     *            - Radius in KM
     * @param resultLimit
     *            - Maximum number of results to be retrieved
     *
     * @return Geo object containing the target points in ascending order of
     *         distance from source point.
     *
     */
    void GetPointsWithInCircle(const char *geoStorageName,double lat, double lng, double radiusInKM, int resultLimit, const app42CallBack& pSelector);
    
    /**
     * Fetch the name of all storage stored on the cloud.
     *
     * @return Geo object containing List of all the storage created
     *
     * @throws App42Exception
     * 
     */
    void GetAllStorage(const app42CallBack& pSelector);
    
    /**
     * Fetch the name of all storage page-wise stored on the cloud.
     *
     * @return Geo object containing List of all the storage created
     *
     * @throws App42Exception
     *
     */
    void GetAllStorageByPaging(int max, int offset, const app42CallBack& pSelector);
    
    void DeleteGeoPoints(const char *geoStorageName, vector<App42GeoPoint> geoPointsList, const app42CallBack& pSelector);

    void DeleteStorage(const char *geoStorageName, const app42CallBack& pSelector);
    
    void GetAllPoints(const char *geoStorageName, const app42CallBack& pSelector);
    
    void GetAllPointsByPaging(const char *geoStorageName, int max, int offset, const app42CallBack& pSelector);
};

#endif /* defined(__App42Cocos2dXSample__GeoService__) */
