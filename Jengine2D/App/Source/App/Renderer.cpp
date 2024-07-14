#include"../Headers/Renderer.h"
#include <iostream>

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear(float f0, float f1, float f2, float f3) const {
	glClearColor(f0, f1, f2, f3);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VAO& vao, const EBO& ebo, const Shader& shader) const {
	shader.Bind();
	vao.Bind();
	ebo.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr));
}