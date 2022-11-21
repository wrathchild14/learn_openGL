#include "Mesh.h"

#include "ElementBuffer.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
{
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

    vertexArrayObject.Bind();

    VertexBuffer vertexBufferObject(vertices);
    ElementBuffer elementBufferObject(indices);

    vertexArrayObject.LinkAttrib(vertexBufferObject, 0, 3, GL_FLOAT, sizeof(Vertex), nullptr);
    vertexArrayObject.LinkAttrib(vertexBufferObject, 1, 3, GL_FLOAT, sizeof(Vertex),
                                 (void*)(3 * sizeof(float)));
    vertexArrayObject.LinkAttrib(vertexBufferObject, 2, 3, GL_FLOAT, sizeof(Vertex),
                                 (void*)(6 * sizeof(float)));
    vertexArrayObject.LinkAttrib(vertexBufferObject, 3, 2, GL_FLOAT, sizeof(Vertex),
                                 (void*)(9 * sizeof(float)));

    vertexArrayObject.Unbind();
    vertexBufferObject.Unbind();
    elementBufferObject.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
    shader.Activate();
    vertexArrayObject.Bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (unsigned int i = 0; i < textures.size(); i ++)
    {
        std::string num;
        std::string type = textures[i].type;
        if (type == "diffuse")
        {
            num = std::to_string(numDiffuse++);
        }
        else if (type == "specular")
        {
            num = std::to_string(numSpecular++);
        }
        textures[i].TexUnit(shader, (type + num).c_str(), i);
        textures[i].Bind();
    }
    const auto cameraPos = camera.GetPosition();
    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), cameraPos.x, cameraPos.y, cameraPos.z);

    camera.Matrix(shader, "camMatrix");
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}
