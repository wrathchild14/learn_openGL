#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VertexBuffer.h"

class vertex_array
{
public:
    GLuint id{};
    vertex_array();
    void link_attrib(vertex_buffer vertex_buffer_object, GLuint layout, GLuint num_components, GLenum type,
                    GLsizei stride,
                    const void* offset);
    void bind() const;
    void unbind();
    void delete_() const;
};

#endif // !VAO_CLASS_H
