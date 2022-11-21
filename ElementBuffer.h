#pragma once

#include <vector>
#include<glad/glad.h>

class ElementBuffer
{
public:
    GLuint id{};
    ElementBuffer(const std::vector<GLuint>& indices);

    void Bind() const;
    void Unbind();
    void Delete() const;
};
