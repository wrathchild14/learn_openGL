#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"Shader.h"
#include"VertexArray.h"
#include"VertexBuffer.h"
#include"ElementBuffer.h"

int main() {
	/// <summary>
	/// Set up
	/// </summary>
	/// <returns></returns>
	if (!glfwInit()) {
		std::cout << "Failed to init GLFW" << std::endl;
		return -1;
	}

	// What version of openGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Using the core profile, so that means we only have modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window in the current context
	glfwMakeContextCurrent(window);
	// Load glad with openGL configuration
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	/// <summary>
	/// Start of our program
	/// </summary>
	/// <returns></returns>

	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	0.8f, 0.3f, 0.02f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		0.8f, 0.3f, 0.02f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	1.0f, 0.6f, 0.32f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.9f, 0.45f, 0.17f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	0.9f, 0.45f, 0.17f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,		0.8f, 0.3f, 0.02f // Inner down
	};

	GLuint indices[] = {
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};

	Shader shaderProgram("default.vert", "default.frag");

	VertexArray vertexArrayObject;
	vertexArrayObject.Bind();

	VertexBuffer vertexBufferObject(vertices, sizeof(vertices));
	ElementBuffer elementBufferObject(indices, sizeof(indices));
	
	vertexArrayObject.LinkAttrib(vertexBufferObject, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	vertexArrayObject.LinkAttrib(vertexBufferObject, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	vertexArrayObject.Unbind();
	vertexBufferObject.Unbind();
	elementBufferObject.Unbind();

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		vertexArrayObject.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // Draw elements from the EBO
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		glfwPollEvents(); // Takes care of all glfw events
	}

	/// <summary>
	/// Freeing memory - deconstructors
	/// </summary>
	/// <returns></returns>

	vertexArrayObject.Delete();
	vertexBufferObject.Delete();
	elementBufferObject.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}