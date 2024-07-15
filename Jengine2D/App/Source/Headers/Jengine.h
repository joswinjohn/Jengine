#pragma once

#include"../Headers/Jengine.h"
#include "Core/Core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	int windowX = 1600;
	int windowY = 1200;

	GLFWwindow* window;
	ImGuiIO* io;

	Shader* shader;
	VAO* vao;
	VBO* vbo;
	EBO* ebo;

	glm::mat4 prog;
	glm::mat4 view;

	Core::World* world;

	double runTime = 0.0;
	double deltaTime;

	~Jengine();

	GLFWwindow* Init(int v_major, int v_minor, GLenum profile, int height, int width, const char* window_name, double ts);
	void BuildCircleMaps(int count, std::vector<Core::Object>& circles);
};