// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"
#include <queue>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>
#include <functional>
#include <string>
#include <fstream>
#include <tuple>
#include <type_traits>
#include <cassert>


namespace recs
{
	using Entity = std::uint32_t;
	using Entity_Group = std::vector<Entity>;
	using Link = std::unordered_map<Entity, size_t>;
	using Null_Entity = nullptr_t;
	constexpr Entity DEFAULT_MAX_ENTITIES = 10;

	struct EntityLink
	{
		Entity entity;
		size_t pos;
	};

	struct HelloWriter
	{
		int hello = 0;
		double test = 0;
		double test2 = 0;
		double test3 = 0;
	};

	struct Test
	{
		int test = 0;
		double test2 = 0;
		double test3 = 0;
		double test4 = 0;
	};

	struct Test2
	{
		int test = 0;
		double test2 = 0;
		double test3 = 0;
		double test4 = 0;
	};
}

#endif //PCH_H
