#include"../Headers/ShapeBuilder.h"

std::vector<GLfloat> ShapeBuilder::BuildCircleArray(float radius, int n) {
    GLfloat x;
    GLfloat y;
    int theta = 0;
    std::vector<GLfloat> buffer_data;

    while (theta < 360) {

        x = (GLfloat)radius * cosf(theta);
        y = (GLfloat)radius * sinf(theta);

        buffer_data.push_back(x);
        buffer_data.push_back(y);

        theta = theta + (360 / n);
    }
    return buffer_data;
}

std::vector<GLuint> ShapeBuilder::BuildCircleIndices(int n) {
    std::vector<GLuint> indices;
    for (int i = 0; i < n - 2; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }
    return indices;
}