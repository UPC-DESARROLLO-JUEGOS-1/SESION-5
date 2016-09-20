#include "NDrawable3D.h"

NDrawable3D::NDrawable3D() :
	mVBO_ID(0), mIBO_ID(0),
	mNeedMatrixUpdate(true),
	mWorldMatrix(1.0f),
	mX(0.0f), mY(0.0f), mZ(0.0f),
	mScaleX(1.0f), mScaleY(1.0f), mScaleZ(1.0f),
	mRotationX(0.0f), mRotationY(0.0f), mRotationZ(0.0f)
{ }

NDrawable3D::~NDrawable3D()
{
	if (mVBO_ID != 0) {
		glDeleteBuffers(1, &mVBO_ID);
	}

	if (mIBO_ID != 0) {
		glDeleteBuffers(1, &mIBO_ID);
	}
}

void NDrawable3D::Initialize(float x, float y, float z) {
	mX = x;
	mY = y;
	mZ = z;

	if (mVBO_ID == 0) {
		glGenBuffers(1, &mVBO_ID);
	}

	if (mIBO_ID == 0) {
		glGenBuffers(1, &mIBO_ID);
	}
}
