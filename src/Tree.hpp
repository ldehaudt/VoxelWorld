#ifndef TREE_HPP
#define TREE_HPP
#include "RenderObject.hpp"

class Tree : public RenderObject
{
	public:
		Tree(Shader& sha, Camera & c, float x, float y, float z, char *);
		~Tree();

		static bool first;
		static unsigned int texture;

		virtual void	SetCurrentRender();

		int	width, height, nrChannels;
};

#endif
