#pragma once

#include <SDL/SDL.h>
#include <functional>
#include "NWindow.h"
#include "NContentManagment.h"
#include "NShaderManagment.h"
#include "NBaseCamera.h"

enum NEnumFrameworkState {
	Running,
	Exit
};

class NFramework
{
public:
	static NFramework* GET_FRAMEWORK();

	NFramework();
	~NFramework();
	
	NContentManagment* GetContentManagment() { return &mContentManagment; }
	NShaderManagment* GetShaderManagment() { return &mShaderManagment; }
	NBaseCamera* GetCamera() { return mCamera; }

	NWindow* GetWindow() { return &mWindow; }

	void Initialize(const std::string windowName, int screenWidth,
		int screenHeight, unsigned int windowFlags);

	void SetFrameworkState(NEnumFrameworkState state) { mFrameworkState = state; }
	void OnInput(std::function<void(SDL_Event)> onInput) { mOnInput = onInput; }

	void DoGameLoop(std::function<void(float)> onUpdate, 
		std::function<void(float)> onDraw);
	void Update(float dt);
	void Draw(float dt);

private:
	static NFramework* M_FRAMEWORK;

	NEnumFrameworkState mFrameworkState;

	NBaseCamera* mCamera;

	NWindow mWindow;
	NShaderManagment mShaderManagment;
	NContentManagment mContentManagment;

	std::function<void(SDL_Event)> mOnInput;
	std::function<void(float)> mOnUpdate;
	std::function<void(float)> mOnDraw;

	float ComputeDeltaTime();
	void OnListenInputFromWindow(SDL_Event evnt);
};

