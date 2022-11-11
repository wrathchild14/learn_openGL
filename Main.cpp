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

	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
		-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
		 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
		 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	GLfloat light_vertices[] =
	{ //     COORDINATES     //
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f,  0.1f
	};

	GLuint light_indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

	Shader shader_program("default.vert", "default.frag");

	VertexArray vertex_array_object;
	vertex_array_object.Bind();

	VertexBuffer vertex_buffer_object(vertices, sizeof(vertices));
	ElementBuffer element_buffer_object(indices, sizeof(indices));

	vertex_array_object.LinkAttrib(vertex_buffer_object, 0, 3, GL_FLOAT, 11 * sizeof(float), nullptr);
	vertex_array_object.LinkAttrib(vertex_buffer_object, 1, 3, GL_FLOAT, 11 * sizeof(float),
		(void*)(3 * sizeof(float)));
	vertex_array_object.LinkAttrib(vertex_buffer_object, 2, 2, GL_FLOAT, 11 * sizeof(float),
		(void*)(6 * sizeof(float)));
	vertex_array_object.LinkAttrib(vertex_buffer_object, 3, 3, GL_FLOAT, 11 * sizeof(float),
		(void*)(8 * sizeof(float)));

	vertex_array_object.Unbind();
	vertex_buffer_object.Unbind();
	element_buffer_object.Unbind();

	// Lights shader
	Shader light_shader("light.vert", "light.frag");

	VertexArray light_vertex_array;
	light_vertex_array.Bind();

	VertexBuffer light_buffer_object(light_vertices, sizeof(light_vertices));
	ElementBuffer light_element_object(light_indices, sizeof(light_indices));

	light_vertex_array.LinkAttrib(light_buffer_object, 0, 3, GL_FLOAT, 3 * sizeof(GL_FLOAT), (void*)0);

	auto light_color = glm::vec4(0.6f, 1.0f, 1.0f, 1.0f);
	auto light_pos = glm::vec3(0.5f, 0.5f, 0.5f);
	auto light_model = glm::mat4(1.0f);
	light_model = translate(light_model, light_pos); // Gives the matrix a position

	auto pyramid_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	auto pyramid_model = glm::mat4(1.0f);
	pyramid_model = translate(pyramid_model, pyramid_pos);

	light_shader.Activate();
	glad_glUniformMatrix4fv(glGetUniformLocation(light_shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(light_model));
	glad_glUniform4f(glGetUniformLocation(light_shader.ID, "lightColor"), light_color.x, light_color.y, light_color.z, light_color.w);
	shader_program.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader_program.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramid_model));
	glad_glUniform4f(glGetUniformLocation(shader_program.ID, "lightColor"), light_color.x, light_color.y, light_color.z, light_color.w);
	
	glad_glUniform3f(glGetUniformLocation(shader_program.ID, "lightPos"), light_pos.x, light_pos.y, light_pos.z);


	Texture wood_tex("wood.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	wood_tex.TexUnit(shader_program, "tex0", 0);
	Texture wood_spec_tex("woodSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	wood_tex.TexUnit(shader_program, "tex1", 1);

	// Get rid of 3D drawing glitches
	glEnable(GL_DEPTH_TEST);

	Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Depth buffer got to be cleared as well

		shader_program.Activate();

		const auto& camera_position = camera.GetPosition();
		glUniform3f(glad_glGetUniformLocation(shader_program.ID, "camPos"), camera_position.x, camera_position.y, camera_position.z);

		camera.Inputs(window);
		camera.UpdateMatrix(60.0f, 0.1f, 100.0f);
		camera.Matrix(shader_program, "camMatrix");

		wood_tex.Bind();
		wood_spec_tex.Bind();
		vertex_array_object.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, nullptr); // Draw elements from the EBO

		light_shader.Activate();
		camera.Matrix(light_shader, "camMatrix");
		light_vertex_array.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(light_indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window); // Swap the back buffer with the front buffer
		glfwPollEvents(); // Takes care of all glfw events
	}

	vertex_array_object.Delete();
	vertex_buffer_object.Delete();
	element_buffer_object.Delete();
	wood_tex.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
