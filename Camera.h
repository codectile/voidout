#pragma once
#include "Common.h"
#include "ShaderHelper.h"

class Camera
{
public:
	Camera(const ShaderHelper& sh, int width, int height);
	void update_cam() const;
	inline void set_cam_pos(const glm::vec3& pos)
	{
		m_position = pos;
	}

	inline glm::vec3 getCamPosition() const
	{
		return m_position;
	}

private:
	glm::vec3 m_position;
	glm::mat4 m_projection;
	ShaderHelper m_shader;
};