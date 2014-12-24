#ifndef __URLENCODE_H__
#define __URLENCODE_H__

#include <iostream>
#include <string>
namespace App42
{
	std::string char2hex(char dec);
	std::string urlencode(const std::string &c);
	std::string url_encode(const std::string &c);
}//namespace App42
#endif // __URLENCODE_H__