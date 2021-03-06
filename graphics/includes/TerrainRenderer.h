#pragma once
#include "RendererCommon.h"
#include <vector>


class TerrainRenderer : public RendererCommon
{
public:
	TerrainRenderer(const ShaderHelper& sh, unsigned int dim, int octaves, int amplitude, float roughness);
	~TerrainRenderer();

	void render() const;

private:
	unsigned int m_index;
};