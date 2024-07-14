#pragma once

#include <vector>
#include <glad/glad.h>
#include"Renderer.h"

struct VBElement {
	GLuint type;
	GLuint count;
	unsigned char normalized;

	static GLuint GetTypeSize(GLuint type) {
		switch (type) {
			case GL_FLOAT:			return sizeof(GLfloat);
			case GL_UNSIGNED_INT:	return sizeof(GLuint);
			case GL_UNSIGNED_BYTE:	return sizeof(GLbyte);
		}
		ASSERT(false);
		return 0;
	}
};

class VBLayout
{
private:
	std::vector<VBElement> elements;
	GLuint stride;
public:
	VBLayout() 
		: stride(0) {}

	template<typename T>
	void Push(GLuint count) {
		static_assert(false);
	}

	template<>
	void Push<GLfloat>(GLuint count) {
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += count * sizeof(GLfloat);
	}

	template<>
	void Push<GLuint>(GLuint count) {
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += count * sizeof(GLuint);
	}

	template<>
	void Push<unsigned char>(GLuint count) {
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		stride += count * sizeof(GLbyte);
	}

	inline const std::vector<VBElement> GetElements() const { return elements;  }
	inline GLuint GetStride() const { return stride; }
};