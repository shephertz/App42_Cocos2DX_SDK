//
//  ResponseScene.h
//  App42Cocos2dXSample
//
//  Created by Shephertz Technologies Pvt Ltd on 10/09/14.
//
//

#ifndef __App42Cocos2dXSample__ResponseScene__
#define __App42Cocos2dXSample__ResponseScene__

#include <iostream>
#include "cocos2d.h"

class ResponseScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void loadResponse(std::string response);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ResponseScene);
    
    float y_pos;
    int serviceId;
    //cocos2d::Scene *scene;
};

#endif /* defined(__App42Cocos2dXSample__ResponseScene__) */
