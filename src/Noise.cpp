#include "Noise.hpp"

float Noise::perlinSize = 16;
Noise* Noise::singleton = NULL;

Noise::Noise(int seed){
	
	if (Noise::singleton != NULL)
		return;

	Noise::singleton = this;
	srand (seed);

	for (int y = 0; y < 16; y++)
		for (int x = 0; x < 16; x++)
		{
			elevRand[x][y] = float(rand() % 256) / 256.0 * 2 * PI;
			roughRand[x][y] = float(rand() % 256) / 256.0 * 2 * PI;
		}
	for (int y = 0; y < 64; y++)
		for (int x = 0; x < 64; x++)
			detailRand[x][y] = float(rand() % 256) / 256.0 * 2 * PI;
}

float interpolate(float e0, float e1, float x) {
	float t = 6 * pow(x, 5) - 15 * pow(x, 4) + 10 * pow(x, 3);
	return e0 * t + e1 * (1.0 - t);
}

float fract(float f)
{
	if (f < 0)
		return f - int(f) + 1;
	return f - int(f);
}

float	Noise::elevation(float x, float y)
{
	int xi = (int(x) + abs(int(x) * 16)) & 15;
	int yi = (int(y) + abs(int(y) * 16)) & 15;

	Vector2f dl(cos(elevRand[xi][yi]), sin(elevRand[xi][yi]));
	Vector2f dr(cos(elevRand[(xi + 1) & 15][yi]), sin(elevRand[(xi + 1) & 15][yi]));
	Vector2f ul(cos(elevRand[xi][(yi + 1) & 15]), sin(elevRand[xi][(yi + 1) & 15]));
	Vector2f ur(cos(elevRand[(xi + 1) & 15][(yi + 1) & 15]),
		sin(elevRand[(xi + 1) & 15][(yi + 1) & 15]));

	float fx = fract(x);
	float fy = fract(y);
	Vector2f dld(fx, fy);
	Vector2f drd(fx - 1.0, fy);
	Vector2f uld(fx, fy - 1.0);
	Vector2f urd(fx - 1.0, fy - 1.0);

	float td = interpolate(dl.dot(dld), dr.dot(drd), 1 - fx);
	float tu = interpolate(ul.dot(uld), ur.dot(urd), 1 - fx);
	float ret = interpolate(td, tu, 1 - fy);
	return ret;
}

float	Noise::roughness(float x, float y)
{
	int xi = (int(x) + abs(int(x) * 16)) & 15;
	int yi = (int(y) + abs(int(y) * 16)) & 15;

	Vector2f dl(cos(roughRand[xi][yi]), sin(roughRand[xi][yi]));
	Vector2f dr(cos(roughRand[(xi + 1) & 15][yi]), sin(roughRand[(xi + 1) & 15][yi]));
	Vector2f ul(cos(roughRand[xi][(yi + 1) & 15]), sin(roughRand[xi][(yi + 1) & 15]));
	Vector2f ur(cos(roughRand[(xi + 1) & 15][(yi + 1) & 15]),
		sin(roughRand[(xi + 1) & 15][(yi + 1) & 15]));

	float fx = fract(x);
	float fy = fract(y);
	Vector2f dld(fx, fy);
	Vector2f drd(fx - 1.0, fy);
	Vector2f uld(fx, fy - 1.0);
	Vector2f urd(fx - 1.0, fy - 1.0);

	float td = interpolate(dl.dot(dld), dr.dot(drd), 1 - fx);
	float tu = interpolate(ul.dot(uld), ur.dot(urd), 1 - fx);
	float ret = interpolate(td, tu, 1 - fy);
	return ret;
}

float	Noise::local(float x, float y)
{
	int xi = (int(x) + abs(int(x) * 64)) & 63;
	int yi = (int(y) + abs(int(y) * 64)) & 63;

	Vector2f dl(cos(detailRand[xi][yi]), sin(detailRand[xi][yi]));
	Vector2f dr(cos(detailRand[(xi + 1) & 63][yi]), sin(detailRand[(xi + 1) & 63][yi]));
	Vector2f ul(cos(detailRand[xi][(yi + 1) & 63]), sin(detailRand[xi][(yi + 1) & 63]));
	Vector2f ur(cos(detailRand[(xi + 1) & 63][(yi + 1) & 63]),
		sin(detailRand[(xi + 1) & 63][(yi + 1) & 63]));

	float fx = fract(x);
	float fy = fract(y);
	Vector2f dld(fx, fy);
	Vector2f drd(fx - 1.0, fy);
	Vector2f uld(fx, fy - 1.0);
	Vector2f urd(fx - 1.0, fy - 1.0);

	float td = interpolate(dl.dot(dld), dr.dot(drd), 1 - fx);
	float tu = interpolate(ul.dot(uld), ur.dot(urd), 1 - fx);
	float ret = interpolate(td, tu, 1 - fy);
	return ret;
}

