//
//  UserService.cpp
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 08/10/13.
//
//

#include "UserService.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "Connector.h"
#include "App42API.h"

using namespace App42Network;


// define the static..
UserService* UserService::_instance = NULL;

UserService::UserService()
{
    
}

UserService* UserService::Initialize(string apikey, string secretkey)
{
	if(_instance == NULL)
    {
		_instance = new UserService();
	}
    _instance->Init(apikey, secretkey);
    return _instance;
}

UserService* UserService::getInstance()
{
	return _instance;
}

void UserService::Terminate()
{
	if(_instance != NULL)
    {
		delete _instance;
		_instance = NULL;
	}
}

string UserService::getJsonStringFromVector(vector<string>roles)
{
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *rolesJSON = cJSON_CreateArray();

    std::vector<string>::iterator it;
    
    for(it=roles.begin(); it!=roles.end(); ++it)
    {
        cJSON_AddItemToArray(rolesJSON, cJSON_CreateString(it->c_str()));
    }
    cJSON_AddItemReferenceToObject(bodyJSON, "role", rolesJSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(rolesJSON);
    cJSON_Delete(bodyJSON);

    free(cptrFormatted);
    
    return bodyString;

}

string UserService::buildCreateUserBody(const char *username, const char *password, const char *email,const char *roleList)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *userJSON = cJSON_CreateObject();
    
    // first construct the user
    if (strlen(username))
    {
        cJSON_AddStringToObject(userJSON, "userName", username);
    }
    
    if (strlen(email))
    {
        cJSON_AddStringToObject(userJSON, "email", email);
    }
    
    if (strlen(password))
    {
        cJSON_AddStringToObject(userJSON, "password", password);
    }
    
    if (strlen(roleList))
    {
        cJSON_AddStringToObject(userJSON, "roles", roleList);
    }
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "user", userJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(userJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}

string UserService::buildChangePasswordBody(string username, string oldPwd, string newPwd)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *userJSON = cJSON_CreateObject();
    
    // first construct the user
    if (username.length())
    {
        cJSON_AddStringToObject(userJSON, "userName", username.c_str());
    }
    
    if (oldPwd.length())
    {
        cJSON_AddStringToObject(userJSON, "oldPassword", oldPwd.c_str());
    }
    
    if (newPwd.length())
    {
        cJSON_AddStringToObject(userJSON, "newPassword", newPwd.c_str());
    }
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "user", userJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(userJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}

string UserService::buildProfileData(App42UserProfile *userProfile)
{
    string profileData = "";
    //construct profile data
    if (userProfile->firstName.length())
    {
        profileData.append("first_name:" + userProfile->firstName + "!");
    }
    
    if (userProfile->lastName.length())
    {
        profileData.append("last_name:" + userProfile->lastName + "!");
    }
    
    if (userProfile->getSex().length())
    {
        profileData.append("sex:" + userProfile->getSex() + "!");
    }
    
    
    if (userProfile->mobile.length())
    {
        profileData.append("mobile:" + userProfile->mobile + "!");
    }
    
    
    if (userProfile->line1.length())
    {
        profileData.append("line1:" + userProfile->line1 + "!");
    }
    
    
    if (userProfile->line2.length())
    {
        profileData.append("line2:" + userProfile->line2 + "!");
    }
    
    
    if (userProfile->city.length())
    {
        profileData.append("city:" + userProfile->city + "!");
    }
    
    
    if (userProfile->state.length())
    {
        profileData.append("state:" + userProfile->state + "!");
    }
    
    
    if (userProfile->country.length())
    {
        profileData.append("country:" + userProfile->country + "!");
    }
    
    
    if (userProfile->pincode.length())
    {
        profileData.append("pincode:" + userProfile->pincode + "!");
    }
    
    
    if (userProfile->homeLandLine.length())
    {
        profileData.append("home_land_line:" + userProfile->homeLandLine + "!");
    }
    
    
    if (userProfile->officeLandLine.length())
    {
        profileData.append("office_land_line:" + userProfile->officeLandLine + "!");
    }
    
    
    if (userProfile->dateOfBirth.length())
    {
        profileData.append("date_of_birth:" + userProfile->dateOfBirth + "!");
    }
    
    return profileData;
}

string UserService::buildCreateOrUpdateProfileBody(App42User *user)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *userJSON = cJSON_CreateObject();
    cJSON *profileJSON = cJSON_CreateObject();

    // first construct the user
    if (user->userName.length())
    {
        cJSON_AddStringToObject(userJSON, "userName", user->userName.c_str());
    }
    
    //construct profile
    App42UserProfile userProfile = user->profile;
    if (userProfile.firstName.length())
    {
        cJSON_AddStringToObject(profileJSON, "firstName", userProfile.firstName.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "firstName", "");
        
    if (userProfile.lastName.length())
    {
        cJSON_AddStringToObject(profileJSON, "lastName", userProfile.lastName.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "lastName", "");
    
    if (userProfile.getSex().length())
    {
        cJSON_AddStringToObject(profileJSON, "sex", userProfile.getSex().c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "sex", "");
    
    if (userProfile.mobile.length())
    {
        cJSON_AddStringToObject(profileJSON, "mobile", userProfile.mobile.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "mobile", "");
    
    if (userProfile.line1.length())
    {
        cJSON_AddStringToObject(profileJSON, "line1", userProfile.line1.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "line1", "");

    if (userProfile.line2.length())
    {
        cJSON_AddStringToObject(profileJSON, "line2", userProfile.line2.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "line2", "");
    
    if (userProfile.city.length())
    {
        cJSON_AddStringToObject(profileJSON, "city", userProfile.city.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "city", "");
    
    if (userProfile.state.length())
    {
        cJSON_AddStringToObject(profileJSON, "state", userProfile.state.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "state", "");
    
    if (userProfile.country.length())
    {
        cJSON_AddStringToObject(profileJSON, "country", userProfile.country.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "country", "");
    
    if (userProfile.pincode.length())
    {
        cJSON_AddStringToObject(profileJSON, "pincode", userProfile.pincode.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "pincode", "");
    
    if (userProfile.homeLandLine.length())
    {
        cJSON_AddStringToObject(profileJSON, "homeLandLine", userProfile.homeLandLine.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "homeLandLine", "");
    
    if (userProfile.officeLandLine.length())
    {
        cJSON_AddStringToObject(profileJSON, "officeLandLine", userProfile.officeLandLine.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "officeLandLine", "");
    
    if (userProfile.dateOfBirth.length())
    {
        cJSON_AddStringToObject(profileJSON, "dateOfBirth", userProfile.dateOfBirth.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "dateOfBirth", "");
    
    char *profileJSONStr = cJSON_PrintUnformatted(profileJSON);
    cJSON_AddStringToObject(userJSON, "profileData", profileJSONStr);
    free(profileJSONStr);
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "user", userJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(profileJSON);
    cJSON_Delete(userJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}

string UserService::buildCreateUserWithProfileBody(const char* userName, const char* password, const char* emailAddress,App42UserProfile *userProfile)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *userJSON = cJSON_CreateObject();
    cJSON *profileJSON = cJSON_CreateObject();
    
    // first construct the user
    if (strlen(userName)>0)
    {
        cJSON_AddStringToObject(userJSON, "userName", userName);
    }
    if (strlen(emailAddress)>0)
    {
        cJSON_AddStringToObject(userJSON, "password", password);
    }
    if (strlen(emailAddress)>0)
    {
        cJSON_AddStringToObject(userJSON, "email", emailAddress);
    }
    
    //construct profile
    if (userProfile->firstName.length())
    {
        cJSON_AddStringToObject(profileJSON, "firstName", userProfile->firstName.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "firstName", "");
    
    if (userProfile->lastName.length())
    {
        cJSON_AddStringToObject(profileJSON, "lastName", userProfile->lastName.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "lastName", "");
    
    if (userProfile->getSex().length())
    {
        cJSON_AddStringToObject(profileJSON, "sex", userProfile->getSex().c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "sex", "");
    
    if (userProfile->mobile.length())
    {
        cJSON_AddStringToObject(profileJSON, "mobile", userProfile->mobile.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "mobile", "");
    
    if (userProfile->line1.length())
    {
        cJSON_AddStringToObject(profileJSON, "line1", userProfile->line1.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "line1", "");
    
    if (userProfile->line2.length())
    {
        cJSON_AddStringToObject(profileJSON, "line2", userProfile->line2.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "line2", "");
    
    if (userProfile->city.length())
    {
        cJSON_AddStringToObject(profileJSON, "city", userProfile->city.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "city", "");
    
    if (userProfile->state.length())
    {
        cJSON_AddStringToObject(profileJSON, "state", userProfile->state.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "state", "");
    
    if (userProfile->country.length())
    {
        cJSON_AddStringToObject(profileJSON, "country", userProfile->country.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "country", "");
    
    if (userProfile->pincode.length())
    {
        cJSON_AddStringToObject(profileJSON, "pincode", userProfile->pincode.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "pincode", "");
    
    if (userProfile->homeLandLine.length())
    {
        cJSON_AddStringToObject(profileJSON, "homeLandLine", userProfile->homeLandLine.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "homeLandLine", "");
    
    if (userProfile->officeLandLine.length())
    {
        cJSON_AddStringToObject(profileJSON, "officeLandLine", userProfile->officeLandLine.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "officeLandLine", "");
    
    if (userProfile->dateOfBirth.length())
    {
        cJSON_AddStringToObject(profileJSON, "dateOfBirth", userProfile->dateOfBirth.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "dateOfBirth", "");
    
    char *profileJSONStr = cJSON_PrintUnformatted(profileJSON);
    cJSON_AddStringToObject(userJSON, "profileData", profileJSONStr);
    free(profileJSONStr);
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "user", userJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(profileJSON);
    cJSON_Delete(userJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}


string UserService::buildLogoutBody(string sessionId)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *userJSON = cJSON_CreateObject();
    
    // first construct the user
    if (sessionId.length())
    {
        cJSON_AddStringToObject(userJSON, "id", sessionId.c_str());
    }
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "session", userJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(userJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}

void UserService::CreateUser(const char *username, const char *password, const char *email, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        Util::throwExceptionIfStringNullOrBlank(password, "Password");
        Util::throwExceptionIfStringNullOrBlank(email, "Email");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();

    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string createUserbody = buildCreateUserBody(username, password, email,"");
    signParams["body"] = createUserbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string baseUrl = getBaseUrl("user");
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, createUserbody.c_str(), std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
    
}


void UserService::CreateUser(const char *username, const char *password, const char *email,vector<string>roleList,const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        Util::throwExceptionIfStringNullOrBlank(password, "Password");
        Util::throwExceptionIfStringNullOrBlank(email, "Email");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();

    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string createUserbody = buildCreateUserBody(username, password, email,getJsonStringFromVector(roleList).c_str());
     Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    signParams["body"] = createUserbody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string baseUrl = getBaseUrl("user/role");
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());

    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, createUserbody.c_str(), std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
    
}


void UserService::AssignRoles(const char *userName, vector<string> roleList,const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();

    /**
     * Creating SignParams and signature
     */
    map<string, string> postMap;
    populateSignParams(postMap);
    string createUserbody = buildCreateUserBody(userName, "", "",getJsonStringFromVector(roleList).c_str());
    postMap["body"] = createUserbody;
    string signature = Util::signMap(secretKey, postMap);
    
    /**
     * Creating URL
     */
    string baseUrl = getBaseUrl("user/assignrole");
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, createUserbody.c_str(), std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
    
}

void UserService::Authenticate(const char *username, const char *password, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        Util::throwExceptionIfStringNullOrBlank(password, "Password");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
        
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector( response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();

    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string postBody = buildCreateUserBody(username, password, "","");
    //Util::app42Trace("\n createUserbody = %s",postBody.c_str());
    signParams["body"] = postBody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string baseUrl = getBaseUrl("user/authenticate");
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    //Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());

    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, postBody.c_str(), std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::GetUser(const char *userName, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();

    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
	populateSignParams( signParams);
	signParams["userName"] = userName;
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append(userName);
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);
    //Util::app42Trace("\n baseUrl = %s",url.c_str());


    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl,headers, std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::GetUserByEmailId(const char *emailId, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(emailId, "EmailId");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> getMap;
	populateSignParams( getMap);
	getMap["emailId"] = emailId;
	string signature = Util::signMap(secretKey, getMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("email/");
    resource.append(emailId);
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);

    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl,headers, std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void UserService::GetAllUsers(const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();

    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
	populateSignParams( signParams);
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl,headers, std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::GetAllUsers(int max, int offset, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfMaxIsNotValid(max, "Max");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        e = NULL;
        return;
    }
    
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	populateSignParams( signMap);
    signMap["max"] = Util::ItoA(max);
    signMap["offset"] = Util::ItoA(offset);
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
    resource.append("paging/");
    resource.append(Util::ItoA(max)+"/");
    resource.append(Util::ItoA(offset));

	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);

    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl,headers, std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::GetAllUsersCount(const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        e = NULL;
        return;
    }
    
    /**
     * Creating SignParams and signature
     */
    /**
     * Creating URL
     */
    /**
     * Creating Headers
     */
    /**
     * Initiating Http call
     */

    
    string resource = "user/";
    resource.append("count/all");
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	populateSignParams( getMap);
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    string encodedUrl = url_encode(url);

    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    Util::executeGet(encodedUrl,headers, std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void UserService::LockUser(const char *username, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
   
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    string postBody = buildCreateUserBody(username, "", "","");
    signMap["body"] = postBody;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("lock");
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);

    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(encodedUrl, headers, postBody.c_str(), std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::UnlockUser(const char *username, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    string postBody = buildCreateUserBody(username, "", "","");
    signMap["body"] = postBody;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("unlock");
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);

    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(encodedUrl, headers, postBody.c_str(), std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::GetLockedUsers(const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        e = NULL;
        return;
    }
    
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> getMap;
	populateSignParams( getMap);
	string signature = Util::signMap(secretKey, getMap);
    
    
    /**
     * Creating URL
     */
    string resource = "user/";
    resource.append("locked");
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);

    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl,headers, std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::GetLockedUsers(int max, int offset, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfMaxIsNotValid(max, "Max");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        e = NULL;
        return;
    }
    
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	populateSignParams( signMap);
    signMap["max"] = Util::ItoA(max);
    signMap["offset"] = Util::ItoA(offset);
	string signature = Util::signMap(secretKey, signMap);
    
    
    /**
     * Creating URL
     */
    string resource = "user/";
    resource.append("locked/");
    resource.append(Util::ItoA(max)+"/");
    resource.append(Util::ItoA(offset));
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);

    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl,headers, std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::GetLockedUsersCount(const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        e = NULL;
        return;
    }
    
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> getMap;
	populateSignParams( getMap);
	string signature = Util::signMap(secretKey, getMap);
    
    
    /**
     * Creating URL
     */
    string resource = "user/";
    resource.append("count/locked");
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);

    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl,headers, std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::UpdateEmail(const char *username,const char *emailAddress, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        Util::throwExceptionIfStringNullOrBlank(emailAddress, "Email Address");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    string postBody = buildCreateUserBody(username, "", emailAddress,"");
    signMap["body"] = postBody;
	string signature = Util::signMap(secretKey, signMap);
    Util::printMap(signMap);
    /**
     * Creating URL
     */
    string resource = "user/";
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);

    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(encodedUrl, headers, postBody.c_str(), std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::DeleteUser(const char *username, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> getMap;
	populateSignParams( getMap);
	getMap["userName"] = username;
	string signature = Util::signMap(secretKey, getMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append(username);
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);

    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeDelete(encodedUrl,headers, std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::ChangeUserPassword(const char *username, const char *oldPassword, const char *newPassword, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        Util::throwExceptionIfStringNullOrBlank(oldPassword, "Old Password");
        Util::throwExceptionIfStringNullOrBlank(newPassword, "New Password");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    string postBody = buildChangePasswordBody(username, oldPassword, newPassword);
    signMap["body"] = postBody;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("changeUserPassword");
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(encodedUrl, headers, postBody.c_str(), std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void UserService::ResetUserPassword(const char *username, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    string postBody = buildCreateUserBody(username, "", "", "");
    signMap["body"] = postBody;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("resetAppUserPassword");
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);

    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(encodedUrl, headers, postBody.c_str(), std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void UserService::createOrUpdateProfile(App42User *user, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(user->userName, "User Name");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    string postBody = buildCreateOrUpdateProfileBody(user);
    signMap["body"] = postBody;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("profile");
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);

    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(encodedUrl, headers, postBody.c_str(), std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::GetUsersByProfileData(App42UserProfile *profileData,const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        //Util::throwExceptionIfStringNullOrBlank(user.userName, "User Name");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
	string signature = Util::signMap(secretKey, signMap);
    /**
     * Creating URL
     */
    string parameters = buildProfileData(profileData);
    string resource = "user/";
	resource.append("profile/");
    resource.append(parameters);
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);

    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl, headers,std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::Logout(const char *sessionId,const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(sessionId, "SessionId");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    string postBody = buildLogoutBody(sessionId);
    signMap["body"] = postBody;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "";
	resource.append("session");
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);

    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(encodedUrl, headers, postBody.c_str(), std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::GetRolesByUser(const char *userName,const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    signMap["userName"] = userName;
	string signature = Util::signMap(secretKey, signMap);
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append(userName);
    resource.append("/roles");
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);

    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl, headers,std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::GetUsersByRole(const char *role, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(role, "Role");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    signMap["role"] = role;
	string signature = Util::signMap(secretKey, signMap);
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("role/");
    resource.append(role);
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);
    
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl, headers,std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::RevokeRole(const char *userName, const char *role, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(role, "Role");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
	signParams["userName"] = userName;
    signParams["role"] = role;
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append(userName);
    resource.append("/revoke/");
    resource.append(role);
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);
    
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeDelete(encodedUrl,headers, std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::RevokeAllRoles(const char *userName, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
	signParams["userName"] = userName;
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append(userName);
    resource.append("/revoke");
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);
    
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeDelete(encodedUrl,headers, std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}


void UserService::GetUsersByGroup(vector<string> users, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfVectorIsNullOrBlank(users, "Users");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
	populateSignParams( signParams);
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("groupusers");
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    
    string usersString = "[";
    usersString.append(Util::GetStringFromVector(users));
    usersString.append("]");
    metaHeaders["userList"] = usersString;
    
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl,headers, std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::CreateUserWithProfile(const char *userName, const char *password, const char *emailAddress, App42UserProfile *profile, const app42CallBack& pSelector)
{
    App42UserResponse *response = new App42UserResponse(pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(password, "Password");
        Util::throwExceptionIfStringNullOrBlank(emailAddress, "EmailAddress");
        //Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if ( pSelector)
        {
            pSelector(response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string postBody = buildCreateUserWithProfileBody(userName, password, emailAddress, profile);
    signParams["body"] = postBody;
	string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("userwithprofile");
	string url = getBaseUrl(resource);
    url.append("?");
    string encodedUrl = url_encode(url);
    
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, postBody.c_str(), std::bind(&App42UserResponse::onComplete, response, std::placeholders::_1, std::placeholders::_2));
}

void UserService::AddUserInfo(App42Object* app42Object, const char* collectionName)
{
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
        Util::throwExceptionIfStringNullOrBlank(App42API::getDbName().c_str(), "Collection Name");
    }
    catch (App42Exception *e)
    {
        throw e;
    }
    
    this->dbName = App42API::getDbName();
    this->collectionName = collectionName;
    this->jsonObject = app42Object->toString();
}

