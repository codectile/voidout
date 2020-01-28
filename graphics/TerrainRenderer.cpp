#include "TerrainRenderer.h"
#include "Perlin.h"
#include <iostream>

TerrainRenderer::TerrainRenderer(const ShaderHelper& sh, unsigned int dim) : RendererCommon(sh)
{
	//int shader_id = m_shader.get_id();
	std::vector<Vertex>vertices;
	Perlin p(4, 10, 0.1f);
	float heights[50][50];
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			
			heights[i][j] = p.perlin(static_cast<float>(i), static_cast<float>(j));
			Vertex v;
			v.m_position = glm::vec3((float)i, heights[i][j], (float)j);

			v.m_color = glm::vec3(110 / 255.f, 58 / 255.f, 166 / 255.f);
			vertices.push_back(v);
		}
	}

	bool flag = true;
	std::vector<int>indices;
	for (int i = 0; i < dim - 1; i++)
	{
		for (int j = 0; j < dim - 1; j++)
		{
			if (flag)
			{
				indices.push_back(i * dim + j);
				indices.push_back((i + 1) * dim + j + 1);
				indices.push_back((i + 1) * dim + j);


				indices.push_back(i * dim + j + 1);
				indices.push_back((i + 1) * dim + j + 1);
				indices.push_back(i * dim + j);
				flag = false;
			}
			else
			{
				indices.push_back(i * dim + j);
				indices.push_back(i * dim + j + 1);
				indices.push_back((i + 1) * dim + j);


				indices.push_back(i * dim + j + 1);
				indices.push_back((i + 1) * dim + j + 1);
				indices.push_back((i + 1) * dim + j);
				flag = true;
			}
			
			
		}
	}


	auto get_height = [=](int x, int z)
	{
		x = x < 0 ? 0 : x;
		z = z < 0 ? 0 : z;
		x = x >= dim ? dim - 1 : x;
		z = z >= dim ? dim - 1 : z;
		return heights[x][z];
	};

	auto get_normal = [=](int x, int z)
	{
		float heightL = get_height(x - 1, z);
		float heightR = get_height(x + 1, z);
		float heightD = get_height(x, z - 1);
		float heightU = get_height(x, z + 1);
		glm::vec3 normal(heightL - heightR, 2.f, heightD - heightU);
		return glm::normalize(normal);
	};
	int n = 0;
	for (int x = 0; x < dim; x++) 
		for (int z = 0; z < dim; z++) 
			vertices[n++].m_normal = get_normal(x, z);



	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)24);
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered m_vbo as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_index = indices.size();
	m_shader.set_mat4("model", m_model);
}

TerrainRenderer::~TerrainRenderer()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
}

void TerrainRenderer::render() const
{
	
	glBindVertexArray(m_vao);

	glDrawElements(GL_TRIANGLES, (unsigned int)m_index, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
