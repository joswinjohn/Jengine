#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO
{
public:
	GLuint ID;
	GLuint count;

	EBO(GLuint* indices, GLuint i_count);
	~EBO();

	void Bind() const;
	void Unbind() const;

	inline GLuint GetCount() const { return count; }
};

#endif