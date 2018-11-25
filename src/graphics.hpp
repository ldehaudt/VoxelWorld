#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <string>
#include <iostream>
#include <OpenGL/gl3ext.h>
#endif
#include <GLFW/glfw3.h>

#define RED "\e[1;38;2;225;20;20m"
#define ORANGE "\e[1;38;2;255;120;10m"
#define YELLO "\e[1;38;2;255;200;0m"
#define GREEN "\e[1;38;2;80;200;60m"
#define BLUE "\e[1;38;2;50;150;250m"

using namespace std;

struct Position {
	float x;
	float y;
};

#define MAPSIZE 2000.0
#define W 2560
#define H 1440
#define PI 3.14159265359

#endif