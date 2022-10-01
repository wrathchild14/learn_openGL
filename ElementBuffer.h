#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class element_buffer
{
public:
    GLuint id{};
    element_buffer(const GLuint* vertices, GLsizeiptr size);

    void bind() const;
    void unbind();
    void Delete() const;
};

#endif // !EBO_CLASS_H
