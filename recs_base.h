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

	public:

		ecs_registry();

		Entity CreateEntity();
		void DestroyEntity(const Entity& entity);

		template<typename T>
		void RegisterComponent(const T& component);

		template<typename T, typename F>
		void ForEach(F func);
	};

	template<typename T>
	inline void ecs_registry::RegisterComponent(const T& component)
	{
		m_componentRegistry.RegisterNewComponent(component);
	}

	template<typename T, typename F>
	inline void ecs_registry::ForEach(F func)
	{
		compArray<T>& compArr = this->m_componentRegistry.GetComponentArray<T>();

		for (auto& entity : this->m_activeEntities)
		{
			func(entity, compArr[entity]);
		}
	}
}