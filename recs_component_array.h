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

		T* m_components;
		size_t m_size = DEFAULT_MAX_ENTITIES;

	public:

		recs_component_array()
		{
			m_components = new T[m_size];
		}

		recs_component_array(const size_t& size)
		{
			m_size = size;
			m_components = new T[m_size];
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
			return m_components[entity];
		}


		// Inherited via recs_component_array_interface
		virtual void RemoveEntity(const Entity& entity) override
		{
			m_components[entity] = {};
		}

	};
}