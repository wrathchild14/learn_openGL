#include"Shader.h"

#include <fstream>
#include <iostream>

std::string GetFileContent(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw errno;
}

Shader::Shader(const char* vertex_file, const char* fragment_file)
{
	const std::string vertex_code = GetFileContent(vertex_file);
	const std::string fragment_code = GetFileContent(fragment_file);

	const char* vertex_source = vertex_code.c_str();
	const char* fragment_source = fragment_code.c_str();

	const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
	glCompileShader(vertex_shader);
	CompileErrors(vertex_shader, "VERTEX");

	const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
	glCompileShader(fragment_shader);
	CompileErrors(fragment_shader, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertex_shader);
	glAttachShader(ID, fragment_shader);
	glLinkProgram(ID);
	CompileErrors(ID, "PROGRAM");

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void Shader::Activate() const
{
	glUseProgram(ID);
}

void Shader::Delete() const
{
	glDeleteProgram(ID);
}

void Shader::CompileErrors(const GLuint shader, const char* type)
{
	GLint has_compiled;
	char info_log[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &has_compiled);
		if (has_compiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, info_log);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
			return;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &has_compiled);
		if (has_compiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, info_log);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
			return;
		}
	}
	std::cout << "Log: Compiled shader: " << type << " with UID: " << shader << std::endl;
}
