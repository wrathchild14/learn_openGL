#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"Shader.h"

class Texture
{
public:
	GLuint ID{};
	
	Texture(const char* image, GLenum tex_type, GLuint slot, GLenum format, GLenum pixel_type);

	void TexUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
private:
	GLenum m_Type;
	GLuint m_Uint;
};
