#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

/*void exitProgram()
{
	std::cout << "Kilépéshez nyomj meg egy billentyût..." << std::endl;
	std::cin.get();
}*/


int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 768;

SDL_Window*     window;                 // holds window properties
SDL_Renderer*   renderer;               // holds rendering surface properties

bool quit = true;



void initialize() {

	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create window in the middle of the screen
	window = SDL_CreateWindow("Pong",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	// Create renderer in order to draw on window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Don't show cursor
	SDL_ShowCursor(0);

}

void destroyer() {

	//SDL_DestroyTexture();

	// Destroy renderer and window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Shuts down SDL
	SDL_Quit();
}

void input() {

}

void update() {

}

void render() {

}
void gameLoop() {

	while (!quit) {
		input();
		update();
		render();
	}

	destroyer();
}


int main(int argc, char* args[])
{

	initialize();
	gameLoop();

	return 0;
}