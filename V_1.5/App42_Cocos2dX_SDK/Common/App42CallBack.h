//
//  App42CallBack.h
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 27/03/14.
//
//

#ifndef App42Cocos2dXSDK_3_0Beta2_Sample_App42CallBack_h
#define App42Cocos2dXSDK_3_0Beta2_Sample_App42CallBack_h

#include <iostream>
#include <functional>

namespace App42
{
	class App42CallBack
	{

	};


	/***
	 * Callback Macro
	 **/

	typedef std::function<void(void*)> SEL_App42CallFuncND;
}
#endif
