#include <iostream>
#include "Core/Core.h"

namespace GraphicsEngine {
	class Jengine3D : Core::World {
	private:
		mesh cube;
	public:
		bool OnStart() override {
			cube.cube_points = std::vector<triangle> {
				triangle{ vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f) },
				triangle{ vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f) },

				triangle{ vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f) },
				triangle{ vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f) },

				triangle{ vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f) },
				triangle{ vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f) },

				triangle{ vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f) },
				triangle{ vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f) },

				triangle{ vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f) },
				triangle{ vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f) },

				triangle{ vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f) },
				triangle{ vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f, 0.0f, 0.0f) },
			};
		}
	};
}