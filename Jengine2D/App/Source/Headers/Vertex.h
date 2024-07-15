#pragma once

#include <iostream>
#include <glad/glad.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

struct Vertex {
public:
	glm::vec2 Position;
	glm::vec4 Color;

	Vertex(glm::vec2 pos = glm::vec2(0.0f, 0.0f), glm::vec4 col = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)) : Position(pos), Color(col) {}
};