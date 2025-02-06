#pragma once

#include "LibMath/VariableType.hpp"
#include "LibMath/Macros.h"
#include "LibMath/Arithmetic.h"

#include <cmath>

/*
*	Radians
*
*	Constructors
*	- void				DONE
*	- value				DONE
*
*	Functions
*	- Wrap				DONE
*	- Limit				REMOVED
*	- Value				DONE
* 
*	Operators
*	- Addition			DONE
*	- Subtraction		DONE
*	- Equality			DONE
*	- Inverse equality	DONE
*/


namespace math
{
	template<math::math_type::NumericType T>
	class Radian
	{
	public:
					Radian(void) = default;
					Radian(T const value);

					~Radian(void) = default;

		Radian<T>	Wrap(bool to2Pi = true);	// true -> 0 - 2Pi | false -> -Pi - Pi
		T			Value(void) const noexcept;
		T&			Value(void);

		Radian<T>	operator+(T const value);
		Radian<T>	operator+(Radian<T> const& radian);
		Radian<T>	operator-(T const value);
		Radian<T>	operator-(Radian<T> const& radian);
		Radian<T>	operator*(T const value);
		Radian<T>	operator/(T const value);
		Radian<T>&	operator+=(T const value);
		Radian<T>&	operator+=(Radian<T> const& radian);
		Radian<T>&	operator-=(T const value);
		Radian<T>&	operator-=(Radian<T> const& radian);

		bool		operator==(Radian const& radian) const noexcept;
		bool		operator!=(Radian const& radian) const noexcept;
	private:
		T m_angle = 0;
	};

	template<math::math_type::NumericType T>
	inline Radian<T>::Radian(T const value)
		: m_angle(value)
	{
	}

	template<math::math_type::NumericType T>
	inline Radian<T> Radian<T>::Wrap(bool to2Pi)
	{
		T lowerBound = to2Pi ? 0.0f : -PI;

		T result = math::Wrap<T>(m_angle, lowerBound, lowerBound + TWO_PI);

		return Radian<T>(result);
	}

	template<math::math_type::NumericType T>
	inline T Radian<T>::Value(void) const noexcept
	{
		return m_angle;
	}

	template<math::math_type::NumericType T>
	inline T& Radian<T>::Value(void)
	{
		return m_angle;
	}

	template<math::math_type::NumericType T>
	inline Radian<T> Radian<T>::operator+(T const value)
	{
		return Radian<T>(m_angle + value);
	}

	template<math::math_type::NumericType T>
	inline math::Radian<T> Radian<T>::operator+(math::Radian<T> const& radian)
	{
		return Radian(m_angle + radian.m_angle);
	}

	template<math::math_type::NumericType T>
	inline Radian<T> Radian<T>::operator-(T const value)
	{
		return Radian<T>(m_angle - value);
	}

	template<math::math_type::NumericType T>
	inline Radian<T> Radian<T>::operator-(Radian<T> const& radian)
	{
		return Radian<T>(m_angle - radian.m_angle);
	}

	template<math::math_type::NumericType T>
	inline Radian<T> Radian<T>::operator*(T const value)
	{
		return Radian<T>(m_angle * value);
	}

	template<math::math_type::NumericType T>
	inline Radian<T> Radian<T>::operator/(T const value)
	{
		_ASSERT(value != 0.0f);

		return Radian<T>(m_angle / value);
	}

	template<math::math_type::NumericType T>
	inline Radian<T>& Radian<T>::operator+=(T const value)
	{
		m_angle += value;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Radian<T>& Radian<T>::operator+=(Radian<T> const& radian)
	{
		m_angle += radian.m_angle;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Radian<T>& Radian<T>::operator-=(T const value)
	{
		m_angle -= value;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Radian<T>& Radian<T>::operator-=(Radian<T> const& radian)
	{
		m_angle -= radian.m_angle;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline bool Radian<T>::operator==(Radian const& radian) const noexcept
	{
		return math::AlmostEqual(m_angle, radian.m_angle, (T) INNACURATE_EPSILON);
	}

	template<math::math_type::NumericType T>
	inline bool Radian<T>::operator!=(Radian const& radian) const noexcept
	{
		return !math::AlmostEqual(m_angle, radian.m_angle);
	}
}

namespace LibMath = math;