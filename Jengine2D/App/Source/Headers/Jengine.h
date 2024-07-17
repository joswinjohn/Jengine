#pragma once

#include"../Headers/Jengine.h"
#include "Core/Core.hpp"

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

	float windowX = 1600;
	float windowY = 1200;

	glm::vec4 bg_color;

	float rad_factor;

	std::default_random_engine r_engine;

	GLFWwindow* window;
	ImGuiIO* io;

	Renderer* renderer;
	Shader* shader;
	VAO* vao;
	VBO* vbo;
	EBO* ebo;

	int max_count;
	int count;
	int points;

	Core::Object* circles;

	Vertex* vertices;

	glm::mat4 prog;
	glm::mat4 view;

	Core::World* world;

	double runTime = 0.0;
	double deltaTime;
	double substepCount = 8;

	~Jengine();

	GLFWwindow* Init(int v_major, int v_minor, GLenum profile, int height, int width, const char* window_name, double ts);
	void AddCircle(float radius, glm::vec4 color, glm::vec2 position);

	void Run();
	void OnUpdate(double ts);
	void OnImGuiUpdate();
};