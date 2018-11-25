#ifndef WATER_HPP
#define WATER_HPP
#include "RenderObject.hpp"
#include <Eigen/Dense>

using namespace Eigen;

class Water : public RenderObject
{
	public:
		Matrix4f posMat;

		Water(Shader& sha, Camera & c, float x, float y, float z,
			float sX, float sY, char *);
		void	SetCurrentRender();
		int				width, height, nrChannels;
		unsigned int	texture;
};

#endif
