#pragma once
#include <queue>
#include "recs_pch.h"
#include "recs_component_registry.h"
#include "recs_component_array.h"
#include "recs_event_handler.h"

namespace recs
{
	template<typename T>
	class recs_entity_handle;

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

		/*
			Storage of all different types of events.
		*/
		std::unordered_map<size_t, std::shared_ptr<recs_event_handler_interface>> m_eventHandler;

		size_t m_size = DEFAULT_MAX_ENTITIES;

		template<typename T>
		recs_event_handler<T>* GetEventHandler()
		{
			const size_t type = typeid(T).hash_code();

			// Create event handler if not already existing.
			if (m_eventHandler.find(type) == m_eventHandler.end())
				m_eventHandler.insert({ type, std::make_shared<recs_event_handler<T>>() });

			return dynamic_cast<recs_event_handler<T>*>(m_eventHandler.at(type).get());
		}

		template<typename T>
		const std::vector<EntityLink>& GetLink(const T&& type)
		{
			return m_componentRegistry.GetEntityLinks<T>();
		}

		template<typename T>
		T* GetComponentFromVoidPointer(const T& type, const size_t& pos)
		{
			return type[pos];
		}

	public:

		// Creates a registry, allocated assigned(size) amount of entities.
		recs_registry(const size_t& size = DEFAULT_MAX_ENTITIES);

		~recs_registry();

		// Generates an entity and outputs it. Another copy is stored inside.
		Entity CreateEntity();

		/*
			Add a component to an entity, outputs a pointer to the newely created component.
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


		// Register an event that can be called with the RunEvent() function.
		template<typename T, T eventType>
		void RegisterEvent(const std::function<void()>& func);


		// Run a specific event linked to the template and template object.
		template<typename T, T eventType>
		void RunEvent();


		/*
			Register a function that will execute each time a component is created.
		*/
		template<typename T>
		void RegisterOnCreate(std::function<void(const Entity&, T&)> func);


		/*
			Register a function that will execute each time Update() is called.
		*/
		template<typename T>
		void RegisterOnUpdate(std::function<void(const Entity&, T&)> func);


		/*
			Register a function that will execute each time the entity or component is destroyed.
		*/
		template<typename T>
		void RegisterOnDestroy(std::function<void(const Entity&, T&)> func);

		// Get a view of a specific component.
		template<typename T>
		recs_entity_handle<T>&& GetView() noexcept
		{
			auto& links = m_componentRegistry.GetEntityLinks<T>();
			auto arrays = m_componentRegistry.GetComponentArray<T>();

			recs_entity_handle<T> view(links, arrays);

			return std::move(view);
		}

		//// Get a group of specific components.
		//template<typename... Args>
		//recs_entity_group<Args...>&& GetGroup()
		//{
		//	auto& links = m_componentRegistry.GetEntityLinks<Args...>();
		//	auto arrays = m_componentRegistry.GetComponentArray<Args...>();

		//	recs_entity_group<Args...> group(links, arrays);
		//	return std::move(group);
		//}


		/*
		Call this function to initiate an update call to each component with 
			a valid update function.
		*/
		void Update();

		recs_component_registry& GetComponentRegistry()
		{
			return m_componentRegistry;
		}
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
		if (compArray == Null_Entity)
			return Null_Entity;

		std::vector<EntityLink>& linker = m_componentRegistry.GetEntityLinks<T>();

		for (auto& entityLink : linker)
		{
			if (entityLink.entity == entity)
				return &compArray[entityLink.pos];
		}

		return Null_Entity;
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

	template<typename T, T eventType>
	inline void recs_registry::RegisterEvent(const std::function<void()>& func)
	{
		this->GetEventHandler<T>()->RegisterEvent<T>(eventType, func);
	}

	template<typename T, T eventType>
	inline void recs_registry::RunEvent()
	{
		this->GetEventHandler<T>()->RunEvent<T, eventType>();
	}
}

/*

	Wrappers that are used for recs_registry.

*/
namespace recs
{
	template<typename T>
	struct HandleLink
	{
		const EntityLink& link;
		T& component;

		HandleLink(const EntityLink& linker, T& comp)
			:link(linker), component(comp)
		{

		}
	};

	/*
		This is a handle that lists all entities linked to a specific component.
	*/

	template<typename T>
	class recs_entity_handle
	{
	protected:

		const std::vector<EntityLink>& m_linker;
		T* m_componentArray = nullptr;
		size_t m_pos = 0;

	public:

		recs_entity_handle(const std::vector<EntityLink>& linker, void* compArray)
			: m_linker(linker), m_componentArray((T*)compArray)
		{
			//m_componentArray = compArray;
			m_pos = 0;
		}

		recs_entity_handle(recs::recs_registry* registry)
			: m_linker(registry->GetComponentRegistry().GetEntityLinks<T>()), m_componentArray(registry->GetComponentRegistry().GetComponentArray<T>())
		{
			m_pos = 0;
		}

		/*
		* The first argument should be 'const Entity& entity'
			loop through each component and execute the function.
			Check the other overloaded functions.
		*/
		void ForEach(const std::function<void(const Entity&, T&)>&& func);

		// loop through each component and execute the function.
		void ForEach(const std::function<void(T&)>&& func);

		/*
			Returns the next value in the string of components.
		*/
		HandleLink<T>&& Next() noexcept
		{
			HandleLink<T> next(m_linker[m_pos], m_componentArray[m_linker[m_pos].pos]);

			if (m_pos > m_linker.size())
				m_pos = 0;
			else
				m_pos += 1;

			return std::move(next);
		}

		/*
			Reset the Next value to 0.
		*/
		void ResetNext()
		{
			m_pos = 0;
		}

		/*
			Reset the Next value with specific position value.
		*/
		void ResetNext(const size_t&& p_value)
		{
			m_pos = p_value;
		}

		virtual const size_t& GetSize() const
		{
			return m_linker.size();
		}
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

	template<class... views>
	class recs_entity_group : public recs_entity_handle<views>...
	{
	private:

		std::tuple<views...> m_views;

	public:

		recs_entity_group(recs::recs_registry* registry)
			:recs_entity_handle<views>(registry)...
		{
			std::tuple<views...> view;
			m_views = std::move(view);
		}
	};
}