#include "Perlin.h"




float Perlin::get_smooth_noise(int x, int y) const
{
	auto get_noise = [=](int x, int y)
	{
		std::mt19937 rng(x * 93157 + y * 75319 + seed);
		std::uniform_real_distribution<float> dist(-1, 1);
		return dist(rng);
	};
	float corners = (get_noise(x - 1, y - 1) + get_noise(x + 1, y - 1) + get_noise(x - 1, y + 1) + get_noise(x + 1, y + 1)) / 16.f;
	float sides = (get_noise(x - 1, y) + get_noise(x + 1, y) + get_noise(x, y - 1) + get_noise(x, y + 1)) / 8.f;
	float center = get_noise(x, y) / 4.f;
	return corners + sides + center;
}

float Perlin::interpolate(float x, float y, float blend) const
{
	float theta = blend * VT_PI;
	float f = (float)((1.f - cos(theta)) * 0.5f);
	return x * (1 - f) + y * f;
}


float Perlin::get_interpolated_noise(float x, float y) const
{
	int intx = (int)x;
	float fracx = x - intx;
	int inty = (int)y;
	float fracy = y - inty;

	float v1 = get_smooth_noise(intx, inty);
	float v2 = get_smooth_noise(intx + 1, inty);
	float v3 = get_smooth_noise(intx, inty + 1);
	float v4 = get_smooth_noise(intx + 1, inty + 1);
	float i1 = interpolate(v1, v2, fracx);
	float i2 = interpolate(v3, v4, fracx);
	return interpolate(i1, i2, fracy);
}

// Compute Perlin noise at coordinates x, y
float Perlin::perlin(float x, float y) const
{

	float total = 0;
	float d = (float)pow(2, octaves - 1);
	for (int i = 0; i < octaves; i++)
	{
		float freq = (float)(pow(2, i) / d);
		float amp = (float)pow(roughness, i) * amplitude;
		total += get_interpolated_noise(x * freq, y * freq) * amp;
	}
	return total;
}
