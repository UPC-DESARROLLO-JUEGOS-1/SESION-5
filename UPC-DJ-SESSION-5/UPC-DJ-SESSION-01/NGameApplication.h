#pragma once

#include <UPCFramework\NWindow.h>
#include <UPCFramework\NBaseShader.h>
#include <UPCFramework\NPrimitiveQuad.h>
#include <UPCFramework\NSprite.h>
#include <UPCFramework\NMultiSprite.h>
#include <UPCFramework\NPrimitiveCircumference2D.h>
#include <UPCFramework\NFramework.h>

class NGameApplication
{
public:
	NGameApplication();
	~NGameApplication();

	void Start();
private:
	NFramework* mFramework;

	NPrimitiveQuad mQuad;
	NSprite mSprite;
	NMultiSprite mMultiSprite;
	NPrimitiveCircumference2D mCircumference;

	void Initialize();
	void ProcessInputs(SDL_Event evnt);
	void Update(float dt);
	void Draw(float dt);
};