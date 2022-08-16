#pragma once
#include "recs_pch.h"
#include <iostream>

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
		std::function<void(const Entity&, T&)> m_onCreateFunction;
		std::function<void(const Entity&, T&)> m_onDestroyFunction;
		std::function<void(const Entity&, T&)> m_onUpdateFunction;

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

		void AssignOnCreate(std::function<void(const Entity&, T&)> func)
		{
			m_onCreateFunction = func;
		}

		void AssignOnDestroy(std::function<void(const Entity&, T&)> func)
		{
			m_onDestroyFunction = func;
		}

		template<typename T>
		T* LinkComponentToEntity(const Entity& entity)
		{
			if (m_availableComponents.empty())
			{
				std::cout << "RECS [Warning!]: Tried to link entity: " << entity <<  " to a component array which was full!\n";
				return nullptr;
			}

			const size_t pos = m_availableComponents.front();
			m_availableComponents.pop();

			EntityLink newLink = { entity, pos };
			m_activeComponents.push_back(newLink);

			if (m_onCreateFunction)
				m_onCreateFunction(entity, m_components[pos]);

			return &m_components[pos];
		}

		void UpdateComponents()
		{
			if (!m_onUpdateFunction)
				return;

			for (auto& link : m_activeComponents)
			{
				m_onUpdateFunction(link.entity, m_components[link.pos]);
			}
		}

		const size_t& GetSize() const
		{
			return m_size;
		}

		T* GetArray()
		{
			return m_components;
		}

		const std::vector<EntityLink>& GetRegisteredComponents()
		{
			return m_activeComponents;
		}

		// Inherited via recs_component_array_interface
		virtual void RemoveEntity(const Entity& entity) override
		{
			for (size_t i = 0; i < m_activeComponents.size(); i++)
			{
				if (m_activeComponents[i].entity == entity)
				{
					if (m_onDestroyFunction)
						m_onDestroyFunction(entity, m_components[m_activeComponents[i].pos]);

					m_availableComponents.push(entity);
					m_activeComponents.erase(m_activeComponents.begin() + i);
					return;
				}
			}

			std::cout << "RECS [WARNING!]: Tried to remove a component from an entity that doesn't have said component.\n";
		}

	};
}