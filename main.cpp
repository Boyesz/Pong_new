#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

/*void exitProgram()
{
std::cout << "Kilépéshez nyomj meg egy billentyût..." << std::endl;
std::cin.get();
}*/

struct ball {
	SDL_Rect Ball;
	int velocityX = 5;
	int velocityY = 5;
};

struct player {


	SDL_Rect player_paddle;
	int score;


};

bool move[4] = { 0,0,0,0 };

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

SDL_Window*     window;                 // holds window properties
SDL_Renderer*   renderer;               // holds rendering surface properties

player p1;
player p2;

ball labda;

bool needQuit = false;

void initialize(player *p1, player *p2,ball *labda) {

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

	p1->player_paddle.x = SCREEN_WIDTH - 30;
	p1->player_paddle.h = 60;
	p1->player_paddle.w = 10;
	p1->player_paddle.y = SCREEN_HEIGHT / 2;

	p2->player_paddle.x = 30;
	p2->player_paddle.h = 60;
	p2->player_paddle.w = 10;
	p2->player_paddle.y = SCREEN_HEIGHT / 2;

	labda->Ball.h = 10;
	labda->Ball.w = 10;
	labda->Ball.x = SCREEN_WIDTH / 2;
	labda->Ball.y = SCREEN_HEIGHT / 2;

	// Don't show cursor
	SDL_ShowCursor(false);

}

void restart(player *p1, player *p2, ball *labda) {

	p1->player_paddle.x = SCREEN_WIDTH - 30;
	p1->player_paddle.h = 60;
	p1->player_paddle.w = 10;
	p1->player_paddle.y = SCREEN_HEIGHT / 2;

	p2->player_paddle.x = 30;
	p2->player_paddle.h = 60;
	p2->player_paddle.w = 10;
	p2->player_paddle.y = SCREEN_HEIGHT / 2;

	labda->Ball.h = 10;
	labda->Ball.w = 10;
	labda->Ball.x = SCREEN_WIDTH / 2;
	labda->Ball.y = SCREEN_HEIGHT / 2;


}

void destroyer() {

	//SDL_DestroyTexture();

	// Destroy renderer and window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Shuts down SDL
	SDL_Quit();
}

void handleEvents( SDL_Event *ev) {
	
		while (SDL_PollEvent(ev))
		{
			switch (ev->type)
			{
			case SDL_QUIT:
				needQuit = true;
				break;
			case SDLK_SPACE:
				break;
			case SDL_KEYDOWN:
				switch (ev->key.keysym.sym)
				{
				case SDLK_UP:
					move[0] = 1;
					break;
				case SDLK_DOWN:
					move[1] = 1;
					break;
				case SDLK_w:
					move[2] = 1;
					break;
				case SDLK_s:
					move[3] = 1;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (ev->key.keysym.sym)
				{
				case SDLK_UP:
					move[0] = 0;
					break;
				case SDLK_DOWN:
					move[1] = 0;
					break;
				case SDLK_w:
					move[2] = 0;
					break;
				case SDLK_s:
					move[3] = 0;
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			}
		}

}

void update(bool move[],player *p1,player *p2,ball *labda) {

	int fetch = 5;

	if (move[0] == 1)//p1 fel
	{
		p1->player_paddle.y -= fetch;
	}
	if (move[1] == 1)//p1 le
	{
		p1->player_paddle.y += fetch;
	}
	if (move[2] == 1)//p2 fel
	{
		p2->player_paddle.y -= fetch;
	}
	if (move[3] == 1)//p2 le
	{
		p2->player_paddle.y += fetch;
	}

	//labda mozgatása

	labda->Ball.y += labda->velocityY;
	labda->Ball.x += labda->velocityX;

	// labda utközés érzékelés;
	if (labda->Ball.y + labda->Ball.h >= SCREEN_HEIGHT)
	{
		 labda->velocityY *= (-1);
	}

	if (labda->Ball.y + labda->Ball.h <= 0)
	{
		 labda->velocityY *= (-1);
	}

	//paddle ütkőzés beta
	if ((p1->player_paddle.x + p1->player_paddle.w) <= (labda->Ball.x + labda->Ball.w) && p1->player_paddle.y <= (labda->Ball.y + labda->Ball.h) && (p1->player_paddle.y + p1->player_paddle.h) >= (labda->Ball.y + labda->Ball.h))
	{
		labda->velocityX *= (-1);
	}
	if ((p2->player_paddle.x + p2->player_paddle.w) >= (labda->Ball.x + labda->Ball.w) && p2->player_paddle.y <= (labda->Ball.y + labda->Ball.h) && (p2->player_paddle.y + p2->player_paddle.h) >= (labda->Ball.y + labda->Ball.h))
	{
		labda->velocityX *= (-1);
	}
	if (labda->Ball.x < 0)
	{
		restart(p1,p2,labda);

	}
	if (labda->Ball.x > SCREEN_WIDTH)
	{
		restart(p1,p2, labda);
	}



}

void render(player *p1,player *p2,ball *labda) {
	
	/*
	//ezen még dolgozom
	bool *launchball;
	bool launch = false;
	launchball = &launch;
	*/
	//háttér
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);        
	SDL_RenderClear(renderer);
	// közép vonal
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_Rect midline = { SCREEN_WIDTH/2 , 0 , 1 , SCREEN_HEIGHT };
	SDL_RenderFillRect(renderer, &midline);

	//ball paddle
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect player1 = { p1->player_paddle.x , p1->player_paddle.y ,p1->player_paddle.w , p1->player_paddle.h };
	SDL_RenderFillRect(renderer, &player1);
	//jobb paddle
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_Rect player2 = { p2->player_paddle.x , p2->player_paddle.y ,p2->player_paddle.w ,p2->player_paddle.h };
	SDL_RenderFillRect(renderer, &player2);
	//labda
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect labda1 = { labda->Ball.x,labda->Ball.y,labda->Ball.w,labda->Ball.h };
	SDL_RenderFillRect(renderer, &labda1);

	//swap buffer
	SDL_RenderPresent(renderer);
}

void gameLoop(SDL_Event *ev,player p1,player p2,ball labda) {

	while (!needQuit) {
		

		handleEvents(ev);
		update(move,&p1,&p2,&labda);
		render(&p1,&p2,&labda);
	}

	destroyer();
}


int main(int argc, char* args[])
{
	SDL_Event ev;

	initialize(&p1,&p2,&labda);
	gameLoop(&ev,p1,p2,labda);

	return 0;
}