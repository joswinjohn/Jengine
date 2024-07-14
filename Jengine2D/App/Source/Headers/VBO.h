#pragma once

#include<glad/glad.h>
#include<glm/glm.hpp>

class VBO
{
public:
	GLuint ID;

	VBO(GLfloat* vertices, GLsizeiptr size);
	~VBO();

	void Bind() const;
	void Unbind() const;
};