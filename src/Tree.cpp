#include "stb_image.h"
#include "Tree.hpp"

bool			Tree::first = true;
unsigned int	Tree::texture;

Tree::Tree(Shader& sha, Camera& c, float x, float y, float z, char *tex)
	: RenderObject(sha, c, x, y, z, 1,1,1)
{
	numVert = 180;
	numInd = 90;
	verts = (float*)calloc(numVert, sizeof(float));
	indices = (unsigned int*)calloc(numInd, sizeof(int));
	float arrVert[] = {
		//trunk
		0, 0, 0, 0.0f, 0.6f,
		1, 0, 0, 1.0f/ 6.0f, 0.6f,
		0, 2, 0, 0.0f, 1.0f,
		1, 2, 0, 1.0f/ 6.0f, 1.0f,
		0, 0, 1, 1.0f/ 6.0f, 0.6f,
		1, 0, 1, 0.0f, 0.6f,
		0, 2, 1, 1.0f/ 6.0f, 1.0f,
		1, 2, 1, 0.0f, 1.0f,

		//tree sides
		-1, 2, -1, 1.0f/ 6.0f, 0.6,
		2, 2, -1, 4.0f/ 6.0f, 0.6,
		-1, 4, -1, 1.0f/ 6.0f, 1,
		2, 4, -1, 4.0f/ 6.0f, 1,
		-1, 2, 2, 4.0f/ 6.0f, 0.6,
		2, 2, 2, 1.0f/ 6.0f, 0.6,
		-1, 4, 2, 4.0f/ 6.0f, 1,
		2, 4, 2, 1.0f/ 6.0f, 1,
		//tree sides up
		-1, 4, -1, 0, 0.6,
		2, 4, -1, 0.5, 0.6,
		-1, 4, 2, 0, 0,
		2, 4, 2, 0.5, 0,
		//tree sides down
		-1, 2, -1, 0.5, 0.6,
		2, 2, -1, 1, 0.6,
		-1, 2, 2, 0.5, 0,
		2, 2, 2, 1, 0,
		//tree top
		0, 4, 0, 0.5, 0.6,
		1, 4, 0, 4/6.0, 0.6,
		0, 5, 0, 0.5, 0.8,
		1, 5, 0, 4/6.0, 0.8,
		0, 4, 1, 4/6.0, 0.6,
		1, 4, 1, 0.5, 0.6,
		0, 5, 1, 4/6.0, 0.8,
		1, 5, 1, 0.5, 0.8,
		//tree top up
		0, 5, 0, 0, 0.2,
		1, 5, 0, 1/6.0, 0.2,
		0, 5, 1, 0, 0,
		1, 5, 1, 1/6.0, 0,
	};

	int arrInd[] = {
		//trunk
		0,1,2,
		1,2,3,

		4,5,6,
		5,6,7,
		0,2,4,
		2,4,6,
		1,3,5,
		3,5,7,
		//tree
		8,9,10,
		9,10,11,

		12,13,14,
		13,14,15,
		8,10,12,
		10,12,14,
		9,11,13,
		11,13,15,
		//tree sides up
		16,17,18,
		17,18,19,
		//tree sides down
		20,21,22,
		21,22,23,
		//tree
		24,25,26,
		25,26,27,

		28,29,30,
		29,30,31,
		24,26,28,
		26,28,30,
		25,27,29,
		27,29,31,
		//tree sides up
		32,33,34,
		33,34,35,
	};

	if (first)
	{
		unsigned char *data = stbi_load(tex, &width, &height, &nrChannels, 0);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		first = false;
	}

	memcpy(verts, arrVert, numVert * sizeof(float));
	memcpy(indices, arrInd, numInd * sizeof(int));
	RenderObject::Activate();
}

void	Tree::SetCurrentRender(){
	glBindTexture(GL_TEXTURE_2D, texture);
	RenderObject::SetCurrentRender();
}
