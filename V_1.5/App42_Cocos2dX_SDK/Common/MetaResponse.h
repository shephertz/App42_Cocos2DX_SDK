//
//  MetaResponse.h
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 25/02/14.
//
//

#ifndef __App42CPPSDK__MetaResponse__
#define __App42CPPSDK__MetaResponse__

#include <iostream>
#include "JSONDocument.h"
#include <vector>
using namespace std;
namespace App42
{
	class MetaResponse
	{
	public:
		std::vector<JSONDocument> getJsonDocList()
		{
			return jsonDocList;
		};
		void setJsonDocList(std::vector<JSONDocument> _jsonDocList)
		{
			jsonDocList = _jsonDocList;
		};

	protected:
		std::vector<JSONDocument> jsonDocList;
	private:

	};
}//namespace App42
#endif /* defined(__App42CPPSDK__MetaResponse__) */
