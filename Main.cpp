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

int WIDTH = 800;
int HEIGHT = 800;

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

	// Getting uniform id for later assigning
	const GLuint uni_id = glGetUniformLocation(shader_program.ID, "scale");

	// Texture
	Texture cat_texture("square_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	cat_texture.TexUnit(shader_program, "tex0", 0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader_program.Activate();
		glUniform1f(uni_id, 1.5f); // Assign uniforms

		// Matrices, activate shader before assigning
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(WIDTH / HEIGHT), 0.1f, 100.f);

		int model_loc = glGetUniformLocation(shader_program.ID, "model");
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));

		int view_loc = glGetUniformLocation(shader_program.ID, "view");
		glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

		int proj_loc = glGetUniformLocation(shader_program.ID, "proj");
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj));


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
