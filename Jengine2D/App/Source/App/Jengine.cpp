#include"../Headers/Jengine.h"
#include "Core/Core.h"

// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ImGui
#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui_impl_glfw.h"
#include "Vendor/imgui/imgui_impl_opengl3.h"

#include"../Headers/Shader.h"
#include"../Headers/VAO.h"
#include"../Headers/VBO.h"
#include"../Headers/EBO.h"
#include"../Headers/ShapeBuilder.h"
#include"../Headers/VBLayout.h"
#include"../Headers/Vertex.h"
#include"../Headers/Renderer.h"

// temporary, remove on cleanup
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <random>


// temporary, remove on cleanup
float get_random(float min, float max)
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(min, max);
    return dis(e);
}

Jengine::~Jengine()
{
    vao->Unbind();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* Jengine::Init(int v_major, int v_minor, GLenum profile, int width = 1600, int height = 1200, const char* window_name = "Jengine", double ts = 0.01) {

    windowX = width;
    windowY = height;

    deltaTime = ts;

    // OpenGL Init

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, v_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, v_minor);

    glfwWindowHint(GLFW_OPENGL_PROFILE, profile);

    GLFWwindow* window = glfwCreateWindow(width, height, window_name, NULL, NULL);
    if (window == NULL) {
        std::cout << "GLFW failure" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, width, height);

    // ImGui Init

    ImGui::CreateContext();
    io = &ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Matrix setup

    prog = glm::ortho((float)-width / 2, (float)width / 2, (float)-height / 2, (float)height / 2, -1.0f, 1.0f);
    view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    return (window);
}

void Jengine::BuildCircleMaps(int count, std::vector<Core::Object>& circles)
{
    for (int i = 0; i < count; i++) {
        Core::Object circle(
            glm::vec3(0.0f, 0.0f, 0.0f),
            10.0f,
            glm::vec3(
                // temporary, change on cleanup
                get_random(-2.0f, 2.0f),
                get_random(-2.0f, 2.0f),
                0.0f
            )
        );
        circles.push_back(circle);
    }

    for (auto& obj : circles) {
        world->add_obj(&obj);
    }
}

int main()
{
    Jengine jengine;
    jengine.window = jengine.Init(3, 3, GLFW_OPENGL_CORE_PROFILE, 1600, 1200, "ex", 0.01);

    VAO vao;
    jengine.vao = &vao;

    // Circle Buffer Build

    const int circle_count = 10;
    const int points = 60;
    float radius = 100.0f;

    VBO cir_VBO(nullptr, points * sizeof(Vertex) * circle_count, GL_DYNAMIC_DRAW);
    jengine.vbo = &cir_VBO;

    std::vector<GLuint> vec_cir_indices = ShapeBuilder::BuildCircleIndices(circle_count, points);
    EBO cir_EBO(&vec_cir_indices[0], ((points - 2) * 3) * circle_count);
    jengine.ebo = &cir_EBO;

    VBLayout layout;
    layout.Push<Vertex>(1);
    jengine.vao->AddBuffer(jengine.vbo, layout);

    Shader shader("Source/Defaults/default.vert", "Source/Defaults/default.frag");
    jengine.shader = &shader;
    jengine.shader->Bind();

    Renderer renderer;

    // Build Physics
    Core::World base(-9.81f);
    jengine.world = &base;

    std::vector<Core::Object> phy_circles;
    jengine.BuildCircleMaps(circle_count, phy_circles);

    Vertex vertices[points * circle_count];

    // Main Loop

    while (!glfwWindowShouldClose(jengine.window)) {

        // Timestep Physics World
        
        jengine.runTime += jengine.deltaTime;
        jengine.world->step(jengine.deltaTime);

        // Create ImGui Window

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // clear back buffer and set bg-color
        renderer.Clear(0.07f, 0.13f, 0.17f, 1.0f);

        // Circle Vertex SubBuffers

        for (int i = 0; i < circle_count; i++) {
            glm::vec3 position(base.objs[i]->Position.x * (float)(jengine.windowX/2), base.objs[i]->Position.y * (float)(jengine.windowY / 2), 0.0f);

            glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
            glm::mat4 mvp = jengine.prog * jengine.view * model;

            std::vector<Vertex> circle = ShapeBuilder::BuildCircleArray(radius, points, glm::vec4(0.8f, 0.3f, 0.02f, 1.0f), mvp);
            memcpy(vertices + i*circle.size(), circle.data(), circle.size() * sizeof(Vertex));
        }

        jengine.vbo->SubBuffer(0, sizeof(vertices), vertices);

        // Draw

        renderer.Draw(jengine.vao, jengine.ebo, jengine.shader);

        // ImGUI Controls

        {
            ImGui::Begin("Edit");

            for (int i = 0; i < circle_count; i++) {
                ImGui::SliderFloat2((std::string("Position ") + std::to_string(i)).c_str(), &base.objs[i]->Position.x, -100.0f, 100.0f);
                ImGui::SliderFloat2((std::string("Velocity ") + std::to_string(i)).c_str(), &base.objs[i]->Velocity.x, -100.0f, 100.0f);
                ImGui::SliderFloat2((std::string("Acceleration ") + std::to_string(i)).c_str(), &base.objs[i]->Acceleration.x, -100.0f, 100.0f);
            }

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / jengine.io->Framerate, jengine.io->Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(jengine.window);
        glfwPollEvents();
    }

    return 0;
}