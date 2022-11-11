#pragma once

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
