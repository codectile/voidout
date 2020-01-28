#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <glad/glad.h>
#include "Common.h"

class ShaderHelper
{
public:
	ShaderHelper() = default;
	

	void load(const char* vsource, const char* fsource);
	inline void start() const
	{
		glUseProgram(m_progid);
	}

	inline GLuint get_id() const
	{
		return m_progid;
	}

	inline void set_bool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_progid, name.c_str()), (int)value);
	}
	
	inline void set_int(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_progid, name.c_str()), value);
	}
	
	inline void set_float(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_progid, name.c_str()), value);
	}

	inline void set_vec2(const std::string &name, const glm::vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation(m_progid, name.c_str()), 1, &value[0]);
	}

	inline void set_vec2(const std::string &name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(m_progid, name.c_str()), x, y);
	}

	inline void set_vec3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(m_progid, name.c_str()), 1, &value[0]);
	}

	inline void set_vec3(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(m_progid, name.c_str()), x, y, z);
	}

	void set_vec4(const std::string &name, const glm::vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(m_progid, name.c_str()), 1, &value[0]);
	}

	void set_vec4(const std::string &name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(m_progid, name.c_str()), x, y, z, w);
	}

	inline void set_mat3(const std::string &name, const glm::mat3 &value) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_progid, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	inline void set_mat4(const std::string &name, const glm::mat4 &value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_progid, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

private:
	GLuint m_progid;

};
