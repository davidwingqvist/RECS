#pragma once
#include <queue>
#include "recs_pch.h"
#include "recs_component_registry.h"
#include "recs_component_array.h"

namespace recs
{
	/*
		A registry that holds each available entities.
		This is the base class of the ECS system.
		Usually only one instance of this object should be present.
		Take a look at the functions present to get familiarized with the system.
	*/
	class recs_registry
	{
	private:

		std::queue<recs::Entity> m_availableEntities;
		std::vector<Entity> m_activeEntities;
		recs_component_registry m_componentRegistry;
		size_t m_size = DEFAULT_MAX_ENTITIES;

	public:

		// Creates a registry, allocated assigned(size) amount of entities.
		recs_registry(const size_t& size = DEFAULT_MAX_ENTITIES);

		// Generates an entity and outputs it. Another copy is stored inside.
		Entity CreateEntity();

		// Connect a component to an entitiy.
		template<typename T>
		void AddComponent(const Entity& entity);

		// Get specific component from an entity. Return nullptr if it doesn't exist.
		template<typename T>
		T* GetComponent(const Entity& entity);

		// Destroy an entity and erase all the components from it.
		void DestroyEntity(const Entity& entity);

		// Register component with DEFAULT_MAX_ENTITIES size.
		template<typename T>
		void RegisterComponent(const T& component);

		// Register component with own defined amount size.
		template<typename T>
		void RegisterComponent(const T& component, const size_t& size);

		// Loops through each entity that has input component.
		template<typename T, typename F>
		void ForEach(F func);
	};

	template<typename T>
	inline void recs_registry::AddComponent(const Entity& entity)
	{
		m_componentRegistry.AddComponentToEntity<T>(entity);
	}

	template<typename T>
	inline T* recs_registry::GetComponent(const Entity& entity)
	{
		T* compArray = m_componentRegistry.GetComponentArray<T>();
		if (compArray == nullptr)
			return nullptr;

		std::vector<EntityLink>& linker = m_componentRegistry.GetEntityLinks<T>();

		for (auto& entityLink : linker)
		{
			if (entityLink.entity == entity)
				return &compArray[entityLink.pos];
		}

		return nullptr;
	}

	template<typename T>
	inline void recs_registry::RegisterComponent(const T& component)
	{
		m_componentRegistry.RegisterNewComponent(component, m_size);
	}

	template<typename T>
	inline void recs_registry::RegisterComponent(const T& component, const size_t& size)
	{
		// Not allowed to have more components than entities. Shrinking to m_size.
		if (m_size < size)
		{
			m_componentRegistry.RegisterNewComponent(component, m_size);
			return;
		}

		m_componentRegistry.RegisterNewComponent(component, size);
	}

	template<typename T, typename F>
	inline void recs_registry::ForEach(F func)
	{
		std::vector<EntityLink>& linker = m_componentRegistry.GetEntityLinks<T>();
		T* compArray = m_componentRegistry.GetComponentArray<T>();

		for (auto& entity : linker)
		{
			func(entity.entity, compArray[entity.pos]);
		}
	}
}