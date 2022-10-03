#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	m_Width = width;
	m_Weight = height;
	m_Position = position;
}

void Camera::Matrix(float fov_deg, float near_plane, float far_plane, Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	view = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
	proj = glm::perspective(glm::radians(fov_deg), (float)(m_Width / m_Weight), near_plane, far_plane);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(proj * view));
}

void Camera::Inputs(GLFWwindow* widnow)
{
}
