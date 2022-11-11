#pragma once

#include<glad/glad.h>
#include"VertexBuffer.h"

class VertexArray
{
public:
    GLuint ID{};
    VertexArray();
    void LinkAttrib(VertexBuffer& vertex_buffer_object, GLuint layout, GLuint num_components, GLenum type,
                    GLsizei stride,
                    const void* offset);
    void Bind() const;
    void Unbind();
    void Delete() const;
};
