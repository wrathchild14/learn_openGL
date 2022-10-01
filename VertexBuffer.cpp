#include"VertexBuffer.h"

vertex_buffer::vertex_buffer(const GLfloat* vertices, const GLsizeiptr size)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void vertex_buffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void vertex_buffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vertex_buffer::delete_() const
{
    glDeleteBuffers(1, &id);
}
