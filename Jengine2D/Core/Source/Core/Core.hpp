#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>

namespace Core {

	struct Object {
		glm::vec2 position;
		glm::vec2 position_last;
		glm::vec2 acceleration;

		glm::vec4 color;
		float radius;
		bool m_anchor = false;

		Object() = default;

		Object(float r, glm::vec2 p, glm::vec4 c = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
			: radius(r), position(p), position_last(p), acceleration(glm::vec2(0.0f, 0.0f)), color(c) {}

		void update(float dt)
		{
			const glm::vec2 displacement = position - position_last;
			position_last = position;

			position = position + displacement + acceleration * (dt * dt);
			acceleration = glm::vec2(0.0f, 0.0f);
		}

		void anchor()
		{
			m_anchor = true;
			position_last = position;
		}

		void accelerate(glm::vec2 a)
		{
			acceleration += a;
		}

		void setVelocity(glm::vec2 v, float dt)
		{
			position_last = position - (v * dt);
		}

		void addVelocity(glm::vec2 v, float dt)
		{
			position_last -= v * dt;
		}

		glm::vec2 getVelocity(float dt) const
		{
			return (position - position_last) / dt;
		}
	};

	class World {
	public:
		std::vector<Object*> objs;
		glm::vec2 world_size;
		glm::vec2 gravity;
		glm::vec2 constraint_center = glm::vec2(0.0f, 0.0f);

		float frame_dt;
		float time = 0.0f;
		int substeps = 8;
		float sub_dt;
		float constraint_radius = 0.5f;

		World(glm::vec2 g, glm::vec2 ws, float fps) : gravity(g), world_size(ws)
		{
			frame_dt = 1.0f / fps;
			sub_dt = frame_dt / substeps;
		}

		void add_obj(Object* obj)
		{
			objs.push_back(obj);
		}

		void step()
		{
			for (Object* obj : objs)
			{
				if (obj->m_anchor) {
					obj->position = obj->position_last;
					continue;
				}
				// Apply Gravity

				obj->accelerate(gravity);

				// Object Collision Check

				const float response_coef = 0.75f;
				const int objects_count = objs.size();

				for (int i=0; i < objects_count; i++) {
					Object* obj_1 = objs[i];

					for (int k = i+1; k < objects_count; k++) {
						Object* obj_2 = objs[k];

						// No repeat i, k pairs in one step

						const glm::vec2 v = obj_1->position - obj_2->position;
						const float dist = sqrt(v.x * v.x + v.y * v.y);
						const float min_dist = obj_1->radius + obj_2->radius;

						// Check overlapping

						if (dist < min_dist) {
							const glm::vec2 n = v / dist;
							const float mass_ratio_1 = obj_1->radius / (obj_1->radius + obj_2->radius);
							const float mass_ratio_2 = obj_2->radius / (obj_1->radius + obj_2->radius);
							const float delta = 0.5f * response_coef * (dist - min_dist);

							// Update positions

							obj_1->position -= n * (mass_ratio_2 * delta);
							obj_2->position += n * (mass_ratio_1 * delta);
						}
					}
				}

				// Border Collision Check

				const glm::vec2 v = constraint_center - obj->position;
				const float dist = sqrt(v.x * v.x + v.y * v.y);

				if (dist > (constraint_radius - obj->radius)) {
					const glm::vec2 n = v / dist;
					obj->position = constraint_center - n * (constraint_radius - obj->radius);
				}

				// Update obj position via Verlet Integration

				obj->update(sub_dt);
			}
		}

		void update()
		{
			time += frame_dt;
			for (int i = 0; i < substeps; i++) {
				//applyConstraint();
				step();
			}
		}

		void setObjectVelocity(Object* obj, glm::vec2 v)
		{
			obj->setVelocity(v, sub_dt);
		}
	};
}