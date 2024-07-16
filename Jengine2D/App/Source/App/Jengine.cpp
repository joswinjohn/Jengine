#include"../Headers/Jengine.h"
#include "Core/Core.h"

// temporary, remove on cleanup
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


// temporary, remove on cleanup
float get_random(float min, float max)
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(min, max);
    return dis(e);
}

Jengine::~Jengine()
{
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

    GLFWwindow* win = glfwCreateWindow(width, height, window_name, NULL, NULL);
    if (win == NULL) {
        std::cout << "GLFW failure" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(win);

    gladLoadGL();

    glViewport(0, 0, width, height);

    // ImGui Init

    ImGui::CreateContext();
    io = &ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    // Matrix setup

    prog = glm::ortho((float)-width / 2, (float)width / 2, (float)-height / 2, (float)height / 2, -1.0f, 1.0f);
    view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    return (win);
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

void Jengine::Run() {
    j_running = true;
    while (!glfwWindowShouldClose(window)) {
        OnUpdate(deltaTime);
        OnImGuiUpdate();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    j_running = false;
}

void Jengine::OnUpdate(double ts) {
    // Timestep Physics World

    runTime += deltaTime;
    world->step(deltaTime);

    // Create ImGui Window

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // clear back buffer and set bg-color
    renderer->Clear(0.07f, 0.13f, 0.17f, 1.0f);

    // Circle Vertex SubBuffers

    for (int i = 0; i < circle_count; i++) {
        glm::vec3 position(world->objs[i]->Position.x * (float)(windowX / 2), world->objs[i]->Position.y * (float)(windowY / 2), 0.0f);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 mvp = prog * view * model;

        std::vector<Vertex> circle = ShapeBuilder::BuildCircleArray(radius, points, glm::vec4(0.8f, 0.3f, 0.02f, 1.0f), mvp);
        memcpy(vertices + i * circle.size(), circle.data(), circle.size() * sizeof(Vertex));
    }

    vbo->SubBuffer(0, points * circle_count * sizeof(Vertex), vertices);

    // Draw

    renderer->Draw(vao, ebo, shader);
}

void Jengine::OnImGuiUpdate() {
    ImGui::Begin("Edit");

    for (int i = 0; i < circle_count; i++) {
        ImGui::SliderFloat2((std::string("Position ") + std::to_string(i)).c_str(), &world->objs[i]->Position.x, -100.0f, 100.0f);
        ImGui::SliderFloat2((std::string("Velocity ") + std::to_string(i)).c_str(), &world->objs[i]->Velocity.x, -100.0f, 100.0f);
        ImGui::SliderFloat2((std::string("Acceleration ") + std::to_string(i)).c_str(), &world->objs[i]->Acceleration.x, -100.0f, 100.0f);
    }

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}