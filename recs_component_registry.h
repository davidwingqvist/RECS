#pragma once
#include "recs_pch.h"
#include "recs_component_array.h"

namespace recs
{
	class recs_component_registry
	{
	private:

		std::unordered_map<size_t, std::shared_ptr<recs_component_array_interface>> m_componentArrays{};

	public:
		 
		recs_component_registry() = default;

		template<typename T>
		void RegisterNewComponent(const T& component);

		template<typename T>
		void RegisterNewComponent(const T& component, const size_t& size);

		template<typename T> 
		void AddComponentToEntity(const Entity& entity);

		template<typename T>
		std::vector<EntityLink>& GetEntityLinks();

		template<typename T>
		T* GetComponentArray();

		void EntityRemoved(const Entity& entity);
	};

	template<typename T>
	inline void recs_component_registry::RegisterNewComponent(const T& component)
	{
		size_t type = typeid(T).hash_code();

		// Component is already registered
		if (m_componentArrays.find(type) != m_componentArrays.end())
			return;

		m_componentArrays.insert({ type, std::make_shared<recs_component_array<T>>() });
	}

	template<typename T>
	inline void recs_component_registry::RegisterNewComponent(const T& component, const size_t& size)
	{
		size_t type = typeid(T).hash_code();

		// Component is already registered
		if (m_componentArrays.find(type) != m_componentArrays.end())
			return;

		m_componentArrays.insert({ type, std::make_shared<recs_component_array<T>>(size) });
	}

	template<typename T>
	inline void recs_component_registry::AddComponentToEntity(const Entity& entity)
	{
		size_t type = typeid(T).hash_code();

		dynamic_cast<recs_component_array<T>*>(m_componentArrays.at(type).get())->LinkComponentToEntity(entity);
	}

	template<typename T>
	inline std::vector<EntityLink>& recs_component_registry::GetEntityLinks()
	{
		size_t type = typeid(T).hash_code();

		return dynamic_cast<recs_component_array<T>*>(m_componentArrays.at(type).get())->GetRegisteredComponents();
	}

	template<typename T>
	inline T* recs_component_registry::GetComponentArray()
	{
		size_t type = typeid(T).hash_code();

		return dynamic_cast<recs_component_array<T>*>(m_componentArrays.at(type).get())->GetArray();
	}
}