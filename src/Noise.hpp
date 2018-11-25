#ifndef NOISE_HPP
#define NOISE_HPP

#include "graphics.hpp"
#include <Eigen/Dense>

using namespace Eigen;

class Noise {
	public:
		float	elevation(float x, float y);
		float	roughness(float x, float y);
		float	local(float x, float y);
		Noise(int);

		static Noise* singleton;

		float elevRand[16][16];
		float roughRand[16][16];
		float detailRand[64][64];
		static float perlinSize;
};

#endif