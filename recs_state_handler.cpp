#include "recs_pch.h"
#include "recs_state_handler.h"
#include "recs_base.h"

namespace recs
{
	recs_state_handler::recs_state_handler(recs_registry* registryRef, recs_component_registry* compRegRef)
		:m_registry(registryRef), m_compReg(compRegRef)
	{
		m_fileFolderPath = DEFAULT_STATE_FOLDER;
	}

	void recs_state_handler::SaveData()
	{
		for (auto& data : m_dataTypeReg)
		{
			char* buffer = new char(data.second.first);
		}
	}

	void recs_state_handler::LoadData()
	{

	}
}
