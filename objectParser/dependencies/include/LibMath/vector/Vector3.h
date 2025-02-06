#pragma once

#include "LibMath/VariableType.hpp"
#include "LibMath/Arithmetic.h"
#include "LibMath/matrix/Matrix3.h"

#include <cmath>
#include <limits>

#define SPECIFIER inline constexpr

/*
*	------- Vector3 -------
*	Static Functions:
*	- Up			DONE
*	- Down			DONE
*	- Left			DONE
*	- Right			DONE
*	- Forward		DONE
*	- Backward		DONE
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
*	- InvCompare	(!=)				DONE
*	- Index			(index operator)	DONE
*/

namespace math
{
	template<math::math_type::NumericType T>
	class Vector3
	{
	public:
		SPECIFIER				Vector3(void);
		SPECIFIER				Vector3(T const& scalar);
		SPECIFIER				Vector3(T const& x, T const& y, T const& z);

								~Vector3(void) = default;

		static	  Vector3<T>	Up(void) noexcept;
		static	  Vector3<T>	Down(void) noexcept;
		static	  Vector3<T>	Left(void) noexcept;
		static	  Vector3<T>	Right(void) noexcept;
		static	  Vector3<T>	Forward(void) noexcept;
		static	  Vector3<T>	Backward(void) noexcept;
		static	  Vector3<T>	Zero(void) noexcept;

		SPECIFIER Vector3<T>	Cross(Vector3<T> const& vec3) const;
		SPECIFIER T				Dot(Vector3<T> const& vec3) const;
		SPECIFIER T				Magnitude(void) const;
		SPECIFIER T				MagnitudeSquared(void) const;
		SPECIFIER Vector3<T>&	Normalize(void);
		SPECIFIER T				AngleFrom(Vector3<T> vec3) const;
		SPECIFIER bool			IsUnit(void) const;
		SPECIFIER bool			IsShorterThan(Vector3<T> vec3) const;
		SPECIFIER bool			IsLongerThan(Vector3<T> vec3) const;
		SPECIFIER Vector3<T>&	Reflect(Vector3<T> const& vec3);
		SPECIFIER Vector3<T>&	Project(Vector3<T> const& vec3);

		SPECIFIER Vector3<T>&	Translate(Vector3<T> const& vec3);
		SPECIFIER Vector3<T>&	Rotate(T const& angleDeg, Vector3 const& axis);
		SPECIFIER Vector3<T>&	Scale(Vector3<T> const& vec3);

		// Operators
		Vector3<T>				operator+(Vector3<T> const& vec3) const;
		Vector3<T>				operator-(Vector3<T> const& vec3) const;
		Vector3<T>				operator*(Vector3<T> const& vec3) const;
		Vector3<T>				operator/(Vector3<T> const& vec3) const;
		Vector3<T>				operator*(T value) const;
		Vector3<T>				operator/(T value) const;
		Vector3<T>&				operator-(void);
		Vector3<T>&				operator+=(Vector3<T> const& vec3);
		Vector3<T>&				operator-=(Vector3<T> const& vec3);
		Vector3<T>&				operator*=(Vector3<T> const& vec3);
		Vector3<T>&				operator/=(Vector3<T> const& vec3);
		bool					operator==(Vector3<T> const& vec3) const;
		bool					operator!=(Vector3<T> const& vec3) const;
		T&						operator[](unsigned int index);
		T						operator[](unsigned int index) const;
	private:
		T m_x;
		T m_y;
		T m_z;
	};

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T>::Vector3(void)
		: m_x((T) 0.0f), m_y((T) 0.0f), m_z((T) 0.0f)
	{
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T>::Vector3(T const& scalar)
		: m_x(scalar), m_y(scalar), m_z(scalar)
	{
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T>::Vector3(T const& x, T const& y, T const& z)
		: m_x(x), m_y(y), m_z(z)
	{
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::Up(void) noexcept
	{
		return Vector3<T>(0.0f, 1.0f, 0.0f);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::Down(void) noexcept
	{
		return Vector3<T>(0.0f, -1.0f, 0.0f);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::Left(void) noexcept
	{
		return Vector3<T>(-1.0f, 0.0f, 0.0f);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::Right(void) noexcept
	{
		return Vector3<T>(1.0f, 0.0f, 0.0f);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::Forward(void) noexcept
	{
		return Vector3<T>(0.0f, 0.0f, 1.0f);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::Backward(void) noexcept
	{
		return Vector3<T>(0.0f, 0.0f, -1.0f);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::Zero(void) noexcept
	{
		return Vector3<T>(0.0f, 0.0f, 0.0f);
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T> Vector3<T>::Cross(Vector3<T> const& vec3) const
	{
		return Vector3<T>
		(
			(m_y * vec3.m_z) - (m_z * vec3.m_y),
			(m_z * vec3.m_x) - (m_x * vec3.m_z),
			(m_x * vec3.m_y) - (m_y * vec3.m_x)
		);
	}

	template<math::math_type::NumericType T>
	SPECIFIER T Vector3<T>::Dot(Vector3<T> const& vec3) const
	{
		// x^2 + y^2 + z^2
		return static_cast<T>((m_x * vec3.m_x) + (m_y * vec3.m_y) + (m_z * vec3.m_z));
	}

	template<math::math_type::NumericType T>
	SPECIFIER T Vector3<T>::Magnitude(void) const
	{
		return std::sqrt(Dot(*this));
	}

	template<math::math_type::NumericType T>
	SPECIFIER T Vector3<T>::MagnitudeSquared(void) const
	{
		return static_cast<T>((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T>& Vector3<T>::Normalize(void)
	{
		const T denom =  1.0f / Magnitude();

		return *this *= denom;
	}

	template<math::math_type::NumericType T>
	SPECIFIER T Vector3<T>::AngleFrom(Vector3<T> vec3) const
	{
		/*
		*		Measure angle between two vectors
		*
		*		Formula:
		*			   vectorA DOT vectorB
		*		acos -----------------------
		*			 ||vectorA||||vectorB||
		*/

		// Calculate magnitude for both vectors
		T magnitude1 = Magnitude();
		T magnitude2 = vec3.Magnitude();

		// Calculate angle
		T theta = acosf(Dot(vec3) / (magnitude1 * magnitude2));

		// Return angle in radian
		return theta;
	}

	template<math::math_type::NumericType T>
	SPECIFIER bool Vector3<T>::IsUnit(void) const
	{
		return Magnitude() == (T) 1;
	}

	template<math::math_type::NumericType T>
	SPECIFIER bool Vector3<T>::IsShorterThan(Vector3<T> vec3) const
	{
		return Magnitude() < vec3.Magnitude();
	}

	template<math::math_type::NumericType T>
	SPECIFIER bool Vector3<T>::IsLongerThan(Vector3<T> vec3) const
	{
		return Magnitude() > vec3.Magnitude();
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T>& Vector3<T>::Reflect(Vector3<T> const& vec3)
	{
		/*
		*	Formula:
		*	r = i - 2(i dot n)n
		*
		*	r -> reflected ray
		*	i -> incident ray
		*	n -> normal (axis)
		*/

		// Initialize normal vector & normalize vector
		Vector3<T> normal(vec3);
		normal.Normalize();

		// Calculate reflection vector
		*this = *this - normal * 2.0f * Dot(normal);

		return *this;
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T>& Vector3<T>::Project(Vector3<T> const& vec3)
	{
		// Calculate projection coefficient
		const T projectionCoefficient = Dot(vec3) / vec3.Dot(vec3);

		// Set all vector component values
		m_x = vec3.m_x * projectionCoefficient;
		m_y = vec3.m_y * projectionCoefficient;
		m_z = vec3.m_z * projectionCoefficient;

		return *this;
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T>& Vector3<T>::Translate(Vector3<T> const& vec3)
	{
		return *this += vec3;
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T>& Vector3<T>::Rotate(T const& angleDeg, Vector3<T> const& axis)
	{
		// Calculate sin & cos angle
		const T cosTheta = cosf(angleDeg * DEG2RAD);
		const T sinTheta = sinf(angleDeg * DEG2RAD);
		const T oneMinusCos = 1.0f - cosTheta;

		// Calculate rotation axis & normalize
		LibMath::Vector3 normalizedAxis = axis;
		normalizedAxis.Normalize();

		// Rotate via matrix
		T	matrixValues[9] =
		{
			cosTheta + normalizedAxis.m_x * normalizedAxis.m_x * oneMinusCos,						normalizedAxis.m_x * normalizedAxis.m_y * oneMinusCos - normalizedAxis.m_z * sinTheta,		normalizedAxis.m_x * normalizedAxis.m_z * oneMinusCos + normalizedAxis.m_y * sinTheta,
			normalizedAxis.m_y * normalizedAxis.m_x * oneMinusCos + normalizedAxis.m_z * sinTheta,	cosTheta + normalizedAxis.m_y * normalizedAxis.m_y * oneMinusCos,							normalizedAxis.m_y * normalizedAxis.m_z * oneMinusCos - normalizedAxis.m_x * sinTheta,
			normalizedAxis.m_z * normalizedAxis.m_x * oneMinusCos - normalizedAxis.m_y * sinTheta,	normalizedAxis.m_z * normalizedAxis.m_y * oneMinusCos + normalizedAxis.m_x * sinTheta,		cosTheta + normalizedAxis.m_z * normalizedAxis.m_z * oneMinusCos
		};

		// Initialize & assign values via array
		Matrix3<T> rotationMatrix(matrixValues);

		// Rotate vector
		*this = rotationMatrix * *this;

		return *this;
	}

	template<math::math_type::NumericType T>
	SPECIFIER Vector3<T>& Vector3<T>::Scale(Vector3<T> const& vec3)
	{
		return *this *= vec3;
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::operator+(Vector3 const& vec3) const
	{
		return Vector3<T>(
			m_x + vec3.m_x,
			m_y + vec3.m_y,
			m_z + vec3.m_z
		);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::operator-(Vector3 const& vec3) const
	{
		return Vector3(
			m_x - vec3.m_x,
			m_y - vec3.m_y,
			m_z - vec3.m_z
		);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::operator*(Vector3 const& vec3) const
	{
		return Vector3(
			m_x * vec3.m_x,
			m_y * vec3.m_y,
			m_z * vec3.m_z
		);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::operator/(Vector3 const& vec3) const
	{
		_ASSERT(vec3.m_x != 0.0f);
		_ASSERT(vec3.m_y != 0.0f);
		_ASSERT(vec3.m_z != 0.0f);

		return Vector3(
			m_x / vec3.m_x,
			m_y / vec3.m_y,
			m_z / vec3.m_z
		);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::operator*(T value) const
	{
		return Vector3<T>(
			m_x * value,
			m_y * value,
			m_z * value
		);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T> Vector3<T>::operator/(T value) const
	{
		_ASSERT(value != 0.0f);

		return Vector3(
			m_x / value,
			m_y / value,
			m_z / value
		);
	}

	template<math::math_type::NumericType T>
	inline Vector3<T>& Vector3<T>::operator-(void)
	{
		m_x = -m_x;
		m_y = -m_y;
		m_z = -m_z;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Vector3<T>& Vector3<T>::operator+=(Vector3 const& vec3)
	{
		*this = *this + vec3;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Vector3<T>& Vector3<T>::operator-=(Vector3 const& vec3)
	{
		*this = *this - vec3;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Vector3<T>& Vector3<T>::operator*=(Vector3 const& vec3)
	{
		*this = *this * vec3;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Vector3<T>& Vector3<T>::operator/=(Vector3 const& vec3)
	{
		*this = *this / vec3;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline bool Vector3<T>::operator==(Vector3 const& vec3) const
	{
		return
			math::AlmostEqual(m_x, vec3.m_x) &&
			math::AlmostEqual(m_y, vec3.m_y) &&
			math::AlmostEqual(m_z, vec3.m_z);
	}

	template<math::math_type::NumericType T>
	inline bool Vector3<T>::operator!=(Vector3 const& vec3) const
	{
		return
			!(math::AlmostEqual(m_x, vec3.m_x) &&
			  math::AlmostEqual(m_y, vec3.m_y) &&
			  math::AlmostEqual(m_z, vec3.m_z));
	}

	template<math::math_type::NumericType T>
	inline T& Vector3<T>::operator[](unsigned int index)
	{
		_ASSERT(index < 4);

		return reinterpret_cast<T*>(this)[index];
	}

	template<math::math_type::NumericType T>
	inline T Vector3<T>::operator[](unsigned int index) const
	{
		_ASSERT(index < 4);

		return reinterpret_cast<const T*>(this)[index];
	}
}

namespace LibMath = math;