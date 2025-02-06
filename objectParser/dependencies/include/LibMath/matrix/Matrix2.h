#pragma once

#include "LibMath/Macros.h"
#include "LibMath/Arithmetic.h"
#include "LibMath/VariableType.hpp"

#include <cmath>

/*
*	================= Matrix 2D =================
*	Column / Row major
*
*	Constructor
*	- void				DONE
*	- Scalar			DONE
*	- X, Y, Z, W		DONE
*
*	Static Functions
*	- Zero				DONE
*	- One				DONE
*	
*	Functions
*	- Identity			DONE
*	- Transpose			DONE
*	- Determinant		DONE
*	- Minor				DONE
*	- Cofactor			DONE
*	- Adjugate			DONE
*	- Inverse			
*
*	Operators
*	- Addition			DONE
*	- Subtraction		DONE
*	- Multiplication	DONE
*		->	Scalar		DONE
*		->	Matrix		DONE
*	- Division (scalar) DONE
*	=================================================
*/

/*
*	================= Matrix Config =================
*
*	The 2x2 matrix class supports both column & row major.
*	By default the class uses row major however this can be
*	overwritten by defining the 'COLUMN_MAJOR' macro.
*
*	Example:
*	#define COLUMN_MAJOR
*	=================================================
*/

namespace math
{
	// Forward declaration for matrix3 minor function
	template<math::math_type::NumericType T>
	class Matrix3;

	template<math::math_type::NumericType T>
	class Matrix2
	{
	public:
							Matrix2(void);
							Matrix2(T value);
							Matrix2(T x, T y, T z, T w);

							~Matrix2(void) = default;

		static Matrix2<T>	Zero(void);
		static Matrix2<T>	One(void);
		static Matrix2<T>	Identity(T scalar);

		Matrix2<T>&			GetMatrix2(Matrix3<T> const& matrix, int row, int column);
		Matrix2<T>&			Transpose(void);
		T					Determinant(void);
		Matrix2<T>&			Minor(void);
		Matrix2<T>&			Cofactor(void);
		Matrix2<T>&			Adjugate(void);
		Matrix2<T>&			Inverse(void);

		Matrix2<T>			operator+(Matrix2<T> const& matrix);
		Matrix2<T>			operator-(Matrix2<T> const& matrix);
		Matrix2<T>			operator*(Matrix2<T> const& matrix);
		Matrix2<T>			operator*(T const& scalar);
		Matrix2<T>			operator/(T const& scalar);
		Matrix2<T>&			operator+=(Matrix2<T> const& matrix);
		Matrix2<T>&			operator-=(Matrix2<T> const& matrix);
		Matrix2<T>&			operator*=(Matrix2<T> const& matrix);
		Matrix2<T>&			operator*=(T const& scalar);
		Matrix2<T>&			operator/=(T const& scalar);

		bool				operator==(Matrix2<T> const& matrix) const noexcept;
		bool				operator!=(Matrix2<T> const& matrix) const noexcept;

		T m_matrix[2][2];
	};

	template<math::math_type::NumericType T>
	inline math::Matrix2<T>::Matrix2(void)
	{
		*this = Identity(1);
	}

	template<math::math_type::NumericType T>
	inline math::Matrix2<T>::Matrix2(T value)
	{
		*this = Identity(value);
	}

	template<math::math_type::NumericType T>
	inline math::Matrix2<T>::Matrix2(T x, T y, T z, T w)
	{
		m_matrix[0][0] = x;
		m_matrix[0][1] = y;
		m_matrix[1][0] = z;
		m_matrix[1][1] = w;

#ifdef COLUMN_MAJOR
		m_matrix[0][1] = z;
		m_matrix[1][0] = y;
#endif
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::Zero(void)
	{
		return Matrix2<T>(0, 0, 0, 0);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::One(void)
	{
		return Matrix2<T>(1, 1, 1, 1);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::Identity(T scalar)
	{
		return Matrix2<T>(scalar, 0, 0, scalar);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::GetMatrix2(Matrix3<T> const& matrix, int row, int column)
	{
		int currentRow = 0;
		int currentColumn = 0;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (i == row || j == column)
					continue;

				m_matrix[currentRow][currentColumn] = matrix.m_matrix[i][j];
				++currentColumn;
			}

			if (i != row)
			{
				++currentRow;
				currentColumn = 0;
			}
		}

		return *this;
	}

	template<math::math_type::NumericType T>
	inline math::Matrix2<T>& Matrix2<T>::Transpose(void)
	{
		T tmp = m_matrix[0][1];

		m_matrix[0][1] = m_matrix[1][0];
		m_matrix[1][0] = tmp;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline T Matrix2<T>::Determinant(void)
	{
		/*
		*	Determinant of 2x2 matrix
		*
		*	|a b|
		*	|c d|
		*
		*	formula:
		*	Determinant = (a * d) - (b * c)
		*/

		return (m_matrix[0][0] * m_matrix[1][1]) - (m_matrix[0][1] * m_matrix[1][0]);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::Minor(void)
	{
		Matrix2<T> tmp(*this);

		m_matrix[0][0] = tmp.m_matrix[1][1];
		m_matrix[0][1] = tmp.m_matrix[1][0];
		m_matrix[1][0] = tmp.m_matrix[0][1];
		m_matrix[1][1] = tmp.m_matrix[0][0];

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::Cofactor(void)
	{
		this->Minor();

		m_matrix[0][1] = -m_matrix[0][1];
		m_matrix[1][0] = -m_matrix[1][0];

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::Adjugate(void)
	{
		this->Cofactor();
		this->Transpose();

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::Inverse(void)
	{
		T determinant = Determinant();
		
		if (determinant == 0)
			return *this;

		*this = Adjugate() / determinant;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::operator+(Matrix2<T> const& matrix)
	{
		return Matrix2<T>(
			m_matrix[0][0] + matrix.m_matrix[0][0], m_matrix[0][1] + matrix.m_matrix[0][1],
			m_matrix[1][0] + matrix.m_matrix[1][0], m_matrix[1][1] + matrix.m_matrix[1][1]
		);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::operator-(Matrix2<T> const& matrix)
	{
		return Matrix2<T>(
			m_matrix[0][0] - matrix.m_matrix[0][0], m_matrix[0][1] - matrix.m_matrix[0][1],
			m_matrix[1][0] - matrix.m_matrix[1][0], m_matrix[1][1] - matrix.m_matrix[1][1]
		);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::operator*(Matrix2<T> const& matrix)
	{
		return Matrix2<T>(
			m_matrix[0][0] * matrix.m_matrix[0][0] + m_matrix[1][0] * matrix.m_matrix[0][1],
			m_matrix[0][1] * matrix.m_matrix[0][0] + m_matrix[1][1] * matrix.m_matrix[0][1],
			m_matrix[0][0] * matrix.m_matrix[1][0] + m_matrix[1][0] * matrix.m_matrix[1][1],
			m_matrix[0][1] * matrix.m_matrix[1][0] + m_matrix[1][1] * matrix.m_matrix[1][1]
		);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::operator*(T const& scalar)
	{
		return Matrix2<T>(
			m_matrix[0][0] * scalar, m_matrix[0][1] * scalar,
			m_matrix[1][0] * scalar, m_matrix[1][1] * scalar
		);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T> Matrix2<T>::operator/(T const& scalar)
	{
		return Matrix2<T>(
			m_matrix[0][0] / scalar, m_matrix[0][1] / scalar,
			m_matrix[1][0] / scalar, m_matrix[1][1] / scalar
		);
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::operator+=(Matrix2<T> const& matrix)
	{
		*this = *this + matrix;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::operator-=(Matrix2<T> const& matrix)
	{
		*this = *this - matrix;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::operator*=(Matrix2<T> const& matrix)
	{
		*this = *this * matrix;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::operator*=(T const& scalar)
	{
		*this = *this * scalar;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix2<T>& Matrix2<T>::operator/=(T const& scalar)
	{
		*this = *this / scalar;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline bool Matrix2<T>::operator==(Matrix2<T> const& matrix) const noexcept
	{
		return
			AlmostEqual(m_matrix[0][0], matrix.m_matrix[0][0]) &&
			AlmostEqual(m_matrix[0][1], matrix.m_matrix[0][1]) &&
			AlmostEqual(m_matrix[1][0], matrix.m_matrix[1][0]) &&
			AlmostEqual(m_matrix[1][1], matrix.m_matrix[1][1]);
	}

	template<math::math_type::NumericType T>
	inline bool Matrix2<T>::operator!=(Matrix2<T> const& matrix) const noexcept
	{
		return
			!(	AlmostEqual(m_matrix[0][0], matrix.m_matrix[0][0]) &&
				AlmostEqual(m_matrix[0][1], matrix.m_matrix[0][1]) &&
				AlmostEqual(m_matrix[1][0], matrix.m_matrix[1][0]) &&
				AlmostEqual(m_matrix[1][1], matrix.m_matrix[1][1]));
	}
}

namespace LibMath = math;