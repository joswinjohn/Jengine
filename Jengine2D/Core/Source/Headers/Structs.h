#pragma once

#include <cmath>
#include <iostream>

class vec2 {
public:
	float x, y;
	vec2() {}
	
	vec2(float xc, float yc)
		: x(xc), y(yc) {}

	float Length() const
	{
		return sqrt(x * x + y * y);
	}

	const vec2 operator- () const
	{
		return vec2(-x, -y);
	}

	void Flip()
	{
		x = -x;
		y = -y;
	}

	const vec2 operator- (const vec2& vec) const
	{
		return vec2(x - vec.x, y - vec.y);
	}
	
	const vec2 operator+ (const vec2& vec) const
	{
		return vec2(x + vec.x, y + vec.y);
	}
	
	const vec2 operator* (float f) const
	{
		return vec2(x * f, y * f);
	}
	
	const vec2 operator/ (float f) const
	{
		float xf = 1. / f;
		return vec2(x * xf, y * xf);
	}
	
	vec2& operator*= (float f)
	{
		x *= f;
		y *= f;
		return *this;
	}
};

inline std::ostream& operator<< (std::ostream& os, const vec2& v)
{
	os << v.x << ", " << v.y;
	return os;
}