#pragma once
#include "recs_component_array.h"

namespace recs
{
	/*
		This class holds a pointer towards an entity
		and a specific component array that said entity is connected to.
	*/
	template<typename T>
	class recs_comp_handle
	{
	private:

		Entity* m_entityPointer = nullptr;
		recs_component_array<T>* m_componentArray = nullptr;

	public:

		recs_comp_handle(Entity* entPointer, recs_component_array<T>* compPointer);
		~recs_comp_handle() = default;

		// Returns a pointer towards the pointer of the entity.
		Entity*& GetEntityPointer();
		Entity& GetEntityRaw();

		// Returns a pointer towards the pointer of the component array.
		recs_component_array<T>*& GetComponentArrayPointer();
		recs_component_array<T>& GetComponentArrayRaw();

	};

	template<typename T>
	inline recs_comp_handle<T>::recs_comp_handle(Entity* entPointer, recs_component_array<T>* compPointer)
	{
		m_entityPointer = entPointer;
		m_componentArray = compPointer;
	}

	template<typename T>
	inline Entity*& recs_comp_handle<T>::GetEntityPointer()
	{
		return m_entityPointer;
	}

	template<typename T>
	inline Entity& recs_comp_handle<T>::GetEntityRaw()
	{
		return *m_entityPointer;
	}

	template<typename T>
	inline recs_component_array<T>*& recs_comp_handle<T>::GetComponentArrayPointer()
	{
		return m_componentArray;
	}
	template<typename T>
	inline recs_component_array<T>& recs_comp_handle<T>::GetComponentArrayRaw()
	{
		return *m_componentArray;
	}

	/*
		This is a handle that lists all entities linked to a specific component.
	*/

	template<typename T>
	class recs_entity_handle
	{
	private:

		std::vector<EntityLink>* m_linker = nullptr;
		T* m_componentArray = nullptr;

	public:

		recs_entity_handle(const std::vector<EntityLink>& linker)
		{
			m_linker = linker;
		}

	};
}
