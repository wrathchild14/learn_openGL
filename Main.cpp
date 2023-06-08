#include <iostream>

#include "Mesh.h"

constexpr int WIDTH = 1200;
constexpr int HEIGHT = 1000;

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
	Vertex vertices[] =
	{
		Vertex{
			glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec2(0.0f, 0.0f)
		},
		Vertex{
			glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f)
		},
		Vertex{
			glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec2(1.0f, 1.0f)
		},
		Vertex{
			glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)
		}
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	Vertex lightVertices[] =
	{
		Vertex{glm::vec3(-0.1f, -0.1f, 0.1f)},
		Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, -0.1f, 0.1f)},
		Vertex{glm::vec3(-0.1f, 0.1f, 0.1f)},
		Vertex{glm::vec3(-0.1f, 0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, 0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, 0.1f, 0.1f)}
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

	Texture textures[]
	{
		Texture("wood.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("woodSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	auto shader_program = std::make_unique<Shader>("default.vert", "default.frag");
	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	// Create floor mesh
	auto floor = std::make_unique<Mesh>(verts, ind, tex);

	auto light_shader = std::make_unique<Shader>("light.vert", "light.frag");
	std::vector<Vertex> light_verts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint> light_inds(light_indices, light_indices + sizeof(light_indices) / sizeof(GLuint));
	// Crate light mesh
	auto light = std::make_unique<Mesh>(light_verts, light_inds, tex);

	auto light_color = glm::vec4(0.85f, 1.0f, 1.0f, 1.0f);
	auto light_pos = glm::vec3(0.5f, 0.5f, 0.5f);
	auto light_model = glm::mat4(1.0f);
	light_model = translate(light_model, light_pos); // Gives the matrix a position

	auto pyramid_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	auto pyramid_model = glm::mat4(1.0f);
	pyramid_model = translate(pyramid_model, pyramid_pos);

	light_shader->Activate();
	glad_glUniformMatrix4fv(glGetUniformLocation(light_shader->ID, "model"), 1, GL_FALSE, value_ptr(light_model));
	glad_glUniform4f(glGetUniformLocation(light_shader->ID, "lightColor"), light_color.x, light_color.y, light_color.z,
	                 light_color.w);
	shader_program->Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader_program->ID, "model"), 1, GL_FALSE, value_ptr(pyramid_model));
	glad_glUniform4f(glGetUniformLocation(shader_program->ID, "lightColor"), light_color.x, light_color.y,
	                 light_color.z, light_color.w);
	glad_glUniform3f(glGetUniformLocation(shader_program->ID, "lightPos"), light_pos.x, light_pos.y, light_pos.z);


	// get rid of drawing on top of structures
	glEnable(GL_DEPTH_TEST);

	Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Depth buffer got to be cleared as well

		shader_program->Activate();

		const auto& camera_position = camera.GetPosition();
		glUniform3f(glad_glGetUniformLocation(shader_program->ID, "camPos"), camera_position.x, camera_position.y,
		            camera_position.z);

		camera.Inputs(window);
		camera.UpdateMatrix(70.0f, 0.01f, 100.0f);
		camera.Matrix(*shader_program, "camMatrix");

		floor->Draw(*shader_program, camera);
		light->Draw(*light_shader, camera);

		glfwSwapBuffers(window); // Swap the back buffer with the front buffer
		glfwPollEvents(); // Takes care of all glfw events
	}

	shader_program->Delete();
	light_shader->Delete();
	shader_program.reset();
	light_shader.reset();
	light.reset();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
