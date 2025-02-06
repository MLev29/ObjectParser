#pragma once

#include "LibMath/VariableType.hpp"
#include "LibMath/Macros.h"
#include "LibMath/Arithmetic.h"

#include <cmath>
/* 
*	------- Vector2 -------
*	Static Functions:
*	- Up			DONE
*	- Down			DONE
*	- Left			DONE
*	- Right			DONE
*	- Zero			DONE
* 
*	Functions:
*	- Dot			DONE
*	- Magnitude		DONE
*	- Normalize		DONE
*	- Normal		DONE
*	- AngleFrom		DONE
*	- IsUnit		DONE
*	- Translate		DONE
*	- Rotate		DONE
*	- Reflect		DONE
*	- Project		DONE
*	- Scale			DONE
*
*	Operators:
*	- Add			(+, +=)				DONE
*	- Subtract		(-, -=)				DONE
*	- Multiply		(*, *=)				DONE
*	- Divide		(/, /=)				DONE
*	- Compare		(==)				DONE
*	- InvCompare	(!-)				DONE
*	- Index			(index operator)	DONE
*
*/

#define SPECIFIER inline constexpr

namespace math
{
	template<math::math_type::NumericType T>
	class Vector2
	{
	public:
		constexpr			Vector2(void);
		constexpr			Vector2(T const& scalar);
		constexpr			Vector2(T const& x, T const& y);

		constexpr			~Vector2(void) = default;

		static Vector2<T>	Up(void) noexcept;
		static Vector2<T>	Down(void) noexcept;
		static Vector2<T>	Left(void) noexcept;
		static Vector2<T>	Right(void) noexcept;
		static Vector2<T>	Zero(void) noexcept;

		T					Cross(Vector2<T> const& vec2) const;
		T					Dot(Vector2<T> const& vec2) const;
		T					Magnitude(void) const;
		Vector2<T>&			Normalize(void);
		Vector2<T>&			Normal(void);
		T					AngleFrom(Vector2<T> const& vec2) const;
		bool				IsUnit(void) const;
		Vector2<T>&			Reflect(Vector2<T> const& vec2);
		Vector2<T>&			Project(Vector2<T> const& vec2);

		void				Translate(Vector2<T> const& vec2);
		void				Rotate(T const& deg);
		void				Scale(Vector2<T> const& vec2);

		Vector2<T>			operator+(Vector2<T> const& vec2) const;
		Vector2<T>			operator-(Vector2<T> const& vec2) const;
		Vector2<T>			operator*(Vector2<T> const& vec2) const;
		Vector2<T>			operator/(Vector2<T> const& vec2) const;
		Vector2<T>			operator*(T value);
		Vector2<T>			operator/(T value);
		Vector2<T>&			operator-(void);
		Vector2<T>&			operator+=(Vector2<T> const& vec2);
		Vector2<T>&			operator-=(Vector2<T> const& vec2);
		Vector2<T>&			operator*=(Vector2<T> const& vec2);
		Vector2<T>&			operator/=(Vector2<T> const& vec2);
		bool				operator==(Vector2<T> const& vec2) const;
		bool				operator!=(Vector2<T> const& vec2) const;
		T					operator[](int const& index) const;
		T&					operator[](int const& index);

	private:
		T m_x;
		T m_y;
	};

	template<math::math_type::NumericType T>
	inline constexpr Vector2<T>::Vector2(void)
		: m_x((T) 0), m_y((T) 0)
	{
	}

	// Constructors
	template<math_type::NumericType T>
	inline constexpr math::Vector2<T>::Vector2(T const& scalar)
		: m_x(scalar), m_y(scalar)
	{
	}

	template<math_type::NumericType T>
	inline constexpr math::Vector2<T>::Vector2(T const& x, T const& y)
		: m_x(x), m_y(y)
	{
	}

	// Static Functions
	template<math_type::NumericType T>
	inline math::Vector2<T> math::Vector2<T>::Up(void) noexcept
	{
		return Vector2(0.0f, 1.0f);
	}

	template<math_type::NumericType T>
	inline math::Vector2<T> math::Vector2<T>::Down(void) noexcept
	{
		return Vector2(0.0f, -1.0f);
	}

	template<math_type::NumericType T>
	inline math::Vector2<T> math::Vector2<T>::Left(void) noexcept
	{
		return Vector2<T>(-1.0f, 0.0f);
	}

	template<math_type::NumericType T>
	inline math::Vector2<T> math::Vector2<T>::Right(void) noexcept
	{
		return Vector2<T>(1.0f, 0.0f);
	}

	template<math_type::NumericType T>
	inline math::Vector2<T> math::Vector2<T>::Zero(void) noexcept
	{
		return Vector2(0.0f, 0.0f);
	}

	template<math::math_type::NumericType T>
	T math::Vector2<T>::Cross(math::Vector2<T> const& vec2) const
	{
		return (m_x * vec2.m_y) - (m_y * vec2.m_x);
	}

	template<math::math_type::NumericType T>
	T math::Vector2<T>::Dot(math::Vector2<T> const& vec2) const
	{	
		return (m_x * vec2.m_x) + (m_y * vec2.m_y);
	}

	template<math::math_type::NumericType T>
	T math::Vector2<T>::Magnitude(void) const
	{
		return (T) std::sqrtf(Dot(*this));
	}

	template<math::math_type::NumericType T>
	math::Vector2<T>& Vector2<T>::Normalize(void)
	{
		/*
		*	Formula:
		*	x = x / mag
		*	y = y / mag
		*
		*	x & y -> Components of vector
		*	mag	  -> Magnitude of the vector
		*/

		const T denominator = 1.0f / Magnitude();

		m_x *= denominator;
		m_y *= denominator;

		return *this;
	}

	template<math::math_type::NumericType T>
	math::Vector2<T>& math::Vector2<T>::Normal(void)
	{
		T tmp = -m_y;
		m_y = m_x;
		m_x = tmp;

		return *this;
	}

	template<math::math_type::NumericType T>
	T math::Vector2<T>::AngleFrom(Vector2<T> const& vec2) const
	{
		/*
			*	Get the angle between two vectors
			*
			*	Formula:
			*	angle = acos((a dot b) / (magA * magB))
			*
			*	a	 -> VectorA (this)
			*	b	 -> VectorB (other)
			*	magA -> Magnitude of vector A
			*	magB -> Magnitude of vector B
		*/

			// Get the magnitude for both vectors
		const T magnitude1 = Magnitude();
		const T magnitude2 = vec2.Magnitude();

		// Calculate angle
		return acosf(Dot(vec2) / (magnitude1 * magnitude2));
	}

	template<math::math_type::NumericType T>
	bool math::Vector2<T>::IsUnit(void) const
	{
		return (static_cast<float>(Magnitude()) == 1.0f);
	}

	template<math::math_type::NumericType T>
	Vector2<T>& Vector2<T>::Reflect(Vector2<T> const& vec2)
	{
		/*
		*	Formula:
		*	r = i - 2(i dot n)n
		*
		*	r -> reflected ray
		*	i -> incident ray
		*	n -> normal (axis)
		*/

		// Initialize normal axis & normalize vector
		Vector2<T> normal(vec2);
		normal.Normalize();

		// Calculate reflected vector
		*this = *this - normal * 2.0f * (Dot(normal));

		return *this;
	}

	template<math::math_type::NumericType T>
	Vector2<T>& Vector2<T>::Project(Vector2<T> const& vec2)
	{
		// Calculate coefficient
		const T projectionCoefficient = Dot(vec2) / vec2.Dot(vec2);

		// Project each component of vector onto the other vector
		m_x = vec2.m_x * projectionCoefficient;
		m_y = vec2.m_y * projectionCoefficient;

		return *this;
	}

	template<math::math_type::NumericType T>
	void math::Vector2<T>::Translate(Vector2<T> const& vec2)
	{
		*this += vec2;
	}

	template<math::math_type::NumericType T>
	void Vector2<T>::Rotate(T const& deg)
	{
		// Calculate cos & sin angle value
		const T sinAngle = sinf(deg);
		const T cosAngle = cosf(deg);

		// Store current x value in order for y rotation calculation to be correct
		const T prevX = m_x;

		// Calculate rotated vector
		m_x = m_x * cosAngle - m_y * sinAngle;
		m_y = prevX * sinAngle + m_y * cosAngle;
	}

	template<math::math_type::NumericType T>
	void Vector2<T>::Scale(Vector2<T> const& vec2)
	{
		*this *= vec2;
	}

	template<math::math_type::NumericType T>
	math::Vector2<T> math::Vector2<T>::operator+(Vector2<T> const& vec2) const
	{
		return Vector2<T>(
			m_x + vec2.m_x,
			m_y + vec2.m_y
		);
	}

	template<math::math_type::NumericType T>
	math::Vector2<T> math::Vector2<T>::operator-(Vector2<T> const& vec2) const
	{
		return Vector2<T>(
			m_x - vec2.m_x,
			m_y - vec2.m_y
		);
	}

	template<math::math_type::NumericType T>
	Vector2<T> Vector2<T>::operator*(Vector2<T> const& vec2) const
	{
		return Vector2<T>(
			m_x * vec2.m_x,
			m_y * vec2.m_y
		);
	}

	template<math::math_type::NumericType T>
	math::Vector2<T> math::Vector2<T>::operator/(Vector2<T> const& vec2) const
	{
		_ASSERT(vec2.m_x != 0.0f);
		_ASSERT(vec2.m_y != 0.0f);

		return Vector2<T>(
			m_x / vec2.m_x,
			m_y / vec2.m_y
		);
	}

	template<math::math_type::NumericType T>
	inline Vector2<T> Vector2<T>::operator*(T value)
	{
		return Vector2<T>(
			m_x * value,
			m_y * value
		);
	}

	template<math::math_type::NumericType T>
	inline Vector2<T> Vector2<T>::operator/(T value)
	{
		_ASSERT(value != 0);

		return Vector2<T>(
			m_x / value,
			m_y / value
		);
	}

	template<math::math_type::NumericType T>
	inline Vector2<T>& Vector2<T>::operator-(void)
	{
		m_x = -m_x;
		m_y = -m_y;

		return *this;
	}

	template<math::math_type::NumericType T>
	Vector2<T>& Vector2<T>::operator+=(Vector2<T> const& vec2)
	{
		*this = *this + vec2;

		return *this;
	}
	template<math::math_type::NumericType T>
	Vector2<T>& Vector2<T>::operator-=(Vector2<T> const& vec2)
	{
		*this = *this - vec2;

		return *this;
	}

	template<math::math_type::NumericType T>
	Vector2<T>& Vector2<T>::operator*=(Vector2<T> const& vec2)
	{
		*this = *this * vec2;

		return *this;
	}

	template<math::math_type::NumericType T>
	Vector2<T>& Vector2<T>::operator/=(Vector2<T> const& vec2)
	{
		*this = *this / vec2;

		return *this;
	}

	template<math::math_type::NumericType T>
	bool Vector2<T>::operator==(Vector2<T> const& vec2) const
	{
		return
			math::AlmostEqual(m_x, vec2.m_x) &&
			math::AlmostEqual(m_y, vec2.m_y);
	}

	template<math::math_type::NumericType T>
	inline bool Vector2<T>::operator!=(Vector2<T> const& vec2) const
	{
		return
			!(math::AlmostEqual(m_x, vec2.m_x) &&
			  math::AlmostEqual(m_y, vec2.m_y));
	}

	template<math::math_type::NumericType T>
	T Vector2<T>::operator[](int const& index) const
	{
		_ASSERT(index >= 0 && index <= 1);

		return reinterpret_cast<const T*>(this)[index];
	}

	template<math::math_type::NumericType T>
	T& Vector2<T>::operator[](int const& index)
	{
		_ASSERT(index >= 0 && index <= 1);

		return reinterpret_cast<T*>(this)[index];
	}
}

namespace LibMath = math;