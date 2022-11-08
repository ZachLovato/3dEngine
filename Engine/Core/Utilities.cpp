#include "Utilities.h" 
#include <algorithm> 

namespace wrap
{
	std::string ToLower(const std::string& str)
	{
		std::string lower = str;
		// convert string characters to lower case 
		for (size_t i = 0; i < lower.size(); i++)
		{
			lower[i] = std::tolower(lower[i]);
		}

		return lower;
	}

	std::string ToUpper(const std::string& str)
	{
		std::string upper = str;
		// convert string characters to upper case 
		for (size_t i = 0; i < upper.size(); i++)
		{
			upper[i] = std::toupper(upper[i]);
		}

		return upper;
	}

	bool CompareIgnoreCase(const std::string& str1, const std::string& str2)
	{
		// if string lengths don't match return false 
		// returns false if string characters aren't equal 

		if (str1.length() != str2.length()) return false;
		
		
		return std::equal(str1.begin(), str1.end(), str2.begin(), str2.end(), [](char c1, char c2)
		{
			return (std::tolower(c1) == std::tolower(c2));
		});
	}
}