#pragma once

#include "NDrawable2D.h"

class NPrimitiveCircumference2D : public NDrawable2D
{
public:
	NPrimitiveCircumference2D() { NDrawable2D::NDrawable2D(); }
	~NPrimitiveCircumference2D() { NDrawable2D::~NDrawable2D(); };

	void Initialize(float x, float y, float radius, int vertexCount);
	void Draw(float dt);
private:
	int mVertexCount;
	int mIndicesCount;
	float mRadius;

	GLuint mIBO_ID;
};

