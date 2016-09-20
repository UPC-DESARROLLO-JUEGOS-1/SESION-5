#pragma once

#include "NDrawable3D.h"

class NPrimitiveCube : public NDrawable3D
{
public:
	NPrimitiveCube() { NDrawable3D::NDrawable3D(); }
	~NPrimitiveCube() { NDrawable3D::~NDrawable3D(); }

	void Initialize(float x, float y, float z, float sizeX, 
		float sizeY, float sizeZ);
	void Draw(float dt);

private:
	float mSizeX, mSizeY, mSizeZ;
};

