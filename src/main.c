#include <stdio.h>
#include <SDL2/SDL.h>
#include "../headers/constants.h"

struct ball 
{
	float x;
	float y;
	float width;
	float height;
} ball;

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

int intialize_window(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error intializing SDL\n");
		return FALSE;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_BORDERLESS
	);
	if (!window)
	{
		fprintf(stderr, "Error creating SDL Window.\n");
		return FALSE;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr,"Error creating SDL Renderer.\n");
		return FALSE;
	}

	return TRUE;
}

void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			game_is_running = FALSE;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				game_is_running = FALSE;
			break;
	}
}

void setup()
{
	ball.x = 80;
	ball.y = 80;
	ball.width = 65;
	ball.height = 65;
}

void update()
{
	//delay to reach fps, makes gameplay be same accross all plartforms
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));
	last_frame_time = SDL_GetTicks();
	ball.x += 2;
	ball.y +=  2;
}

void render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Draw a rectangle
	SDL_Rect ball_rect = {
		(int)ball.x,
		(int)ball.y,
		(int)ball.width,
		(int)ball.height
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
	SDL_RenderFillRect(renderer, &ball_rect);

	SDL_RenderPresent(renderer);
}

void destroy_window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main()
{
	game_is_running = intialize_window();

	setup();

	while (game_is_running)
	{
		process_input();
		update();
		render();
	}

	destroy_window();

	return 0;
}
