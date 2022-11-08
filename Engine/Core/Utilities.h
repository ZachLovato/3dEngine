#pragma once
#include <string>

namespace wrap
{
	std::string ToLower(const std::string& str);
	std::string ToUpper(const std::string& str);
	bool CompareIgnoreCase(const std::string& str1, const std::string& str2);
}