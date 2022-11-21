#pragma once

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <vector>
#include <glm/vec2.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
};

class VertexBuffer
{
public:
    GLuint ID{};
    VertexBuffer(const std::vector<Vertex>& vertices);

    void Bind() const;
    void Unbind();
    void Delete() const;
};
