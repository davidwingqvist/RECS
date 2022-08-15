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

		std::array<T, DEFAULT_MAX_ENTITIES> m_components{};

	public:

		recs_component_array() = default;

		std::array<T, DEFAULT_MAX_ENTITIES>& GetArray()
		{
			return m_components;
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