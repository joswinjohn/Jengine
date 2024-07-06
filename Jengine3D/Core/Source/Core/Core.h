#pragma once
#include "../../Structs.h"
#include <vector>

namespace Core {

	struct Object {
		vec3 Position, Velocity, Acceleration;
		float Mass;

		void exert(vec3 Force) {
			Acceleration = Acceleration + (Force / Mass);
		}

		Object(
			vec3 p, 
			float m, 
			vec3 v = vec3(0.0f, 0.0f, 0.0f),
			vec3 a = vec3(0.0f, 0.0f, 0.0f)
		) {
			Position = p;
			Velocity = v;
			Acceleration = a;
			Mass = m;
		}
	};

    class World {
    private:
        std::vector<Object*> objs;
        float gravity;
    public:

		virtual bool OnStart() = 0;

        void add_obj(Object* obj);

		void step(float deltaTime);

		World(float g);
    };
}