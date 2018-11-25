#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "Input.hpp"
#include "Noise.hpp"
#include "Camera.hpp"
#include "ChunkManager.hpp"
#include "Chunk.hpp"
#include "Window.hpp"
#include "Water.hpp"
#include "Shader.hpp"
#include "Skybox.hpp"

int main(int ac, char ** av)
{
	Window win("Vox", W ,H);
	if (ac != 2)
	{
		cout << ORANGE << "Usage: Vox [-r | seed(integer)]" << endl;
		cout << "\t-r : random seed" << endl;
		exit(1);
	}
	if (!strcmp(av[1], "-r"))
		Noise n(time(NULL));
	else
		Noise n(atoi(av[1]));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glfwSetInputMode(win.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Camera cam;
	Shader	basicShader("shaders/vert.vs", "shaders/frag.fs");
	Shader	skyShader("shaders/sky.vs", "shaders/sky.fs");
	Input	in(cam, win);
	Water	water(basicShader, cam, 0, 65, 0, 400, 400, "textures/water.png");
	ChunkManager	cm(basicShader, cam, cam.pos[0], cam.pos[2]);
	vector<RenderObject*> objs;
	Skybox sky (skyShader, cam, 0, -10, 0, 200,300,200, "textures/day.png");

	while(!glfwWindowShouldClose(win.window))
	{
		glClearColor(0.0859f, 0.121f, 0.226f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		in.KeyHold(win);

		glDepthMask(GL_FALSE);
		sky.SetCurrentRender();
		sky.Render();

		glDepthMask(GL_TRUE);
		cm.renderChunks();
		water.SetCurrentRender();
		water.Render();
		win.Update();
	}
}
