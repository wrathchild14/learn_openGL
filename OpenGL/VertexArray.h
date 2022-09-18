#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VertexBuffer.h"

class VertexArray {
public:
	GLuint ID;
	VertexArray();

	void LinkAttrib(VertexBuffer vertexBufferObject, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif // !VAO_CLASS_H
