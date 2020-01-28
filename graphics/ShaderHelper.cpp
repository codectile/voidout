#include "ShaderHelper.h"
#include <iostream>


void ShaderHelper::load(const char * vsource, const char* fsource)
{
	std::ifstream file1(vsource), file2(fsource);
	if (!file1 || !file2)
		return;
	std::stringstream ss1, ss2;
	ss1 << file1.rdbuf();
	ss2 << file2.rdbuf();

	int vtx, frag;
	vtx = glCreateShader(GL_VERTEX_SHADER);
	std::string s1 = ss1.str();
	const char* vtxcode = s1.c_str();
	
	glShaderSource(vtx, 1, &vtxcode, NULL);
	glCompileShader(vtx);

	frag = glCreateShader(GL_FRAGMENT_SHADER);
	std::string s2 = ss2.str();
	const char* fragcode = s2.c_str();
	glShaderSource(frag, 1, &fragcode, NULL);
	glCompileShader(frag);
	
	m_progid = glCreateProgram();
	glAttachShader(m_progid, vtx);
	glAttachShader(m_progid, frag);
	glLinkProgram(m_progid);
	
	glDeleteShader(vtx);
	glDeleteShader(frag);

}
