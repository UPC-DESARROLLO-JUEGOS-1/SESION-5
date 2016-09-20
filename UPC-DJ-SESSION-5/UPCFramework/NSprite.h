#pragma once

#include "NImageContent.h"
#include "NDrawable2D.h"

#include <string>

class NSprite : public NDrawable2D
{
public:
	NSprite() { NDrawable2D::NDrawable2D(); }
	~NSprite() { NDrawable2D::~NDrawable2D(); }

	void Initialize(float x, float y, float width,
		float height, const std::string path);
	void Draw(float dt);
protected:
	float mWidth;
	float mHeight;
	
	NImageContent* mContent;
};

