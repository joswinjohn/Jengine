#include <cstdio>

#include "lib.hpp"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 600

int main() {
    glfw::init();

    window win(WINDOW_WIDTH, WINDOW_HEIGHT, "Jengine");
    win.start();
    
    return 0;
}
