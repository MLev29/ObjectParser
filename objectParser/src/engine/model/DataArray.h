#pragma once
#include <stdlib.h>
#include "tools/MemoryCheck.h"

/*
*	STL style vector class implementation for large sets of 
*	consecutive data. Used for faster 3D model parsing.
*/

static int g_memoryBlockSize = 500;

template<typename T>
class DataArray
{
public:
	DataArray(void);
	~DataArray(void) = default;

	void Append(T const& data);
	void Clear(void);
	int Size(void) const noexcept;

	T* m_data;
private:
	int m_size;
	int m_capacity;
};

template<typename T>
inline DataArray<T>::DataArray(void)
	: m_size(0), m_capacity(0)
{
	m_data = nullptr;
}

template<typename T>
inline void DataArray<T>::Append(T const& data)
{
	++m_size;

	if (m_size > m_capacity)
	{
		m_capacity += g_memoryBlockSize;
		m_data = (T*) realloc(m_data, sizeof(T) * m_capacity);
	}

	m_data[m_size - 1] = data;
}

template<typename T>
inline void DataArray<T>::Clear(void)
{
	if (m_data)
		free(m_data);

	m_data = nullptr;
	m_capacity = 0;
	m_size = 0;
}

template<typename T>
inline int DataArray<T>::Size(void) const noexcept
{
	return m_size;
}
