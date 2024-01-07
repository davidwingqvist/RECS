#include "recs_pch.h"
#include "recs_state_handler.h"
#include "recs_base.h"

const std::string FILEPATH = "Options/recs/";

namespace recs
{
	recs_state_handler::recs_state_handler(recs_registry* registryRef)
		:m_registry(registryRef)
	{

	}
	void recs_state_handler::SaveAllEntitiesToFile()
	{
		std::ofstream outfile(FILEPATH + "entities.txt");

		outfile << "--Entities--\n%" << std::endl;

		for (int i = 0; i < m_registry->GetEntities().size(); i++)
		{
			outfile << m_registry->GetEntities()[i] << std::endl;
		}

		outfile << "#" << "\nEnd Of File";

		outfile.close();
	}
	void recs_state_handler::SaveAllEntityLinksToFile()
	{

	}
}
