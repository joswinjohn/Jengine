#include"../Headers/EBO.h"
#include"../Headers/Renderer.h"

// Constructor that generates a Elements Buffer Object and links it to indices
EBO::EBO(GLuint* indices, GLuint i_count)
	: count(i_count)
{
	GLCall(glGenBuffers(1, &ID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_count * sizeof(GLuint), indices, GL_STATIC_DRAW));
}

// Binds the EBO
void EBO::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
}

// Unbinds the EBO
void EBO::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

EBO::~EBO()
{
	GLCall(glDeleteBuffers(1, &ID));
}