#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<sstream>

std::string get_file_content(const char* filename);

class Shader
{
public:
    GLuint ID;
    Shader(const char* vertex_file, const char* fragment_file);

    void Activate() const;
    void Delete() const;

private:
    void CompileError(GLuint shader, const char* type);
};


#endif // !SHADER_CLASS_H
