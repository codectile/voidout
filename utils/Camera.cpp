#include "Camera.h"

Camera::Camera(const ShaderHelper& sh, int width, int height, const glm::vec3& front, const glm::vec3& up, float speed) : m_position(glm::vec3(0, 3, 1)), m_shader(sh), m_front(front), m_up(up), m_speed(speed)
{
	m_projection = glm::perspective<float>(glm::radians(45.f), (float)width / height, 0.1f, 100.0f);
	sh.set_mat4("proj", m_projection);
}

void Camera::process_cam(const Window& window, float dt)
{
	if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.close_window();

	if (window.get_key(GLFW_KEY_W) == GLFW_PRESS)
		move_front(dt);
	if (window.get_key(GLFW_KEY_S) == GLFW_PRESS)
		move_back(dt);
	if (window.get_key(GLFW_KEY_A) == GLFW_PRESS)
		move_left(dt);
	if (window.get_key(GLFW_KEY_D) == GLFW_PRESS)
		move_right(dt);
	if (window.get_key(GLFW_KEY_UP) == GLFW_PRESS)
		move_up(dt);
	if (window.get_key(GLFW_KEY_DOWN) == GLFW_PRESS)
		move_down(dt);

	if (window.get_key(GLFW_KEY_0) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (window.get_key(GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Camera::update_cam() const
{
	glm::mat4 view = glm::lookAt(m_position, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_shader.set_mat4("view", view);
}
