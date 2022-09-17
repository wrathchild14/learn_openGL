#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {
	if (!glfwInit()) {
		std::cout << "Failed to init GLFW" << std::endl;
		return -1;
	}

	// What version of openGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Using the core profile, so that means we only have modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

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

	// unsinged integer - positive integer
	// Create shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	if (shaderProgram != NULL)
		std::cout << "Shader program is created" << std::endl;
	else {
		std::cout << "Exited because shader pgoram couldnt be created" << std::endl;
		return -1;
	}
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// VBO (vertex buffer object) array of references
	GLuint VAO, VBO;

	// Generate vao and vbo with one object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the vao the current vao by binding it
	glBindVertexArray(VAO);

	// Now bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the variable
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the verttex atrribute so it knows how to use it
	glEnableVertexAttribArray(0);

	// Bind the vbo and vao to 0 so we dont modify the ones we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Main while loop - rendering
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// Using triangles primitives
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		glfwPollEvents(); // Takes care of all glfw events
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}