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
		T* AddComponentToEntity(const Entity& entity);

		template<typename T>
		void RemoveComponentFromEntity(const Entity& entity);

		template<typename T>
		const std::vector<EntityLink>& GetEntityLinks();

		void UpdateAllComponents();

		template<typename T>
		T* GetComponentArray();

		void EntityRemoved(const Entity& entity);

		template<typename T>
		void AssignOnCreateToComponent(std::function<void(const Entity&, T&)> func);

		template<typename T>
		void AssignOnUpdateToComponent(std::function<void(const Entity&, T&)> func);

		template<typename T>
		void AssignOnDestroyToComponent(std::function<void(const Entity&, T&)> func);
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
	inline T* recs_component_registry::AddComponentToEntity(const Entity& entity)
	{
		size_t type = typeid(T).hash_code();

		return dynamic_cast<recs_component_array<T>*>(m_componentArrays.at(type).get())->LinkComponentToEntity<T>(entity);
	}

	template<typename T>
	inline void recs_component_registry::RemoveComponentFromEntity(const Entity& entity)
	{
		size_t type = typeid(T).hash_code();

		dynamic_cast<recs_component_array<T>*>(m_componentArrays.at(type).get())->RemoveEntity(entity);
	}

	template<typename T>
	inline const std::vector<EntityLink>& recs_component_registry::GetEntityLinks()
	{
		size_t type = typeid(T).hash_code();

		return dynamic_cast<recs_component_array<T>*>(m_componentArrays.at(type).get())->GetRegisteredComponents();
	}

	template<typename T>
	inline T* recs_component_registry::GetComponentArray()
	{
		size_t type = typeid(T).hash_code();

		if (m_componentArrays.find(type) == m_componentArrays.end())
			return nullptr;

		return dynamic_cast<recs_component_array<T>*>(m_componentArrays.at(type).get())->GetArray();
	}

	template<typename T>
	inline void recs_component_registry::AssignOnCreateToComponent(std::function<void(const Entity&, T&)> func)
	{
		size_t type = typeid(T).hash_code();

		if (m_componentArrays.find(type) == m_componentArrays.end())
			return;

		dynamic_cast<recs_component_array<T>*>(m_componentArrays.at(type).get())->AssignOnCreate(func);
	}

	template<typename T>
	inline void recs_component_registry::AssignOnUpdateToComponent(std::function<void(const Entity&, T&)> func)
	{
		size_t type = typeid(T).hash_code();

		if (m_componentArrays.find(type) == m_componentArrays.end())
			return;

		dynamic_cast<recs_component_array<T>*>(m_componentArrays.at(type).get())->AssignOnUpdate(func);
	}

	template<typename T>
	inline void recs_component_registry::AssignOnDestroyToComponent(std::function<void(const Entity&, T&)> func)
	{
		size_t type = typeid(T).hash_code();

		if (m_componentArrays.find(type) == m_componentArrays.end())
			return;

		dynamic_cast<recs_component_array<T>*>(m_componentArrays.at(type).get())->AssignOnDestroy(func);
	}
}