#pragma once

#include<glad/glad.h>
#include<glm/glm.hpp>

#include <vector>

#include"Vertex.h"

class VBO
{
public:
	GLuint ID;
	std::vector<Vertex> vertices;

	VBO(GLfloat* vertices, GLsizeiptr size, GLenum type);
	~VBO();

	void SubBuffer(GLint offset, GLsizeiptr size, Vertex* vertices);

	void Bind() const;
	void Unbind() const;
};