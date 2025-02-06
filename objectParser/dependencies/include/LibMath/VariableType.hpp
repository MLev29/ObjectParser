#pragma once

#include <type_traits>

namespace math
{
	namespace math_type
	{
		template<typename T>
		concept NumericType = std::is_arithmetic<T>::value;

		template<typename T>
		concept UnsignedType = std::is_unsigned<T>::value;


	}
}