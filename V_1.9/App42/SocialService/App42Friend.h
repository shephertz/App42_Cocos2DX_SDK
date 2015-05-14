//
//  App42Friend.h
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 26/06/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__App42Friend__
#define __App42Cocos2dX3_0Sample__App42Friend__

#include <iostream>

using namespace std;
class App42Friend
{
public:
    
    /**
     * Getters
     */
    string getName(){return name;};
    string getPicture(){return picture;};
    string getFriendId(){return friendId;};
    bool getInstalled(){return installed;};
    
    /**
     * Setters
     */
    void setName(string _name){name=_name;};
    void setPicture(string _picture){ picture=_picture;};
    void setFriendId(string _friendId){ friendId=_friendId;};
    void setInstalled(double _installed){ installed=_installed;};
    
protected:
    std::string name;
    std::string picture;
    std::string friendId;
    bool installed;
    
private:
};

#endif /* defined(__App42Cocos2dX3_0Sample__App42Friend__) */
