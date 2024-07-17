#pragma once

#include<glad/glad.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#include "VAO.h"
#include "EBO.h"
#include "Shader.h"

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
	void Clear(glm::vec4 color) const;
	void Draw(const VAO* vao, const EBO* ebo, const Shader* shader) const;
};