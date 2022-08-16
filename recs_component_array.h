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
		std::queue<size_t> m_availableComponents;
		std::vector<EntityLink> m_activeComponents;

	public:

		recs_component_array()
		{
			m_components = new T[m_size];
			for (size_t i = 0; i < m_size; i++)
			{
				m_availableComponents.push(i);
			}
			m_activeComponents.reserve(m_size);
		}

		recs_component_array(const size_t& size)
		{
			m_size = size;
			m_components = new T[m_size];
			for (size_t i = 0; i < m_size; i++)
			{
				m_availableComponents.push(i);
			}
			m_activeComponents.reserve(m_size);
		}

		void LinkComponentToEntity(const Entity& entity)
		{
			const size_t pos = m_availableComponents.front();
			m_availableComponents.pop();

			EntityLink newLink = { entity, pos };
			m_activeComponents.push_back(newLink);
		}

		const size_t& GetSize() const
		{
			return m_size;
		}

		T& GetArray()
		{
			return *m_components;
		}

		std::vector<Entity, size_t>& GetRegisteredComponents()
		{
			return m_activeComponents;
		}

		// Inherited via recs_component_array_interface
		virtual void RemoveEntity(const Entity& entity) override
		{
			m_components[entity] = {};
		}

	};
}