#include "VertexArray.h"

vertex_array::vertex_array()
{
    glGenVertexArrays(1, &id);
}

// Binds, sets, enables and unbinds the VBO.
void vertex_array::link_attrib(vertex_buffer vertex_buffer_object, const GLuint layout, const GLuint num_components,
                             const GLenum type,
                             const GLsizei stride, const void* offset)
{
    vertex_buffer_object.bind();
    glVertexAttribPointer(layout, num_components, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vertex_buffer_object.unbind();
}

void vertex_array::bind() const
{
    glBindVertexArray(id);
}

void vertex_array::unbind()
{
    glBindVertexArray(0);
}

void vertex_array::delete_() const
{
    glDeleteVertexArrays(1, &id);
}
