#pragma once
#include "gmath.h"
class Vector3f
{
public:
	float x;
	float y;
	float z;

	Vector3f():x(0.0f), y(0.0f), z(0.0f)	{}
	Vector3f(float _x, float _y, float _z):x(_x) ,y(_y) ,z(_z)	{}
	~Vector3f()	{}

	Vector3f operator+ (const Vector3f& v);	// operator+ is used to add two Vector3's. operator+ returns a new Vector3
	const Vector3f operator+ (const Vector3f& v) const;
	Vector3f operator- (const Vector3f& v);	// operator- is used to take difference of two Vector3's. operator- returns a new Vector3
	const Vector3f operator- (const Vector3f& v) const;
	Vector3f operator* (float value);	// operator* is used to scale a Vector3 by a value. This value multiplies the Vector3's x, y and z.
	const Vector3f operator* (float value) const;
	Vector3f operator/ (float value);	// operator/ is used to scale a Vector3 by a value. This value divides the Vector3's x, y and z.
	const Vector3f operator/ (float value) const;

	Vector3f& operator+= (const Vector3f& v);	// operator+= is used to add another Vector3 to this Vector3.
	Vector3f& operator-= (const Vector3f& v);	// operator-= is used to subtract another Vector3 from this Vector3.
	Vector3f& operator*= (float value);	// operator*= is used to scale this Vector3 by a value.
	Vector3f& operator/= (float value);	// operator/= is used to scale this Vector3 by a value.

	Vector3f operator- ();	// operator- is used to set this Vector3's x, y, and z to the negative of them.	

	Vector3f operator*(const Vector3f& v);	// cross product (vector product)
	float dotProduct(const Vector3f& v);

	float length();	// length() returns the length of this Vector3
	float unitize();	// unitize() normalizes this Vector3 that its direction remains the same but its length is 1.
	Vector3f unit();	// unit() returns a new Vector3. The returned value is a unitized version of this Vector3.
};

inline Vector3f Vector3f::operator+ (const Vector3f& v)				// operator+ is used to add two Vector3's. operator+ returns a new Vector3
{
	return Vector3f(x + v.x, y + v.y, z + v.z);
}

inline Vector3f Vector3f::operator- (const Vector3f& v)				// operator- is used to take difference of two Vector3's. operator- returns a new Vector3
{
	return Vector3f(x - v.x, y - v.y, z - v.z);
}

inline Vector3f Vector3f::operator* (float value)			// operator* is used to scale a Vector3 by a value. This value multiplies the Vector3's x, y and z.
{
	return Vector3f(x * value, y * value, z * value);
}

inline const Vector3f Vector3f::operator* (float value) const
{
	return Vector3f(x * value, y * value, z * value);
}

inline Vector3f Vector3f::operator/ (float value)			// operator/ is used to scale a Vector3 by a value. This value divides the Vector3's x, y and z.
{
	return Vector3f(x / value, y / value, z / value);
}

inline const Vector3f Vector3f::operator/ (float value) const
{
	return Vector3f(x / value, y / value, z / value);
}

inline Vector3f& Vector3f::operator+= (const Vector3f& v)			// operator+= is used to add another Vector3 to this Vector3.
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline Vector3f& Vector3f::operator-= (const Vector3f& v)			// operator-= is used to subtract another Vector3 from this Vector3.
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline Vector3f& Vector3f::operator*= (float value)			// operator*= is used to scale this Vector3 by a value.
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

inline Vector3f& Vector3f::operator/= (float value)			// operator/= is used to scale this Vector3 by a value.
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

inline Vector3f Vector3f::operator- ()						// operator- is used to set this Vector3's x, y, and z to the negative of them.
{
	return Vector3f(-x, -y, -z);
}

// cross product (vector product)
inline Vector3f Vector3f::operator*(const Vector3f& v)
{
	Vector3f res;
	res.x = this->y*v.z - this->z*v.y;
	res.y = this->x*v.z - this->z*v.x;
	res.z = this->x*v.y - this->y*v.x;
	return res;
}

inline float Vector3f::dotProduct(const Vector3f& v)
{
	return this->x*v.x + this->y*v.y + this->z*v.z;
}

inline float Vector3f::length()								// length() returns the length of this Vector3
{
	return sqrt(x*x + y*y + z*z);
};

inline float Vector3f::unitize()								// unitize() normalizes this Vector3 that its direction remains the same but its length is 1.
{
	float length = this->length();

	if (length == 0.0f)
		return 0.0;

	x /= length;
	y /= length;
	z /= length;
	return length;
}

inline Vector3f Vector3f::unit()								// unit() returns a new Vector3. The returned value is a unitized version of this Vector3.
{
	float length = this->length();

	if (length == 0)
		return *this;

	return Vector3f(x / length, y / length, z / length);
}

inline const Vector3f Vector3f::operator+ (const Vector3f& rv) const				// operator- is used to take difference of two Vector3's. operator- returns a new Vector3
{
	return Vector3f(x + rv.x, y + rv.y, z + rv.z);
}

inline const Vector3f Vector3f::operator- (const Vector3f& rv) const				// operator- is used to take difference of two Vector3's. operator- returns a new Vector3
{
	return Vector3f(x - rv.x, y - rv.y, z - rv.z);
}
