#pragma once

#include <cstdio>
#include <cstdlib>

#include <fstream>
#include <sstream>
#include <GLES3/gl3.h>

#include "globjects.hpp"

#define MAJOR_VER 3
#define MINOR_VER 3

#define BACKGROUND_COLOR 0.043F, 0.035F, 0.050F, 1.0F

class glfw {
public:
    // implicit structors from clang-tidy
    glfw(const glfw&) = default;
    glfw(glfw&&) = delete;
    glfw& operator=(const glfw&) = default;
    glfw& operator=(glfw&&) = delete;

    // exit glfw windows on deconstruction
    ~glfw() {
        glfwTerminate();
    }

    // initialize glfw
    static void init() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VER);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VER);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    // explicit exit
    static void exit(const int exit_code) {
        glfwTerminate();
        std::exit(exit_code);
    }

    static void framebuffer_size_callback([[maybe_unused]] GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
};

class window {
public:
    GLFWwindow* winptr = nullptr;
    int view_height;
    int view_width;

    // store shader source text
    const char* m_vertex_shader_string{};
    const char* m_fragment_shader_string{};

    // shader states
    unsigned int vertex_shader{};
    unsigned int fragment_shader{};
    unsigned int shader_program{};

    // initialize gl window
    window(int h, int w, const char* window_name) {
        // create window
        winptr = glfwCreateWindow(w, h, window_name, nullptr, nullptr);

        // assign width and height
        view_height = h;
        view_width = w;

        // get gl error if window fails to start
        if (winptr == nullptr) {
            const char* err = nullptr;
            glfwGetError(&err);
            // NOLINTNEXTLINE printf > cout :)
            printf("GLFW window failed: %s", err);

            // exit due to window error
            glfw::exit(-1);
        }
    }

    void load_shaders(const char* vertex_shader_file, const char* fragment_shader_file) {
        // read shader files
        read_file(vertex_shader_file, m_vertex_shader_string);
        read_file(fragment_shader_file, m_fragment_shader_string);
        
        // log reads

        // compile shaders
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &m_vertex_shader_string, nullptr);
        glCompileShader(vertex_shader);

        fragment_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(fragment_shader, 1, &m_fragment_shader_string, nullptr);
        glCompileShader(fragment_shader);

        // log shader compilations

        shader_program = glCreateProgram();

        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);

        glLinkProgram(shader_program);
        glUseProgram(shader_program);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        // log shader program
    }

    static void read_file(const char* file, const char* out) {
        std::ifstream ifs(file);
        std::stringstream buffer;

        buffer << ifs.rdbuf();
        out = buffer.str().c_str();
    }

    // initalize window and start update loop
    void start() const {
        
        // set window size
        glViewport(0, 0, view_width, view_height);
        glfwMakeContextCurrent(winptr);

        // change viewport size on resize
        glfwSetFramebufferSizeCallback(winptr, glfw::framebuffer_size_callback);


        // start update loop
        while(glfwWindowShouldClose(winptr) == 0) {
            update();
        }

        // exit glfw safely
        glfw::exit(0);
    }
    
    // update loop
    void update() const {
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(winptr);
        glfwPollEvents();
    }
};
