#pragma once

#include <random>
#include <iostream>
#include "vtMathConstants.h"

//Credits: https://web.archive.org/web/20160530124230/http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
class Perlin
{
public:
	Perlin() = default;
	inline Perlin(int oct, float amp, float rough) : octaves(oct), amplitude(amp), roughness(rough)
	{

		seed = rand();
	}
	
	// Compute Perlin noise at coordinates x, y
	float perlin(float x, float y) const;

	
private:
	float get_smooth_noise(int x, int y) const;
	float get_interpolated_noise(float x, float y) const;
	float interpolate(float x, float y, float blend) const;

	int seed;
	float roughness;
	int octaves;
	float amplitude;
};