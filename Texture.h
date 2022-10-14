#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"Shader.h"

class Texture
{
public:
	GLuint ID{};
	GLenum type;
	Texture(const char* image, GLenum tex_type, GLenum slot, GLenum format, GLenum pixel_type);

	void TexUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};
