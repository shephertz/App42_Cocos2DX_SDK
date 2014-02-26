//
//  Exceptions.h
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 20/02/14.
//
//

#ifndef App42CPPSDK_Exceptions_h
#define App42CPPSDK_Exceptions_h

//#include "Signing.h"
#include "App42Exception.h"
using namespace std;

namespace Util
{
    string removeSpaces(string input)
    {
        input.erase(std::remove(input.begin(),input.end(),' '),input.end());
        return input;
    }
    
    static void throwExceptionIfStringNullOrBlank(string obj, string name)
    {
		if(obj.c_str()==NULL)
        {
			throw new App42Exception(name + ": parameter can not be null ",100,200);
		}
        string temp = removeSpaces(obj);
		int len = temp.length();
        if(len==0)
        {
            throw new App42Exception(name + ": parameter can not be blank ",201,401);
        }
	}
    
}

#endif
