#include "Camera.h"

Camera::Camera(const ShaderHelper& sh, int width, int height) : m_position(glm::vec3(0, 3, 1)), m_shader(sh)
{
	m_projection = glm::perspective<float>(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	sh.set_mat4("proj", m_projection);
}

void Camera::update_cam() const
{
	glm::mat4 view = glm::lookAt(m_position, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_shader.set_mat4("view", view);
}
