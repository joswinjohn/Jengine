#pragma once
#include "../Headers/Structs.h"
#include <vector>

namespace Core {

	struct Object {
		vec2 Position, Velocity, Acceleration;
		float Mass;
		double Id;
		

		void exert(vec2 Force) {
			Acceleration = Acceleration + (Force / Mass);
		}

		Object(
			double i,
			vec2 p, 
			float m, 
			vec2 v = vec2(0.0f, 0.0f),
			vec2 a = vec2(0.0f, 0.0f)
		) {
			Id = i;
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

	inline std::ostream& operator<< (std::ostream& os, const Object& obj)
	{
		os	<< "Id: "
			<< obj.Id
			<< std::endl
			<< "Pos: "
			<< obj.Position 
			<< std::endl
			<< "Vel: "
			<< obj.Velocity 
			<< std::endl
			<< "Acc: "
			<< obj.Acceleration 
			<< std::endl;
		return os;
	}

	inline std::ostream& operator<< (std::ostream& os, const World& w)
	{
		os << "G: " << w.gravity << "; " << std::endl;
		for (Object* obj : w.objs) {
			os << *obj << std::endl;
		}
		return os;
	}
}