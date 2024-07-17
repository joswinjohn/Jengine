#include"../Headers/Jengine.h"
#include "Core/Core.hpp"

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

bool fequals(double a, double b)
{
    return fabs(a - b) < 0.001;
}

Jengine::~Jengine()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* Jengine::Init(int v_major, int v_minor, GLenum profile, int width = 1200, int height = 1200, const char* window_name = "Jengine", double ts = 0.01) {

    windowX = width;
    windowY = height;

    rad_factor = width / 2;

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

void Jengine::AddCircle(float radius, glm::vec4 color, glm::vec2 position)
{
    static std::uniform_real_distribution<> r_rad(0.01f, 0.03f);
    static std::uniform_real_distribution<> r_pos(-0.01f, 0.01f);
    static std::uniform_real_distribution<> r_col(0.0f, 1.0f);

    Core::Object circle(
        // temporary, change on cleanup
        radius, //get_random(0.01f, 0.02f),
        position,
        color
    );

    circle.position_last = position;
    circle.addVelocity(glm::vec2(0.8f, -1.0f), deltaTime);
    circles[count-1] = circle;
    world->add_obj(&circles[count-1]);
    
    std::cout << "AddedCircle: " << count - 1 << " | " << circles[count - 1].position.x << ", " << circles[count - 1].position.y << std::endl;
}

void Jengine::Run() {
    j_running = true;
    while (!glfwWindowShouldClose(window)) {
        runTime += deltaTime;
        world->step();

        OnUpdate(deltaTime);
        OnImGuiUpdate();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    j_running = false;
}

void Jengine::OnUpdate(double ts) {
    // Create ImGui Window
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static std::uniform_real_distribution<> r_rad(0.02f, 0.06f);
    static std::uniform_real_distribution<> r_pos(-0.01f, 0.01f);
    static std::uniform_real_distribution<> r_col(0.0f, 1.0f);

    // clear back buffer and set bg-color
    renderer->Clear(bg_color);
     
    if (fequals(fmod(runTime, 0.1 ), 0.0) && (count < max_count)) {
        count++;
        AddCircle(r_rad(r_engine), glm::vec4(cosf(count), sinf(count), count / 100.0f, 1.0f), glm::vec2(-0.2, 0.3));
    }

    for (int i = 0; i < count; i++) {
        glm::vec3 position(world->objs[i]->position.x * (windowX / 2), world->objs[i]->position.y * (windowY / 2), 0.0f);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 mvp = prog * view * model;
        
        std::vector<Vertex> circle = ShapeBuilder::BuildCircleArray(world->objs[i]->radius * rad_factor, points, world->objs[i]->color, mvp);
        memcpy(vertices + i * circle.size(), circle.data(), circle.size() * sizeof(Vertex));
    }

    vbo->SubBuffer(0, points * count * sizeof(Vertex), vertices);
    // Draw

    renderer->Draw(vao, ebo, shader);
}

void Jengine::OnImGuiUpdate() {
    ImGui::Begin("Edit");

    ImGui::Text("Circle Count %d", count);

    ImGui::BeginChild("Scrolling", ImVec2(400.0f, 200.0f));
    for (int i = 0; i < count; i++) {
        ImGui::SliderFloat((std::string("Radius ") + std::to_string(i)).c_str(), &world->objs[i]->radius, 0.0f, world->constraint_radius);
        ImGui::Checkbox((std::string("Anchor ") + std::to_string(i)).c_str(), &world->objs[i]->m_anchor);
    }
    ImGui::EndChild();

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}