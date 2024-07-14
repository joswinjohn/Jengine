#include "Core/Core.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui_impl_glfw.h"
#include "Vendor/imgui/imgui_impl_opengl3.h"

#include"../Headers/Shader.h"
#include"../Headers/VAO.h"
#include"../Headers/VBO.h"
#include"../Headers/EBO.h"
#include"../Headers/ShapeBuilder.h"
#include"../Headers/VBLayout.h"

#include"../Headers/Renderer.h"

// Check if two numerical values are equal with tolerance
// tolerance check with doubles
bool equal_tolerance(double a, double b, double epsilon = 1e-9) {
    return std::abs(a - b) < epsilon;
}

// tolerance check with floats
bool equal_tolerance(float a, float b, float epsilon = 1e-9f) {
    return std::abs(a - b) < epsilon;
}

//

// Vertices coordinates
GLfloat vertices[] = {
//                 coords                                         colors          
    -0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.0f,     0.8f, 0.3f,  0.02f, 1.0f, // Lower left corner
     0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.0f,     0.8f, 0.3f,  0.02f, 1.0f, // Lower right corner
     0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 0.0f,     0.8f, 0.3f,  0.02f, 1.0f, // Upper corner
    -0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f, 0.0f,     0.8f, 0.3f,  0.02f, 1.0f, // Inner left
     0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f, 0.0f,     0.8f, 0.3f,  0.02f, 1.0f, // Inner right
     0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.0f,     0.8f, 0.3f,  0.02f, 1.0f  // Inner down
};

GLfloat vertices_no_col[] = {
    //                 coords                                      
        -0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.0f, // Lower left corner
         0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.0f, // Lower right corner
         0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 0.0f, // Upper corner
        -0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f, 0.0f, // Inner left
         0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f, 0.0f, // Inner right
         0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.0f // Inner down
};

GLfloat vertices_sim[] = {
    //                 coords                                      
        -0.5f, -0.5f * float(sqrt(3)) * 1 / 3, // Lower left corner
         0.5f, -0.5f * float(sqrt(3)) * 1 / 3, // Lower right corner
         0.0f,  0.5f * float(sqrt(3)) * 2 / 3, // Upper corner
        -0.25f, 0.5f * float(sqrt(3)) * 1 / 6, // Inner left
         0.25f, 0.5f * float(sqrt(3)) * 1 / 6, // Inner right
         0.0f, -0.5f * float(sqrt(3)) * 1 / 3 // Inner down
};

// Indices for vertices order
GLuint indices[] = {
    0, 1, 2
};

//remove on cleanup
GLuint cir_indices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 3, 4,
    0, 4, 5,
    0, 5, 6,
    0, 6, 7,
    0, 7, 8,
    0, 8, 9,
    0, 9, 10,
    0, 10, 11,
    0, 11, 12,
    0, 12, 13,
    0, 13, 14,
    0, 14, 15,
    0, 15, 16,
    0, 16, 17,
    0, 17, 18,
    0, 18, 19,
    0, 19, 20,
    0, 20, 21,
    0, 21, 22,
    0, 22, 23,
    0, 23, 24,
    0, 24, 25,
    0, 25, 26,
    0, 26, 27,
    0, 27, 28,
    0, 28, 29,
};

//

//remove on cleanup
/*
GLfloat* build_cir_array(float radius = 0.5f) {
    GLfloat x;
    GLfloat y;
    GLfloat z = 0.0f;
    int theta = 0;
    int currentSize = 0;
    const int n = 30;
    GLfloat buffer_data[6+(n*6)];

    buffer_data.push_back() = z;
    buffer_data.push_back() = z;
    buffer_data.push_back() = z;
    buffer_data.push_back() = (GLfloat) 0.8f;
    buffer_data.push_back() = (GLfloat) 0.3f;
    buffer_data.push_back() = (GLfloat) 0.02f;

    while (theta < 360) {

        x = (GLfloat)radius * cosf(theta);
        y = (GLfloat)radius * sinf(theta);

        buffer_data.push_back() = x;
        buffer_data.push_back() = y;
        buffer_data.push_back() = z;
        std::cout << currentSize << " | " << z << " | " << buffer_data[currentSize] << std::endl;
        buffer_data.push_back() = (GLfloat) 0.8f;
        std::cout << currentSize << " | " << (GLfloat) 0.8f << " | " << buffer_data[currentSize] << std::endl;
        buffer_data.push_back() = (GLfloat) 0.3f;
        buffer_data.push_back() = (GLfloat) 0.02f;

        theta = theta + (360 / n);
    }
    std::cout << currentSize << std::endl;
    return buffer_data;
}
*/

//

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int windowX = 1600;
    const int windowY = 1200;

    GLFWwindow* window = glfwCreateWindow(windowX, windowY, "Jengine", NULL, NULL);
    if (window == NULL) {
        std::cout << "GLFW failure" << std::endl;
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, windowX, windowY);

    // Circle VAO

    VAO cir_VAO;
    cir_VAO.Bind();

    // Build Circle

    ShapeBuilder builder;

    const int points = 60;
    const GLfloat radius = 100.0f;

    // Build Arrays for vertices and indices

    std::vector<GLfloat> vec_cir_verts = builder.BuildCircleArray(radius, points);
    GLfloat cir_verts_arr[points * 2];
    std::copy(vec_cir_verts.begin(), vec_cir_verts.end(), cir_verts_arr);

    for (GLfloat vert : cir_verts_arr) {
        std::cout << vert << std::endl;
    }

    std::cout << vec_cir_verts.size() << std::endl << points * 8 << std::endl;

    std::vector<GLuint> vec_cir_indices = builder.BuildCircleIndices(points);
    GLuint cir_indices_arr[(points - 2) * 3];
    std::copy(vec_cir_indices.begin(), vec_cir_indices.end(), cir_indices_arr);

    VBO cir_VBO(cir_verts_arr, sizeof(cir_verts_arr));
    EBO cir_EBO(cir_indices_arr, (points - 2) * 3);

    VBLayout cir_layout;
    cir_layout.Push<GLfloat>(2);
    cir_VAO.AddBuffer(cir_VBO, cir_layout);

    cir_VAO.Unbind();
    cir_VBO.Unbind();
    cir_EBO.Unbind();

    Shader shader("Source/Defaults/default.vert", "Source/Defaults/default.frag");
    shader.Bind();

    shader.SetUniform4f("u_color", 0.8f, 0.3f, 0.02f, 1.0f);

    glm::mat4 prog = glm::ortho((float)-windowX / 2, (float)windowX / 2, (float)-windowY / 2, (float)windowY / 2, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    Renderer renderer;

    // Build Physics

    Core::World base(-9.81f* (float)windowY / 2);

    Core::Object ball(
        1.0, // Id
        glm::vec3(0.0f, 0.0f, 0.0f), // Position
        10.0f, // Mass
        glm::vec3(2.0f * (float)windowX / 2, 3.0f * (float)windowY / 2, 0.0f) // Velocity
    );

    Core::Object ball2(
        2.0, // Id
        glm::vec3(0.0f, 0.0f, 0.0f), // Position
        10.0f, // Mass
        glm::vec3(-1.0f * (float)windowX / 2, 3.0f * (float)windowY / 2, 0.0f)  // Velocity
    );

    base.add_obj(&ball);
    base.add_obj(&ball2);

    double current_time = 0.0;
    double delta_time = 0.01;

    //ImGUI

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!glfwWindowShouldClose(window)) {
        current_time += delta_time;
        base.step(delta_time);

        //clear back buffer
        renderer.Clear(0.07f, 0.13f, 0.17f, 1.0f);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), ball.Position);
            glm::mat4 mvp = prog * view * model;
            
            shader.Bind();

            shader.SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(cir_VAO, cir_EBO, shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), ball2.Position);
            glm::mat4 mvp = prog * view * model;
            
            shader.Bind();

            shader.SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(cir_VAO, cir_EBO, shader);
        }

        {
            ImGui::Begin("Edit");

            ImGui::SliderFloat2("Ball 1 Position", &ball.Position.x, (float)-windowX / 2, (float)windowX / 2);
            ImGui::SliderFloat2("Ball 2 Position", &ball2.Position.x, (float)-windowX / 2, (float)windowX / 2);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}