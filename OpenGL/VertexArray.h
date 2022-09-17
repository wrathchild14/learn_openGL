#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VertexBuffer.h"

class VertexArray {
public:
	GLuint ID;
	VertexArray();

	void LinkVertexBuffer(VertexBuffer VBO, GLuint layout);
	void Bind();
	void Unbind();
	void Delete();
};

#endif // !VAO_CLASS_H
