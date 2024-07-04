#pragma once
#include "vec.h"

struct Object {
	vec3 Position, Velocity, Acceleration;
	float Mass;

	Object(vec3 p, float m, vec3 v = vec3(0.0f, 0.0f, 0.0f), vec3 a = vec3(0.0f, 0.0f, 0.0f)) {
		Position = p;
		Velocity = v;
		Acceleration = a;
		Mass = m;
	}
};