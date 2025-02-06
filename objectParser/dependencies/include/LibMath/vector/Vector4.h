#pragma once

#include "LibMath/VariableType.hpp"
#include "LibMath/Arithmetic.h"

#include <cmath>
#include <limits>

/*
*	------- Vector4 -------
*	Static Functions:
*	- Zero			DONE
* 
*	- Magnitude		DOME
*	- Normalize		DONE
*	- Translate		DONE
*	- Scale			DONE
* 
* Operators:
*	- Add		(+, +=)				DONE
*	- Subtract	(-, -=)				DONE
*	- Multiply	(*, *=)				DONE
*	- Divide	(/, /=)				DONE
*	- Compare	(==)				DONE
*	- Compare	(!=)				DONE
*	- Index		(index operator)	DONE
*/

namespace math
{
	template<math::math_type::NumericType T>
	class Vector4
	{
	public:
							Vector4(void);
							Vector4(T scalar);
							Vector4(T x, T y, T z, T w);

							~Vector4(void) = default;

		static Vector4<T>	Zero(void) noexcept;

		T					Magnitude(void) const;
		T					Dot(Vector4<T> const& vec4) const;
		Vector4<T>&			Normalize(void);
		bool				IsShorterThan(Vector4<T> const& vec4) const;
		bool				IsLongerThan(Vector4<T> const& vec4) const;

		Vector4<T>&			Translate(Vector4<T> vec4);
		Vector4<T>&			Scale(Vector4<T> scale);

		Vector4<T>			operator+(Vector4<T> const vec4) const;
		Vector4<T>			operator-(Vector4<T> const vec4) const;
		Vector4<T>			operator*(Vector4<T> const vec4) const;
		Vector4<T>			operator/(Vector4<T> const vec4) const;
		Vector4<T>			operator*(T value) const;
		Vector4<T>			operator/(T value) const;
		Vector4<T>&			operator-(void);
		Vector4<T>&			operator+=(Vector4<T> const& vec4);
		Vector4<T>&			operator-=(Vector4<T> const& vec4);
		Vector4<T>&			operator*=(Vector4<T> const& vec4);
		Vector4<T>&			operator/=(Vector4<T> const& vec4);
		Vector4<T>&			operator*=(T value);
		Vector4<T>&			operator/=(T value);
		bool				operator==(Vector4<T> vec4) const;
		bool				operator!=(Vector4<T> vec4) const;
		T					operator[](unsigned int index) const;
		T&					operator[](unsigned int index);

	private:
		T m_x;
		T m_y;
		T m_z;
		T m_w;
	};

	template<math::math_type::NumericType T>
	inline Vector4<T>::Vector4(void)
		: m_x((T) 0.0f), m_y((T) 0.0f), m_z((T) 0.0f), m_w((T) 0.0f)
	{
	}

	template<math::math_type::NumericType T>
	inline Vector4<T>::Vector4(T scalar)
		: m_x(scalar), m_y(scalar), m_z(scalar), m_w(scalar)
	{
	}

	template<math::math_type::NumericType T>
	inline Vector4<T>::Vector4(T x, T y, T z, T w)
		: m_x(x), m_y(y), m_z(z), m_w(w)
	{
	}

	template<math::math_type::NumericType T>
	inline Vector4<T> Vector4<T>::Zero(void) noexcept
	{
		T zero = static_cast<T>(0.0f);

		return Vector4<T>(zero, zero, zero, zero);
	}

	template<math::math_type::NumericType T>
	inline T Vector4<T>::Magnitude(void) const
	{
		return (T) std::sqrt(Dot(*this));
	}

	template<math::math_type::NumericType T>
	inline T Vector4<T>::Dot(Vector4<T> const& vec4) const
	{
		return static_cast<T>((m_x * vec4.m_x) + (m_y * vec4.m_y) + (m_z * vec4.m_z)) + (m_w * vec4.m_w);
	}

	template<math::math_type::NumericType T>
	inline Vector4<T>& Vector4<T>::Normalize(void)
	{
		const T denom = 1.0f / Magnitude();

		return *this *= denom;
	}

	template<math::math_type::NumericType T>
	inline bool Vector4<T>::IsShorterThan(Vector4<T> const& vec4) const
	{
		return Magnitude() < vec4.Magnitude();
	}

	template<math::math_type::NumericType T>
	inline bool Vector4<T>::IsLongerThan(Vector4<T> const& vec4) const
	{
		return Magnitude() > vec4.Magnitude();
	}

	template<math::math_type::NumericType T>
	inline Vector4<T>& Vector4<T>::Translate(Vector4<T> vec4)
	{
		return *this += vec4;
	}

	template<math::math_type::NumericType T>
	inline Vector4<T>& Vector4<T>::Scale(Vector4<T> scale)
	{
		return *this *= scale;
	}

	template<math::math_type::NumericType T>
	inline math::Vector4<T> Vector4<T>::operator+(Vector4<T> const vec4) const
	{
		return Vector4<T>(
			m_x + vec4.m_x,
			m_y + vec4.m_y,
			m_z + vec4.m_z,
			m_w + vec4.m_w
		);
	}

	template<math::math_type::NumericType T>
	inline math::Vector4<T> Vector4<T>::operator-(Vector4<T> const vec4) const
	{
		return Vector4<T>(
			m_x - vec4.m_x,
			m_y - vec4.m_y,
			m_z - vec4.m_z,
			m_w - vec4.m_w
		);
	}

	template<math::math_type::NumericType T>
	inline math::Vector4<T> Vector4<T>::operator*(Vector4<T> const vec4) const
	{
		return Vector4<T>(
			m_x * vec4.m_x,
			m_y * vec4.m_y,
			m_z * vec4.m_z,
			m_w * vec4.m_w
		);
	}

	template<math::math_type::NumericType T>
	inline math::Vector4<T> Vector4<T>::operator/(Vector4<T> const vec4) const
	{
		_ASSERT(vec4.m_x != (T) 0.0f);
		_ASSERT(vec4.m_y != (T) 0.0f);
		_ASSERT(vec4.m_z != (T) 0.0f);
		_ASSERT(vec4.m_w != (T) 0.0f);

		return Vector4<T>(
			m_x / vec4.m_x,
			m_y / vec4.m_y,
			m_z / vec4.m_z,
			m_w / vec4.m_w
		);
	}

	template<math::math_type::NumericType T>
	inline Vector4<T> Vector4<T>::operator*(T value) const
	{
		return Vector4<T>(
			m_x * value,
			m_y * value,
			m_z * value,
			m_w * value
		);
	}

	template<math::math_type::NumericType T>
	inline Vector4<T> Vector4<T>::operator/(T value) const
	{
		_ASSERT(value != 0);

		return Vector4<T>(
			m_x / value,
			m_y / value,
			m_z / value,
			m_w / value
		);
	}

	template<math::math_type::NumericType T>
	inline Vector4<T>& Vector4<T>::operator-(void)
	{
		m_x = -m_x;
		m_y = -m_y;
		m_z = -m_z;
		m_w = -m_w;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Vector4<T>& Vector4<T>::operator+=(Vector4<T> const& vec4)
	{
		*this = *this + vec4;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Vector4<T>& Vector4<T>::operator-=(Vector4<T> const& vec4)
	{
		*this = *this - vec4;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Vector4<T>& Vector4<T>::operator*=(Vector4<T> const& vec4)
	{
		*this = *this * vec4;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Vector4<T>& Vector4<T>::operator/=(Vector4<T> const& vec4)
	{
		*this = *this / vec4;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Vector4<T>& Vector4<T>::operator*=(T value)
	{
		*this = *this * value;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Vector4<T>& Vector4<T>::operator/=(T value)
	{
		*this = *this / value;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline bool Vector4<T>::operator==(Vector4<T> vec4) const
	{
		bool xEqual = math::AlmostEqual(m_x, vec4.m_x);
		bool yEqual = math::AlmostEqual(m_y, vec4.m_y);
		bool zEqual = math::AlmostEqual(m_z, vec4.m_z);
		bool wEqual = math::AlmostEqual(m_w, vec4.m_w);

		return xEqual && yEqual && zEqual && wEqual;
	}

	template<math::math_type::NumericType T>
	inline bool Vector4<T>::operator!=(Vector4<T> vec4) const
	{
		bool xEqual = math::AlmostEqual(m_x, vec4.m_x);
		bool yEqual = math::AlmostEqual(m_y, vec4.m_y);
		bool zEqual = math::AlmostEqual(m_z, vec4.m_z);
		bool wEqual = math::AlmostEqual(m_w, vec4.m_w);

		return !(xEqual && yEqual && zEqual && wEqual);
	}

	template<math::math_type::NumericType T>
	inline T Vector4<T>::operator[](unsigned int index) const
	{
		_ASSERT(index < 4);

		return reinterpret_cast<const T*>(this)[index];
	}

	template<math::math_type::NumericType T>
	inline T& Vector4<T>::operator[](unsigned int index)
	{
		_ASSERT(index < 4);

		return reinterpret_cast<T*>(this)[index];
	}
}

namespace LibMath = math;