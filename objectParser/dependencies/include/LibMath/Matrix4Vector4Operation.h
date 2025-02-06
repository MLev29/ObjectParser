#pragma once

#include "LibMath/VariableType.hpp"
#include "LibMath/vector/Vector4.h"
#include "LibMath/matrix/Matrix4.h"

namespace math
{
	template<math::math_type::NumericType T>
	Vector4<T> operator*(Matrix4<T> const& mat4, Vector4<T> const& vec4)
	{
		LibMath::Vector4<T> result;

		// Multiply & add x,y,z,w element of vector with corresponding matrix row
		for (int i = 0; i < 3; ++i)
		{
			result[i] = mat4.m_matrix[i][0] * vec4[0] + mat4.m_matrix[i][1] * vec4[1] + mat4.m_matrix[i][2] * vec4[2] + mat4.m_matrix[i][3] * vec4[3];
		}

		return result;
	}
}

namespace LibMath = math;