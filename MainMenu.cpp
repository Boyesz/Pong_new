#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "pong2.h"
/*void exitProgram()
{
std::cout << "Kilépéshez nyomj meg egy billentyût..." << std::endl;
std::cin.get();
}*/


SDL_Texture* Menuprogs = NULL;
SDL_Texture* Background = NULL;
SDL_Texture* G3dpong = NULL;
SDL_Texture* G2dpong = NULL;
SDL_Texture* MenuG = NULL;
SDL_Texture* Mainmenu = NULL;
SDL_Texture* Menumath = NULL;


SDL_Rect Mainmenu1;
SDL_Rect Menugames1;
SDL_Rect Menuprogs1;
SDL_Rect Menumaths1;
SDL_Rect G2dpong1;
SDL_Rect G3dpong1;

bool click = false , InMain = true , InGame = false;

SDL_MouseButtonEvent* botton;

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

	G2dpong = IMG_LoadTexture(renderer, "Games2dpong.png");
	if (G2dpong == 0)
	{
		std::cout << "[Kép betöltése] Hiba: " << IMG_GetError() << std::endl;
		SDL_DestroyWindow(window);
	}
	G3dpong = IMG_LoadTexture(renderer, "Games3dpong.png");
	if (G3dpong == 0)
	{
		std::cout << "[Kép betöltése] Hiba: " << IMG_GetError() << std::endl;
		SDL_DestroyWindow(window);
	}
	MenuG = IMG_LoadTexture(renderer, "Menugames.png");
	if (MenuG == 0)
	{
		std::cout << "[Kép betöltése] Hiba: " << IMG_GetError() << std::endl;
		SDL_DestroyWindow(window);
		
	}
	Mainmenu= IMG_LoadTexture(renderer, "Mainmenu.png");
	if (Mainmenu == 0)
	{
		std::cout << "[Kép betöltése] Hiba: " << IMG_GetError() << std::endl;
		SDL_DestroyWindow(window);
	}
	Menumath = IMG_LoadTexture(renderer, "Menumath.png");
	if (Menumath == 0)
	{
		std::cout << "[Kép betöltése] Hiba: " << IMG_GetError() << std::endl;
		SDL_DestroyWindow(window);
	}
	Menuprogs = IMG_LoadTexture(renderer, "Menugprogs.png");
	if (Menuprogs == 0)
	{
		std::cout << "[Kép betöltése] Hiba: " << IMG_GetError() << std::endl;
		SDL_DestroyWindow(window);
	}
	Background = IMG_LoadTexture(renderer, "Background.png");
	if (Background == 0)
	{
		std::cout << "[Kép betöltése] Hiba: " << IMG_GetError() << std::endl;
		SDL_DestroyWindow(window);
	}

}


void handleEventsMenu(SDL_Event *ev) {

	int elozox;
	int elozoy;

	while (SDL_PollEvent(ev))
	{
		switch (ev->type)
		{
		case SDL_QUIT:
			needQuit = true;
			break;
		case SDLK_SPACE:
			break;
		case SDL_MOUSEMOTION:
			elozox = ev->motion.x;
			elozoy = ev->motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (ev->button.button == SDL_BUTTON_LEFT) {
				click = true;
				elozox = ev->button.x;
				elozoy = ev->button.y;
			}
			if (Mainmenu1.x + Mainmenu1.w >= elozox && Mainmenu1.x <= elozox && Mainmenu1.y + Mainmenu1.h >= elozoy &&  Mainmenu1.y <= elozoy && click == true )
			{
				InMain = true;
				InGame = false;
			}
			if (Menugames1.x + Menugames1.w >= elozox && Menugames1.x <= elozox && Menugames1.y + Menugames1.h >= elozoy &&  Menugames1.y <= elozoy && click== true)
			{
				InMain = false;
				InGame = true;
			}
			if (G2dpong1.x + G2dpong1.w >= elozox && G2dpong1.x <= elozox && G2dpong1.y + G2dpong1.h >= elozoy &&  G2dpong1.y <= elozoy && click == true && InGame == true)
			{
				destroyer();
				start();
			}

			break;
		case SDL_MOUSEBUTTONUP:
			if (ev->button.button == SDL_BUTTON_LEFT) {
				click = false;
			}
			break;
		}
	}

}

void render() {

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_Rect Background1 = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	SDL_RenderCopy(renderer, Background, NULL,NULL);

	Mainmenu1 = { SCREEN_WIDTH/3+30,SCREEN_HEIGHT/4,130,30 };
	SDL_RenderCopy(renderer, Mainmenu, NULL, &Mainmenu1);

	if (InMain == true)
	{
		Menugames1 = { 50,300,130,30 };
		SDL_RenderCopy(renderer, MenuG, NULL, &Menugames1);

		Menuprogs1 = { 250,300,130,30 };
		SDL_RenderCopy(renderer, Menuprogs, NULL, &Menuprogs1);

		Menumaths1 = { 450,300,130,30 };
		SDL_RenderCopy(renderer, Menumath, NULL, &Menumaths1);
	}

	if (InGame == true)
	{
		G2dpong1 = { 50,300,130,30 };
		SDL_RenderCopy(renderer, G2dpong, NULL, &G2dpong1);

		G3dpong1 = { 250,300,130,30 };
		SDL_RenderCopy(renderer, G3dpong, NULL, &G3dpong1);
	}
	//swap buffer
	SDL_RenderPresent(renderer);
}

void gameLoop(SDL_Event *ev) {

	while (!needQuit) {

		handleEventsMenu(ev);
		render();
	}

	destroyer();
}


int main(int argc, char* args[])
{
	SDL_Event ev;

	initialize();
	gameLoop(&ev);



	return 0;
}