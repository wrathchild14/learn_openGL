#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<sstream>

std::string get_file_content(const char* filename);

class shader
{
public:
    GLuint id;
    shader(const char* vertex_file, const char* fragment_file);

    void activate() const;
    void delete_() const;

private:
    void compile_error(GLuint shader, const char* type);
};


#endif // !SHADER_CLASS_H
