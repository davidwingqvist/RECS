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

		/*
			Add a component to an entity.
			This will also register a component if it doesn't already exist.
		*/
		template<typename T>
		T* AddComponent(const Entity& entity);

		// Get specific component from an entity. Return nullptr if it doesn't exist.
		template<typename T>
		T* GetComponent(const Entity& entity);

		// Remove specific component from an entity.
		template<typename T>
		void RemoveComponent(const Entity& entity);

		// Destroy an entity and erase all the components from it.
		void DestroyEntity(const Entity& entity);

		// Register component with DEFAULT_MAX_ENTITIES size.
		template<typename T>
		void RegisterComponent(const T& component);

		// Register component with own defined amount size.
		template<typename T>
		void RegisterComponent(const T& component, const size_t& size);

		// Register a component with DEFAULT_MAX_ENTITIES size, without triggering any constructors.
		template<typename T>
		void RegisterComponent();

		// Register a component with own defined size, without triggering any constructors.
		template<typename T>
		void RegisterComponent(const size_t& size);

		// Register a function that will execute each time a component is created.
		template<typename T>
		void RegisterOnCreate(std::function<void(const Entity&, T&)> func);

		// Register a function that will execute each time Update() is called.
		template<typename T>
		void RegisterOnUpdate(std::function<void(const Entity&, T&)> func);

		// Register a function that will execute each time the entity or component is destroyed.
		template<typename T>
		void RegisterOnDestroy(std::function<void(const Entity&, T&)> func);

		/*
		Call this function to initiate an update call to each component with 
			a valid update function.
		*/
		void Update();

		/*
			Loops through each entity that has input component.
			Remember:
				The first parameter intake needs to be a (const Entity&),
				otherwise undefined behavior or fail to compile may happen.
		*/
		template<typename T, typename F>
		void ForEach(F func);
	};

	template<typename T>
	inline T* recs_registry::AddComponent(const Entity& entity)
	{
		return m_componentRegistry.AddComponentToEntity<T>(entity);
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
	inline void recs_registry::RemoveComponent(const Entity& entity)
	{
		m_componentRegistry.RemoveComponentFromEntity<T>(entity);
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

	template<typename T>
	inline void recs_registry::RegisterComponent()
	{
		m_componentRegistry.RegisterNewComponent<T>();
	}

	template<typename T>
	inline void recs_registry::RegisterComponent(const size_t& size)
	{
		m_componentRegistry.RegisterNewComponent<T>(size);
	}

	template<typename T>
	inline void recs_registry::RegisterOnCreate(std::function<void(const Entity&, T&)> func)
	{
		m_componentRegistry.AssignOnCreateToComponent<T>(func);
	}

	template<typename T>
	inline void recs_registry::RegisterOnUpdate(std::function<void(const Entity&, T&)> func)
	{
		m_componentRegistry.AssignOnUpdateToComponent(func);
	}

	template<typename T>
	inline void recs_registry::RegisterOnDestroy(std::function<void(const Entity&, T&)> func)
	{
		m_componentRegistry.AssignOnDestroyToComponent(func);
	}

	template<typename T, typename F>
	inline void recs_registry::ForEach(F func)
	{
		const std::vector<EntityLink>& linker = m_componentRegistry.GetEntityLinks<T>();
		T* compArray = m_componentRegistry.GetComponentArray<T>();

		for (auto& link : linker)
		{
			func(link.entity, compArray[link.pos]);
		}
	}
}