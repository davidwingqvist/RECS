#include "recs_pch.h"
#include "recs_thread.h"

namespace recs
{

	recs_thread_pool::recs_thread_pool()
	{
		m_threads = nullptr;
	}

	recs_thread_pool::~recs_thread_pool()
	{
		m_running = false;
		if (m_threads)
			delete[] m_threads;
	}

	void recs_thread_pool::Initialize(const size_t& numThreads)
	{
		m_threads = new recs_thread[numThreads];

		for (size_t i = 0; i < numThreads; i++)
		{
			recs_thread thread;
			thread.CreatePooled(this);
			m_threads[i] = std::move(thread);
		}
	}

	const bool& recs::recs_thread_pool::GetRunStatus()
	{
		return m_running;
	}

	void recs_thread::PoolMain()
	{
		m_status = RUNNING;
		while (m_pool->GetRunStatus())
		{

		}
		m_status = STOPPED;
	}

	recs_thread::~recs_thread()
	{

	}

	void Test()
	{

	}

	void recs_thread::CreatePooled(recs_thread_pool* control)
	{
		m_pool = control;
		m_thread = new std::thread([&] {this->PoolMain(); });
	}
}
