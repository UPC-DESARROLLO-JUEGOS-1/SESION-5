#pragma once

#include <SDL\SDL.h>
#include <string>
#include <functional>

class NWindow
{
public:
	NWindow();
	~NWindow();

	int GetScreenWidth() { return mScreenWidth; }
	int GetScreenHeight() { return mScreenHeight; }
	
	void Present();
	void Update(float dt);
	void AddInputListener(std::function<void(SDL_Event)> callback) {
		mInputCallback = callback;
	}

	int Create(const std::string windowName, int width, int height, 
		unsigned int windowFlags);
private:
	int mScreenWidth;
	int mScreenHeight;
	
	SDL_Window* mWindow;
	std::function<void(SDL_Event)> mInputCallback;

	void ProcessInputs();
};

