//
//  ACL.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 24/07/14.
//
//

#include "ACL.h"

ACL::ACL(const char* _userName, Permission _permission)
{
    userName = _userName;
    permission = getPermission(_permission);
}

ACL::ACL()
{
    userName = "";
    permission = "";
}


ACL::~ACL()
{
    
}

void ACL::setUserName(string _userName)
{
    userName = _userName;
}
void ACL::setPermission(Permission _permission)
{
    permission = getPermission(_permission);
}

void ACL::setPermission(string _permission)
{
    permission = _permission;
}

string ACL::getUserName()
{
    return userName;
}
string ACL::getPermission()
{
    return permission;
}

string ACL::toString()
{
    string aclString = "User : ";
    aclString.append(userName);
    aclString.append(" Permission : ");
    aclString.append(permission);
    return aclString;
}

bool ACL::equals(ACL *aclObject)
{
    if (aclObject == NULL)
    {
        return false;
    }
    else
    {
        if (aclObject->userName.length() && aclObject->permission.length() && (aclObject->userName.compare(userName) ==0)&& (aclObject->permission.compare(permission)==0))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}