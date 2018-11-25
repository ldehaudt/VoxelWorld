#include "Camera.hpp"
#include "ChunkManager.hpp"
#include "Noise.hpp"
#include <math.h>
float fract(float f);

Camera::Camera(){
	first = true;
	xRot = 0;
	yRot = 0;

	mode = 2;

	pitchMat = Matrix4f::Identity();
	yawMat = Matrix4f::Identity();
	viewMat = Matrix4f::Identity();
	projectionMat = Matrix4f::Identity();

	pos[0] = 10000;
	pos[1] = 0;
	pos[2] = 10000;

	viewMat(0, 3) = -pos[0];
	viewMat(1, 3) = -pos[1];
	viewMat(2, 3) = -pos[2];
	projectionMat(0, 0) = 1.0 / tan(FOV / 2 * PI / 180);
	projectionMat(1, 1) = projectionMat(0, 0);
	projectionMat(2, 2) = -FAR / (FAR - NEAR);
	projectionMat(2, 3) = -FAR * NEAR / (FAR - NEAR);
	projectionMat(3, 2) = -1;
	projectionMat(3, 3) = 0;
	reloadCameraAngle();
	reload();
}

void	Camera::reloadCameraAngle(){
	pitchMat(0, 0) = cos(xRot);
	pitchMat(0, 2) = -sin(xRot);
	pitchMat(2, 0) = sin(xRot);
	pitchMat(2, 2) = cos(xRot);

	yawMat(1, 1) = cos(yRot);
	yawMat(1, 2) = sin(yRot);
	yawMat(2, 1) = -sin(yRot);
	yawMat(2, 2) = cos(yRot);
	reload();
}

void	Camera::lookHoriz(float amount){
	xRot += amount / 200.0f;
	if (xRot > PI)
		xRot = -PI + 0.0001;
	if (xRot < -PI)
		xRot = PI;
	reloadCameraAngle();
}

void	Camera::lookVert(float amount){
	yRot += amount / 200.0f;
	if (yRot > PI / 2)
		yRot =  PI / 2;
	if (yRot < -PI / 2)
		yRot = -PI / 2;
	reloadCameraAngle();
}

void	Camera::reload(){
	Matrix = projectionMat * yawMat * pitchMat * viewMat;
}

void Camera::groundMode()
{
	float me = ChunkManager::singleton->getPlayerChunk().heightArr
	[(int)(pos[0]) % 16 + 1][(int)(pos[2]) % 16 + 1];
	float nx = ChunkManager::singleton->getPlayerChunk().heightArr
	[(int)(pos[0]) % 16 + (fract(pos[0]) > 0.5 ? 1 : -1) + 1]
	[(int)(pos[2]) % 16 + 1];
	float nz = ChunkManager::singleton->getPlayerChunk().heightArr
	[(int)(pos[0]) % 16 + 1]
	[(int)(pos[2]) % 16 + (fract(pos[2]) > 0.5 ? 1 : -1) + 1];
	float nxz = ChunkManager::singleton->getPlayerChunk().heightArr
	[(int)(pos[0]) % 16 + (fract(pos[0]) > 0.5 ? 1 : -1) + 1]
	[(int)(pos[2]) % 16 + (fract(pos[2]) > 0.5 ? 1 : -1) + 1];

	float wx = abs(fract(pos[0]) - 0.5) * (1 - abs(fract(pos[2]) - 0.5));
	float wz = abs(fract(pos[2]) - 0.5) * (1 - abs(fract(pos[0]) - 0.5));
	float wxz = abs(fract(pos[0]) - 0.5) * abs(fract(pos[2]) - 0.5);
	pos[1] = wx * nx + wz * nz + wxz * nxz + me * (1 - wx - wz - wxz) + 2;
}


void	Camera::reloadPos()
{
	viewMat(0, 3) = -pos[0];
	viewMat(2, 3) = -pos[2];
	if (mode == 2)
		groundMode();
	else if (mode == 4)
	{
		float me = ChunkManager::singleton->getPlayerChunk().caveButt
		[(int)(pos[0]) % 16 + 1][(int)(pos[2]) % 16 + 1];
		if (me == 0)
			me = ChunkManager::singleton->getPlayerChunk().heightArr
			[(int)(pos[0]) % 16 + 1][(int)(pos[2]) % 16 + 1];
		pos[1] = me + 1.5;
	}
	viewMat(0, 3) = -pos[0] - 1;
	viewMat(2, 3) = -pos[2] - 1;
	viewMat(1,3) = -pos[1];
}
