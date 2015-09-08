//
//  TestHome.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 02/04/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__TestHome__
#define __App42Cocos2dX3_0Sample__TestHome__

#include <iostream>
#include "cocos2d.h"
#include "App42API.h"
#include "ResponseScene.h"

//PushTest42
#define API_KEY    "7c935af6a59831bc47ec98b764e8f0e06dad59cd4c7ed86970b14875aa8bf4bc"
#define SECRET_KEY "742baa8ac6ba0bfc0285117f27ec3988ce307ae2f5eed0849997c387efc4c685"
//#define APP_ADMIN_KEY "34cc7a8c5520fe59c51ba7e1cd741c97fbc4c90954f2a0af62503bda05f8d0e3"

/**** For Custom Code Testing*/
/* #define API_KEY     "223c91f16cec32abf64c6dea5ab3e894151e9c5b72a10a03814afd7e3b27173f"//"063a13ebe6fdc49fa2e5dce3545e082eff204ccd73000b85d1215f0e1e37ba66"
   #define SECRET_KEY  "622dd65d3d7afd03f07cf70d9a35b189754959d7366cbcf036c6704d7cf60001"//"6f576e30fba0f9f0d4857e66e23a720ed2b316ef38aedf4fd9162521c422b172"
*/

 extern const time_t sec_per_day;


USING_NS_CC;
class TestHome : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestHome);
};
#endif /* defined(__App42Cocos2dX3_0Sample__TestHome__) */
