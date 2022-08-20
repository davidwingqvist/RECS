#pragma once
#include <utility>
#include <functional>

namespace recs
{
	/*
		Turn a string into a hashed integer.
	*/
	const int hash_string(const char* str)
	{
		std::hash<std::string> hasher;
		const int hashed = hasher(str);
		return hashed;
	}
}