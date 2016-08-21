#pragma once
#include "../Constans.h"
#include "Vector3f.h"

namespace Math
{
	class Matrix3
	{

	public:
		Matrix3() {}
		Matrix3(float m11, float m12, float m13,
			float m21, float m22, float m23,
			float m31, float m32, float m33);
		~Matrix3() {}

		float *operator[](int row);
		const float *operator[](int row) const;

		inline Matrix3 &operator*(const Matrix3 &rhs);
		Vector3f operator*(const Vector3f &lhs);
		Matrix3 &operator*(float scalar);

		float det();
		void transpond();
		bool inverse();
	private:
		float mtx[3][3];
	};

	inline Matrix3::Matrix3(float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33)
	{
		mtx[0][0] = m11, mtx[0][1] = m12, mtx[0][2] = m13,
			mtx[1][0] = m21, mtx[1][1] = m22, mtx[1][2] = m23,
			mtx[2][0] = m31, mtx[2][1] = m32, mtx[2][2] = m33;
	}

	inline float *Matrix3::operator[](int row)
	{
		return mtx[row];
	}

	inline const float *Matrix3::operator[](int row) const
	{
		return mtx[row];
	}


	inline Matrix3 &Matrix3::operator*(const Matrix3 &rhs)
	{
		Matrix3 tmp;

		// Row 1.
		tmp.mtx[0][0] = (mtx[0][0] * rhs.mtx[0][0]) + (mtx[0][1] * rhs.mtx[1][0]) + (mtx[0][2] * rhs.mtx[2][0]);
		tmp.mtx[0][1] = (mtx[0][0] * rhs.mtx[0][1]) + (mtx[0][1] * rhs.mtx[1][1]) + (mtx[0][2] * rhs.mtx[2][1]);
		tmp.mtx[0][2] = (mtx[0][0] * rhs.mtx[0][2]) + (mtx[0][1] * rhs.mtx[1][2]) + (mtx[0][2] * rhs.mtx[2][2]);

		// Row 2.
		tmp.mtx[1][0] = (mtx[1][0] * rhs.mtx[0][0]) + (mtx[1][1] * rhs.mtx[1][0]) + (mtx[1][2] * rhs.mtx[2][0]);
		tmp.mtx[1][1] = (mtx[1][0] * rhs.mtx[0][1]) + (mtx[1][1] * rhs.mtx[1][1]) + (mtx[1][2] * rhs.mtx[2][1]);
		tmp.mtx[1][2] = (mtx[1][0] * rhs.mtx[0][2]) + (mtx[1][1] * rhs.mtx[1][2]) + (mtx[1][2] * rhs.mtx[2][2]);

		// Row 3.
		tmp.mtx[2][0] = (mtx[2][0] * rhs.mtx[0][0]) + (mtx[2][1] * rhs.mtx[1][0]) + (mtx[2][2] * rhs.mtx[2][0]);
		tmp.mtx[2][1] = (mtx[2][0] * rhs.mtx[0][1]) + (mtx[2][1] * rhs.mtx[1][1]) + (mtx[2][2] * rhs.mtx[2][1]);
		tmp.mtx[2][2] = (mtx[2][0] * rhs.mtx[0][2]) + (mtx[2][1] * rhs.mtx[1][2]) + (mtx[2][2] * rhs.mtx[2][2]);

		*this = tmp;
		return *this;
	}
	inline Vector3f Matrix3::operator*(const Vector3f &lhs)
	{
		return Vector3f((lhs.x *mtx[0][0]) + (lhs.y * mtx[1][0]) + (lhs.z * mtx[2][0]),
			(lhs.x * mtx[0][1]) + (lhs.y * mtx[1][1]) + (lhs.z * mtx[2][1]),
			(lhs.x * mtx[0][2]) + (lhs.y * mtx[1][2]) + (lhs.z * mtx[2][2]));
	}


	inline Matrix3 &Matrix3::operator*(float scalar)
	{
		mtx[0][0] *= scalar, mtx[0][1] *= scalar, mtx[0][2] *= scalar,
			mtx[1][0] *= scalar, mtx[1][1] *= scalar, mtx[1][2] *= scalar,
			mtx[2][0] *= scalar, mtx[2][1] *= scalar, mtx[2][2] *= scalar;
		return *this;
	}

	inline float Matrix3::det()
	{
		return mtx[0][0] * mtx[1][1] * mtx[2][2] + mtx[0][1] * mtx[1][2] * mtx[2][0] + mtx[0][2] * mtx[1][0] * mtx[2][1]
			- mtx[0][0] * mtx[1][2] * mtx[2][1] - mtx[0][1] * mtx[1][0] * mtx[2][2] - mtx[0][2] * mtx[1][1] * mtx[2][0];
	}

	inline void Matrix3::transpond()
	{
		float c;
		for (int i = 0; i < 3; i++)
			for (int j = i + 1; j < 3; j++)
			{
				c = mtx[j][i];
				mtx[j][i] = mtx[i][j];
				mtx[i][j] = c;
			}
	}

	inline bool Matrix3::inverse()
	{
		float det = this->det();
		if (det != 0)
		{
			float a00 = mtx[1][1] * mtx[2][2] - mtx[2][1] * mtx[1][2];
			a00 *= 1.0f;
			float a01 = mtx[1][0] * mtx[2][2] - mtx[2][0] * mtx[1][2];
			a01 *= -1.0f;
			float a02 = mtx[1][0] * mtx[2][1] - mtx[2][0] * mtx[1][1];
			a02 *= 1.0f;
			float a10 = mtx[0][1] * mtx[2][2] - mtx[2][1] * mtx[0][2];
			a10 *= -1.0f;
			float a11 = mtx[0][0] * mtx[2][2] - mtx[2][0] * mtx[0][2];
			a11 *= 1.0f;
			float a12 = mtx[0][0] * mtx[2][1] - mtx[2][0] * mtx[0][1];
			a12 *= -1.0f;
			float a20 = mtx[0][1] * mtx[1][2] - mtx[1][1] * mtx[0][2];
			a20 *= 1.0f;
			float a21 = mtx[0][0] * mtx[1][2] - mtx[1][0] * mtx[0][2];
			a21 *= -1.0f;
			float a22 = mtx[0][0] * mtx[1][1] - mtx[1][0] * mtx[0][1];
			a22 *= 1.0f;
			//Matrix3 S(a00, a01, a02, a10, a11, a12, a20, a21, a22);

			mtx[0][0] = a00, mtx[0][1] = a01, mtx[0][2] = a02,
				mtx[1][0] = a10, mtx[1][1] = a11, mtx[1][2] = a12,
				mtx[2][0] = a20, mtx[2][1] = a21, mtx[2][2] = a22;
			transpond();
			operator*(1.0f / det);
			return true;
		}
		else
			return false;
	}

}