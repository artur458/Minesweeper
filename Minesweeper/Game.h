#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "UI.h"
class Game
{
public:

	SDL_Renderer* renderer;

	SDL_Texture* cellTextures;

	UI ui;
	int grid[24][25]; // one cell is 20x20 pixels, so 24*20=480, 25*20=500

	bool flags[24][25]{};
	bool opened[24][25]{};

	int startMines = 50;
	int currectMines;

	bool gameOver = false;

	void Setup();
	void GameLoop();

private:
	void CellButton(
		int x, int y,
		SDL_Renderer* renderer,
		SDL_Texture* cellTexture);
	void OpenCell(int x, int y);
};