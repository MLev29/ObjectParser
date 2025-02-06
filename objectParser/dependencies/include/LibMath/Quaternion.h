#pragma once

#include "LibMath/VariableType.hpp"
#include "LibMath/Arithmetic.h"
#include "LibMath/vector/Vector3.h"

/*
*	-------- Quaternion --------
*	Order:
*	w, x, y, z
*	real (w), imaginary(x,y,z)
* 
*	Constructor:
*	- void					DONE
*	- Scalar				DONE
*	- 4 values				DONE
*	- real + imaginary		DONE
*
*	Functions
*	- IsPure				DONE
*	- IsUnit				DONE
*	- Conjugate				DONE
*	- Rotate point			
*	- Magnitude				DONE
*	- Normalize				DONE
*	- Inverse				DONE
*
*	Operators
*	- Add		(+, +=)		DONE
*	- Subtract	(-, -=)		DONE
*	- Multiply	(*, *=)		DONE
*	- Equality	(==, !=)	DONE
*	- Index		([])		DONE
*/

namespace math
{
	template <math::math_type::NumericType T>
	class Vector3;

	template <math::math_type::NumericType T>
	class Quaternion
	{
	public:
						Quaternion(void);
						Quaternion(T value);
						Quaternion(T w, T x, T y, T z);
						Quaternion(T w, Vector3<T> const& imaginary);

						~Quaternion(void) = default;

		bool			IsPure(void) const;
		bool			IsUnit(void) const;
		Quaternion<T>&	Conjugate(void);
		Quaternion<T>	Rotate(T angle, Vector3<T> const& axis) const;
		T				Magnitude(void) const;
		Quaternion<T>&	Normalize(void);
		Quaternion<T>	Inverse(void) const;

		Quaternion<T>	operator+(Quaternion<T> const& quat) const;
		Quaternion<T>	operator-(Quaternion<T> const& quat) const;
		Quaternion<T>	operator*(Quaternion<T> const& quat) const;
		Quaternion<T>	operator/(Quaternion<T> const& quat) const;
		Quaternion<T>	operator*(T value) const;
		Quaternion<T>	operator/(T value) const;
		Quaternion<T>&	operator+=(Quaternion<T> const& quat);
		Quaternion<T>&	operator-=(Quaternion<T> const& quat);
		Quaternion<T>&	operator*=(Quaternion<T> const& quat);
		Quaternion<T>&	operator*=(T value);
		Quaternion<T>&	operator/=(T value);
		bool			operator==(Quaternion<T> const& quat) const;
		bool			operator!=(Quaternion<T> const& quat) const;
		T				operator[](unsigned int index) const;
		T&				operator[](unsigned int index);

	private:
		Vector3<T> m_imaginary;
		T m_w;
	};

	template<math::math_type::NumericType T>
	inline math::Quaternion<T>::Quaternion(void)
		: m_imaginary((T) 0), m_w((T) 0)
	{
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T>::Quaternion(T value)
		: m_imaginary(value), m_w(value)
	{
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T>::Quaternion(T w,T x, T y, T z)
		: m_imaginary(x, y, z), m_w(w)
	{
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T>::Quaternion(T w, Vector3<T> const& imaginary)
		: m_imaginary(imaginary), m_w(w)
	{
	}

	template<math::math_type::NumericType T>
	inline bool Quaternion<T>::IsPure(void) const
	{
		return m_w == (T) 0.0f;
	}

	template<math::math_type::NumericType T>
	inline bool Quaternion<T>::IsUnit(void) const
	{
		return Magnitude() == 1.0f;
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T>& Quaternion<T>::Conjugate(void)
	{
		m_imaginary = -m_imaginary;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T> Quaternion<T>::Rotate(T angle, Vector3<T> const& axis) const
	{
		/*
			Rotation Quaternion

			|axe| cos (theta / 2), axe * sin(theta / 2)
		*/

		Quaternion<T> result(*this);
		const T length = result.Magnitude();

		if (length - (T) 1 > 0.01f)
		{
			const T denom = 1 / length;
			result *= denom;
		}
		
		const T sinAngle = sinf((angle * DEG2RAD) * 0.5f);
		
		result.m_w = Magnitude() * cosf((angle * DEG2RAD) * 0.5f);
		result.m_imaginary[0] = axis[0] * sinAngle;
		result.m_imaginary[1] = axis[1] * sinAngle;
		result.m_imaginary[2] = axis[2] * sinAngle;

		return result;
	}

	template<math::math_type::NumericType T>
	inline T Quaternion<T>::Magnitude(void) const
	{
		return (T) std::sqrtf(
				m_imaginary.Dot(m_imaginary) +
				m_w * m_w
			);
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T>& Quaternion<T>::Normalize(void)
	{
		const T denom = 1.0f / Magnitude();

		m_imaginary *= denom;
		m_w *= denom;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T> Quaternion<T>::Inverse(void) const
	{
		Quaternion<T> result(*this);
		const T denom = 1.0f / (m_imaginary.Dot(m_imaginary) + m_w * m_w);
		result = result.Conjugate() * denom;

		return result;
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T> Quaternion<T>::operator+(Quaternion<T> const& quat) const
	{
		return Quaternion<T>(
			m_w + quat.m_w,
			m_imaginary + quat.m_imaginary
		);
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T> Quaternion<T>::operator-(Quaternion<T> const& quat) const
	{
		return Quaternion<T>(
			m_w - quat.m_w,
			m_imaginary - quat.m_imaginary
		);
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T> Quaternion<T>::operator*(Quaternion<T> const& quat) const
	{
		Quaternion<T> result;

		result.m_w = (m_w * quat.m_w) - m_imaginary.Dot(quat.m_imaginary);
		result.m_imaginary[0] = (m_w * quat.m_imaginary[0]) + (quat.m_w * m_imaginary[0]) + m_imaginary[1] * quat.m_imaginary[2] - m_imaginary[2] * quat.m_imaginary[1]; // i
		result.m_imaginary[1] = (m_w * quat.m_imaginary[1]) + (quat.m_w * m_imaginary[1]) + m_imaginary[2] * quat.m_imaginary[0] - m_imaginary[0] * quat.m_imaginary[2]; // j
		result.m_imaginary[2] = (m_w * quat.m_imaginary[2]) + (quat.m_w * m_imaginary[2]) + m_imaginary[0] * quat.m_imaginary[1] - m_imaginary[1] * quat.m_imaginary[0]; // k

		return result;
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T> Quaternion<T>::operator/(Quaternion<T> const& quat) const
	{
		Quaternion<T> result(*this);
		Quaternion<T> resultDenom(quat);
		Quaternion<T> conjugate(quat);
		conjugate.Conjugate();

		result = result * conjugate;
		resultDenom = (resultDenom * conjugate) * 0.1f;

		result.m_w *= resultDenom.m_w;
		result.m_imaginary *= resultDenom.m_imaginary;

		return result;
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T> Quaternion<T>::operator*(T value) const
	{
		return Quaternion<T>(m_w * value, m_imaginary * value);
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T> Quaternion<T>::operator/(T value) const
	{
		_ASSERT(value != 0);

		return Quaternion<T>(m_w / value, m_imaginary / value);
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T>& Quaternion<T>::operator+=(Quaternion<T> const& quat)
	{
		*this = *this + quat;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T>& Quaternion<T>::operator-=(Quaternion<T> const& quat)
	{
		*this = *this - quat;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T>& Quaternion<T>::operator*=(Quaternion<T> const& quat)
	{
		*this = *this * quat;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T>& Quaternion<T>::operator*=(T value)
	{
		return *this = *this * value;
	}

	template<math::math_type::NumericType T>
	inline Quaternion<T>& Quaternion<T>::operator/=(T value)
	{
		return *this = *this / value;
	}

	template<math::math_type::NumericType T>
	inline bool Quaternion<T>::operator==(Quaternion<T> const& quat) const
	{
		return
			m_imaginary == quat.m_imaginary &&
			AlmostEqual(m_w, quat.m_w);
	}

	template<math::math_type::NumericType T>
	inline bool Quaternion<T>::operator!=(Quaternion<T> const& quat) const
	{
		return !(*this == quat);
	}

	template<math::math_type::NumericType T>
	inline T Quaternion<T>::operator[](unsigned int index) const
	{
		_ASSERT(index < 4);

		return index > 0 ? m_imaginary[index - 1] : m_w;
	}

	template<math::math_type::NumericType T>
	inline T& Quaternion<T>::operator[](unsigned int index)
	{
		_ASSERT(index < 4);

		return index > 0 ? m_imaginary[index - 1] : m_w;
	}
}

namespace LibMath = math;