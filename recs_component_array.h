#pragma once
#include "recs_pch.h"

namespace recs
{
	class recs_component_array_interface
	{
	public:
		virtual ~recs_component_array_interface() = default;
		virtual void RemoveEntity(const recs::Entity& entity) = 0;
	};

	template<typename T>
	class recs_component_array : public recs_component_array_interface
	{
	private:

		T m_failure;
		T* m_components;
		size_t m_size = DEFAULT_MAX_ENTITIES;
		std::unordered_map<Entity, T*> m_entityToComponent;
		std::queue<size_t> m_availableComponents;

	public:

		recs_component_array()
		{
			m_components = new T[m_size];
			for (size_t i = 0; i < m_size; i++)
			{
				m_availableComponents.push(i);
			}
		}

		recs_component_array(const size_t& size)
		{
			m_size = size;
			m_components = new T[m_size];
			for (size_t i = 0; i < m_size; i++)
			{
				m_availableComponents.push(i);
			}
		}

		void LinkComponentToEntity(const Entity& entity)
		{
			const size_t pos = m_availableComponents.front();
			m_availableComponents.pop();

			// Link entity to the pos in T array
			m_entityToComponent[entity] = &T[pos];
		}

		const size_t& GetSize() const
		{
			return m_size;
		}

		T& GetArray()
		{
			return *m_components;
		}

		T& GetComponent(const Entity& entity)
		{
			if (m_entityToComponent.find(entity) == m_entityToComponent.end())
				return m_failure;

			return *m_entityToComponent[entity];
		}


		// Inherited via recs_component_array_interface
		virtual void RemoveEntity(const Entity& entity) override
		{
			m_components[entity] = {};
		}

	};
}