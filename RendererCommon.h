#pragma once
#include "Common.h"
#include "ShaderHelper.h"

class RendererCommon
{
public:
	inline RendererCommon() : m_worldpos(0.f, 0.f, 0.f), m_model(glm::mat4(1.f)), m_vao(0), m_vbo(0), m_ebo(0)
	{

	}
	inline RendererCommon(const ShaderHelper& shader) : RendererCommon()
	{
		m_shader = shader;
	}
	virtual ~RendererCommon()
	{
		m_worldpos = glm::vec3(0.f, 0.f, 0.f);
		m_model = glm::mat4(1.f);
		m_vao = 0;
		m_vbo = 0;
		m_ebo = 0;
	}

	virtual inline void set_world_pos(const glm::vec3 pos)
	{
		m_worldpos = pos;
		m_model = glm::translate(glm::mat4(1.0), m_worldpos);
	}

	virtual inline glm::vec3 get_world_pos() const
	{
		return m_worldpos;
	}

	virtual void render() const = 0;

protected:
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ebo;
	ShaderHelper m_shader;
	glm::vec3 m_worldpos;
	glm::mat4 m_model;
};