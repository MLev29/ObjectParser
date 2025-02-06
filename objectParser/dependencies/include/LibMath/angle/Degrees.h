#pragma once

#include "LibMath/VariableType.hpp"
#include "LibMath/Macros.h"
#include "LibMath/Arithmetic.h"

#include <cmath>

/*
	To Do Degrees

	Constructor
	- void				DONE
	- value				DONE
	- Radian			REMOVED

	Functions
	- Deg2Rad			REMOVED
	- Rad2Deg			REMOVED
	- Wrap				DONE
	- Value				DONE

	Operators
	- Add				DONE
	- Subtract			DONE
	- Equality			DONE
	- Inverse equality	DONE
*/

namespace math
{
	template<math::math_type::NumericType T>
	class Degree
	{
	public:
					Degree(void) = default;
					Degree(T const value);

					~Degree(void) = default;

		Degree<T>	Wrap(bool to360 = true);	// true -> 0 - 360 | false -> -180 - 180
		T			Value(void) const noexcept;
		T&			Value(void);

		Degree<T>	operator+(T const value);
		Degree<T>	operator+(Degree<T> const& value);
		Degree<T>	operator-(T const value);
		Degree<T>	operator-(Degree<T> const& value);
		Degree<T>	operator*(T const value);
		Degree<T>	operator/(T const value);
		Degree<T>&	operator+=(T const value);
		Degree<T>&	operator+=(Degree<T> const& value);
		Degree<T>&	operator-=(T const value);
		Degree<T>&	operator-=(Degree<T> const& value);

		bool		operator==(Degree<T> const& Degree) const noexcept;
		bool		operator!=(Degree<T> const& Degree) const noexcept;
	private:
		T m_angle = 0;
	};

	template<math::math_type::NumericType T>
	inline math::Degree<T>::Degree(T const value)
		: m_angle(value)
	{
	}

	template<math::math_type::NumericType T>
	inline Degree<T> Degree<T>::Wrap(bool to360)
	{
		T lowerBound = to360 ? 0 : -180;

		T result = math::Wrap<T>(m_angle, lowerBound, lowerBound + 360);

		return Degree<T>(result);
	}

	template<math::math_type::NumericType T>
	inline T Degree<T>::Value(void) const noexcept
	{
		return m_angle;
	}

	template<math::math_type::NumericType T>
	inline T& Degree<T>::Value(void)
	{
		return m_angle;
	}

	template<math::math_type::NumericType T>
	inline math::Degree<T> math::Degree<T>::operator+(T const value)
	{
		return m_angle + value;
	}

	template<math::math_type::NumericType T>
	inline Degree<T> Degree<T>::operator+(Degree<T> const& value)
	{
		return Degree<T>(m_angle + value.m_angle);
	}

	template<math::math_type::NumericType T>
	inline math::Degree<T> math::Degree<T>::operator-(T const value)
	{
		return m_angle - value;
	}

	template<math::math_type::NumericType T>
	inline Degree<T> Degree<T>::operator-(Degree<T> const& value)
	{
		return Degree<T>(m_angle - value.m_angle);
	}

	template<math::math_type::NumericType T>
	inline Degree<T> Degree<T>::operator*(T const value)
	{
		return Degree<T>(m_angle * value);
	}

	template<math::math_type::NumericType T>
	inline Degree<T> Degree<T>::operator/(T const value)
	{
		_ASSERT(value != (T) 0);

		return Degree<T>(m_angle / value);
	}

	template<math::math_type::NumericType T>
	inline math::Degree<T>& Degree<T>::operator+=(T const value)
	{
		T result = m_angle + value;

		return result;
	}

	template<math::math_type::NumericType T>
	inline Degree<T>& Degree<T>::operator+=(Degree<T> const& value)
	{
		m_angle += value.m_angle;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline math::Degree<T>& math::Degree<T>::operator-=(T const value)
	{
		T result = m_angle - value;

		return result;
	}

	template<math::math_type::NumericType T>
	inline Degree<T>& Degree<T>::operator-=(Degree<T> const& value)
	{
		m_angle -= value.m_angle;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline bool Degree<T>::operator==(Degree<T> const& Degree) const noexcept
	{
		bool result = math::AlmostEqual(m_angle, Degree.m_angle);

		return result;
	}

	template<math::math_type::NumericType T>
	inline bool Degree<T>::operator!=(Degree<T> const& Degree) const noexcept
	{
		return !math::AlmostEqual(m_angle, Degree.m_angle);
	}
}

namespace LibMath = math;