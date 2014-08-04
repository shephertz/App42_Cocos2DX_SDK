//
//  App42UserResponse.h
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 14/10/13.
//
//

#ifndef __App42CPPSDK__App42UserResponse__
#define __App42CPPSDK__App42UserResponse__

#include <iostream>
#include "cJSON.h"
#include "App42Response.h"
#include "App42Constants.h"
#include "JSONDocument.h"

using namespace std;

struct App42User;
struct App42UserProfile;

class App42UserResponse : public App42Response
{
public:
    App42UserResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector);
    vector<App42User> users;
	~App42UserResponse();
    void onComplete(void *sender, void *data);
private:
    void init();
    App42UserProfile buildUserProfile(cJSON* ptrProfile);
};

typedef struct App42UserProfile
{
    string firstName;
    string lastName;
    string sex;
    string mobile;
    string line1;
    string line2;
    string city;
    string state;
    string country;
    string pincode;
    string homeLandLine;
    string officeLandLine;
    string dateOfBirth;
    
    bool accountLocked;
    
    typedef enum UserGender
    {
        MALE,
        FEMALE,
    }UserGender;
    
    inline void setSex(UserGender userGender)
    {
        const char *strings[] = {"MALE", "FEMALE"};
        sex = strings[userGender];
    }
    
    inline string getSex()
    {
        return sex;
    }
    
private:
    
}App42UserProfile;

typedef struct App42User
{
    string userName;
    string email;
    string password;
    string sessionId;
    string createdOn;
    vector<string> roleList;
    App42UserProfile profile;
    vector<JSONDocument> jsonDocArray;
    bool isAccountLocked;
    
}App42User;



#endif /* defined(__App42CPPSDK__App42UserResponse__) */


