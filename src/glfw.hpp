#include <cstdio>
#include <cstdlib>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include <GLFW/glfw3.h>

#define MAJOR_VER 3
#define MINOR_VER 3

#define BACKGROUND_COLOR 0.043F, 0.035F, 0.050F, 1.0F

class glfw {
public:
    // assign ..structors as default due to non-default deconstructor (suggested by clang-tidy)
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

struct window {
    GLFWwindow* winptr = nullptr;
    int view_height;
    int view_width;

    // initialize window
    window(int h, int w, const char* window_name) {
        // create window
        winptr = glfwCreateWindow(w, h, window_name, nullptr, nullptr);

        // assign width and height
        view_height = h;
        view_width = w;

        if (winptr == nullptr) {
            // get gl error if window fails to start
            const char* err = nullptr;
            glfwGetError(&err);
            printf("GLFW window failed: %s", err);

            // exit due to window error
            glfw::exit(-1);
        }
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
        glfw::exit(-1);
    }

    void update() const {
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(winptr);
        glfwPollEvents();
    }
};
