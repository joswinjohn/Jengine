#include "Core.h"

#include <iostream>
#include <vector>

namespace Core {

    

    void World::add_obj(Object* obj) {
        obj->Acceleration = obj->Acceleration + vec2(0.0f, gravity);
        objs.push_back(obj);
    }

    void World::step(float deltaTime) {
        for (Object* obj : objs) {
            obj->Position = obj->Position + (obj->Velocity * deltaTime);
            // std::cout << "deltaPos: " << (obj->Velocity * deltaTime);

            obj->Velocity = obj->Velocity + (obj->Acceleration * deltaTime);
            // std::cout << "deltaVel: " << (obj->Acceleration * deltaTime);
        }
    }

    World::World(float g) {
        gravity = g;
    }
}