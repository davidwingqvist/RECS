#pragma once
#include "recs_component_array.h"

namespace recs
{
	/*
		This is a handle that lists all entities linked to a specific component.
	*/

	template<typename T>
	class recs_entity_handle
	{
	private:

		const std::vector<EntityLink>& m_linker;
		T* m_componentArray = nullptr;

	public:

		recs_entity_handle(const std::vector<EntityLink>& linker, T* compArray)
			: m_linker(linker), m_componentArray(compArray)
		{
			//m_componentArray = compArray;
		}

		void ForEach(const std::function<void(const Entity&, T&)>&& func);
		void ForEach(const std::function<void(T&)>&& func);

	};

	template<typename T>
	inline void recs_entity_handle<T>::ForEach(const std::function<void(const Entity&, T&)>&& func)
	{
		for (auto& link : m_linker)
			func(link.entity, m_componentArray[link.pos]);
	}

	template<typename T>
	inline void recs_entity_handle<T>::ForEach(const std::function<void(T&)>&& func)
	{
		for (auto& link : m_linker)
			func(m_componentArray[link.pos]);
	}
}