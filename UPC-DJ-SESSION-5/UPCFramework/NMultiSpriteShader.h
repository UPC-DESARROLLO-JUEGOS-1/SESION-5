#pragma once
#include "NBaseShader.h"
class NMultiSpriteShader : public NBaseShader
{
public:
	NMultiSpriteShader() { NBaseShader::NBaseShader(); }
	~NMultiSpriteShader() { NBaseShader::~NBaseShader(); };

protected:
	void CreateAttributes();
};

