#include "stb_image.h"
#include "Skybox.hpp"
#include "Input.hpp"

Skybox::Skybox(Shader& sha, Camera& c, float x, float y, float z,
	float sX, float sY, float sZ, char *tex)
	: RenderObject(sha, c, x, y, z, sX, sY, sZ)
{
	verts = (float*)calloc(120, sizeof(float));
	indices = (unsigned int*)calloc(36, sizeof(int));

	numVert = 120;
	numInd = 36;

	float arrVert[] = {
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f,


		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,


		-0.5f,  0.5f, -0.5f, 1.0f, 1,
		 0.5f,  0.5f, -0.5f, 1.0f, 1,
		 0.5f,  0.5f,  0.5f, 1.0f, 1,
		-0.5f,  0.5f,  0.5f, 1.0f, 1,

		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f };

	int arrInd[] = {
		16,  17, 19,  17, 18, 19,
		21, 20, 22, 22, 23, 20,

		3,  2,  7,  2,  6,  7,
		1,  5,  0,  0,  5,  4,

		8, 11, 12, 11, 12, 15,
		10,  9, 14,  9, 13, 14,
		 };

	string names[3];

	names[0] = "textures/day.png";
	names[1] = "textures/dusk.png";
	names[2] = "textures/night.png";

	for (int i = 0; i < 3; i++){
		unsigned char *data = stbi_load(names[i].c_str(), &width, &height, &nrChannels, 0);
		glGenTextures(1, &texture[i]);
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}

	memcpy(verts, arrVert, numVert * sizeof(float));
	memcpy(indices, arrInd, numInd * sizeof(int));

	RenderObject::Activate();
}

void	Skybox::SetCurrentRender(){
	glUseProgram(shader.program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glActiveTexture(GL_TEXTURE0);
	Matrix4f vMat = cam.viewMat;
	vMat(0,3) = 0;
	vMat(1,3) = 0;
	vMat(2,3) = 0;

	posMat = cam.projectionMat * cam.yawMat * cam.pitchMat * vMat;

	glUniform1i(glGetUniformLocation(shader.program, "tex0"), 0);
	glUniform1i(glGetUniformLocation(shader.program, "tex1"), 1);
	glUniform1i(glGetUniformLocation(shader.program, "tex2"), 2);
	GLint uniMat = glGetUniformLocation(shader.program, "matrix");
	glUniformMatrix4fv(uniMat, 1, GL_FALSE, posMat.data());
	GLint uniDay = glGetUniformLocation(shader.program, "day");
	glUniform1f(uniDay, sin((float)Input::singleton->dayFrame / 1000.0 * PI));
}
