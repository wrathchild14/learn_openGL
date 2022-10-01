#pragma once

#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class ElementBuffer
{
public:
	GLuint id{};
	ElementBuffer(const GLuint* vertices, GLsizeiptr size);

	void Bind() const;
	void Unbind();
	void Delete() const;
};

#endif // !EBO_CLASS_H
