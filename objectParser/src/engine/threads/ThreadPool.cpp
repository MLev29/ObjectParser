#include "ThreadPool.h"

std::mutex engine::ThreadPool::m_mutex;
engine::ThreadPool* engine::ThreadPool::m_instance = nullptr;

engine::ThreadPool* engine::ThreadPool::GetInstance(void)
{
	if (!m_instance)
	{
		std::unique_lock<std::mutex> lock(m_mutex);

		if (!m_instance)
			m_instance = new ThreadPool();
	}

	return m_instance;
}

int engine::ThreadPool::InitThreads(void)
{
	const int threadCount = std::thread::hardware_concurrency();

	for (int i = 0; i < threadCount; ++i)
	{

	}

	return 0;
}

int engine::ThreadPool::CloseThreadPool(void)
{
	return 0;
}

