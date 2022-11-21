#include "Texture.h"

#include <stb/stb_image.h>

Texture::Texture(const char* image, const char* tex_type, const GLuint slot, const GLenum format,
                 const GLenum pixel_type)
{
    type = tex_type;

    int width_img, height_img, num_col_ch;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &width_img, &height_img, &num_col_ch, 0);

    // The type of GLuint is our pointer to the texture
    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + slot);
    m_Uint = slot;
    glBindTexture(GL_TEXTURE_2D, ID);

    // how will be drawn
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // how will it be repeated
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_img, height_img, 0, format, pixel_type, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::TexUnit(const Shader& shader, const char* uniform, const GLuint unit)
{
    const GLuint tex_uniform = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(tex_uniform, unit);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + m_Uint);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}
