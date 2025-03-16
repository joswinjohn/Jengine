#include <array>
#include <cstdio>

// possibly replace with glad in the future
#include <GLES3/gl3.h>
#include <EGL/egl.h>

#include <GLFW/glfw3.h>

#define CUBE_VERTICIES 24   // 8 verticies per cube * 3 floats per vertex
#define CUBE_INDICES 36     // 3 vertices per triangle * 12 triangles per cube

#define VECTOR_3 3

class gl_cube {
public:
    unsigned int vao{};
    unsigned int vbo{};
    unsigned int ebo{};

    std::array<float, CUBE_VERTICIES> vertices = {
        // NOLINTBEGIN disable magic number linting
        -0.5F, 0.5F, 0.5F,      // top left front
        -0.5F, -0.5F, 0.5F,     // bottom left front
        0.5F, -0.5F, 0.5F,      // bottom right front
        0.5F, 0.5F, 0.5F,       // top right front
        -0.5F, 0.5F, -0.5F,     // top left back
        -0.5F, -0.5F, -0.5F,    // bottom left back
        0.5F, -0.5F, -0.5F,     // bottom right back
        0.5F, 0.5F, -0.5F       // top right back
        // NOLINTEND
    };

    std::array<unsigned int, CUBE_INDICES> indices = {
        // NOLINTBEGIN disable magic number linting
        0, 1, 2,    // triangle 1 front
        2, 3, 0,    // triangle 2 front
        4, 0, 3,    // triangle 1 top
        3, 7, 4,    // triangle 2 top
        4, 5, 6,    // triangle 1 back
        6, 7, 4,    // triangle 2 back
        1, 5, 6,    // triangle 1 bottom
        6, 2, 1,    // triangle 2 bottom
        4, 5, 1,    // triangle 1 left
        1, 0, 4,    // triangle 2 left
        7, 6, 2,    // triangle 1 right
        2, 3, 7,    // triangle 2 right
        // NOLINTEND
    };

    gl_cube() {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * CUBE_VERTICIES, vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * CUBE_INDICES, indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        
    }
};
