#pragma once

#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VertexBuffer.h"

class VertexArray
{
public:
    GLuint id{};
    VertexArray();
    void LinkAttrib(VertexBuffer vertex_buffer_object, GLuint layout, GLuint num_components, GLenum type,
                    GLsizei stride,
                    const void* offset);
    void Bind() const;
    void Unbind();
    void Delete() const;
};

#endif // !VAO_CLASS_H
