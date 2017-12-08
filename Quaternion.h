#pragma once
#include "math.h"
#include "Vector3f.h"

class Quaternion
{
	friend Quaternion operator*(float lhs, const Quaternion &rhs);

public:
	float w, x, y, z;

	Quaternion() {}
	Quaternion(float _w, float _x, float _y, float _z);
	Quaternion(float angleD, const Vector3f &axic)
	{
		Vector3f naxic = axic;
		naxic.unitize();
		fromAngleAxis(angleD, naxic);
	}
	~Quaternion() {}

	bool operator==(const Quaternion &rhs) const;
	bool operator!=(const Quaternion &rhs) const;

	Quaternion &operator+=(const Quaternion &rhs);
	Quaternion &operator-=(const Quaternion &rhs);
	Quaternion &operator*=(const Quaternion &rhs);
	Quaternion &operator*=(const Vector3f &vec);
	Quaternion &operator*=(float scalar);
	Quaternion &operator/=(float scalar);

	Quaternion operator+(const Quaternion &rhs) const;
	Quaternion operator-(const Quaternion &rhs) const;
	Quaternion operator*(const Quaternion &rhs) const;
	Quaternion operator*(const Vector3f &vec) const;
	Quaternion operator*(float scalar) const;
	Quaternion operator/(float scalar) const;

	Quaternion conjugate() const;

	void normalize();

	Vector3f Normal(const Vector3f &p);

	
	void fromAngleXYZ(const Vector3f &angle);
	void identity();
	Quaternion inverse() const;
	float magnitude() const;
	
	void fromAngleAxis(float degrees, const Vector3f &axis);
	void toAngleAxis(float &degrees, Vector3f &axis) const;
	void rotate(Vector3f &v) const;

	//oid toHeadPitchRoll(float &headDegrees, float &pitchDegrees, float &rollDegrees) const;
	//atrix4 toMatrix4() const;
	
	//void rotate(Vector3 &v) const;
	//oid fromMatrix(const Matrix4 &m);
	//oid fromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees);
};

const Quaternion QIDENTITY(1.0f, 0.0f, 0.0f, 0.0f);

inline Quaternion operator*(float lhs, const Quaternion &rhs)
{
	return rhs * lhs;
}

inline Quaternion operator*(Quaternion &q1, const Quaternion &q2)
{
	return q1.operator*(q2);
}

inline Quaternion::Quaternion(float w_, float x_, float y_, float z_)
	: w(w_), x(x_), y(y_), z(z_) {}

inline bool Quaternion::operator==(const Quaternion &rhs) const
{
	return closeEnough(w, rhs.w) && closeEnough(x, rhs.x)
		&& closeEnough(y, rhs.y) && closeEnough(z, rhs.z);
}

inline bool Quaternion::operator!=(const Quaternion &rhs) const
{
	return !(*this == rhs);
}

inline Quaternion &Quaternion::operator+=(const Quaternion &rhs)
{
	w += rhs.w, x += rhs.x, y += rhs.y, z += rhs.z;
	return *this;
}

inline Quaternion &Quaternion::operator-=(const Quaternion &rhs)
{
	w -= rhs.w, x -= rhs.x, y -= rhs.y, z -= rhs.z;
	return *this;
}

inline Quaternion &Quaternion::operator*=(const Quaternion &rhs)
{
	// Multiply so that rotations are applied in a left to right order.
	Quaternion tmp(
		(w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z),
		(w * rhs.x) + (x * rhs.w) - (y * rhs.z) + (z * rhs.y),
		(w * rhs.y) + (x * rhs.z) + (y * rhs.w) - (z * rhs.x),
		(w * rhs.z) - (x * rhs.y) + (y * rhs.x) + (z * rhs.w));

	/*
	// Multiply so that rotations are applied in a right to left order.
	Quaternion tmp(
	(w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z),
	(w * rhs.x) + (x * rhs.w) + (y * rhs.z) - (z * rhs.y),
	(w * rhs.y) - (x * rhs.z) + (y * rhs.w) + (z * rhs.x),
	(w * rhs.z) + (x * rhs.y) - (y * rhs.x) + (z * rhs.w));
	*/

	*this = tmp;
	return *this;
}

inline Quaternion &Quaternion::operator*=(const Vector3f &v)
{
	const float w_ = -(x * v.x) - (y * v.y) - (z * v.z);
	const float x_ = (w * v.x) + (y * v.z) - (z * v.y);
	const float y_ = (w * v.y) + (z * v.x) - (x * v.z);
	const float z_ = (w * v.z) + (x * v.y) - (y * v.x);

	Quaternion ret(x_, y_, z_, w_);

	*this = ret;
	return *this;
}

inline Quaternion &Quaternion::operator*=(float scalar)
{
	w *= scalar, x *= scalar, y *= scalar, z *= scalar;
	return *this;
}

inline Quaternion &Quaternion::operator/=(float scalar)
{
	w /= scalar, x /= scalar, y /= scalar, z /= scalar;
	return *this;
}

inline Quaternion Quaternion::operator+(const Quaternion &rhs) const
{
	Quaternion tmp(*this);
	tmp += rhs;
	return tmp;
}

inline Quaternion Quaternion::operator-(const Quaternion &rhs) const
{
	Quaternion tmp(*this);
	tmp -= rhs;
	return tmp;
}

inline Quaternion Quaternion::operator*(const Quaternion &rhs) const
{
	Quaternion tmp(*this);
	tmp *= rhs;
	return tmp;
}

inline Quaternion Quaternion::operator*(const Vector3f &vec) const
{
	Quaternion tmp(*this);
	tmp *= vec;
	return tmp;
}

inline Quaternion Quaternion::operator*(float scalar) const
{
	Quaternion tmp(*this);
	tmp *= scalar;
	return tmp;
}

inline Quaternion Quaternion::operator/(float scalar) const
{
	Quaternion tmp(*this);
	tmp /= scalar;
	return tmp;
}

inline Quaternion Quaternion::conjugate() const
{
	Quaternion tmp(w, -x, -y, -z);
	return tmp;
}

inline void Quaternion::fromAngleXYZ(const Vector3f &angle)
{
	Vector3f vx(1, 0, 0), vy(0, 1, 0), vz(0, 0, 1);
	Quaternion qx, qy, qz, qt;

	qx.fromAngleAxis(angle.x, vx);
	qy.fromAngleAxis(angle.y, vy);
	qz.fromAngleAxis(angle.z, vz);
	qt = qx*qy*qz;
	w = qt.w;
	x = qt.x;
	y = qt.y;
	z = qt.z;
	this->normalize();
}


inline void Quaternion::identity()
{
	w = 1.0f, x = y = z = 0.0f;
}

inline Quaternion Quaternion::inverse() const
{
	float invMag = 1.0f / magnitude();
	return conjugate() * invMag;
}

inline float Quaternion::magnitude() const
{
	return sqrt(w * w + x * x + y * y + z * z);
}

inline void Quaternion::normalize()
{
	if (w == 0.0f&&x == 0.0f&&y == 0.0f&&z == 0.0f)
		identity();
	float invMag = 1.0f / magnitude();
	w *= invMag, x *= invMag, y *= invMag, z *= invMag;
}


inline void Quaternion::toAngleAxis(float &degrees, Vector3f &axis) const
{
	// Converts this quaternion to an axis and an angle.

	float sinHalfThetaSq = 1.0f - w * w;

	// Guard against numerical imprecision and identity quaternions.

	if (sinHalfThetaSq <= 0.0f)
	{
		axis.x = 0.0f, axis.y = axis.z = 0.0f;///!!!
		degrees = 0.0f;
	}
	else
	{
		float invSinHalfTheta = 1.0f / sqrt(sinHalfThetaSq);

		axis.x = x * invSinHalfTheta;
		axis.y = y * invSinHalfTheta;
		axis.z = z * invSinHalfTheta;

		degrees = radiansToDegrees(2.0f * atan2f(sqrt(sinHalfThetaSq), w));
	}
}

inline void Quaternion::rotate(Vector3f & v) const
{
	Vector3f u(x, y, z);
	float sinHalfAlpha = u.unitize();
	v = v*(w*w) + (u*v - v*u)*sinHalfAlpha*w - u*v*u*(sinHalfAlpha*sinHalfAlpha);
}

inline void Quaternion::fromAngleAxis(float degrees, const Vector3f &axis)
{
	float halfTheta = degreesToRadians(degrees) * 0.5f;
	float s = sin(halfTheta);
	w = cos(halfTheta), x = axis.x * s, y = axis.y * s, z = axis.z * s;
}

inline Vector3f Quaternion::Normal(const Vector3f &p)
{
	//Vector3f v(x, y, z);
	//v.unitize();
	//Vector3f v2(p);
	//v2.unitize();
	//v = v * v2;
	

	//Vector3f v(x, y, z);
	//v = v*Vector3f(0.0f, 0.0f, 1.0f);
	//v.unitize();
	//if (closeEnough(w, 1.0f))
		//return v;
	Quaternion t = *this * p;
	t = t * inverse();
	Vector3f a;
	float angle;
	t.toAngleAxis(angle, a);
	Vector3f res(a.x, a.y, a.z);

	res.unitize();
	return res;
}



/*
inline Matrix4 Quaternion::toMatrix4() const
{
	// Converts this quaternion to a rotation matrix.
	//
	//  | 1 - 2(y^2 + z^2)	2(xy + wz)			2(xz - wy)			0  |
	//  | 2(xy - wz)		1 - 2(x^2 + z^2)	2(yz + wx)			0  |
	//  | 2(xz + wy)		2(yz - wx)			1 - 2(x^2 + y^2)	0  |
	//  | 0					0					0					1  |

	float x2 = x + x;
	float y2 = y + y;
	float z2 = z + z;
	float xx = x * x2;
	float xy = x * y2;
	float xz = x * z2;
	float yy = y * y2;
	float yz = y * z2;
	float zz = z * z2;
	float wx = w * x2;
	float wy = w * y2;
	float wz = w * z2;

	Matrix4 m;

	m[0][0] = 1.0f - (yy + zz);
	m[0][1] = xy + wz;
	m[0][2] = xz - wy;
	m[0][3] = 0.0f;

	m[1][0] = xy - wz;
	m[1][1] = 1.0f - (xx + zz);
	m[1][2] = yz + wx;
	m[1][3] = 0.0f;

	m[2][0] = xz + wy;
	m[2][1] = yz - wx;
	m[2][2] = 1.0f - (xx + yy);
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;

	return m;
}


inline Vector3f Quaternion::rotate(const Vector3f &p)
{

	Matrix3 RotateM;
	RotateM[0][0] = 1 - 2 * y*y - 2 * z*z;
	RotateM[0][1] = 2 * x*y - 2 * z*w;
	RotateM[0][2] = 2 * x*z + 2 * y*w;
	RotateM[1][0] = 2 * x*y + 2 * z*w;
	RotateM[1][1] = 1 - 2 * x*x - 2 * z*z;
	RotateM[1][2] = 2 * y*z - 2 * x*w;
	RotateM[2][0] = 2 * x*z - 2 * y*w;
	RotateM[2][1] = 2 * y*z + 2 * x*w;
	RotateM[2][2] = 1 - 2 * x*x - 2 * y*y;


	Vector3f p1 = RotateM * p;
	return p1;
}

inline void Quaternion::toHeadPitchRoll(float &headDegrees, float &pitchDegrees, float &rollDegrees) const
{
    Matrix4 m;
    m.toHeadPitchRoll(headDegrees, pitchDegrees, rollDegrees)
	m = this->toMatrix4();
}


inline void Quaternion::fromMatrix(const Matrix4 &m)
{
// Creates a quaternion from a rotation matrix.
// The algorithm used is from Allan and Mark Watt's "Advanced
// Animation and Rendering Techniques" (ACM Press 1992).

float s = 0.0f;
float q[4] = {0.0f};
float trace = m[0][0] + m[1][1] + m[2][2];

if (trace > 0.0f)
{
s = sqrtf(trace + 1.0f);
q[3] = s * 0.5f;
s = 0.5f / s;
q[0] = (m[1][2] - m[2][1]) * s;
q[1] = (m[2][0] - m[0][2]) * s;
q[2] = (m[0][1] - m[1][0]) * s;
}
else
{
int nxt[3] = {1, 2, 0};
int i = 0, j = 0, k = 0;

if (m[1][1] > m[0][0])
i = 1;

if (m[2][2] > m[i][i])
i = 2;

j = nxt[i];
k = nxt[j];
s = sqrtf((m[i][i] - (m[j][j] + m[k][k])) + 1.0f);

q[i] = s * 0.5f;
s = 0.5f / s;
q[3] = (m[j][k] - m[k][j]) * s;
q[j] = (m[i][j] + m[j][i]) * s;
q[k] = (m[i][k] + m[k][i]) * s;
}

x = q[0], y = q[1], z = q[2], w = q[3];
}

inline void Quaternion::fromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees)
{
	Matrix4 m;
	m.fromHeadPitchRoll(headDegrees, pitchDegrees, rollDegrees);
	fromMatrix(m);
}
*/