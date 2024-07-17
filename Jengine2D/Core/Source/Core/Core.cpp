//#include <iostream>
//#include <vector>
//
//namespace Core {
//
//    
//
//    void World::add_obj(Object* obj) 
//    {
//        obj->exert(glm::vec3(gravity, 0.0f));
//        objs.push_back(obj);
//    }
//
//    void World::step(float deltaTime) 
//    {
//        for (Object* obj : objs) 
//        {
//            const glm::vec2 v = m_constraint_center - obj.position;
//            const float        dist = sqrt(v.x * v.x + v.y * v.y);
//            if (dist > (m_constraint_radius - obj.radius)) {
//                const sf::Vector2f n = v / dist;
//                obj.position = m_constraint_center - n * (m_constraint_radius - obj.radius);
//            }
//
//            obj->Position += obj->Velocity * deltaTime;
//            obj->Velocity += obj->Acceleration * deltaTime;
//        }
//    }
//
//    World::World(glm::vec2 g, glm::vec2 ws) 
//    {
//        gravity = g;
//        world_size = ws;
//    }
//}