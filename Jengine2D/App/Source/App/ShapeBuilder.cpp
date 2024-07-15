#include"../Headers/ShapeBuilder.h"

// temporary, remove on cleanup
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

std::vector<Vertex> ShapeBuilder::BuildCircleArray(float radius, int n, glm::vec4 color, glm::mat4 mvp) {
    glm::vec4 point_pos;
    int theta = 0;
    std::vector<Vertex> buffer_data;

    while (theta < 360) {

        point_pos.x = (radius * cosf(theta));
        point_pos.y = (radius * sinf(theta));
        point_pos.z = 0.0f;
        point_pos.w = 1.0f;

        glm::vec4 m_pos = mvp * point_pos;
        glm::vec2 o_pos(m_pos.x, m_pos.y);

        buffer_data.push_back(Vertex(o_pos, color));

        theta = theta + (360 / n);
    }
    return buffer_data;
};

std::vector<GLuint> ShapeBuilder::BuildCircleIndices(int count, int n) {
    std::vector<GLuint> indices;
    for (int j = 0; j < count; j++) {
        for (int i = 0; i < n - 2; i++)
        {
            indices.push_back(j*n);
            indices.push_back(j*n + i + 1);
            indices.push_back(j*n + i + 2);
        }
    }
    return indices;
}