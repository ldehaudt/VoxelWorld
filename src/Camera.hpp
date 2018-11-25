#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "graphics.hpp"
#include <Eigen/Dense>

using namespace Eigen;

class Camera{
	public:
		Matrix4f projectionMat;
		Matrix4f yawMat;
		Matrix4f pitchMat;
		Matrix4f viewMat;
		Matrix4f Matrix;
		float pos[3];
		float xMouse;
		float yMouse;
		float first = false;
		Camera();
		void	lookVert(float ammount);
		void	lookHoriz(float ammount);
		float	getRotation();
		void	reloadPos();
		void    reload();
		float   xRot;
		float   yRot;

		void groundMode();

		int mode;

	private:
		void	reloadCameraAngle();
		const float FAR = 300;
		const float NEAR = 0.6f;
		const float FOV = 90;
};

#endif