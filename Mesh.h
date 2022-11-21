#pragma once
#include <glad/glad.h>

#include "Camera.h"
#include "Texture.h"
#include "VertexArray.h"

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    VertexArray vertexArrayObject;

    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

    void Draw(Shader& shader, Camera& camera);
};
