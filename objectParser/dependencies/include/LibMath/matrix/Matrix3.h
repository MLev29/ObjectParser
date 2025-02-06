#pragma once

#include "LibMath/angle/Radians.h"
#include "LibMath/Arithmetic.h"
#include "LibMath/Macros.h"
#include "LibMath/VariableType.hpp"
#include "LibMath/matrix/Matrix2.h"

#include "Matrix4.h"
#include <cmath>

/*
*	Matrix3
*
*	Constructors
*	- Void			DONE
*	- Scalar		DONE
*	- Array			DONE
*
*	Functions
*	- Transpose		DONE
*	- Identity		DONE
*	- Determinant	DONE
*	- Minor			DONE
*	- Cofactor		DONE
*	- Adjugate		DONE
*	- Inverse		DONE
*
*	Transformation
*	- Rotation		DONE
*
*	Operators
*	- equal 3x3 array		DONE
*	- Addition				DONE
*	- Subtraction			DONE
*	- Multiplication		DONE
*	- Division (scalar)		DONE
*	- Equality				DONE
*	- Inverse equality		DONE
* 
*/

namespace math
{
	template<math::math_type::NumericType T>
	class Matrix4;

	template<math::math_type::NumericType T>
	class Matrix3
	{
	public:
							Matrix3(void);
							Matrix3(T scalar);
							Matrix3(T const arr[9]);

							~Matrix3(void) = default;

				Matrix3<T>&	GetMatrix3(Matrix4<T> const& matrix, int row, int column);
				Matrix3<T>&	Transpose(void);
		static	Matrix3<T>	Identity(void);
				T			Determinant(void);
				Matrix3<T>&	Minor(void);
				Matrix3<T>&	Cofactor(void);
				Matrix3<T>&	Adjugate(void);
				Matrix3<T>&	Inverse(void);

		static	Matrix3<T>	RollPitchYawRotation(Radian<T> const& thetaX, Radian<T> const& thetaY, Radian<T> const& thetaZ);

				Matrix3<T>&	operator=(const T arr[][3]);
				Matrix3<T>&	operator=(const T arr[9]);
				Matrix3<T>	operator+(Matrix3<T> const& matrix);
				Matrix3<T>	operator-(Matrix3<T> const& matrix);
				Matrix3<T>	operator*(Matrix3<T> const& matrix);
				Matrix3<T>	operator*(T scalar);
				Matrix3<T>	operator/(T scalar);
				Matrix3<T>&	operator+=(Matrix3<T> const& matrix);
				Matrix3<T>&	operator-=(Matrix3<T> const& matrix);
				Matrix3<T>&	operator*=(Matrix3<T> const& matrix);
				Matrix3<T>&	operator*=(T scalar);
				Matrix3<T>&	operator/=(T scalar);

				bool		operator==(Matrix3<T> const& matrix) const noexcept;
				bool		operator!=(Matrix3<T> const& matrix) const noexcept;

		T m_matrix[3][3];
	};


	template<math::math_type::NumericType T>
	inline Matrix3<T>::Matrix3(void)
	{
		m_matrix[0][0] = 1; m_matrix[0][1] = 0; m_matrix[0][2] = 0;
		m_matrix[1][0] = 0; m_matrix[1][1] = 1; m_matrix[1][2] = 0;
		m_matrix[2][0] = 0; m_matrix[2][1] = 0; m_matrix[2][2] = 1;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T>::Matrix3(T scalar)
	{
		*this = Matrix3<T>() * scalar;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T>::Matrix3(T const arr[9])
	{
#ifndef COLUMN_MAJOR
		m_matrix[0][0] = arr[0]; m_matrix[0][1] = arr[1]; m_matrix[0][2] = arr[2];
		m_matrix[1][0] = arr[3]; m_matrix[1][1] = arr[4]; m_matrix[1][2] = arr[5];
		m_matrix[2][0] = arr[6]; m_matrix[2][1] = arr[7]; m_matrix[2][2] = arr[8];
#else
		m_matrix[0][0] = arr[0]; m_matrix[0][1] = arr[3]; m_matrix[0][2] = arr[6];
		m_matrix[1][0] = arr[1]; m_matrix[1][1] = arr[4]; m_matrix[1][2] = arr[7];
		m_matrix[2][0] = arr[2]; m_matrix[2][1] = arr[5]; m_matrix[2][2] = arr[8];
#endif
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T>& Matrix3<T>::GetMatrix3(Matrix4<T> const& matrix, int row, int column)
	{
		int currentRow = 0;
		int currentColumn = 0;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
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
	inline Matrix3<T>& math::Matrix3<T>::Transpose(void)
	{
		const Matrix3<T> tmp = *this;

		m_matrix[0][1] = tmp.m_matrix[1][0];
		m_matrix[0][2] = tmp.m_matrix[2][0];
		m_matrix[1][0] = tmp.m_matrix[0][1];
		m_matrix[1][2] = tmp.m_matrix[2][1];
		m_matrix[2][0] = tmp.m_matrix[0][2];
		m_matrix[2][1] = tmp.m_matrix[1][2];

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T> math::Matrix3<T>::Identity(void)
	{
		return math::Matrix3<T>();
	}

	template<math::math_type::NumericType T>
	inline T Matrix3<T>::Determinant(void)
	{
		/*
		*	Split 3x3 matrix into 3 2x2 matrix and multiply by the coefficient
		*
		*	Equation:
		*	|a b c|
		*	|d e f|
		*	|g h i|
		*
		*	Determinant = a(ei - fh) - b(di - gf) + c(dh - eg)
		*/

		T a = m_matrix[0][0] * ((m_matrix[1][1] * m_matrix[2][2]) - (m_matrix[1][2] * m_matrix[2][1]));
		T b = m_matrix[0][1] * ((m_matrix[1][0] * m_matrix[2][2]) - (m_matrix[2][0] * m_matrix[1][2]));
		T c = m_matrix[0][2] * ((m_matrix[1][0] * m_matrix[2][1]) - (m_matrix[1][1] * m_matrix[2][0]));

		return a - b + c;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T>& Matrix3<T>::Minor(void)
	{
		/*
		*	Minor: set each value in the given 3x3 matrix equal to the determinant
		*	of a 2x2 matrix
		*/
		
		Matrix2<T> matrix2;
		const Matrix3<T> tmp(*this);

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				matrix2.GetMatrix2(tmp, i, j);

				T determinant = matrix2.Determinant();

				m_matrix[i][j] = determinant;
			}
		}

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T>& Matrix3<T>::Cofactor(void)
	{
		this->Minor();

		m_matrix[0][1] = -m_matrix[0][1];
		m_matrix[1][0] = -m_matrix[1][0];
		m_matrix[1][2] = -m_matrix[1][2];
		m_matrix[2][1] = -m_matrix[2][1];

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T>& Matrix3<T>::Adjugate(void)
	{
		this->Cofactor();
		this->Transpose();

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T>& math::Matrix3<T>::Inverse(void)
	{
		/*
		*	The inverse of a matrix is equal to the adjugate of the matrix
		*	divided by the determinant
		*/
		
		T determinant = this->Determinant();

		if (determinant == 0)
			return *this;

		this->Adjugate();

		*this /= determinant;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline math::Matrix3<T> math::Matrix3<T>::RollPitchYawRotation(Radian<T> const& thetaX, Radian<T> const& thetaY, Radian<T> const& thetaZ)
	{
		// Convert radian values to float
		static const T halfPi = PI * 0.5f;

		// Calculate sin & cos for yaw, pitch & roll
		T sinYaw = sinf(thetaX);
		T sinPitch = sinf(thetaY);
		T sinRoll = sinf(thetaZ);

		// Instead of calculating cos we add an offset to sin 
		T cosYaw = sinYaw + halfPi;
		T cosPitch = sinPitch + halfPi;
		T cosRoll = sinRoll + halfPi;

		// Create array & calculate values for rotation matrix
		T matrixValues[9] =
		{
			 cosYaw * cosRoll + sinYaw * sinPitch * sinRoll,	-cosYaw * sinRoll + sinYaw * sinPitch * cosRoll,		 sinYaw * cosPitch,
			 sinRoll * cosPitch,								 cosRoll * cosPitch,									-sinPitch,
			-sinYaw * cosRoll + cosYaw * sinPitch * sinRoll,	 sinRoll * sinYaw + cosYaw * sinPitch * cosRoll,		 cosYaw * cosPitch
		};

		// Initialize & return 3x3 matrix using array
		return Matrix3<T>(matrixValues);
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T>& math::Matrix3<T>::operator=(const T arr[][3])
	{
		m_matrix[0][0] = arr[0][0]; m_matrix[0][1] = arr[0][1]; m_matrix[0][2] = arr[0][2];
		m_matrix[1][0] = arr[1][0]; m_matrix[1][1] = arr[1][1]; m_matrix[1][2] = arr[1][2];
		m_matrix[2][0] = arr[2][0]; m_matrix[2][1] = arr[2][1]; m_matrix[2][2] = arr[2][2];

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T>& Matrix3<T>::operator=(const T arr[9])
	{
		m_matrix[0][0] = arr[0]; m_matrix[0][1] = arr[1]; m_matrix[0][2] = arr[2];
		m_matrix[1][0] = arr[3]; m_matrix[1][1] = arr[4]; m_matrix[1][2] = arr[5];
		m_matrix[2][0] = arr[6]; m_matrix[2][1] = arr[7]; m_matrix[2][2] = arr[8];

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T> Matrix3<T>::operator+(Matrix3<T> const& matrix)
	{
		Matrix3<T> result(*this);

		result.m_matrix[0][0] += matrix.m_matrix[0][0]; result.m_matrix[0][1] += matrix.m_matrix[0][1]; result.m_matrix[0][2] += matrix.m_matrix[0][2];
		result.m_matrix[1][0] += matrix.m_matrix[1][0]; result.m_matrix[1][1] += matrix.m_matrix[1][1]; result.m_matrix[1][2] += matrix.m_matrix[1][2];
		result.m_matrix[2][0] += matrix.m_matrix[2][0]; result.m_matrix[2][1] += matrix.m_matrix[2][1]; result.m_matrix[2][2] += matrix.m_matrix[2][2];

		return result;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T> Matrix3<T>::operator-(Matrix3<T> const& matrix)
	{
		Matrix3<T> result(*this);

		result.m_matrix[0][0] -= matrix.m_matrix[0][0]; result.m_matrix[0][1] -= matrix.m_matrix[0][1]; result.m_matrix[0][2] -= matrix.m_matrix[0][2];
		result.m_matrix[1][0] -= matrix.m_matrix[1][0]; result.m_matrix[1][1] -= matrix.m_matrix[1][1]; result.m_matrix[1][2] -= matrix.m_matrix[1][2];
		result.m_matrix[2][0] -= matrix.m_matrix[2][0]; result.m_matrix[2][1] -= matrix.m_matrix[2][1]; result.m_matrix[2][2] -= matrix.m_matrix[2][2];

		return result;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T> Matrix3<T>::operator*(Matrix3<T> const& matrix)
	{
		// Initialize null 3x3 matrix
		Matrix3<T> result((T) 0);
		
		// Iterate through matrix to set the result matrix equal to the sum of the 2 matrices multiplied
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					// Add the value obtained from multiplying the 2 matrices row * column
					result.m_matrix[i][j] += m_matrix[i][k] * matrix.m_matrix[k][j];
				}
			}
		}
		
		return result;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T> Matrix3<T>::operator*(T scalar)
	{
		Matrix3<T> result(*this);

		result.m_matrix[0][0] *= scalar; result.m_matrix[0][1] *= scalar; result.m_matrix[0][2] *= scalar;
		result.m_matrix[1][0] *= scalar; result.m_matrix[1][1] *= scalar; result.m_matrix[1][2] *= scalar;
		result.m_matrix[2][0] *= scalar; result.m_matrix[2][1] *= scalar; result.m_matrix[2][2] *= scalar;

		return result;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T> Matrix3<T>::operator/(T scalar)
	{
		Matrix3<T> result(*this);

		result.m_matrix[0][0] /= scalar; result.m_matrix[0][1] /= scalar; result.m_matrix[0][2] /= scalar;
		result.m_matrix[1][0] /= scalar; result.m_matrix[1][1] /= scalar; result.m_matrix[1][2] /= scalar;
		result.m_matrix[2][0] /= scalar; result.m_matrix[2][1] /= scalar; result.m_matrix[2][2] /= scalar;

		return result;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T>& Matrix3<T>::operator+=(Matrix3<T> const& matrix)
	{
		*this = *this + matrix;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T>& Matrix3<T>::operator-=(Matrix3<T> const& matrix)
	{
		*this = *this - matrix;
		
		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T>& Matrix3<T>::operator*=(Matrix3<T> const& matrix)
	{
		*this = *this * matrix;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T>& Matrix3<T>::operator*=(T scalar)
	{
		*this = *this * scalar;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline Matrix3<T>& Matrix3<T>::operator/=(T scalar)
	{
		*this = *this / scalar;

		return *this;
	}

	template<math::math_type::NumericType T>
	inline bool Matrix3<T>::operator==(Matrix3<T> const& matrix) const noexcept
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (!AlmostEqual(m_matrix[i][j], matrix.m_matrix[i][j]))
				{
					return false;
				}
			}
		}

		return true;
	}

	template<math::math_type::NumericType T>
	inline bool Matrix3<T>::operator!=(Matrix3<T> const& matrix) const noexcept
	{
		return !(*this == matrix);
	}
}

namespace LibMath = math;