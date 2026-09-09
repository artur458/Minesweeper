#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <SDL3_image/SDL_image.h>

#include <SDL3_ttf/SDL_ttf.h>

#include "UI.h"
#include "Game.h"

#include <iostream>
#include <string>

static SDL_Window* window;
static SDL_Renderer* renderer;

Game game;

TTF_Font* buttonFont;
TTF_Font* scoreFont;


SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	SDL_CreateWindowAndRenderer("Minesweeper by DPStudio", 500, 630, SDL_EVENT_WINDOW_RESIZED, &window, &renderer);

	game.Setup();
	game.renderer = renderer;
	game.cellTextures = IMG_LoadTexture(renderer, "textures/cells.png");

	buttonFont = TTF_OpenFont("font/Roboto-Regular.ttf", 13);
	scoreFont = TTF_OpenFont("font/Roboto-Regular.ttf", 50);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);
	SDL_RenderClear(renderer);

#pragma region UI
	if (game.ui.Button(0, "Window", buttonFont, { 0, 0, 0, 255 }, renderer, 10, 10, 50, 20,
		{ 192, 192, 192, 255 },
		{ 128, 128, 128, 255 },
		{ 64, 64, 64, 255 }))
		SDL_ShowWindowSystemMenu(window, 10, 10);

	if (game.ui.Button(1, "Game", buttonFont, { 0, 0, 0, 255 }, renderer, 70, 10, 50, 20,
		{ 192, 192, 192, 255 },
		{ 128, 128, 128, 255 },
		{ 64, 64, 64, 255 }))
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_INFORMATION,
			"Game",
			"Here you can set mine count.",
			NULL
		);
		

	if (game.ui.Button(2, "Help", buttonFont, { 0, 0, 0, 255 }, renderer, 130, 10, 50, 20,
		{ 192, 192, 192, 255 },
		{ 128, 128, 128, 255 },
		{ 64, 64, 64, 255 }))
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_INFORMATION,
			"Help",
			"Left click to open a cell.\nRight click to place a flag.\n\nIf you open a mine, you lose.\nIf you place all flags correctly, you win.",
			NULL
		);
	}

	game.ui.DrawPanelOld(renderer, 10, 40, 480, 70);

	game.ui.DrawText(0, renderer, scoreFont, std::to_string(game.startMines).c_str(), 15, 15, { 255, 84, 84, 255 });

	game.ui.DrawPanelOld(renderer, 10, 120, 480, 500);

#pragma endregion

	game.GameLoop();

	SDL_RenderPresent(renderer);
	if (game.gameOver)
	{
		game.gameOver = false;

		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR,
			"Game Over",
			"You hit a mine! Game Over!",
			NULL
		);
		return SDL_APP_SUCCESS;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	if (event->type == SDL_EVENT_QUIT)
		return SDL_APP_SUCCESS;

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_CloseFont(scoreFont);
	TTF_CloseFont(buttonFont);
	TTF_Quit();
	SDL_Quit();
}