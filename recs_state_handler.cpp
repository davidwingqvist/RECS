#include "recs_pch.h"
#include "recs_state_handler.h"
#include "recs_base.h"
#include <sstream>

struct Test2
{
	int i = 0;
};

namespace recs
{
	const std::string DEFAULT_STATE_FOLDER = "Options/recs/";

	recs_state_handler::recs_state_handler(recs_registry* registryRef, recs_component_registry* compRegRef)
		:m_registry(registryRef), m_compReg(compRegRef)
	{
		m_fileFolderPath = DEFAULT_STATE_FOLDER;
	}

	void recs_state_handler::SetFolderPath(const std::string& path)
	{
		m_fileFolderPath = path;
	}

	bool recs_state_handler::SaveData()
	{
		/*
			Save Components
		*/
		for (auto& data : m_dataTypeReg)
		{
			std::string path = m_fileFolderPath + std::to_string(data.first) + ".txt";
			std::ofstream stream(path);

			// Couldn't open file, close.
			if (!stream.is_open())
			{
				return false;
			}

			char* buffer = new char[data.second.first];
			char* ptr = (char*)m_compReg->GetComponentArray(data.first);


			for (int i = 0; i < m_registry->GetMaxSize(); i++)
			{
				// Copy data from array to buffer.
				memcpy(buffer, (ptr + (i * data.second.first)), data.second.first);
				stream.write(buffer, data.second.first);
			}
			stream.close();
			delete[] buffer;
		}

		/*
			Save entities
		*/
		{
			std::string path = m_fileFolderPath + "entities.txt";
			std::ofstream stream(path);
			// Couldn't open file, close.
			if (!stream.is_open())
			{
				return false;
			}

			char* buffer = new char[sizeof Entity];
			char* size_buffer = new char[sizeof size_t];


			const Entity_Group& entgrp = m_registry->GetEntities();
			size_t size = entgrp.size();
			memcpy(size_buffer, &size, sizeof size_t);
			stream.write(size_buffer, sizeof size_t);


			delete[] size_buffer;
			for (int i = 0; i < entgrp.size(); i++)
			{
				stream << entgrp[i] << ' ';
			}
			stream.close();
			delete[] buffer;
		}

		return true;
	}

	bool recs_state_handler::LoadData()
	{
		/*
			Load Components
		*/
		for (auto& data : m_dataTypeReg)
		{
			std::string path = m_fileFolderPath + std::to_string(data.first) + ".txt";
			std::ifstream stream(path);

			// Couldn't open file, close.
			if (!stream.is_open())
			{
				return false;
			}

			char* buffer = new char[data.second.first + 1];
			buffer[data.second.first] = '\0'; // make terminate string.
			char* ptr = (char*)m_compReg->GetComponentArray(data.first);

			for (int i = 0; i < m_registry->GetMaxSize(); i++)
			{
				stream.read(buffer, data.second.first);
				// Copy data from buffer to array.
				memcpy(ptr + (i * data.second.first), buffer, data.second.first);
			}
			stream.close();
			delete[] buffer;
		}

		/*
			Load Entities
		*/
		{
			std::string path = m_fileFolderPath + "entities.txt";
			std::ifstream stream(path);

			// Couldn't open file, close.
			if (!stream.is_open())
			{
				return false;
			}

			char* buffer = new char[sizeof Entity];
			size_t size = 0;
			char* size_buffer = new char[sizeof size_t];
			stream.read(size_buffer, sizeof size_t);
			memcpy(&size, size_buffer, sizeof size_t);
			delete[] size_buffer;

			size_t read_size = sizeof Entity;
			for (int i = 0; i < size; i++)
			{
				Entity ent = 0;
				stream >> ent;
				m_registry->CreateEntity(ent);
			}
			stream.close();
			delete[] buffer;
		}

		return true;
	}
}
