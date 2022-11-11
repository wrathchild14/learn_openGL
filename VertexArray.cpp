#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);
}

// Binds, sets, enables and unbinds the VBO.
void VertexArray::LinkAttrib(VertexBuffer& vertex_buffer_object, const GLuint layout, const GLuint num_components,
                             const GLenum type,
                             const GLsizei stride, const void* offset)
{
    vertex_buffer_object.Bind();
    glVertexAttribPointer(layout, num_components, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vertex_buffer_object.Unbind();
}

void VertexArray::Bind() const
{
    glBindVertexArray(ID);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void VertexArray::Delete() const
{
    glDeleteVertexArrays(1, &ID);
}
