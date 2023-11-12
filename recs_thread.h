#pragma once
#include <thread>

namespace recs
{
	class recs_thread;

	enum recs_thread_status : size_t
	{
		INITIALIZING = 0,
		RUNNING = 1,
		STOPPED = 2,
		PAUSED = 3
	};

	/*
		This is a thread pool class that is recommended
		to use if continually creating and destroying threads is degrading performance.
	*/
	class recs_thread_pool
	{
	private:

		recs_thread* m_threads;
		bool m_running = false;

	public:

		recs_thread_pool();
		//recs_thread_pool(const size_t& numThreads = std::thread::hardware_concurrency() - 1);
		~recs_thread_pool();

		void Initialize(const size_t& numThreads = std::thread::hardware_concurrency() - 1);

		// Return the run status of pool system.
		const bool& GetRunStatus();

	};

	class recs_thread
	{
	private:

		std::thread* m_thread = nullptr;
		recs_thread_status m_status = INITIALIZING;
		recs_thread_pool* m_pool = nullptr;


	public:

		recs_thread() = default;
		~recs_thread();

		void CreatePooled(recs_thread_pool* control);

		void PoolMain();
	};
}