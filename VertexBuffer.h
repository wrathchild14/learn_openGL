#pragma once

#ifndef VBO_CLASS_H
#define VBO_CLASS_H

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

#endif // !VBO_CLASS_H
