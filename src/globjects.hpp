#include <array>
#include <cstdio>
#include <fstream>
#include <sstream>

// possibly replace with glad in the future
#include <GLES3/gl3.h>
#include <EGL/egl.h>

#include <GLFW/glfw3.h>

#define CHAR_BUFFER_SIZE

class gl_object {
public:
    std::string m_vertex_shader_string;
    std::string m_fragment_shader_string;

    unsigned int VAO;
    unsigned int VBO;

    gl_object(const char* vertex_shader_file, const char* fragment_shader_file) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        read_shader(vertex_shader_file, &m_vertex_shader_string);
        read_shader(fragment_shader_file, &m_fragment_shader_string);
    }

    static void read_shader(const char* shader_file, std::string* out) {
        std::ifstream ifs(shader_file);
        std::stringstream buffer;

        buffer << ifs.rdbuf();
        *out = buffer.str();
    }
};

#define CUBE_VERTICIES 24   // 8 verticies per cube * 3 floats per vertex
#define CUBE_INDICES 36     // 3 vertices per triangle * 12 triangles per cube

class gl_cube : gl_object {
public:
    unsigned int EBO{};

    std::array<float, CUBE_VERTICIES> vertices = {
        // disable magic number linting
        // NOLINTBEGIN
        -0.5F, 0.5F, 0.0F,  // top left
        -0.5F, -0.5F, 0.0F, // bottom left
        0.5F, -0.5F, 0.0F,  // bottom right
        0.5F, 0.5F, 0.0F    // top right
        // NOLINTEND
    };

    std::array<unsigned int, CUBE_INDICES> indices = {
        0, 1, 2,    // bottom left
        2, 3, 0     // top right
    };

    gl_cube(const char* vertex_shader_file, const char* fragment_shader_file) : gl_object(vertex_shader_file, fragment_shader_file) {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * CUBE_VERTICIES, vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * CUBE_INDICES, indices.data(), GL_STATIC_DRAW);
    }
};
