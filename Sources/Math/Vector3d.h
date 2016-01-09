#pragma once
#include "Math.h"

class Vector3d		//---> An object to represent a 3D vector or a 3D point in space
{
public:
    Vector3d()									// Constructor to set x = y = z = 0
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
    {
    }

    Vector3d(float64 x, float64 y, float64 z)			// Constructor that initializes this Vector3 to the intended values of x, y and z
	: x(x)
	, y(y)
	, z(z)
    {
    }

// 	Vector3(Vector3 vec)
// 	: x(vec.x)
// 	, y(vec.y)
// 	, z(vec.z)
// 	{
// 	}

    void Set(float64 x_, float64 y_, float64 z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }

    Vector3d& operator= (Vector3d v)			// operator= sets values of v to this Vector3. example: v1 = v2 means that values of v2 are set onto v1
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    Vector3d operator+ (Vector3d v)				// operator+ is used to add two Vector3's. operator+ returns a new Vector3
    {
        return Vector3d(x + v.x, y + v.y, z + v.z);
    }

    Vector3d operator- (Vector3d v)				// operator- is used to take difference of two Vector3's. operator- returns a new Vector3
    {
        return Vector3d(x - v.x, y - v.y, z - v.z);
    }

    Vector3d operator* (float64 value)			// operator* is used to scale a Vector3 by a value. This value multiplies the Vector3's x, y and z.
    {
        return Vector3d(x * value, y * value, z * value);
    }

    Vector3d operator/ (float64 value)			// operator/ is used to scale a Vector3 by a value. This value divides the Vector3's x, y and z.
    {
        return Vector3d(x / value, y / value, z / value);
    }

    Vector3d& operator+= (Vector3d v)			// operator+= is used to add another Vector3 to this Vector3.
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3d& operator-= (Vector3d v)			// operator-= is used to subtract another Vector3 from this Vector3.
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3d& operator*= (float64 value)			// operator*= is used to scale this Vector3 by a value.
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    Vector3d& operator/= (float64 value)			// operator/= is used to scale this Vector3 by a value.
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }


    Vector3d operator- ()						// operator- is used to set this Vector3's x, y, and z to the negative of them.
    {
        return Vector3d(-x, -y, -z);
    }

	// cross product (vector product)
	Vector3d operator*(Vector3d v)
	{
		Vector3d res;
		res.x = this->y*v.z - this->z*v.y;
		res.y = this->x*v.z - this->z*v.x;
		res.z = this->x*v.y - this->y*v.x;
		return res;
	}

	float64 dotProduct(Vector3d v)
	{
		return this->x*v.x + this->y*v.y + this->z*v.z;
	}

    float64 length()								// length() returns the length of this Vector3
    {
        return sqrt(x*x + y*y + z*z);
    };			   		

    float64 unitize()								// unitize() normalizes this Vector3 that its direction remains the same but its length is 1.
    {
        float64 length = this->length();

        if (length == 0)
            return 0.0;

        x /= length;
        y /= length;
        z /= length;
		return length;
    }

    Vector3d unit()								// unit() returns a new Vector3. The returned value is a unitized version of this Vector3.
    {
        float64 length = this->length();

        if (length == 0)
            return *this;

        return Vector3d(x / length, y / length, z / length);
    }

//private:
    float64 x;									// the x value of this Vector3
    float64 y;									// the y value of this Vector3
    float64 z;									// the z value of this Vector3
};

// float DistanceV3(Vector3 v1, Vector3 v2)
// {
//  	return (v1 - v2).length();
// }