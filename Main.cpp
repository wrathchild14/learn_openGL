#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"Shader.h"
#include"VertexArray.h"
#include"VertexBuffer.h"
#include"ElementBuffer.h"

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

    GLfloat vertices[] = {
        -0.5f, -0.5f * static_cast<float>(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f, // Lower left corner
        0.5f, -0.5f * static_cast<float>(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f, // Lower right corner
        0.0f, 0.5f * static_cast<float>(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f, 0.32f, // Upper corner
        -0.5f / 2, 0.5f * static_cast<float>(sqrt(3)) / 6, 0.0f, 0.9f, 0.45f, 0.17f, // Inner left
        0.5f / 2, 0.5f * static_cast<float>(sqrt(3)) / 6, 0.0f, 0.9f, 0.45f, 0.17f, // Inner right
        0.0f, -0.5f * static_cast<float>(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f // Inner down
    };

    GLuint indices[] = {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1
    };

    const Shader shader_program("default.vert", "default.frag");

    VertexArray vertex_array_object;
    vertex_array_object.Bind();

    VertexBuffer vertex_buffer_object(vertices, sizeof(vertices));
    ElementBuffer element_buffer_object(indices, sizeof(indices));

    vertex_array_object.LinkAttrib(vertex_buffer_object, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), nullptr);
    vertex_array_object.LinkAttrib(vertex_buffer_object, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat),
                                   (void*)(3 * sizeof(GLfloat)));

    vertex_array_object.Unbind();
    vertex_buffer_object.Unbind();
    element_buffer_object.Unbind();

    // Getting uniform id for later assigning
    const GLuint uni_id = glGetUniformLocation(shader_program.ID, "scale");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_program.Activate();
        glUniform1f(uni_id, 1.5f); // Assign uniforms

        vertex_array_object.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr); // Draw elements from the EBO
        glfwSwapBuffers(window); // Swap the back buffer with the front buffer
        glfwPollEvents(); // Takes care of all glfw events
    }

    vertex_array_object.Delete();
    vertex_buffer_object.Delete();
    element_buffer_object.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
