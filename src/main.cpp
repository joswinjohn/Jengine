#include <cstdio>

#include "lib.hpp"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 600

int main() {
    glfw::init();

    window win(WINDOW_WIDTH, WINDOW_HEIGHT, "Jengine");

    // load shaders from file
    win.load_shaders("shaders/vertex_cube.glsl", "shaders/fragment_cube.glsl");

    // create gl objects
    gl_cube cube;

    // start window
    win.start();
    
    return 0;
}
