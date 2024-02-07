#include "recs_pch.h"
#include "recs_state_handler.h"
#include "recs_base.h"

struct Test2
{
	int i = 0;
};

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
			char* buffer = new char[data.second.first + 1];
			buffer[data.second.first] = '\0'; // Add an end incase of string.
			char* ptr = (char*)m_compReg->GetComponentArray(data.first);
			std::string path = DEFAULT_STATE_FOLDER /*+ std::to_string(data.first) + ".txt"*/;
			std::ofstream stream(path);
			for (int i = 0; i < m_registry->GetMaxSize(); i++)
			{
				memcpy(buffer, (ptr + (i * data.second.first)), data.second.first);
				stream.write(buffer, data.second.first);
				//stream << buffer << ' ';
			}
			stream.close();
			delete[] buffer;
		}
	}

	void recs_state_handler::LoadData()
	{
		for (auto& data : m_dataTypeReg)
		{
			char* buffer = new char[data.second.first];
			std::string path = DEFAULT_STATE_FOLDER /*+ std::to_string(data.first) + ".txt"*/;
			std::ifstream stream(path);
			for (int i = 0; i < m_registry->GetMaxSize(); i++)
			{
				stream.read(buffer, data.second.first);
				Test2 t;
				memcpy(&t, buffer, data.second.first);
				std::cout << t.i << "\n";
			}
			stream.close();
			delete[] buffer;
		}
	}
}
