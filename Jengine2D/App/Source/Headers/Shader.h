#pragma once

#include<glad/glad.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<string>
#include<unordered_map>


std::string get_file_contents(const char* filename);

class Shader
{
private:
	GLuint ID;
	std::unordered_map<std::string, GLuint> UniformLocationCache;
public:
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1f(const std::string& name, GLfloat f);
	void SetUniform4f(const std::string& name, GLfloat f0, GLfloat f1, GLfloat f2, GLfloat f3);
	void SetUniform4fv(const std::string& name, glm::vec4 vec);
	void SetUniformMat4f(const std::string& name, glm::mat4& mat);
private:
	GLuint GetUniformLocation(const std::string& name);
	void compileErrors(unsigned int shader, const char* type);
};