//
//  TestUserService.cpp
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#include "TestUserService.h"
#include "TestHome.h"


#define GO_HOME 101



USING_NS_CC;

Scene* TestUserService::createScene()
{
    // 'scene' is an autorelease Object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease Object
    auto layer = TestUserService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestUserService::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    float button_y_Offset =30;
    float y_pos = visibleSize.height-button_y_Offset;
    float x_pos = origin.x + visibleSize.width/4;
    
    
    /**
     * Create User
     */
    auto createUserLabel = LabelTTF::create("Create User", "Marker Felt", 24);
    createUserLabel->setColor(Color3B::WHITE);
    auto createUserItem  = MenuItemLabel::create(createUserLabel, CC_CALLBACK_1(TestUserService::createUser, this));
    createUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Create User With Roles
     */
    auto createUserWithRolesLabel = LabelTTF::create("CreateUserWithRoles", "Marker Felt", 24);
    createUserWithRolesLabel->setColor(Color3B::WHITE);
    auto createUserWithRolesItem  = MenuItemLabel::create(createUserWithRolesLabel, CC_CALLBACK_1(TestUserService::createUserWithRoles, this));
    y_pos = y_pos-button_y_Offset;
    createUserWithRolesItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * AssignRoles
     */
    auto assignRolesLabel = LabelTTF::create("AssignRoles", "Marker Felt", 24);
    assignRolesLabel->setColor(Color3B::WHITE);
    auto assignRolesItem  = MenuItemLabel::create(assignRolesLabel, CC_CALLBACK_1(TestUserService::assignRoles, this));
    y_pos = y_pos-button_y_Offset;
    assignRolesItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Authenticate User
     */
    auto authenticateUserLabel = LabelTTF::create("Authenticate User", "Marker Felt", 24);
    authenticateUserLabel->setColor(Color3B::WHITE);
    auto authenticateUserItem  = MenuItemLabel::create(authenticateUserLabel, CC_CALLBACK_1(TestUserService::authenticateUser, this));
    y_pos = y_pos-button_y_Offset;
    authenticateUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Authenticate User Via Email
     */
    auto authenticateUserViaEmailLabel = LabelTTF::create("AuthenticateUserViaEmail", "Marker Felt", 24);
    authenticateUserViaEmailLabel->setColor(Color3B::WHITE);
    auto authenticateUserViaEmailItem  = MenuItemLabel::create(authenticateUserViaEmailLabel, CC_CALLBACK_1(TestUserService::authenticateUserViaEmail, this));
    y_pos = y_pos-button_y_Offset;
    authenticateUserViaEmailItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get User With User Name
     */
    auto getUserLabel = LabelTTF::create("Get User", "Marker Felt", 24);
    getUserLabel->setColor(Color3B::WHITE);
    auto getUserItem  = MenuItemLabel::create(getUserLabel, CC_CALLBACK_1(TestUserService::getUserWithUserName, this));
    y_pos = y_pos-button_y_Offset;
    getUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get User With EmailID
     */
    auto getUserByEmailLabel = LabelTTF::create("GetUserByEmailId", "Marker Felt", 24);
    getUserByEmailLabel->setColor(Color3B::WHITE);
    auto getUserByEmailItem  = MenuItemLabel::create(getUserByEmailLabel, CC_CALLBACK_1(TestUserService::getUserWithEmailId, this));
    y_pos = y_pos-button_y_Offset;
    getUserByEmailItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get All Users
     */
    auto getAllUserLabel = LabelTTF::create("GetAllUser", "Marker Felt", 24);
    getAllUserLabel->setColor(Color3B::WHITE);
    auto getAllUserItem  = MenuItemLabel::create(getAllUserLabel, CC_CALLBACK_1(TestUserService::getAllUser, this));
    y_pos = y_pos-button_y_Offset;
    getAllUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get All Users By Paging
     */
    auto getAllUserByPagingLabel = LabelTTF::create("GetAllUserByPaging", "Marker Felt", 24);
    getAllUserByPagingLabel->setColor(Color3B::WHITE);
    auto getAllUserByPagingItem  = MenuItemLabel::create(getAllUserByPagingLabel, CC_CALLBACK_1(TestUserService::getAllUsersByPaging, this));
    y_pos = y_pos-button_y_Offset;
    getAllUserByPagingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get All Users Count
     */
    auto getAllUsersCountLabel = LabelTTF::create("GetAllUsersCount", "Marker Felt", 24);
    getAllUsersCountLabel->setColor(Color3B::WHITE);
    auto getAllUsersCountItem  = MenuItemLabel::create(getAllUsersCountLabel, CC_CALLBACK_1(TestUserService::getAllUsersCount, this));
    y_pos = y_pos-button_y_Offset;
    getAllUsersCountItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Lock User
     */
    auto lockUserLabel = LabelTTF::create("LockUser", "Marker Felt", 24);
    lockUserLabel->setColor(Color3B::WHITE);
    auto lockUserItem  = MenuItemLabel::create(lockUserLabel, CC_CALLBACK_1(TestUserService::lockUser, this));
    y_pos = y_pos-button_y_Offset;
    lockUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * UnLock User
     */
    auto unlockUserLabel = LabelTTF::create("UnLockUser", "Marker Felt", 24);
    unlockUserLabel->setColor(Color3B::WHITE);
    auto unlockUserItem  = MenuItemLabel::create(unlockUserLabel, CC_CALLBACK_1(TestUserService::unlockUser, this));
    y_pos = y_pos-button_y_Offset;
    unlockUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetLockedUsers
     */
    auto getAllLockedUsersLabel = LabelTTF::create("GetLockedUsers", "Marker Felt", 24);
    getAllLockedUsersLabel->setColor(Color3B::WHITE);
    auto getAllLockedUsersItem  = MenuItemLabel::create(getAllLockedUsersLabel, CC_CALLBACK_1(TestUserService::getLockedUsers, this));
    y_pos = y_pos-button_y_Offset;
    getAllLockedUsersItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetLockedUsersByPaging
     */
    auto getLockedUsersPagingLabel = LabelTTF::create("GetLockedUsersByPaging", "Marker Felt", 24);
    getLockedUsersPagingLabel->setColor(Color3B::WHITE);
    auto getLockedUsersPagingItem  = MenuItemLabel::create(getLockedUsersPagingLabel, CC_CALLBACK_1(TestUserService::getLockedUsersByPaging, this));
    y_pos = y_pos-button_y_Offset;
    getLockedUsersPagingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetLockedUsersCount
     */
    auto getAllLockedUsersCountLabel = LabelTTF::create("GetLockedUsersCount", "Marker Felt", 24);
    getAllLockedUsersCountLabel->setColor(Color3B::WHITE);
    auto getAllLockedUsersCountItem  = MenuItemLabel::create(getAllLockedUsersCountLabel, CC_CALLBACK_1(TestUserService::getLockedUsersCount, this));
    y_pos = y_pos-button_y_Offset;
    getAllLockedUsersCountItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Update Email
     */
    auto updateEmailLabel = LabelTTF::create("UpdateEmail", "Marker Felt", 24);
    updateEmailLabel->setColor(Color3B::WHITE);
    auto updateEmailItem  = MenuItemLabel::create(updateEmailLabel, CC_CALLBACK_1(TestUserService::updateEmail, this));
    y_pos = visibleSize.height-button_y_Offset;;
    x_pos += visibleSize.width/2;
    updateEmailItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Delete User
     */
    auto deleteUserLabel = LabelTTF::create("DeleteUser", "Marker Felt", 24);
    deleteUserLabel->setColor(Color3B::WHITE);
    auto deleteUserItem  = MenuItemLabel::create(deleteUserLabel, CC_CALLBACK_1(TestUserService::deleteUser, this));
    y_pos = y_pos-button_y_Offset;
    deleteUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Delete User Permanent
     */
    auto deleteUserPermanentLabel = LabelTTF::create("DeleteUserPermanent", "Marker Felt", 24);
    deleteUserPermanentLabel->setColor(Color3B::WHITE);
    auto deleteUserPermanentItem  = MenuItemLabel::create(deleteUserPermanentLabel, CC_CALLBACK_1(TestUserService::deleteUserPermanent, this));
    y_pos = y_pos-button_y_Offset;
    deleteUserPermanentItem->setPosition(Point(x_pos,y_pos));

    /**
     * Change User Password
     */
    auto changePwdLabel = LabelTTF::create("ChangePassword", "Marker Felt", 24);
    changePwdLabel->setColor(Color3B::WHITE);
    auto changePwdItem  = MenuItemLabel::create(changePwdLabel, CC_CALLBACK_1(TestUserService::changePassword, this));
    y_pos = y_pos-button_y_Offset;
    changePwdItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Reset User Password
     */
    auto resetPwdLabel = LabelTTF::create("ResetPassword", "Marker Felt", 24);
    resetPwdLabel->setColor(Color3B::WHITE);
    auto resetPwdItem  = MenuItemLabel::create(resetPwdLabel, CC_CALLBACK_1(TestUserService::resetPassword, this));
    y_pos = y_pos-button_y_Offset;
    resetPwdItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Create or Update User Profile
     */
    auto profileLabel = LabelTTF::create("Create/UpdateUserProfile", "Marker Felt", 24);
    profileLabel->setColor(Color3B::WHITE);
    auto profileItem  = MenuItemLabel::create(profileLabel, CC_CALLBACK_1(TestUserService::createOrUpdateProfile, this));
    y_pos = y_pos-button_y_Offset;
    profileItem->setPosition(Point(x_pos,y_pos));

    /**
     * Get Users By Profile
     */
    auto getUsersByProfileLabel = LabelTTF::create("GetUsersByProfile", "Marker Felt", 24);
    getUsersByProfileLabel->setColor(Color3B::WHITE);
    auto getUsersByProfileItem  = MenuItemLabel::create(getUsersByProfileLabel, CC_CALLBACK_1(TestUserService::getUserByProfileData, this));
    y_pos = y_pos-button_y_Offset;
    getUsersByProfileItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * LogOut
     */
    auto logoutLabel = LabelTTF::create("LogOut", "Marker Felt", 24);
    logoutLabel->setColor(Color3B::WHITE);
    auto logoutItem  = MenuItemLabel::create(logoutLabel, CC_CALLBACK_1(TestUserService::logout, this));
    y_pos = y_pos-button_y_Offset;
    logoutItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetRolesByUser
     */
    auto getRolesByUserLabel = LabelTTF::create("GetRolesByUser", "Marker Felt", 24);
    getRolesByUserLabel->setColor(Color3B::WHITE);
    auto getRolesByUserItem  = MenuItemLabel::create(getRolesByUserLabel, CC_CALLBACK_1(TestUserService::getRolesByUser, this));
    y_pos = y_pos-button_y_Offset;
    getRolesByUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetUsersByRole
     */
    auto getUsersByRoleLabel = LabelTTF::create("GetUsersByRole", "Marker Felt", 24);
    getUsersByRoleLabel->setColor(Color3B::WHITE);
    auto getUsersByRoleItem  = MenuItemLabel::create(getUsersByRoleLabel, CC_CALLBACK_1(TestUserService::getUsersByRole, this));
    y_pos = y_pos-button_y_Offset;
    getUsersByRoleItem->setPosition(Point(x_pos,y_pos));
    
    
    /**
     * RevokeRole
     */
    auto revokeRoleLabel = LabelTTF::create("RevokeRole", "Marker Felt", 24);
    revokeRoleLabel->setColor(Color3B::WHITE);
    auto revokeRoleItem  = MenuItemLabel::create(revokeRoleLabel, CC_CALLBACK_1(TestUserService::revokeRole, this));
    y_pos = y_pos-button_y_Offset;
    revokeRoleItem->setPosition(Point(x_pos,y_pos));

    /**
     * RevokeAllRoles
     */
    auto revokeAllRolesLabel = LabelTTF::create("RevokeAllRoles", "Marker Felt", 24);
    revokeAllRolesLabel->setColor(Color3B::WHITE);
    auto revokeAllRolesItem  = MenuItemLabel::create(revokeAllRolesLabel, CC_CALLBACK_1(TestUserService::revokeAllRoles, this));
    y_pos = y_pos-button_y_Offset;
    revokeAllRolesItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetUsersByGroup
     */
    auto getUsersByGroupLabel = LabelTTF::create("GetUsersByGroup", "Marker Felt", 24);
    getUsersByGroupLabel->setColor(Color3B::WHITE);
    auto getUsersByGroupItem  = MenuItemLabel::create(getUsersByGroupLabel, CC_CALLBACK_1(TestUserService::getUsersByGroup, this));
    y_pos = y_pos-button_y_Offset;
    getUsersByGroupItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * CreateUserWithProfile
     */
    auto createUserWithProfileLabel = LabelTTF::create("CreateUserWithProfile", "Marker Felt", 24);
    createUserWithProfileLabel->setColor(Color3B::WHITE);
    auto createUserWithProfileItem  = MenuItemLabel::create(createUserWithProfileLabel, CC_CALLBACK_1(TestUserService::createUserWithProfile, this));
    y_pos = y_pos-button_y_Offset;
    createUserWithProfileItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * CreateUserWithCustomData
     */
    auto createUserWithCustomDataLabel = LabelTTF::create("CreateUserWithCustomData", "Marker Felt", 24);
    createUserWithCustomDataLabel->setColor(Color3B::WHITE);
    auto createUserWithCustomDataItem  = MenuItemLabel::create(createUserWithCustomDataLabel, CC_CALLBACK_1(TestUserService::createUserWithCustomData, this));
    y_pos = y_pos-button_y_Offset;
    createUserWithCustomDataItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetUserWithCustomData
     */
    auto getUserWithCustomDataLabel = LabelTTF::create("GetUserWithCustomData", "Marker Felt", 24);
    getUserWithCustomDataLabel->setColor(Color3B::WHITE);
    auto getUserWithCustomDataItem  = MenuItemLabel::create(getUserWithCustomDataLabel, CC_CALLBACK_1(TestUserService::getUserWithCustomData, this));
    y_pos = y_pos-button_y_Offset;
    getUserWithCustomDataItem->setPosition(Point(x_pos,y_pos));

    /**
     * GetAllUsersWithCustomData
     */
    auto getAllUsersWithCustomDataLabel = LabelTTF::create("GetAllUsersWithCustomData", "Marker Felt", 24);
    getAllUsersWithCustomDataLabel->setColor(Color3B::WHITE);
    auto getAllUsersWithCustomDataItem  = MenuItemLabel::create(getAllUsersWithCustomDataLabel, CC_CALLBACK_1(TestUserService::getAllUsersWithCustomData, this));
    y_pos = y_pos-button_y_Offset;
    getAllUsersWithCustomDataItem->setPosition(Point(x_pos,y_pos));
    
    /*
     
     createUserWithProfile
     */
    
    /**
     * Back Button
     */
    auto backButtonItem = MenuItemImage::create(
                                           "BackButton.png",
                                           "BackButton.png",
                                           CC_CALLBACK_1(TestUserService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(origin.x + visibleSize.width/2 ,
                                 origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    
    
    
    /**
     * Create Menu
     */
    auto menu = Menu::create(createUserItem,
                             createUserWithRolesItem,
                             assignRolesItem,
                             authenticateUserItem,
                             authenticateUserViaEmailItem,
                             getUserItem,
                             getUserByEmailItem,
                             backButtonItem,
                             getAllUserItem,
                             getAllUserByPagingItem,NULL);

	auto menu1 = Menu::create(
                             getAllUsersCountItem,
                             lockUserItem,
                             unlockUserItem,
                             getAllLockedUsersItem,
                             getLockedUsersPagingItem,
                             getAllLockedUsersCountItem,
                             updateEmailItem,
                             deleteUserItem,
                             deleteUserPermanentItem,NULL);

	auto menu2 = Menu::create(
                             changePwdItem,
                             resetPwdItem,
                             profileItem,
                             getUsersByProfileItem,
                             logoutItem,
                             getRolesByUserItem,
                             getUsersByRoleItem,
                             revokeRoleItem,
                             revokeAllRolesItem, NULL);

	auto menu3 = Menu::create(
                             getUsersByGroupItem,
                             createUserWithProfileItem,
                             createUserWithCustomDataItem,
                             getUserWithCustomDataItem,
                             getAllUsersWithCustomDataItem,NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	menu1->setPosition(Point::ZERO);
    this->addChild(menu1, 1);

	menu2->setPosition(Point::ZERO);
    this->addChild(menu2, 1);

	menu3->setPosition(Point::ZERO);
    this->addChild(menu3, 1);

    return true;
}



void TestUserService::createUser(Ref* pSender)
{
    UserService *userService = App42API::BuildUserService();
    const char* userName = "Nick243453232323";
    const char* pwd = "*******";
    const char* emailId = "Nick243452323232@shephertz.co.in";
    userService->CreateUser(userName, pwd, emailId,app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::createUserWithCustomData(Ref* pSender)
{
    UserService *userService = App42API::BuildUserService();
    const char* userName = "App42Cocos2dx";
    const char* pwd = "*******";
    const char* emailId = "App42Cocos2dx@shephertz.co.in";
    
    const char* dbName = "jsonDocument2";
    const char* collectionName = "TestingScore";
    
    App42Object *object = new App42Object();
    object->setObject("FirstName", "App42");
    object->setObject("LastName", "CloudAPI");
    App42API::setDbName(dbName);
    userService->AddUserInfo(object, collectionName);
    userService->CreateUser(userName, pwd, emailId,app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::getUserWithCustomData(Ref* pSender)
{
    UserService *userService = App42API::BuildUserService();
    const char* key = "FirstName";
    const char* value = "App42";
    const char* dbName = "jsonDocument2";
    const char* collectionName = "TestingScore";
    //App42API::setDbName(dbName);
    Query *query = QueryBuilder::BuildQuery(key, value, APP42_OP_EQUALS);
    userService->setQuery(dbName, collectionName, query);
    //userService->setQuery(collectionName, query);
    const char* userName = "App42Cocos2dx";
    userService->GetUser(userName, app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::getAllUsersWithCustomData(Ref* pSender)
{
    UserService *userService = App42API::BuildUserService();
    const char* key = "FirstName";
    const char* value = "App42";
    const char* dbName = "jsonDocument2";
    const char* collectionName = "TestingScore";
    App42API::setDbName(dbName);
    Query *query = QueryBuilder::BuildQuery(key, value, APP42_OP_EQUALS);
    userService->setQuery(collectionName, query);
    userService->GetAllUsers(app42callback(TestUserService::onUserRequestCompleted, this));
}



void TestUserService::createUserWithRoles(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    const char* userName = "Nick";
    const char* pwd = "*******";
    const char* emailId = "nick@shephertz.co.in";
    
    vector<string>roles;
    roles.push_back("s_admin");
    roles.push_back("s_manager");
    roles.push_back("s_techlead");

    userService->CreateUser(userName, pwd, emailId, roles, app42callback(TestUserService::onUserRequestCompleted, this));
}


void TestUserService::assignRoles(Ref *sender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    const char* userName = "RajeevRanjan111";
    
    vector<string>roles;
    roles.push_back("s_Manager");
    roles.push_back("COO");

    
    userService->AssignRoles(userName, roles, app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::authenticateUser(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    const char* userName = "Nick243";
    const char* pwd = "*******";
   // const char* emailId = "nick@shephertz.co.in";
    
    userService->Authenticate(userName, pwd, app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::authenticateUserViaEmail(Ref *sender)
{
    UserService *userService = App42API::BuildUserService();
    
    const char* pwd = "*******";
    const char* emailId = "nick@shephertz.com";
    
    map<string,string>otherMetaHeaders;
    otherMetaHeaders["emailAuth"] = "true";
    userService->setOtherMetaHeaders(otherMetaHeaders);
    
    userService->Authenticate(emailId, pwd, app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::getUserWithUserName(Ref* pSender)
{
    UserService *userService = App42API::BuildUserService();
    const char* userName = "Nicky";
    userService->GetUser(userName, app42callback(TestUserService::onUserRequestCompleted, this));
}



void TestUserService::getUserWithEmailId(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    const char* emailId = "nicky@shephertz.co.in";

    userService->GetUserByEmailId(emailId, app42callback(TestUserService::onUserRequestCompleted, this));
    
}

void TestUserService::getAllUser(Ref* pSender)
{
    //App42API::setIsTraceEnabled(true)(false);
    UserService *userService = App42API::BuildUserService();
    userService->GetAllUsers(app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::getAllUsersByPaging(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    int max = 1;
    int offset = 0;
    userService->GetAllUsers(max,offset,app42callback(TestUserService::onUserRequestCompleted, this));
}


void TestUserService::getAllUsersCount(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    userService->GetAllUsersCount(app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::lockUser(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    const char* userName = "Nicky";
    userService->LockUser(userName,app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::unlockUser(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    const char* userName = "Nicky";
    userService->UnlockUser(userName,app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::getLockedUsers(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    userService->GetLockedUsers(app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::getLockedUsersByPaging(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    int max = 1;
    int offset = 0;
    userService->GetLockedUsers(max,offset,app42callback(TestUserService::onUserRequestCompleted, this));
}


void TestUserService::getLockedUsersCount(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    userService->GetLockedUsersCount(app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::updateEmail(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    const char* userName = "Nick";
    const char* emailId = "nick@shephertz.com";
    userService->setAdminKey(APP_ADMIN_KEY);
    userService->UpdateEmail(userName,emailId, app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::deleteUser(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    const char* userName = "RajeevRanjan11";
    userService->DeleteUser(userName, app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::deleteUserPermanent(Ref *sender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    const char* userName = "Nick";
    map<string,string>otherMetaHeaders;
    otherMetaHeaders["deletePermanent"] = "true";
    userService->setOtherMetaHeaders(otherMetaHeaders);
    
    userService->DeleteUser(userName, app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::changePassword(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    const char* userName = "Nicky";
    const char* oldPwd = "*******";
    const char* newPwd = "8800927154";
    userService->ChangeUserPassword(userName, newPwd, oldPwd, app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::resetPassword(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    const char* userName = "Brown";
    user->ResetUserPassword(userName, app42callback(TestUserService::onUserRequestCompleted, this));
}


void TestUserService::createOrUpdateProfile(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    App42User user;
    user.userName = "Nicky";
    App42UserProfile userProfile;
    userProfile.firstName = "Nick";
    userProfile.lastName = "Gill";
    userProfile.setSex(App42UserProfile::MALE);
    userProfile.dateOfBirth = "";
    userProfile.city = "Houston";
    userProfile.state = "Texas";
    userProfile.pincode = "74193";
    userProfile.country = "USA";
    userProfile.mobile = "+1-1111-111-111";
    userProfile.homeLandLine = "+1-2222-222-222";
    userProfile.officeLandLine = "+1-33333-333-333";
    user.profile = userProfile;
    userService->createOrUpdateProfile(&user, app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::getUserByProfileData(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();

    App42UserProfile userProfile;
    userProfile.firstName = "Nick";
    userProfile.lastName = "Gill";
//    userProfile.setSex(App42UserProfile::MALE);
//    userProfile.dateOfBirth = "";
//    userProfile.city = "Houston";
//    userProfile.state = "Texas";
//    userProfile.pincode = "74193";
//    userProfile.country = "USA";
//    userProfile.mobile = "+1-1111-111-111";
//    userProfile.homeLandLine = "+1-2222-222-222";
//    userProfile.officeLandLine = "+1-33333-333-333";
//    printf("Sex=%s",userProfile.getSex().c_str());
    userService->GetUsersByProfileData(&userProfile, app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::logout(Ref* pSender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    const char* sessionId = "78724aea-3c8d-43a0-98d9-84df215ba510";
    userService->Logout(sessionId, app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::getRolesByUser(Ref *sender)
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    const char* userName = "Nicky";
    userService->GetRolesByUser(userName, app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::getUsersByRole(Ref* sender)
{
    UserService *userService = App42API::BuildUserService();
    const char* role = "COO";
    userService->GetUsersByRole(role, app42callback(TestUserService::onUserRequestCompleted, this));

}
void TestUserService::revokeRole(Ref* sender)
{
    UserService *userService = App42API::BuildUserService();
    const char* userName = "RajeevRanjan111";
    const char* role = "COO";
    userService->RevokeRole(userName, role, app42callback(TestUserService::onUserRequestCompleted, this));
}
void TestUserService::revokeAllRoles(Ref* sender)
{
    UserService *userService = App42API::BuildUserService();
    const char* userName = "RajeevRanjan111";
    userService->RevokeAllRoles(userName, app42callback(TestUserService::onUserRequestCompleted, this));
}

void TestUserService::getUsersByGroup(Ref* sender)
{
    UserService *userService = App42API::BuildUserService();

    vector<string>users;
    users.push_back("RajeevRanjan111");
    users.push_back("Nicky");
    userService->GetUsersByGroup(users, app42callback(TestUserService::onUserRequestCompleted, this));
}
void TestUserService::createUserWithProfile(Ref *sender)
{
    const char* userName = "Brown";
    const char* password = "chocobrowny";
    const char* email = "brown@shephertz.co.in";
    App42UserProfile userProfile;
    userProfile.firstName = "Brown";
    userProfile.city = "NewYork";
    userProfile.mobile = "1234567890";
    
    UserService *userService = App42API::BuildUserService();
    userService->CreateUserWithProfile(userName, password, email, &userProfile, app42callback(TestUserService::onUserRequestCompleted, this));
    
}

void TestUserService::getUserInfo(Ref *sender)
{
    
}


/**
 * Callback Methods
 */
void TestUserService::onUserRequestCompleted( void *response)
{
    App42UserResponse *userResponse = (App42UserResponse*)response;
    printf("\ncode=%d...=%d",userResponse->getCode(),userResponse->isSuccess);
    printf("\nResponse Body=%s",userResponse->getBody().c_str());
    
    
    string code = StringUtils::format("Code = %d",userResponse->getCode());
    responseArray.push_back(code);
    
    if (userResponse->isSuccess)
    {
        printf("\nTotalRecords=%d",userResponse->getTotalRecords());
        
        for(std::vector<App42User>::iterator it = userResponse->users.begin(); it != userResponse->users.end(); ++it)
        {
            printf("\n UserName=%s",it->userName.c_str());
            printf("\n Email=%s",it->email.c_str());
            printf("\n SessionId=%s",it->sessionId.c_str());
            printf("\n isAccountLocked=%d",it->isAccountLocked);
            printf("\n CreatedOn=%s",it->createdOn.c_str());
            printf("\n Password=%s",it->password.c_str());
            //Fetching Profile Info
            printf("\n FirstName=%s",it->profile.firstName.c_str());
            printf("\n LastName=%s",it->profile.lastName.c_str());
            printf("\n Sex=%s",it->profile.getSex().c_str());
            printf("\n Date of Birth=%s",it->profile.dateOfBirth.c_str());
            printf("\n Line1=%s",it->profile.line1.c_str());
            printf("\n Line2=%s",it->profile.line2.c_str());
            printf("\n City=%s",it->profile.city.c_str());
            printf("\n State=%s",it->profile.state.c_str());
            printf("\n Pincode=%s",it->profile.pincode.c_str());
            printf("\n Country=%s",it->profile.country.c_str());
            printf("\n Mobile=%s",it->profile.mobile.c_str());
            printf("\n HomeLandLine=%s",it->profile.homeLandLine.c_str());
            printf("\n OfficeLandLine=%s",it->profile.officeLandLine.c_str());

            //Fetching Roles
            std::vector<string>::iterator iit;
            for(iit=it->roleList.begin(); iit!=it->roleList.end(); ++iit)
            {
                printf("\n%s",iit->c_str());
            }
            
            //Fetching Custom Data
            std::vector<JSONDocument>::iterator jsonDoc;
            for(jsonDoc=it->jsonDocArray.begin(); jsonDoc!=it->jsonDocArray.end(); ++jsonDoc)
            {
                printf("\n CreatedAt=%s",jsonDoc->getCreatedAt().c_str());
                printf("\n DocId=%s",jsonDoc->getDocId().c_str());
                printf("\n Event=%s",jsonDoc->getEvent().c_str());
                printf("\n Owner=%s",jsonDoc->getOwner().c_str());
                printf("\n UpdatedAt=%s",jsonDoc->getUpdatedAt().c_str());
                printf("\n JsonDoc=%s\n",jsonDoc->getJsonDoc().c_str());
            }
        }
    }
    else
    {
        printf("\nerrordetails:%s",userResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",userResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",userResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",userResponse->httpErrorCode);
        string error = StringUtils::format("Error = %s",userResponse->errorDetails.c_str());
        responseArray.push_back(error);
        string errorMsg = StringUtils::format("ErrorMessage = %s",userResponse->errorMessage.c_str());
        responseArray.push_back(errorMsg);
    }
    auto scheduler = Director::getInstance()->getScheduler();
    
    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(TestUserService::loadResponseScene, this));
    
}

void TestUserService::loadResponseScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ResponseScene::create();
    layer->serviceId = GO_HOME;
    // add layer as a child to scene
    vector<string>::iterator it;
    
    for (it= responseArray.begin(); it!= responseArray.end(); it++)
    {
        layer->loadResponse(*it);
    }
    scene->addChild(layer);
    // run
    Director::getInstance()->replaceScene(scene);
}





void TestUserService::menuCloseCallback(Ref* pSender)
{
    MenuItem *item = (MenuItem*)pSender;
    int senderTag = item->getTag();
    switch (senderTag)
    {
        case GO_HOME:
        {
            // create a scene. it's an autorelease Object
            auto scene = TestHome::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        default:
            break;
    }
}