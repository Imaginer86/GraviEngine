#pragma once
//-----------------------------------------------------------------------------
// A homogeneous row-major 4x4 matrix class.
//
// Matrices are concatenated in a left to right order.
// Multiplies Vector3s to the left of the matrix.
//-----------------------------------------------------------------------------

//#define  _USE_MATH_DEFINES
//#include <math.h>

#include "Math.h"

class Matrix4
{
	friend Vector3 operator*(const Vector3 &lhs, const Matrix4 &rhs);
	friend Matrix4 operator*(float scalar, const Matrix4 &rhs);

public:
	static const Matrix4 IDENTITY;

	Matrix4() {}
	Matrix4(float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44);
	~Matrix4() {}

	float *operator[](int row);
	const float *operator[](int row) const;

	bool operator==(const Matrix4 &rhs) const;
	bool operator!=(const Matrix4 &rhs) const;

	Matrix4 &operator+=(const Matrix4 &rhs);
	Matrix4 &operator-=(const Matrix4 &rhs);
	Matrix4 &operator*=(const Matrix4 &rhs);
	Matrix4 &operator*=(float scalar);
	Matrix4 &operator/=(float scalar);

	Matrix4 operator+(const Matrix4 &rhs) const;
	Matrix4 operator-(const Matrix4 &rhs) const;
	Matrix4 operator*(const Matrix4 &rhs) const;
	Matrix4 operator*(float scalar) const;
	Matrix4 operator/(float scalar) const;

	void fromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees);
	void identity();
	void rotate(const Vector3 &axis, float degrees);
	void toHeadPitchRoll(float &headDegrees, float &pitchDegrees, float &rollDegrees) const;

private:
	float mtx[4][4];
};

inline Vector3 operator*(const Vector3 &lhs, const Matrix4 &rhs)
{
	return Vector3((lhs.x * rhs.mtx[0][0]) + (lhs.y * rhs.mtx[1][0]) + (lhs.z * rhs.mtx[2][0]),
		(lhs.x * rhs.mtx[0][1]) + (lhs.y * rhs.mtx[1][1]) + (lhs.z * rhs.mtx[2][1]),
		(lhs.x * rhs.mtx[0][2]) + (lhs.y * rhs.mtx[1][2]) + (lhs.z * rhs.mtx[2][2]));
}

inline Matrix4 operator*(float scalar, const Matrix4 &rhs)
{
	return rhs * scalar;
}

inline Matrix4::Matrix4(float m11, float m12, float m13, float m14,
						float m21, float m22, float m23, float m24,
						float m31, float m32, float m33, float m34,
						float m41, float m42, float m43, float m44)
{
	mtx[0][0] = m11, mtx[0][1] = m12, mtx[0][2] = m13, mtx[0][3] = m14;
	mtx[1][0] = m21, mtx[1][1] = m22, mtx[1][2] = m23, mtx[1][3] = m24;
	mtx[2][0] = m31, mtx[2][1] = m32, mtx[2][2] = m33, mtx[2][3] = m34;
	mtx[3][0] = m41, mtx[3][1] = m42, mtx[3][2] = m43, mtx[3][3] = m44;
}

inline float *Matrix4::operator[](int row)
{
	return mtx[row];
}

inline const float *Matrix4::operator[](int row) const
{
	return mtx[row];
}

inline bool Matrix4::operator==(const Matrix4 &rhs) const
{
	return Math::closeEnough(mtx[0][0], rhs.mtx[0][0])
		&& Math::closeEnough(mtx[0][1], rhs.mtx[0][1])
		&& Math::closeEnough(mtx[0][2], rhs.mtx[0][2])
		&& Math::closeEnough(mtx[0][3], rhs.mtx[0][3])
		&& Math::closeEnough(mtx[1][0], rhs.mtx[1][0])
		&& Math::closeEnough(mtx[1][1], rhs.mtx[1][1])
		&& Math::closeEnough(mtx[1][2], rhs.mtx[1][2])
		&& Math::closeEnough(mtx[1][3], rhs.mtx[1][3])
		&& Math::closeEnough(mtx[2][0], rhs.mtx[2][0])
		&& Math::closeEnough(mtx[2][1], rhs.mtx[2][1])
		&& Math::closeEnough(mtx[2][2], rhs.mtx[2][2])
		&& Math::closeEnough(mtx[2][3], rhs.mtx[2][3])
		&& Math::closeEnough(mtx[3][0], rhs.mtx[3][0])
		&& Math::closeEnough(mtx[3][1], rhs.mtx[3][1])
		&& Math::closeEnough(mtx[3][2], rhs.mtx[3][2])
		&& Math::closeEnough(mtx[3][3], rhs.mtx[3][3]);
}

inline bool Matrix4::operator!=(const Matrix4 &rhs) const
{
	return !(*this == rhs);
}

inline Matrix4 &Matrix4::operator+=(const Matrix4 &rhs)
{
	mtx[0][0] += rhs.mtx[0][0], mtx[0][1] += rhs.mtx[0][1], mtx[0][2] += rhs.mtx[0][2], mtx[0][3] += rhs.mtx[0][3];
	mtx[1][0] += rhs.mtx[1][0], mtx[1][1] += rhs.mtx[1][1], mtx[1][2] += rhs.mtx[1][2], mtx[1][3] += rhs.mtx[1][3];
	mtx[2][0] += rhs.mtx[2][0], mtx[2][1] += rhs.mtx[2][1], mtx[2][2] += rhs.mtx[2][2], mtx[2][3] += rhs.mtx[2][3];
	mtx[3][0] += rhs.mtx[3][0], mtx[3][1] += rhs.mtx[3][1], mtx[3][2] += rhs.mtx[3][2], mtx[3][3] += rhs.mtx[3][3];
	return *this;
}

inline Matrix4 &Matrix4::operator-=(const Matrix4 &rhs)
{
	mtx[0][0] -= rhs.mtx[0][0], mtx[0][1] -= rhs.mtx[0][1], mtx[0][2] -= rhs.mtx[0][2], mtx[0][3] -= rhs.mtx[0][3];
	mtx[1][0] -= rhs.mtx[1][0], mtx[1][1] -= rhs.mtx[1][1], mtx[1][2] -= rhs.mtx[1][2], mtx[1][3] -= rhs.mtx[1][3];
	mtx[2][0] -= rhs.mtx[2][0], mtx[2][1] -= rhs.mtx[2][1], mtx[2][2] -= rhs.mtx[2][2], mtx[2][3] -= rhs.mtx[2][3];
	mtx[3][0] -= rhs.mtx[3][0], mtx[3][1] -= rhs.mtx[3][1], mtx[3][2] -= rhs.mtx[3][2], mtx[3][3] -= rhs.mtx[3][3];
	return *this;
}

inline Matrix4 &Matrix4::operator*=(const Matrix4 &rhs)
{
	Matrix4 tmp;

	// Row 1.
	tmp.mtx[0][0] = (mtx[0][0] * rhs.mtx[0][0]) + (mtx[0][1] * rhs.mtx[1][0]) + (mtx[0][2] * rhs.mtx[2][0]) + (mtx[0][3] * rhs.mtx[3][0]);
	tmp.mtx[0][1] = (mtx[0][0] * rhs.mtx[0][1]) + (mtx[0][1] * rhs.mtx[1][1]) + (mtx[0][2] * rhs.mtx[2][1]) + (mtx[0][3] * rhs.mtx[3][1]);
	tmp.mtx[0][2] = (mtx[0][0] * rhs.mtx[0][2]) + (mtx[0][1] * rhs.mtx[1][2]) + (mtx[0][2] * rhs.mtx[2][2]) + (mtx[0][3] * rhs.mtx[3][2]);
	tmp.mtx[0][3] = (mtx[0][0] * rhs.mtx[0][3]) + (mtx[0][1] * rhs.mtx[1][3]) + (mtx[0][2] * rhs.mtx[2][3]) + (mtx[0][3] * rhs.mtx[3][3]);

	// Row 2.
	tmp.mtx[1][0] = (mtx[1][0] * rhs.mtx[0][0]) + (mtx[1][1] * rhs.mtx[1][0]) + (mtx[1][2] * rhs.mtx[2][0]) + (mtx[1][3] * rhs.mtx[3][0]);
	tmp.mtx[1][1] = (mtx[1][0] * rhs.mtx[0][1]) + (mtx[1][1] * rhs.mtx[1][1]) + (mtx[1][2] * rhs.mtx[2][1]) + (mtx[1][3] * rhs.mtx[3][1]);
	tmp.mtx[1][2] = (mtx[1][0] * rhs.mtx[0][2]) + (mtx[1][1] * rhs.mtx[1][2]) + (mtx[1][2] * rhs.mtx[2][2]) + (mtx[1][3] * rhs.mtx[3][2]);
	tmp.mtx[1][3] = (mtx[1][0] * rhs.mtx[0][3]) + (mtx[1][1] * rhs.mtx[1][3]) + (mtx[1][2] * rhs.mtx[2][3]) + (mtx[1][3] * rhs.mtx[3][3]);

	// Row 3.
	tmp.mtx[2][0] = (mtx[2][0] * rhs.mtx[0][0]) + (mtx[2][1] * rhs.mtx[1][0]) + (mtx[2][2] * rhs.mtx[2][0]) + (mtx[2][3] * rhs.mtx[3][0]);
	tmp.mtx[2][1] = (mtx[2][0] * rhs.mtx[0][1]) + (mtx[2][1] * rhs.mtx[1][1]) + (mtx[2][2] * rhs.mtx[2][1]) + (mtx[2][3] * rhs.mtx[3][1]);
	tmp.mtx[2][2] = (mtx[2][0] * rhs.mtx[0][2]) + (mtx[2][1] * rhs.mtx[1][2]) + (mtx[2][2] * rhs.mtx[2][2]) + (mtx[2][3] * rhs.mtx[3][2]);
	tmp.mtx[2][3] = (mtx[2][0] * rhs.mtx[0][3]) + (mtx[2][1] * rhs.mtx[1][3]) + (mtx[2][2] * rhs.mtx[2][3]) + (mtx[2][3] * rhs.mtx[3][3]);

	// Row 4.
	tmp.mtx[3][0] = (mtx[3][0] * rhs.mtx[0][0]) + (mtx[3][1] * rhs.mtx[1][0]) + (mtx[3][2] * rhs.mtx[2][0]) + (mtx[3][3] * rhs.mtx[3][0]);
	tmp.mtx[3][1] = (mtx[3][0] * rhs.mtx[0][1]) + (mtx[3][1] * rhs.mtx[1][1]) + (mtx[3][2] * rhs.mtx[2][1]) + (mtx[3][3] * rhs.mtx[3][1]);
	tmp.mtx[3][2] = (mtx[3][0] * rhs.mtx[0][2]) + (mtx[3][1] * rhs.mtx[1][2]) + (mtx[3][2] * rhs.mtx[2][2]) + (mtx[3][3] * rhs.mtx[3][2]);
	tmp.mtx[3][3] = (mtx[3][0] * rhs.mtx[0][3]) + (mtx[3][1] * rhs.mtx[1][3]) + (mtx[3][2] * rhs.mtx[2][3]) + (mtx[3][3] * rhs.mtx[3][3]);

	*this = tmp;
	return *this;
}

inline Matrix4 &Matrix4::operator*=(float scalar)
{
	mtx[0][0] *= scalar, mtx[0][1] *= scalar, mtx[0][2] *= scalar, mtx[0][3] *= scalar;
	mtx[1][0] *= scalar, mtx[1][1] *= scalar, mtx[1][2] *= scalar, mtx[1][3] *= scalar;
	mtx[2][0] *= scalar, mtx[2][1] *= scalar, mtx[2][2] *= scalar, mtx[2][3] *= scalar;
	mtx[3][0] *= scalar, mtx[3][1] *= scalar, mtx[3][2] *= scalar, mtx[3][3] *= scalar;
	return *this;
}

inline Matrix4 &Matrix4::operator/=(float scalar)
{
	mtx[0][0] /= scalar, mtx[0][1] /= scalar, mtx[0][2] /= scalar, mtx[0][3] /= scalar;
	mtx[1][0] /= scalar, mtx[1][1] /= scalar, mtx[1][2] /= scalar, mtx[1][3] /= scalar;
	mtx[2][0] /= scalar, mtx[2][1] /= scalar, mtx[2][2] /= scalar, mtx[2][3] /= scalar;
	mtx[3][0] /= scalar, mtx[3][1] /= scalar, mtx[3][2] /= scalar, mtx[3][3] /= scalar;
	return *this;
}

inline Matrix4 Matrix4::operator+(const Matrix4 &rhs) const
{
	Matrix4 tmp(*this);
	tmp += rhs;
	return tmp;
}

inline Matrix4 Matrix4::operator-(const Matrix4 &rhs) const
{
	Matrix4 tmp(*this);
	tmp -= rhs;
	return tmp;
}

inline Matrix4 Matrix4::operator*(const Matrix4 &rhs) const
{
	Matrix4 tmp(*this);
	tmp *= rhs;
	return tmp;
}

inline Matrix4 Matrix4::operator*(float scalar) const
{
	Matrix4 tmp(*this);
	tmp *= scalar;
	return tmp;
}

inline Matrix4 Matrix4::operator/(float scalar) const
{
	Matrix4 tmp(*this);
	tmp /= scalar;
	return tmp;
}

inline void Matrix4::identity()
{
	mtx[0][0] = 1.0f, mtx[0][1] = 0.0f, mtx[0][2] = 0.0f, mtx[0][3] = 0.0f;
	mtx[1][0] = 0.0f, mtx[1][1] = 1.0f, mtx[1][2] = 0.0f, mtx[1][3] = 0.0f;
	mtx[2][0] = 0.0f, mtx[2][1] = 0.0f, mtx[2][2] = 1.0f, mtx[2][3] = 0.0f;
	mtx[3][0] = 0.0f, mtx[3][1] = 0.0f, mtx[3][2] = 0.0f, mtx[3][3] = 1.0f;
}

inline void Matrix4::toHeadPitchRoll(float &headDegrees, float &pitchDegrees, float &rollDegrees) const
{
// 	float D = -asin( mtx[2]);
// 	pitchDegrees = D;        /* Считаем ось Y */
// 	float C           =  cos( pitchDegrees );
// 	pitchDegrees    *= RADIANS;
// 
// 	if ( fabs( C ) > 0.005 )             /* ось зафиксирована? */
// 	{
// 		trx      =  mat[10] / C;           /* Нет, так что находим угол по X */
// 		try      = -mat[6]  / C;
// 
// 		headDegrees  = atan2( try, trx ) * RADIANS;
// 
// 		trx      =  mat[0] / C;            /* находим угол по оси Z */
// 		try      = -mat[1] / C;
// 
// 		rollDegrees  = atan2( try, trx ) * RADIANS;
// 	}
// 	else                                 /* ось все-таки зафиксирована */
// 	{
// 		headDegrees  = 0;                      /* Устанавливаем угол по оси X на 0 */
// 
// 		trx      = mat[5];                 /* И считаем ось Z */
// 		try      = mat[4];
// 
// 		rollDegrees  = atan2( try, trx ) * RADIANS;
// 	}
// 
// 	headDegrees = clamp( headDegrees, 0, 360 );  /* Приводим углы к диапазону */
// 	pitchDegrees = clamp( pitchDegrees, 0, 360 );
// 	rollDegrees = clamp( rollDegrees, 0, 360 );

}
