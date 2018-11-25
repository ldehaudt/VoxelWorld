#ifndef SKYBOX_HPP
#define SKYBOX_HPP
#include "RenderObject.hpp"

class Skybox : public RenderObject
{
	public:
		Matrix4f posMat;
		Skybox(Shader& sha, Camera & c, float x, float y, float z,
			float sX, float sY, float sZ, char *);
		virtual void	SetCurrentRender();
		int				width, height, nrChannels;
		unsigned int	texture[3];
};

#endif
