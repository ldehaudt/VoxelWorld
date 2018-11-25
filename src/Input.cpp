#include "input.hpp"
#include "math.h"
#include "ChunkManager.hpp"
#include <vector>

Input* Input::singleton;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (Input::singleton->cam.first)
	{
		Input::singleton->cam.xMouse = xpos;
		Input::singleton->cam.yMouse = ypos;
		Input::singleton->cam.first = false;
	}

	Input::singleton->cam.lookHoriz(Input::singleton->cam.xMouse - xpos);
	Input::singleton->cam.lookVert(Input::singleton->cam.yMouse - ypos);
	Input::singleton->cam.xMouse = xpos;
	Input::singleton->cam.yMouse = ypos;
}

Input::Input(Camera& c, Window& w) : cam(c), win(w)
{
	Input::singleton = this;
	glfwSetCursorPosCallback(win.window, &mouse_callback);
	startTime = glfwGetTime();
	dayFrame = 0;
}

float	Input::dist(Position& a, Position& b)
{
	return (sqrt(pow(a.x + b.x, 2) + pow(a.y + b.y, 2)));
}

void	Input::KeyHold(Window& win)
{
	dayFrame++;
	if (dayFrame >= 2000)
		dayFrame = 0;
	curTime = glfwGetTime();
	float deltaTime = curTime - lastTime;
	lastTime = glfwGetTime();

	if (glfwGetKey(win.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(win.window, true);

	if (cam.mode == 4)
		moveSpeed = deltaTime * 1.0f;
	else
		moveSpeed = deltaTime * 20.0f;

	if (glfwGetKey(win.window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (cam.mode == 3)
		{
			cam.pos[1] += sin(cam.yRot) * moveSpeed;
			cam.pos[2] -= cos(-cam.xRot) * moveSpeed * cos(cam.yRot);
			cam.pos[0] += sin(-cam.xRot) * moveSpeed * cos(cam.yRot);
		}
		else
		{
			cam.pos[2] -= cos(-cam.xRot) * moveSpeed;
			cam.pos[0] += sin(-cam.xRot) * moveSpeed;
		}
	}
	if (glfwGetKey(win.window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (cam.mode == 3){
			cam.pos[1] -= sin(cam.yRot) * moveSpeed;
			cam.pos[2] += cos(-cam.xRot) * moveSpeed * cos(cam.yRot);
			cam.pos[0] -= sin(-cam.xRot) * moveSpeed * cos(cam.yRot);
		}
		else
		{
			cam.pos[2] += cos(-cam.xRot) * moveSpeed;
			cam.pos[0] -= sin(-cam.xRot) * moveSpeed;
		}
	}
	if (glfwGetKey(win.window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cam.pos[0] -= cos(-cam.xRot) * moveSpeed;
		cam.pos[2] -= sin(-cam.xRot) * moveSpeed;
	}
	if (glfwGetKey(win.window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cam.pos[0] += cos(-cam.xRot) * moveSpeed;
		cam.pos[2] += sin(-cam.xRot) * moveSpeed;
	}
	if (glfwGetKey(win.window, GLFW_KEY_SPACE) == GLFW_PRESS)
			cam.pos[1] += 0.3f;
	if (glfwGetKey(win.window, GLFW_KEY_1) == GLFW_PRESS)
		cam.mode = 3;
	if (glfwGetKey(win.window, GLFW_KEY_2) == GLFW_PRESS)
		cam.mode = 2;
	if (glfwGetKey(win.window, GLFW_KEY_3) == GLFW_PRESS)
		cam.mode = 1;
	if (glfwGetKey(win.window, GLFW_KEY_4) == GLFW_PRESS)
		cam.mode = 4;
	if (glfwGetKey(win.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && cam.mode == 1)
		cam.pos[1] -= 0.8f;
	
	ChunkManager::singleton->PlayerMoved(cam.pos[0], cam.pos[2]);
	cam.reloadPos();
	cam.reload();

	if (glfwGetKey(win.window, GLFW_KEY_SPACE) == GLFW_PRESS)
		spaceDown = true;
	else
		spaceDown = false;
}
