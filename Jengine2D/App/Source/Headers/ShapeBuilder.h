#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>

static class ShapeBuilder {
public:
    std::vector<GLfloat> BuildCircleArray(float radius, int n);
    std::vector<GLuint> BuildCircleIndices(int n);
};