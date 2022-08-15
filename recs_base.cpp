#include "recs_pch.h"
#include "recs_base.h"

recs::ecs_registry::ecs_registry()
{
	for (Entity i = 0; i < DEFAULT_MAX_ENTITIES; i++)
		m_availableEntities.push(i);
}

recs::Entity recs::ecs_registry::CreateEntity()
{
	const Entity entity = m_availableEntities.front();
	m_activeEntities.push_back(entity);
	m_availableEntities.pop();

	return entity;
}

void recs::ecs_registry::DestroyEntity(const Entity& entity)
{

}
