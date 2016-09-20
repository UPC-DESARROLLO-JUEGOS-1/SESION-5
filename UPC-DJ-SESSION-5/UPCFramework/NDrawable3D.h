#pragma once

#include <GL/glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "NBaseShader.h"
#include "NBaseCamera.h"

class NDrawable3D
{
public:
	NDrawable3D();
	~NDrawable3D();

	virtual float GetX() { return mX; }
	virtual float GetY() { return mY; }
	virtual float GetZ() { return mZ; }
	virtual float GetRotationX() { return mRotationX; }
	virtual float GetRotationY() { return mRotationY; }
	virtual float GetRotationZ() { return mRotationZ; }
	virtual float GetScaleX() { return mScaleX; }
	virtual float GetScaleY() { return mScaleY; }
	virtual float GetScaleZ() { return mScaleZ; }

	virtual void SetX(float value) {
		mX = value;
		mNeedMatrixUpdate = true;
	}

	virtual void SetY(float value) {
		mY = value;
		mNeedMatrixUpdate = true;
	}

	virtual void SetZ(float value) {
		mZ = value;
		mNeedMatrixUpdate = true;
	}

	virtual void SetScaleX(float value) {
		mScaleX = value;
		mNeedMatrixUpdate = true;
	}

	virtual void SetScaleY(float value) {
		mScaleY = value;
		mNeedMatrixUpdate = true;
	}

	virtual void SetScaleZ(float value) {
		mScaleZ = value;
		mNeedMatrixUpdate = true;
	}

	virtual void SetRotationX(float value) {
		mRotationX = value;
		mNeedMatrixUpdate = true;
	}

	virtual void SetRotationY(float value) {
		mRotationY = value;
		mNeedMatrixUpdate = true;
	}

	virtual void SetRotationZ(float value) {
		mRotationZ = value;
		mNeedMatrixUpdate = true;
	}

	void SetRenderCamera(NBaseCamera* renderCamera) { mRenderCamera = renderCamera; }

	virtual void Initialize(float x, float y, float z);

	virtual void Update(float dt) {
		if (mNeedMatrixUpdate) {
			glm::mat4 result(1.0f);

			glm::vec3 translate(mX, mY, mZ);
			glm::vec3 scale(mScaleX, mScaleY, mScaleZ);
			
			result = glm::translate(result, translate);
			result = glm::scale(result, scale);
			result = glm::rotate(result, mRotationX, glm::vec3(1.0f, 0.0f, 0.0f));
			result = glm::rotate(result, mRotationY, glm::vec3(0.0f, 1.0f, 0.0f));
			result = glm::rotate(result, mRotationZ, glm::vec3(0.0f, 0.0f, 1.0f));

			mWorldMatrix = result;

			mNeedMatrixUpdate = false;
		}
	}

	virtual void Draw(float dt) {}

protected:
	float mX, mY, mZ;
	float mScaleX, mScaleY, mScaleZ;
	float mRotationX, mRotationY, mRotationZ;
	glm::mat4 mWorldMatrix;

	GLuint mVBO_ID;
	GLuint mIBO_ID;
	NBaseShader* mCurrentShader;
	NBaseCamera* mRenderCamera;
private:
	bool mNeedMatrixUpdate;
};

