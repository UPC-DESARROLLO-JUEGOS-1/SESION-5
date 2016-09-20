#include "FatalError.h"

#include <iostream>
#include <SDL\SDL.h>

void FatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit game...";

	int tmp;
	std::cin >> tmp;

	SDL_Quit();
	exit(100);
}