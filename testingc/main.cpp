#include <iostream>
#include <vector>
#include "objs.h"

class World {
private:
    std::vector<Object*> objs;
    float gravity;
public:

    void add_obj(Object* obj) {
        obj->Acceleration = obj->Acceleration + vec3(0.0f, gravity, 0.0f);
        objs.push_back(obj);
    }

    void step(float deltaTime){
        for (Object* obj : objs) {
            obj->Position = obj->Position + (obj->Velocity * deltaTime);
            std::cout << "deltaPos: " << (obj->Velocity * deltaTime);

            obj->Velocity = obj->Velocity + (obj->Acceleration * deltaTime);
            std::cout << "deltaVel: " << (obj->Acceleration * deltaTime);
        }
    }

    World(float g) {
        gravity = g;
    }
};

void print_kinematics(Object& obj) {
    std::cout << "Pos: " << obj.Position;
    std::cout << "Vel: " << obj.Velocity;
    std::cout << "Acc: " << obj.Acceleration;
    std::cout << std::endl;
}

int main()
{
    World base(-9.81f);

    std::cout << "Hello World2!\n";

    Object ball(vec3(2.0f, 0.0f, 0.0f), 10, vec3(3.0f, 2.0f, 0.0f));
    Object* pBall = &ball;
    base.add_obj(pBall);

    float total_time = 0.0f;

    std::cout << "Time: " << total_time << std::endl;
    print_kinematics(ball);

    while (total_time < 2.0f) {
        total_time += 0.1f;
        std::cout << "Time: " << total_time << std::endl;
        base.step(0.1f);
        print_kinematics(ball);
    }
    int n;
    std::cin >> n;
    
}