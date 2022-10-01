#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class vertex_buffer
{
public:
    GLuint id{};
    vertex_buffer(const GLfloat* vertices, GLsizeiptr size);

    void bind() const;
    void unbind();
    void delete_() const;
};

#endif // !VBO_CLASS_H
