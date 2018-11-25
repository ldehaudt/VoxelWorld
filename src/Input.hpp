#ifndef INPUT_HPP
#define INPUT_HPP

#include "Camera.hpp"
#include "Window.hpp"
#include "graphics.hpp"

class PostProcess;

class Input{
	public:
		float curTime;
		float startTime;
		int dayFrame;
		float lastTime;
		float moveSpeed;

		Input(Camera& c, Window& w);
		Camera& cam;
		Window& win;
		void KeyHold(Window& win);
		float   dist(Position& a, Position& b);
		bool spaceDown = false;
		int obj;
		static Input* singleton;
};

#endif