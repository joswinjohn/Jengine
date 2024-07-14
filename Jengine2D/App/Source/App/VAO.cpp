#include"../Headers/VAO.h"
#include"../Headers/Renderer.h"
#include"../Headers/VBLayout.h"

#include<iostream>

VAO::VAO()
{
	GLCall(glGenVertexArrays(1, &ID));
}

void VAO::AddBuffer(const VBO& vbo, const VBLayout& layout)
{
	Bind();
	vbo.Bind();
	const auto& elements = layout.GetElements();
	GLuint offset = 0;
	for (GLuint i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, 0, layout.GetStride(), (const void*)offset));

		std::cout << "added buffer: " << i << ", " << element.count << ", " << element.type << ", " << element.normalized << ", " << layout.GetStride() << ", " << offset << ", " << std::endl;

		offset += element.count * VBElement::GetTypeSize(element.type);
	}
	
	
	vbo.Unbind();
}

void VAO::Bind() const
{
	GLCall(glBindVertexArray(ID));
}

void VAO::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

VAO::~VAO()
{
	GLCall(glDeleteVertexArrays(1, &ID));
}