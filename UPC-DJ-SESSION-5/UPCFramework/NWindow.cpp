#include "NWindow.h"
#include "NEnumWindowFlags.h"
#include "FatalError.h"

#include <GL/glew.h>

NWindow::NWindow() :
	mScreenWidth(0),
	mScreenHeight(0)
{
}

NWindow::~NWindow()
{
}

void NWindow::Present() {
	SDL_GL_SwapWindow(mWindow);
}

int NWindow::Create(const std::string windowName, int width, int height,
	unsigned int windowFlags) {

	mScreenWidth = width;
	mScreenHeight = height;

	Uint32 flags = SDL_WINDOW_OPENGL;

	if (windowFlags & NEnumWindowFlags::Invisible) { flags |= SDL_WINDOW_HIDDEN; }
	if (windowFlags & NEnumWindowFlags::Fullscreen) { flags |= SDL_WINDOW_FULLSCREEN; }
	if (windowFlags & NEnumWindowFlags::Borderless) { flags |= SDL_WINDOW_BORDERLESS; }

	// Create window with SDL
	mWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, mScreenWidth, mScreenHeight, flags);

	if (mWindow == nullptr) {
		FatalError("SDL Window could not be created!");
	}

	// Create OpenGL Context
	SDL_GLContext glContext = SDL_GL_CreateContext(mWindow);

	if (glContext == nullptr) {
		FatalError("SDL_GL_Context could not be created!");
	}

	// Initialize GLEW
	GLenum error = glewInit();

	if (error != GLEW_OK) {
		FatalError("GLEW could not be Initialize!");
	}
	
	// Clear the initial window
	glClearColor(0, 0, 1.0f, 1.0f);
	// This print to console the OpenGL version
	std::printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));
	// Set V-Sync
	SDL_GL_SetSwapInterval(1);

	return 0;
}

void NWindow::ProcessInputs()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		if (mInputCallback != NULL) {
			mInputCallback(evnt);
		}
	}
}

void NWindow::Update(float dt)
{
	ProcessInputs();
}
