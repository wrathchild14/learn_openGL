#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"Shader.h"
#include"VertexArray.h"
#include"VertexBuffer.h"
#include"ElementBuffer.h"
#include"Texture.h"

#include<stb/stb_image.h>

int main()
{
	if (!glfwInit())
	{
		std::cout << "Log: Failed to initialize GLFW - Terminating..." << std::endl;
		return -1;
	}

	// What version of openGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Using the core profile, so that means we only have modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window in the current context
	glfwMakeContextCurrent(window);
	// Load glad with openGL configuration
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	GLfloat vertices[] =
	{
		//     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,     0.0f, 0.0f, 0.0f, // Lower left corner
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,      0.0f, 0.0f, 1.0f, // Upper left corner
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f,       1.0f, 1.0f, 1.0f, // Upper right corner
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f,      1.0f, 1.0f, 0.0f // Lower right corner
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 2, 1, // Upper triangle
		0, 3, 2 // Lower triangle
	};

	const Shader shader_program("default.vert", "default.frag");

	VertexArray vertex_array_object;
	vertex_array_object.Bind();

	VertexBuffer vertex_buffer_object(vertices, sizeof(vertices));
	ElementBuffer element_buffer_object(indices, sizeof(indices));

	// vertex_array_object.LinkAttrib(vertex_buffer_object, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), nullptr);
	// vertex_array_object.LinkAttrib(vertex_buffer_object, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat),
	//                                (void*)(3 * sizeof(GLfloat)));

	vertex_array_object.LinkAttrib(vertex_buffer_object, 0, 3, GL_FLOAT, 8 * sizeof(float), nullptr);
	vertex_array_object.LinkAttrib(vertex_buffer_object, 1, 3, GL_FLOAT, 8 * sizeof(float),
		reinterpret_cast<void*>(3 * sizeof(float)));
	vertex_array_object.LinkAttrib(vertex_buffer_object, 2, 2, GL_FLOAT, 8 * sizeof(float),
		reinterpret_cast<void*>(6 * sizeof(float)));

	vertex_array_object.Unbind();
	vertex_buffer_object.Unbind();
	element_buffer_object.Unbind();

	// Getting uniform id for later assigning
	const GLuint uni_id = glGetUniformLocation(shader_program.id, "scale");

	// Texture
	Texture cat_texture("square_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	cat_texture.TexUnit(shader_program, "tex0", 0);


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader_program.Activate();
		glUniform1f(uni_id, 1.5f); // Assign uniforms

		cat_texture.Bind();
		vertex_array_object.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // Draw elements from the EBO
		glfwSwapBuffers(window); // Swap the back buffer with the front buffer
		glfwPollEvents(); // Takes care of all glfw events
	}

	vertex_array_object.Delete();
	vertex_buffer_object.Delete();
	element_buffer_object.Delete();
	cat_texture.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
