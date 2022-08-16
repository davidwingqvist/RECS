#pragma once
#include <queue>
#include "recs_pch.h"
#include "recs_component_registry.h"
#include "recs_component_array.h"

namespace recs
{
	class ecs_registry
	{
	private:

		std::queue<recs::Entity> m_availableEntities;
		std::vector<Entity> m_activeEntities;
		recs_component_registry m_componentRegistry;
		size_t m_size = DEFAULT_MAX_ENTITIES;

	public:

		// Creates a registry, allocated assigned(size) amount of entities.
		ecs_registry(const size_t& size = DEFAULT_MAX_ENTITIES);

		Entity CreateEntity();

		template<typename T>
		void AddComponent(const Entity& entity);

		void DestroyEntity(const Entity& entity);

		// Register component with DEFAULT_MAX_ENTITIES size.
		template<typename T>
		void RegisterComponent(const T& component);

		// Register component with own defined size.
		template<typename T>
		void RegisterComponent(const T& component, const size_t& size);

		template<typename T, typename F>
		void ForEach(F func);
	};

	template<typename T>
	inline void ecs_registry::AddComponent(const Entity& entity)
	{
		m_componentRegistry.AddComponentToEntity<T>(entity);
	}

	template<typename T>
	inline void ecs_registry::RegisterComponent(const T& component)
	{
		m_componentRegistry.RegisterNewComponent(component, m_size);
	}

	template<typename T>
	inline void ecs_registry::RegisterComponent(const T& component, const size_t& size)
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
	inline void ecs_registry::ForEach(F func)
	{
		std::vector<EntityLink>& linker = m_componentRegistry.GetEntityLinks<T>();
		T* compArray = m_componentRegistry.GetComponentArray<T>();

		for (auto& entity : linker)
		{
			func(entity.entity, compArray[entity.pos]);
		}
	}
}