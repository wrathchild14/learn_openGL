#pragma once

#include<glad/glad.h>

class VertexBuffer
{
public:
	GLuint ID{};
	VertexBuffer(const GLfloat* vertices, GLsizeiptr size);

	void Bind() const;
	void Unbind();
	void Delete() const;
};
