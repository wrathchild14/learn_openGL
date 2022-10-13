#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Shader.h"
#include"VertexArray.h"
#include"VertexBuffer.h"
#include"ElementBuffer.h"
#include"Texture.h"
#include"Camera.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 800;

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

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", nullptr, nullptr);
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
	glViewport(0, 0, WIDTH, HEIGHT);

	// Vertices coordinates
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	Shader shader_program("default.vert", "default.frag");

	VertexArray vertex_array_object;
	vertex_array_object.Bind();

	VertexBuffer vertex_buffer_object(vertices, sizeof(vertices));
	ElementBuffer element_buffer_object(indices, sizeof(indices));

	vertex_array_object.LinkAttrib(vertex_buffer_object, 0, 3, GL_FLOAT, 8 * sizeof(float), nullptr);
	vertex_array_object.LinkAttrib(vertex_buffer_object, 1, 3, GL_FLOAT, 8 * sizeof(float),
		(void*)(3 * sizeof(float)));
	vertex_array_object.LinkAttrib(vertex_buffer_object, 2, 2, GL_FLOAT, 8 * sizeof(float),
		(void*)(6 * sizeof(float)));

	vertex_array_object.Unbind();
	vertex_buffer_object.Unbind();
	element_buffer_object.Unbind();

	// Texture
	Texture cat_texture("square_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	cat_texture.TexUnit(shader_program, "tex0", 0);

	// Get rid of 3D drawing glitches
	glEnable(GL_DEPTH_TEST);

	Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Depth buffer got to be cleared as well

		shader_program.Activate();

		camera.Inputs(window);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);
		camera.Matrix(shader_program, "camMatrix");

		cat_texture.Bind();
		vertex_array_object.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, nullptr); // Draw elements from the EBO
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
