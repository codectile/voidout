#pragma once
#include "Common.h"
#include "ShaderHelper.h"
#include "Window.h"

class Camera
{
public:
	Camera(const ShaderHelper& sh, int width, int height, const glm::vec3& front, const glm::vec3& up, float speed);
	void process_cam(const Window& window, float dt);
	void update_cam() const;
	inline void set_cam_pos(const glm::vec3& pos)
	{
		m_position = pos;
	}

	inline glm::vec3 get_cam_pos() const
	{
		return m_position;
	}

	inline void move_front(float dt)
	{
		m_position += m_speed * dt * m_front;
	}

	inline void move_back(float dt)
	{
		m_position -= m_speed * dt * m_front;
	}

	inline void move_up(float dt)
	{
		m_position += m_speed * dt * m_up;
	}

	inline void move_down(float dt)
	{
		m_position -= m_speed * dt * m_up;
	}

	inline void move_left(float dt)
	{
		m_position -= glm::normalize(glm::cross(m_front, m_up)) * m_speed * dt;
	}

	inline void move_right(float dt)
	{
		m_position += glm::normalize(glm::cross(m_front, m_up)) * m_speed * dt;
	}

private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::mat4 m_projection;
	float m_speed;
	ShaderHelper m_shader;
};