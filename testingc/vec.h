#pragma once

#include <cmath>
#include <iostream>

/*! \defgroup vec3group 3D vectors */
/*! \{ */

/*! Class representing a 3D cartesian vector. */
class vec3 {
public:
	float x, y, z;
	/*! Default constructor. Does not initialize \a x, \a y, and \a z. */
	vec3() {}
	/*! Creates a vector with the coordinates \a xc, \a yc, and \a zc. */
	vec3(float xc, float yc, float zc)
		: x(xc), y(yc), z(zc) {}
		
	/*! Creates a unit vector from a z coordinate and an azimuthal angle. */
	void set_z_phi(float z_, float phi)
		{
			using namespace std;
			float sintheta = sqrt((1. - z_) * (1. + z_));
			x = sintheta * cos(phi);
			y = sintheta * sin(phi);
			z = z_;
		}
		
	/*! Normalizes the vector to length 1. */
	void Normalize()
		{
			using namespace std;
		    float l = 1.0 / sqrt(x * x + y * y + z * z);
		    x *= l; y *= l; z *= l;
       }

	/*! Returns the length of the vector. */
	float Length() const
		{ return sqrt(x * x + y * y + z * z); }

	/*! Returns the squared length of the vector. */
	float SquaredLength() const
		{ return (x * x + y * y + z * z); }
	/*! Returns the vector with the signs of all coordinates flipped. */
	const vec3 operator- () const
		{ return vec3(-x, -y, -z); }
	/*! Flips the signs of all coordinates. */
	void Flip()
		{ x = -x; y = -y; z = -z; }
	/*! Subtracts \a vec from the vector. */
	const vec3 operator- (const vec3& vec) const
		{ return vec3(x - vec.x, y - vec.y, z - vec.z); }
	/*! Adds \a vec to the vector. */
	const vec3 operator+ (const vec3& vec) const
		{ return vec3(x + vec.x, y + vec.y, z + vec.z); }
	/*! Returns the vector scaled by \a fact. */
	const vec3 operator* (float fact) const
		{ return vec3(x * fact, y * fact, z * fact); }
	/*! Returns the vector scaled by \a 1/fact. */
	const vec3 operator/ (float fact) const
		{ float xfact = 1. / fact; return vec3(x * xfact, y * xfact, z * xfact); }
	/*! Scales the vector by \a fact. */
	vec3 & operator*= (float fact)
		{ x *= fact; y *= fact; z *= fact; return *this; }
};

 /*! Returns the dot product of \a v1 and \a v2.
     \relates vec3 */
inline float dotprod(const vec3 & v1, const vec3 & v2)
	{ return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

 /*! Returns the cross product of \a a and \a b.
     \relates vec3 */
inline vec3 crossprod(const vec3 & a, const vec3 & b)
	{ return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

 /*! Writes \a v to \a os.
     \relates vec3 */
inline std::ostream & operator<< (std::ostream & os, const vec3 & v)
	{
		os << v.x << ", " << v.y << ", " << v.z << std::endl;
		return os;
	}