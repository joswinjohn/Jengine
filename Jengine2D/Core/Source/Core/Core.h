#pragma once
#include "../Headers/Structs.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <vector>

namespace Core {

	struct Object {
		glm::vec3 Position, Velocity, Acceleration;
		float Mass;
		

		void exert(glm::vec3 Force) {
			Acceleration = Acceleration + (Force / Mass);
		}

		Object(
			glm::vec3 p,
			float m, 
			glm::vec3 v = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 a = glm::vec3(0.0f, 0.0f, 0.0f)
		) {
			Position = p;
			Velocity = v;
			Acceleration = a;
			Mass = m;
		}
	};

    class World {
    public:
		std::vector<Object*> objs;
		float gravity;

        void add_obj(Object* obj);

		void step(float deltaTime);

		World(float g);
    };
}