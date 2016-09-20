#include "NGameApplication.h"
#include <UPCFramework\NEnumWindowFlags.h>
#include <GL/glew.h>

#include <iostream>

NGameApplication::NGameApplication()
{
}

NGameApplication::~NGameApplication()
{
}

void NGameApplication::Start()
{
	// Initialize the Game
	Initialize();
}

void NGameApplication::Initialize()
{
	// Initialize Framework
	mFramework = new NFramework();
	mFramework->Initialize("UPC Framework", 800, 600, NEnumWindowFlags::Windowed);
	mFramework->OnInput(std::bind(&NGameApplication::ProcessInputs, this, std::placeholders::_1));


	//// Initialize Primitive Quad
	mQuad.Initialize(10.0f, 200.0f, 200, 200);
	mQuad.SetRenderCamera(mFramework->GetCamera());

	std::string imagePath = "Sprites/sonic.png";
	std::string imageBumpPath = "Sprites/bump_map.png";

	//// Initialize Sprite
	mSprite.Initialize(10.0f, 10.0f, 200, 200, imagePath);
	mSprite.SetRenderCamera(mFramework->GetCamera());

	//// Initialize MultiSprite
	mMultiSprite.Initialize(400.0f, 120.0f, 200, 200, imagePath, imageBumpPath);
	mMultiSprite.SetRenderCamera(mFramework->GetCamera());

	// Initialize Primitive Circumference
	mCircumference.Initialize(600, 120, 80, 15);
	mCircumference.SetRenderCamera(mFramework->GetCamera());

	// Start Game Loop
	mFramework->DoGameLoop(
		std::bind(&NGameApplication::Update, this, std::placeholders::_1),
		std::bind(&NGameApplication::Draw, this, std::placeholders::_1));
}

void NGameApplication::ProcessInputs(SDL_Event evnt)
{
	switch (evnt.type) {
	case SDL_MOUSEMOTION:
		std::cout << "Mouse x: " << evnt.motion.x << " y: " << 
			evnt.motion.y << std::endl;
		break;
	case SDL_KEYDOWN:
		switch (evnt.key.keysym.sym) {
		case SDLK_w:
			std::cout << "INPUT 'W'";
			break;
		}
		break;
	}
}

void NGameApplication::Update(float dt) {
	float ro = mSprite.GetRotationZ();
	ro += 0.01f;
	mSprite.SetRotationZ(ro);

	mQuad.Update(dt);
	mSprite.Update(dt);
	mMultiSprite.Update(dt);
	mCircumference.Update(dt);
}

void NGameApplication::Draw(float dt) {
	mQuad.Draw(dt);
	mSprite.Draw(dt);
	mMultiSprite.Draw(dt);
	mCircumference.Draw(dt);
}
