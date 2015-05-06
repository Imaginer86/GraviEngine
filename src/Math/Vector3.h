#pragma once
#include "math.h"

class Vector3		//---> An object to represent a 3D vector or a 3D point in space
{
public:
    Vector3()									// Constructor to set x = y = z = 0
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
    {
    }

    Vector3(float x, float y, float z)			// Constructor that initializes this Vector3 to the intended values of x, y and z
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

    void Set(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3& operator= (Vector3 v)			// operator= sets values of v to this Vector3. example: v1 = v2 means that values of v2 are set onto v1
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    Vector3 operator+ (Vector3 v)				// operator+ is used to add two Vector3's. operator+ returns a new Vector3
    {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 operator- (Vector3 v)				// operator- is used to take difference of two Vector3's. operator- returns a new Vector3
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 operator* (float value)			// operator* is used to scale a Vector3 by a value. This value multiplies the Vector3's x, y and z.
    {
        return Vector3(x * value, y * value, z * value);
    }

    Vector3 operator/ (float value)			// operator/ is used to scale a Vector3 by a value. This value divides the Vector3's x, y and z.
    {
        return Vector3(x / value, y / value, z / value);
    }

    Vector3& operator+= (Vector3 v)			// operator+= is used to add another Vector3 to this Vector3.
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3& operator-= (Vector3 v)			// operator-= is used to subtract another Vector3 from this Vector3.
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3& operator*= (float value)			// operator*= is used to scale this Vector3 by a value.
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    Vector3& operator/= (float value)			// operator/= is used to scale this Vector3 by a value.
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }


    Vector3 operator- ()						// operator- is used to set this Vector3's x, y, and z to the negative of them.
    {
        return Vector3(-x, -y, -z);
    }

	// cross product (vector product)
	Vector3 operator*(Vector3 v)
	{
		Vector3 res;
		res.x = this->y*v.z - this->z*v.y;
		res.y = this->x*v.z - this->z*v.x;
		res.z = this->x*v.y - this->y*v.x;
		return res;
	}

	float dotProduct(Vector3 v)
	{
		return this->x*v.x + this->y*v.y + this->z*v.z;
	}

    float length()								// length() returns the length of this Vector3
    {
        return sqrt(x*x + y*y + z*z);
    };			   		

    float unitize()								// unitize() normalizes this Vector3 that its direction remains the same but its length is 1.
    {
        float length = this->length();

        if (length == 0)
            return 0.0f;

        x /= length;
        y /= length;
        z /= length;
		return length;
    }

    Vector3 unit()								// unit() returns a new Vector3. The returned value is a unitized version of this Vector3.
    {
        float length = this->length();

        if (length == 0)
            return *this;

        return Vector3(x / length, y / length, z / length);
    }

//private:
    float x;									// the x value of this Vector3
    float y;									// the y value of this Vector3
    float z;									// the z value of this Vector3
};

// float DistanceV3(Vector3 v1, Vector3 v2)
// {
//  	return (v1 - v2).length();
// }