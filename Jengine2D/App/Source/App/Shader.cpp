#include"../Headers/Shader.h"
#include"../Headers/Renderer.h"

#include <Windows.h>

#include<fstream>
#include<sstream>
#include<iostream>

//remove on cleanup
/*
std::string getCurrentDirectoryOnWindows()
{
	const unsigned long maxDir = 260;
	wchar_t currentDir[maxDir];
	GetCurrentDirectory(maxDir, currentDir);
	std::wstring ws(currentDir);
	std::string current_dir(ws.begin(), ws.end());
	return std::string(current_dir);
}
*/

std::string get_file_contents(const char* filename)
{
	//remove on cleanup
	// std::string path = getCurrentDirectoryOnWindows();
	// std::cout << filename << std::endl << path << std::endl;

	//

	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}

	// Error checking
	if (in.fail())
	{
		std::ios_base::iostate state = in.rdstate();

		if (state & std::ios_base::eofbit)
		{
			std::cout << "End of file reached." << std::endl;
		}
		if (state & std::ios_base::failbit)
		{
			std::cout << "Non-fatal I/O error occurred." << std::endl;
		}
		if (state & std::ios_base::badbit)
		{
			std::cout << "Fatal I/O error occurred." << std::endl;
		}

		// Print system error message
		std::perror("Error: ");
	}
	return("err");
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
	: ID(0)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLCall(glShaderSource(vertexShader, 1, &vertexSource, NULL));
	GLCall(glCompileShader(vertexShader));
	compileErrors(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLCall(glShaderSource(fragmentShader, 1, &fragmentSource, NULL));
	GLCall(glCompileShader(fragmentShader));
	compileErrors(fragmentShader, "FRAGMENT");

	ID = glCreateProgram();
	GLCall(glAttachShader(ID, vertexShader));
	GLCall(glAttachShader(ID, fragmentShader));
	GLCall(glLinkProgram(ID));
	compileErrors(ID, "PROGRAM");

	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(ID));
}

void Shader::Bind() const {
	GLCall(glUseProgram(ID));
}

void Shader::Unbind() const {
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1f(const std::string& name, GLfloat f) {
	GLCall(glUniform1f(GetUniformLocation(name), f));
}

void Shader::SetUniform4f(const std::string& name, GLfloat f0, GLfloat f1, GLfloat f2, GLfloat f3) {
	GLCall(glUniform4f(GetUniformLocation(name), f0, f1, f2, f3));
}

void Shader::SetUniform4fv(const std::string& name, glm::vec4 vec) {
	GLCall(glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(vec)));
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4& mat) {
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

GLuint Shader::GetUniformLocation(const std::string& name) {
	if (UniformLocationCache.find(name) != UniformLocationCache.end()) {
		return UniformLocationCache[name];
	}

	GLCall(GLuint loc = glGetUniformLocation(ID, name.c_str()));
	if (loc == -1) {
		std::cout << "Uniform: " << name << " doesn't exist" << std::endl;
	}
	UniformLocationCache[name] = loc;
	return loc;
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;

	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}