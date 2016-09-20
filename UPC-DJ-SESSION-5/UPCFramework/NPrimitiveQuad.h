#pragma once

#include "NDrawable2D.h"

class NPrimitiveQuad : public NDrawable2D
{
public:
	NPrimitiveQuad() { NDrawable2D::NDrawable2D(); }
	~NPrimitiveQuad() { NDrawable2D::~NDrawable2D(); }

	void Initialize(float x, float y, float width, float height);
	void Draw(float dt);

private:
	float mWidth;
	float mHeight;
};

