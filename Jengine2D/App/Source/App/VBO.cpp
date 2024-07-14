#include"../Headers/VBO.h"
#include"../Headers/Renderer.h"

#include<glm/glm.hpp>

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	GLCall(glGenBuffers(1, &ID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

void VBO::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
}

void VBO::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VBO::~VBO()
{
	GLCall(glDeleteBuffers(1, &ID));
}