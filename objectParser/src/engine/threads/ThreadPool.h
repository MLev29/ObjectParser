#pragma once

#include <mutex>
#include <thread>
#include <queue>
#include <vector>

namespace engine
{
	class ThreadPool
	{
	public:
		static ThreadPool* GetInstance(void);

		int InitThreads(void);
		int CloseThreadPool(void);

	private:
		ThreadPool(void) = default;
		ThreadPool(ThreadPool const& threadPool) = delete;
		ThreadPool& operator=(ThreadPool const& threadPool) = delete;

		static std::mutex			m_mutex;
		static ThreadPool*			m_instance;
		std::vector<std::thread>	m_threads;
	};
}