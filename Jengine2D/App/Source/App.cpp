#include "Core/Core.h"

void print_kinematics(Core::Object& obj) {
    std::cout << "Pos: " << obj.Position;
    std::cout << "Vel: " << obj.Velocity;
    std::cout << "Acc: " << obj.Acceleration;
    std::cout << std::endl;
}

// Check if two numerical values are equal with tolerance
// tolerance check with doubles
bool equal_tolerance(double a, double b, double epsilon = 1e-9) {
    return std::abs(a - b) < epsilon;
}

// tolerance check with floats
bool equal_tolerance(float a, float b, float epsilon = 1e-9f) {
    return std::abs(a - b) < epsilon;
}

//

int main()
{
    Core::World base(-9.81f);

    Core::Object ball(
        1.0, // Id
        vec2(2.0f, 0.0f), // Position
        10.0f, // Mass
        vec2(3.0f, 20.0f) // Velocity
    );

    base.add_obj(&ball);

    double current_time = 0.0;
    double end_time = 2;
    double delta_time = 0.01;

    // Inital log
    // std::cout << "Time: " << current_time << std::endl;
    std::cout << base;

    while (current_time < end_time) {
        current_time += delta_time;
        // std::cout << "Time: " << current_time << std::endl;
        base.step(delta_time);
        //std::cout << ball;

        //force test case
        if (equal_tolerance(current_time, 1.0, 0.001)) {
            std::cout << "EXERTED FORCE OF: +10N in Y" << std::endl;
            ball.exert(vec2(0.0f, 10.0f));
        }
    }

    std::cout << "Runtime: " << end_time << std::endl;
    std::cout << base;

    int n;
    std::cin >> n;
}