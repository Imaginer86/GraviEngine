#pragma once
#include <iostream>
using namespace std;


class Quaternion
{
   private:
      // Data Fields
      float r, i, j, k;

   public:
      // Constructors
      Quaternion();
      Quaternion(float, float, float, float);
      Quaternion(const Quaternion &);
      ~Quaternion();

      // Operators
      const Quaternion & operator = (const Quaternion &);
      Quaternion operator + (const Quaternion &);
      Quaternion operator - (const Quaternion &);
      Quaternion operator - () const;
      Quaternion operator * (const Quaternion &);
      Quaternion operator * (float);
      Quaternion operator / (const Quaternion &);
      Quaternion operator ~ () const;

      // Member Functions
      Quaternion sqr();
      Quaternion conjugate() const;
      Quaternion inverse() const;
      float magnitude() const;

      // Friendship Functions
  //    friend Quaternion<T> operator * <>(T, Quaternion<T> &);

      // Streams
      friend ostream & operator << <>(ostream&, const Quaternion &);
      friend istream & operator >> <>(istream&, Quaternion &);
};

inline
Quaternion::Quaternion()
   : r(float(0)), i(float(0)), j(float(0)), k(float(0)) {}

inline
Quaternion::Quaternion(float r1, float i1, float j1, float k1)
   : r(r1), i(i1), j(j1), k(k1) {}

inline
Quaternion::Quaternion(const Quaternion &arg)
   : r(arg.r), i(arg.i), j(arg.j), k(arg.k) {}

inline
Quaternion::~Quaternion() {}

inline
const Quaternion& Quaternion::operator = (const Quaternion &rvalue)
{
   r = rvalue.r; i = rvalue.i; j = rvalue.j; k = rvalue.k;
   return *this;
}

inline
Quaternion Quaternion::operator + (const Quaternion &arg)
{
   return Quaternion(r+arg.r, i+arg.i, j+arg.j, k+arg.k);
}

inline
Quaternion Quaternion::operator - (const Quaternion &arg)
{
   return Quaternion(r-arg.r, i-arg.i, j-arg.j, k-arg.k);
}

inline
Quaternion Quaternion::operator - () const
{
   return Quaternion(-r,-i,-j,-k); 
}

inline
Quaternion Quaternion::operator * (const Quaternion &arg)
{
   return Quaternion(r*arg.r - i*arg.i - j*arg.j - k*arg.k,
                        r*arg.i + i*arg.r + j*arg.k - k*arg.j,
                        r*arg.j + j*arg.r + k*arg.i - i*arg.k,
                        r*arg.k + k*arg.r + i*arg.j - j*arg.i);
}

inline
Quaternion Quaternion::operator * (float arg)
{
   return Quaternion(r*arg, i*arg, j*arg, k*arg);
}

inline
Quaternion Quaternion::operator / (const Quaternion &arg)
{
   return *this * arg.inverse();
}
 

// Normalize Quaternion
inline
Quaternion Quaternion::operator ~ () const
{
   Quaternion result;
   float length = magnitude();

   result.r = r/length; result.i = i/length;
   result.j = j/length; result.k = k/length;
   return result;
}

inline
Quaternion Quaternion::sqr()
{
   Quaternion result;
   float temp;
   float two = float(2);
   temp = two*r;
   result.r = r*r - i*i - j*j - k*k;
   result.i = temp*i;
   result.j = temp*j;
   result.k = temp*k;
   return result;
}

inline
Quaternion Quaternion::conjugate() const
{
   return Quaternion(r,-i,-j,-k);
}

inline
Quaternion Quaternion::inverse() const
{
   Quaternion temp1(conjugate());
   float             temp2 = r*r + i*i + j*j + k*k;

   return Quaternion(temp1.r/temp2,temp1.i/temp2,
                        temp1.j/temp2,temp1.k/temp2);
}

inline
float Quaternion::magnitude() const
{
   return sqrt(r*r + i*i + j*j + k*k);
}

/*template <class T> Quaternion<T> operator * (T factor, Quaternion<T> &arg)
{
   return arg * factor;
}                        */

inline
ostream & operator << (ostream &s, const Quaternion &arg)
{
   s << "(" << arg.r << "," << arg.i << ","
            << arg.j << "," << arg.k << ")";
   return s;
}

inline
istream & operator >> (istream &s, Quaternion &arg)
{
   s >> arg.r >> arg.i >> arg.j >> arg.k;
   return s;
}