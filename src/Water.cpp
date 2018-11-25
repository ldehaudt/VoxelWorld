#include "stb_image.h"
#include "Water.hpp"

Water::Water(Shader& sha, Camera& c, float x, float y, float z,
	float sX, float sZ, char *tex)
	: RenderObject(sha, c, x, y, z, sX, 1, sZ)
{
	numVert = y * 20;
	numInd = y * 6;

	verts = (float*)calloc(numVert, sizeof(float));
	indices = (unsigned int*)calloc(numInd, sizeof(int));

	for (int i = 0; i < numVert; i+= 20){
		verts[i + 0] = -0.5; 
		verts[i + 1] = -i / 20 + 0.5; 
		verts[i + 2] = -0.5; 
		verts[i + 3] = 0.0; 
		verts[i + 4] = 0.0; 

		verts[i + 5] = 0.5; 
		verts[i + 6] = -i / 20 + 0.5; 
		verts[i + 7] = -0.5; 
		verts[i + 8] = 0.0; 
		verts[i + 9] = sZ; 

		verts[i + 10] = 0.5; 
		verts[i + 11] = -i / 20 + 0.5; 
		verts[i + 12] = 0.5; 
		verts[i + 13] = sX; 
		verts[i + 14] = sZ; 

		verts[i + 15] = -0.5; 
		verts[i + 16] = -i / 20 + 0.5; 
		verts[i + 17] = 0.5; 
		verts[i + 18] = sX; 
		verts[i + 19] = 0.0; 
	}

	int num = numInd - 1;

	for (int i = 0; i < numInd * 2 / 3; i += 4){
		indices[num--] = i ;
		indices[num--] = i + 1;
		indices[num--] = i + 3;
		indices[num--] = i + 1;
		indices[num--] = i + 2;
		indices[num--] = i + 3;
	}

	unsigned char *data = stbi_load(tex, &width, &height, &nrChannels, 0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	RenderObject::Activate();
}

void	Water::SetCurrentRender(){
	glBindTexture(GL_TEXTURE_2D, texture);

	glUseProgram(shader.program);

	Matrix4f vMat = cam.viewMat;
	vMat(0,3) = cam.viewMat(0,3) - (int)cam.viewMat(0,3);
	vMat(2,3) = cam.viewMat(2,3) - (int)cam.viewMat(2,3);

	posMat = cam.projectionMat * cam.yawMat * cam.pitchMat * vMat;

	GLint uniMat = glGetUniformLocation(shader.program, "matrix");
	glUniformMatrix4fv(uniMat, 1, GL_FALSE, posMat.data());
}
