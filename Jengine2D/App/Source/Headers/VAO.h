#pragma once

#include<glad/glad.h>
#include"VBO.h"

class VBLayout;

class VAO
{
public:
	GLuint ID;

	VAO();
	~VAO();

	void AddBuffer(const VBO* vbo, const VBLayout& layout);
	void Bind() const;
	void Unbind() const;
};