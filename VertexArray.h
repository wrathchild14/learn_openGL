#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VertexBuffer.h"

class VertexArray
{
public:
    GLuint ID{};
    VertexArray();
    void LinkAttrib(VertexBuffer vertex_buffer_object, GLuint layout, GLuint num_components, GLenum type, GLsizei stride,
                    const void* offset);
    void Bind();
    void Unbind();
    void Delete();
};

#endif // !VAO_CLASS_H
