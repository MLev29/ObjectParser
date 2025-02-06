#pragma once
#include "LibMath/vector/Vector3.h"
#include "LibMath/vector/Vector2.h"

#include "tools/MemoryCheck.h"

namespace objParser
{
	struct Vertex
	{
		Vertex(math::Vector3<float> const& position, math::Vector3<float> const& normal, math::Vector2<int> const& texCoord)
			: m_position(position), m_normal(normal), m_texCoord(texCoord)
		{
		}

		Vertex(math::Vector3<float> const& position, math::Vector3<float> const& normal)
			: m_position(position), m_normal(normal)
		{
			m_texCoord = math::Vector2(0);
		}

		Vertex(math::Vector3<float> const& position, math::Vector2<int> const& texCoord)
			: m_position(position), m_texCoord(texCoord)
		{
			m_normal = math::Vector3(0.0f);
		}

		math::Vector3<float>	m_position;
		math::Vector3<float>	m_normal;
		math::Vector2<int>		m_texCoord;
	};
}