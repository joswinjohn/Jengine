#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 m_color;

out vec4 a_color;

//uniform mat4 u_MVP;

void main()
{
	gl_Position = position;
	a_color = m_color;
}