#pragma once

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

#include <random>

class Jengine {
public:
	bool j_running = false;

	int windowX = 1600;
	int windowY = 1200;

	GLFWwindow* window;
	ImGuiIO* io;

	Renderer* renderer;
	Shader* shader;
	VAO* vao;
	VBO* vbo;
	EBO* ebo;

	int circle_count;
	int points;
	float radius;

	Vertex* vertices;

	glm::mat4 prog;
	glm::mat4 view;

	Core::World* world;

	double runTime = 0.0;
	double deltaTime;

	~Jengine();

	GLFWwindow* Init(int v_major, int v_minor, GLenum profile, int height, int width, const char* window_name, double ts);
	void BuildCircleMaps(int count, std::vector<Core::Object>& circles);

	void Run();
	void OnUpdate(double ts);
	void OnImGuiUpdate();
};