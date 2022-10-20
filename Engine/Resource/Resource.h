#pragma once
#include <string>

namespace wrap
{
	class Resource
	{
	public:
		virtual bool Create(std::string name, ...) = 0;
	};
}
