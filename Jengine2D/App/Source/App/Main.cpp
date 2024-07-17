#include"../Headers/Jengine.h"
#include "Core/Core.hpp"

const int circle_count = 100;
const int points = 60;

int main()
{
    Jengine jengine;
    jengine.window = jengine.Init(3, 3, GLFW_OPENGL_CORE_PROFILE, 1200, 1200, "ex", 1.0f / 60);

    VAO vao;

    VBO vbo(nullptr, points * sizeof(Vertex) * circle_count, GL_DYNAMIC_DRAW);

    std::vector<GLuint> vec_cir_indices = ShapeBuilder::BuildCircleIndices(circle_count, points);
    EBO ebo(&vec_cir_indices[0], ((points - 2) * 3) * circle_count);

    VBLayout layout;
    layout.Push<Vertex>(1);
    vao.AddBuffer(&vbo, layout);

    Shader shader("Source/Defaults/default.vert", "Source/Defaults/default.frag");
    shader.Bind();

    Renderer renderer;

    Core::World base(glm::vec2(0.0f, -60.0f), glm::vec2(jengine.windowX, jengine.windowY), 60.0f);

    jengine.vao = &vao;
    jengine.vbo = &vbo;
    jengine.ebo = &ebo;
    jengine.shader = &shader;
    jengine.renderer = &renderer;
    jengine.world = &base;

    jengine.max_count = circle_count;
    jengine.count = 0;
    jengine.points = points;

    jengine.bg_color = glm::vec4(0.07f, 0.13f, 0.17f, 1.0f);
    
    Core::Object circles[circle_count];
    jengine.circles = circles;
    //jengine.AddCircles(circle_count);
    //jengine.AddCircle(0.04f, glm::vec4(cosf(1), sinf(1), 1 / 100.0f, 1.0f), glm::vec2(-0.2, 0.3));

    Vertex vertices[points * circle_count];
    jengine.vertices = &vertices[0];

    // Main Loop

    jengine.Run();

    return 0;
}