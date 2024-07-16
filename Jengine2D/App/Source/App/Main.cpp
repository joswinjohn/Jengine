#include"../Headers/Jengine.h"
#include "Core/Core.h"

const int circle_count = 10;
const int points = 60;
float radius = 100.0f;

int main()
{
    Jengine jengine;
    jengine.window = jengine.Init(3, 3, GLFW_OPENGL_CORE_PROFILE, 1600, 1200, "ex", 0.01);

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

    Core::World base(-9.81f);

    jengine.vao = &vao;
    jengine.vbo = &vbo;
    jengine.ebo = &ebo;
    jengine.shader = &shader;
    jengine.renderer = &renderer;
    jengine.world = &base;

    jengine.circle_count = circle_count;
    jengine.points = points;
    jengine.radius = radius;

    std::vector<Core::Object> phy_circles;
    jengine.BuildCircleMaps(circle_count, phy_circles);

    Vertex vertices[points * circle_count];
    jengine.vertices = &vertices[0];

    // Main Loop

    jengine.Run();

    return 0;
}