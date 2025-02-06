#pragma once

#include "LibMath/VariableType.hpp"

#include <cmath>
#include <limits>
#include <exception>
#include <assert.h>

#ifdef _MSC_VER
	// Prevent warning due to loss of data from implicit type conversion
	#pragma warning(disable: 4244) 
#endif

/*
*	Arithmetic Operations
*	Absolute					DONE
*	Almost Equal (epsilon)		DONE
*	Min (2 numbers & array)		DONE
*	Max (2 numbers & array)		DONE
*	Clamp						DONE
*	Wrap						DONE
*	Floor						DONE
*	Ceiling						DONE
*	Power						DONE
*	Sqrt						
*	Root						
*	Factorial					DONE
*	Epsilon						DONE
*/

namespace math
{
	template<math::math_type::NumericType T>
	inline constexpr T Abs(T val) noexcept;

	template<math::math_type::NumericType T>
	bool AlmostEqual(T val1, T val2);

	template<math::math_type::NumericType T>
	bool AlmostEqual(T val1, T val2, T epsilon);

	template<math_type::NumericType T>
	inline constexpr T Min(T const& val1, T const& val2) noexcept;
	
	template<math_type::NumericType T>
	inline constexpr T Max(T const& val1, T const& val2) noexcept;
	
	template<math_type::NumericType T>
	inline constexpr T Clamp(T const& val, T const& min, T const& max);

	template<math_type::NumericType T>
	constexpr T Wrap(T const& val, T const& min, T const& max);

	template<math::math_type::NumericType T>
	inline constexpr int Floor(T const& val) noexcept;

	template<math::math_type::NumericType T>
	inline constexpr int Ceiling(T const& val) noexcept;

	template<math::math_type::NumericType T>
	inline constexpr T Power(T const& val, unsigned int const power);

	template<math::math_type::UnsignedType T>
	inline constexpr T Sqrt(T const& val) noexcept;

	template<math::math_type::UnsignedType T, math::math_type::NumericType Tindex>
	inline constexpr T Root(T const& val, Tindex const& index) noexcept;

	template<math::math_type::NumericType T>
	inline constexpr T Factorial(T const& val);
}

template<math::math_type::NumericType T>
constexpr T math::Abs(T const val) noexcept
{
	return (val < 0) ? -val : val;
}

template<math::math_type::NumericType T>
bool math::AlmostEqual(T val1, T val2)
{
	// Calculate difference
	T delta = val2 - val1;

	return math::Abs(delta) <= std::numeric_limits<T>().epsilon();
}

template<math::math_type::NumericType T>
bool math::AlmostEqual(T val1, T val2, T epsilon)
{
	// Calculate difference
	T delta = val2 - val1;

	return math::Abs(delta) <= epsilon;
}

template<math::math_type::NumericType T>
constexpr T math::Min(T const& val1, T const& val2) noexcept
{
	return (val1 < val2) ? val1 : val2;
}

template<math::math_type::NumericType T>
constexpr T math::Max(T const& val1, T const& val2) noexcept
{
	return (val1 > val2) ? val1 : val2;
}

template<math::math_type::NumericType T>
constexpr T math::Clamp(T const& val, T const& min, T const& max)
{
	_ASSERT(min <= max);

	if (val < min)
		return min;
	else if (val > max)
		return max;

	return val;
}

template<math::math_type::NumericType T>
constexpr T math::Wrap(T const& val, T const& min, T const& max)
{
	_ASSERT(min <= max);

	// Check if number is within the range
	if (val >= min && val <= max)
		return val;
	
	// Calculate range
	T range = max - min;

	// Check if number is smaller than minimum
	if (val < min)
	{
		// Calculate offset between number & min
		T offsetRange = min - val;

		// Compare offset & range size 
		if (offsetRange < range)
			return max - math::Abs(val);
		else
			return max - std::fmodf(offsetRange, range);
	}
	// If number is larger than maximum
	else
	{
		// Calculate offset between number & max
		T offsetRange = val - max;
		
		// Compare offset & range size
		if (offsetRange < range)
			return min + math::Abs(offsetRange);
		else
			return min + std::fmodf(offsetRange, range);
	}
}

template<math::math_type::NumericType T>
constexpr int math::Floor(T const& val) noexcept
{
	// Convert value into an integer
	int integer = static_cast<int>(val);

	// Check if the value's decimal is equal to .0f
	bool isInt = (val - static_cast<T>(integer)) == 0.0f;

	if (integer < 0 && !isInt)
		--integer;

	// Return value if number is already an integer otherwise cast as type
	return isInt ? val : integer;
}

template<math::math_type::NumericType T>
constexpr int math::Ceiling(T const& val) noexcept
{
	int	integer = static_cast<int>(val);

	if (integer < 0)
		integer -= 1;

	// Return value if number is already an integer otherwise increment integer & cast as type
	return ((val - integer) == 0.0f) ? val : static_cast<T>(++integer);
}

template<math::math_type::NumericType T>
constexpr T math::Power(T const& val, unsigned int const power)
{
	T result = val;

	if (power == 0)
		return static_cast<T>(1);

	for (unsigned int i = 1; i < power; ++i)
		result *= val;

	return result;
}

template<math::math_type::UnsignedType T>
constexpr T math::Sqrt(T const& val) noexcept
{
	// TODO: finish sqrt function
	__debugbreak();

	return 0;
}

template<math::math_type::UnsignedType T, math::math_type::NumericType Tindex>
constexpr T math::Root(T const& val, Tindex const& index) noexcept
{
	// TODO: finish root function
	__debugbreak();

	return 0;
}

template<math::math_type::NumericType T>
constexpr T math::Factorial(T const& val)
{
	T result = 1;

	for (int i = result; i <= math::Abs(val); ++i)
		result *= i;

	return (val < 0) ? -result : result;
}

namespace LibMath = math;