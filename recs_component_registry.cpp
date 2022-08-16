#include "recs_pch.h"
#include "recs_component_registry.h"

void recs::recs_component_registry::EntityRemoved(const Entity& entity)
{
	for (auto& comp : m_componentArrays)
	{
		comp.second.get()->RemoveEntity(entity);
	}
}