#include "recs_pch.h"
#include "recs_state_handler.h"
#include "recs_base.h"

namespace recs
{
	const std::string DEFAULT_STATE_FOLDER = "Options/recs/entities.txt";

	recs_state_handler::recs_state_handler(recs_registry* registryRef, recs_component_registry* compRegRef)
		:m_registry(registryRef), m_compReg(compRegRef)
	{
		m_fileFolderPath = DEFAULT_STATE_FOLDER;
	}

	void recs_state_handler::SaveData()
	{
		for (auto& data : m_dataTypeReg)
		{
			char* buffer = new char[data.second.first];
			void* ptr = m_compReg->GetComponentArray(data.first);
			std::string path = DEFAULT_STATE_FOLDER /*+ std::to_string(data.first) + ".txt"*/;
			std::ofstream stream(path);
			for (int i = 0; i < m_registry->GetMaxSize(); i++)
			{
				memcpy(buffer, data.second.second, data.second.first);
				stream << buffer << ' ';
			}
			stream.close();
			delete[] buffer;
		}
	}

	void recs_state_handler::LoadData()
	{

	}
}
