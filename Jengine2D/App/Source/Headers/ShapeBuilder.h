#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Vertex.h"

static class ShapeBuilder {
public:
    static std::vector<Vertex> BuildCircleArray(float radius, int n, glm::vec4 color, glm::mat4 mvp);
    static std::vector<GLuint> BuildCircleIndices(int count, int n);
};