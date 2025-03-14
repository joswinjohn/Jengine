#include <cstdio>
#include <fstream>
#include <sstream>

// possibly replace with glad in the future
#include <GLES3/gl3.h>
#include <EGL/egl.h>

#include <GLFW/glfw3.h>

#define CHAR_BUFFER_SIZE

class GL_object {
    std::string m_vertex_shader_string;
    std::string m_fragment_shader_string;

    GL_object(const char* vertex_shader_file, const char* fragment_shader_file) {
        unsigned int VAO;
        unsigned int VBO;

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

class gl_cube : GL_object {
public:
    // implicit structors from clang-tidy
    gl_cube(const gl_cube&) = default;
    gl_cube(gl_cube&&) = default;
    gl_cube& operator=(const gl_cube&) = default;
    gl_cube& operator=(gl_cube&&) = default;

};
