#include "NCamera3D.h"

#define PI 3.14159265
#define PiOver4 PI / 4.0f;

void NCamera3D::Initialize(int screenWidth, int screenHeight)
{
	NBaseCamera::Initialize(screenWidth, screenHeight);

	float aspectRatio = (float)screenWidth / (float)screenHeight;
	float fov = PiOver4;

	mZ = -5.0f;

	glm::vec3 lookAt(mX, mY, mZ); 
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	mProjectionMatrix = glm::perspectiveFov(fov, (float)screenWidth, (float)screenHeight, 0.01f, 10.0f);
	mViewMatrix = glm::lookAt(lookAt, center, up);
}

void NCamera3D::Update(float dt)
{
	NBaseCamera::Update(dt);
}
