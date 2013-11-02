#pragma once

#include <cmath>

// class Vector3D		---> An object to represent a 3D vector or a 3D point in space
class Vector3D
{
public:
    float x;									// the x value of this Vector3D
    float y;									// the y value of this Vector3D
    float z;									// the z value of this Vector3D

    Vector3D()									// Constructor to set x = y = z = 0
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector3D(float x, float y, float z)			// Constructor that initializes this Vector3D to the intended values of x, y and z
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void Set(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3D& operator= (Vector3D v)			// operator= sets values of v to this Vector3D. example: v1 = v2 means that values of v2 are set onto v1
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    Vector3D operator+ (Vector3D v)				// operator+ is used to add two Vector3D's. operator+ returns a new Vector3D
    {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }

    Vector3D operator- (Vector3D v)				// operator- is used to take difference of two Vector3D's. operator- returns a new Vector3D
    {
        return Vector3D(x - v.x, y - v.y, z - v.z);
    }

    Vector3D operator* (float value)			// operator* is used to scale a Vector3D by a value. This value multiplies the Vector3D's x, y and z.
    {
        return Vector3D(x * value, y * value, z * value);
    }

    Vector3D operator/ (float value)			// operator/ is used to scale a Vector3D by a value. This value divides the Vector3D's x, y and z.
    {
        return Vector3D(x / value, y / value, z / value);
    }

    Vector3D& operator+= (Vector3D v)			// operator+= is used to add another Vector3D to this Vector3D.
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3D& operator-= (Vector3D v)			// operator-= is used to subtract another Vector3D from this Vector3D.
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3D& operator*= (float value)			// operator*= is used to scale this Vector3D by a value.
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    Vector3D& operator/= (float value)			// operator/= is used to scale this Vector3D by a value.
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }


    Vector3D operator- ()						// operator- is used to set this Vector3D's x, y, and z to the negative of them.
    {
        return Vector3D(-x, -y, -z);
    }

    float length()								// length() returns the length of this Vector3D
    {
        return sqrt(x*x + y*y + z*z);
    };			   		

    void unitize()								// unitize() normalizes this Vector3D that its direction remains the same but its length is 1.
    {
        float length = this->length();

        if (length == 0)
            return;

        x /= length;
        y /= length;
        z /= length;
    }

    Vector3D unit()								// unit() returns a new Vector3D. The returned value is a unitized version of this Vector3D.
    {
        float length = this->length();

        if (length == 0)
            return *this;

        return Vector3D(x / length, y / length, z / length);
    }

};

// float DistanceV3(Vector3D v1, Vector3D v2)
// {
//  	return (v1 - v2).length();
// }