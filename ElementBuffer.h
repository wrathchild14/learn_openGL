#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class ElementBuffer {
public:
	GLuint ID;
	ElementBuffer(GLuint* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif // !EBO_CLASS_H
