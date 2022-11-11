#include "Texture.h"

Texture::Texture(const char* image, GLenum tex_type, GLuint slot, GLenum format, GLenum pixel_type)
{
    m_Type = tex_type;

    int width_img, height_img, num_col_ch;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &width_img, &height_img, &num_col_ch, 0);

    // The type of GLuint is our pointer to the texture
    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + slot);
    m_Uint = slot;
    glBindTexture(tex_type, ID);

    // how will be drawn
    glTexParameteri(tex_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(tex_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // how will it be repeated
    glTexParameteri(tex_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(tex_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(tex_type, 0, GL_RGBA, width_img, height_img, 0, format, pixel_type, bytes);
    glGenerateMipmap(tex_type);

    stbi_image_free(bytes);
    glBindTexture(tex_type, 0);
}

void Texture::TexUnit(Shader& shader, const char* uniform, GLuint unit)
{
    const GLuint tex_uniform = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(tex_uniform, unit);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + m_Uint);
    glBindTexture(m_Type, ID);
}

void Texture::Unbind()
{
    glBindTexture(m_Type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}
