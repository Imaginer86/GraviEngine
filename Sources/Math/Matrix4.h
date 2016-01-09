#pragma once
//-----------------------------------------------------------------------------
// A homogeneous row-major 4x4 matrix class.
//
// Matrices are concatenated in a left to right order.
// Multiplies Vector3s to the left of the matrix.
//-----------------------------------------------------------------------------

#include "Math.h"
#include "Vector3f.h"

class Matrix4
{
	friend Vector3f operator*(const Vector3f &lhs, const Matrix4 &rhs);
	friend Matrix4 operator*(float32 scalar, const Matrix4 &rhs);

public:
	static const Matrix4 IDENTITY;

	Matrix4() {}
	Matrix4(float32 m11, float32 m12, float32 m13, float32 m14,
		float32 m21, float32 m22, float32 m23, float32 m24,
		float32 m31, float32 m32, float32 m33, float32 m34,
		float32 m41, float32 m42, float32 m43, float32 m44);
	~Matrix4() {}

	float32 *operator[](int row);
	const float32 *operator[](int row) const;

	bool operator==(const Matrix4 &rhs) const;
	bool operator!=(const Matrix4 &rhs) const;

	Matrix4 &operator+=(const Matrix4 &rhs);
	Matrix4 &operator-=(const Matrix4 &rhs);
	Matrix4 &operator*=(const Matrix4 &rhs);
	Matrix4 &operator*=(float32 scalar);
	Matrix4 &operator/=(float32 scalar);

	Matrix4 operator+(const Matrix4 &rhs) const;
	Matrix4 operator-(const Matrix4 &rhs) const;
	Matrix4 operator*(const Matrix4 &rhs) const;
	Matrix4 operator*(float32 scalar) const;
	Matrix4 operator/(float32 scalar) const;

	//void fromHeadPitchRoll(float32 headDegrees, float32 pitchDegrees, float32 rollDegrees);
	void identity();
	//void rotate(const Vector3 &axis, float32 degrees);
	//void toHeadPitchRoll(float32 &headDegrees, float32 &pitchDegrees, float32 &rollDegrees) const;

private:
	float32 mtx[4][4];
};

inline Vector3f operator*(const Vector3f &lhs, const Matrix4 &rhs)
{
	return Vector3f((lhs.x * rhs.mtx[0][0]) + (lhs.y * rhs.mtx[1][0]) + (lhs.z * rhs.mtx[2][0]),
		(lhs.x * rhs.mtx[0][1]) + (lhs.y * rhs.mtx[1][1]) + (lhs.z * rhs.mtx[2][1]),
		(lhs.x * rhs.mtx[0][2]) + (lhs.y * rhs.mtx[1][2]) + (lhs.z * rhs.mtx[2][2]));
}

inline Matrix4 operator*(float32 scalar, const Matrix4 &rhs)
{
	return rhs * scalar;
}

inline Matrix4::Matrix4(float32 m11, float32 m12, float32 m13, float32 m14,
						float32 m21, float32 m22, float32 m23, float32 m24,
						float32 m31, float32 m32, float32 m33, float32 m34,
						float32 m41, float32 m42, float32 m43, float32 m44)
{
	mtx[0][0] = m11, mtx[0][1] = m12, mtx[0][2] = m13, mtx[0][3] = m14;
	mtx[1][0] = m21, mtx[1][1] = m22, mtx[1][2] = m23, mtx[1][3] = m24;
	mtx[2][0] = m31, mtx[2][1] = m32, mtx[2][2] = m33, mtx[2][3] = m34;
	mtx[3][0] = m41, mtx[3][1] = m42, mtx[3][2] = m43, mtx[3][3] = m44;
}

inline float32 *Matrix4::operator[](int row)
{
	return mtx[row];
}

inline const float32 *Matrix4::operator[](int row) const
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

inline Matrix4 &Matrix4::operator*=(float32 scalar)
{
	mtx[0][0] *= scalar, mtx[0][1] *= scalar, mtx[0][2] *= scalar, mtx[0][3] *= scalar;
	mtx[1][0] *= scalar, mtx[1][1] *= scalar, mtx[1][2] *= scalar, mtx[1][3] *= scalar;
	mtx[2][0] *= scalar, mtx[2][1] *= scalar, mtx[2][2] *= scalar, mtx[2][3] *= scalar;
	mtx[3][0] *= scalar, mtx[3][1] *= scalar, mtx[3][2] *= scalar, mtx[3][3] *= scalar;
	return *this;
}

inline Matrix4 &Matrix4::operator/=(float32 scalar)
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

inline Matrix4 Matrix4::operator*(float32 scalar) const
{
	Matrix4 tmp(*this);
	tmp *= scalar;
	return tmp;
}

inline Matrix4 Matrix4::operator/(float32 scalar) const
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

//inline void Matrix4::fromHeadPitchRoll(float32 headDegrees, float32 pitchDegrees, float32 rollDegrees)
//{

//}

/*
inline void Matrix4::toHeadPitchRoll(float32 &headDegrees, float32 &pitchDegrees, float32 &rollDegrees) const
{
 	float32 D = -asinf( mtx[0][2]);
 	pitchDegrees = D;        // Считаем ось Y 
 	float32 C           =  cosf( pitchDegrees );
 	pitchDegrees    *= Math::RADIANS;
 
 	if ( fabs( C ) > 0.005 )             // ось зафиксирована? 
 	{
 		trx      =  mat[10] / C;           // Нет, так что находим угол по X
 		try      = -mat[6]  / C;
 
 		headDegrees  = atan2( try, trx ) * RADIANS;
 
 		trx      =  mat[0] / C;            // находим угол по оси Z 
 		try      = -mat[1] / C;
 
 		rollDegrees  = atan2( try, trx ) * RADIANS;
 	}
 	else                                 // ось все-таки зафиксирована
 	{
 		headDegrees  = 0;                      // Устанавливаем угол по оси X на 0
 
 		trx      = mat[5];                 // И считаем ось Z
 		try      = mat[4];
 
 		rollDegrees  = atan2( try, trx ) * RADIANS;
 	}
 
 	headDegrees = clamp( headDegrees, 0, 360 );  // Приводим углы к диапазону 
 	pitchDegrees = clamp( pitchDegrees, 0, 360 );
 	rollDegrees = clamp( rollDegrees, 0, 360 );

}*/
