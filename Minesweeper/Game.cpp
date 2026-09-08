#include "Game.h"
#include <random>
#include <time.h>

bool isHover(float mouseX, float mouseY, const SDL_FRect& rect)
{
	return mouseX >= rect.x &&
		mouseX < rect.x + rect.w &&
		mouseY >= rect.y &&
		mouseY < rect.y + rect.h;
}

void Game::Setup() {
	srand(time(NULL));

    for (int x = 0; x < 24; x++)
    {
        for (int y = 0; y < 25; y++)
        {
            grid[x][y] = 0;
        }
    }

    int mines = 0;

    while (mines < startMines)
    {
        int x = rand() % 24;
        int y = rand() % 25;

        if (grid[x][y] == -1)
            continue;

        grid[x][y] = -1;
        mines++;

        if (x > 0 && y > 0 && grid[x - 1][y - 1] != -1)
            grid[x - 1][y - 1]++;

        if (x > 0 && grid[x - 1][y] != -1)
            grid[x - 1][y]++;

        if (x > 0 && y < 24 && grid[x - 1][y + 1] != -1)
            grid[x - 1][y + 1]++;

        if (y < 24 && grid[x][y + 1] != -1)
            grid[x][y + 1]++;

        if (x < 23 && y < 24 && grid[x + 1][y + 1] != -1)
            grid[x + 1][y + 1]++;

        if (x < 23 && grid[x + 1][y] != -1)
            grid[x + 1][y]++;

        if (x < 23 && y > 0 && grid[x + 1][y - 1] != -1)
            grid[x + 1][y - 1]++;

        if (y > 0 && grid[x][y - 1] != -1)
            grid[x][y - 1]++;
    }
}

void Game::GameLoop()
{
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 25; j++) {
			if (opened[i][j]) {
				if(grid[i][j] == -1) {
                    ui.DrawPanelOldWithTexture(renderer, cellTextures, { 10.f + i * 20, 120.f + j * 20, 20, 20 }, { 32, 0, 16, 16 });
				}
                else if (grid[i][j] == 1) {
                    ui.DrawPanelOldWithTexture(renderer, cellTextures, { 10.f + i * 20, 120.f + j * 20, 20, 20 }, { 0, 16, 16, 16 });
                }
				else if(grid[i][j] == 2) {
					ui.DrawPanelOldWithTexture(renderer, cellTextures, { 10.f + i * 20, 120.f + j * 20, 20, 20 }, { 16, 16, 16, 16 });
				}
                else if (grid[i][j] == 3) {
                    ui.DrawPanelOldWithTexture(renderer, cellTextures, { 10.f + i * 20, 120.f + j * 20, 20, 20 }, { 32, 16, 16, 16 });
                }
                else if (grid[i][j] == 4) {
                    ui.DrawPanelOldWithTexture(renderer, cellTextures, { 10.f + i * 20, 120.f + j * 20, 20, 20 }, { 48, 16, 16, 16 });
                }
                else if (grid[i][j] == 5) {
                    ui.DrawPanelOldWithTexture(renderer, cellTextures, { 10.f + i * 20, 120.f + j * 20, 20, 20 }, { 0, 32, 16, 16 });
                }
                else if (grid[i][j] == 6) {
                    ui.DrawPanelOldWithTexture(renderer, cellTextures, { 10.f + i * 20, 120.f + j * 20, 20, 20 }, { 16, 32, 16, 16 });
                }
                else if (grid[i][j] == 7) {
                    ui.DrawPanelOldWithTexture(renderer, cellTextures, { 10.f + i * 20, 120.f + j * 20, 20, 20 }, { 32, 32, 16, 16 });
                }
                else if (grid[i][j] == 8) {
                    ui.DrawPanelOldWithTexture(renderer, cellTextures, { 10.f + i * 20, 120.f + j * 20, 20, 20 }, { 48, 32, 16, 16 });
                }
				else {
					ui.DrawPanelOldWithTexture(renderer, cellTextures, { 10.f + i * 20, 120.f + j * 20, 20, 20 }, { 48, 0, 16, 16 });
				}
			}
			else {
				CellButton(i, j, renderer, cellTextures);
			}
		}
	}
}

void Game::CellButton(
    int x, int y,
    SDL_Renderer* renderer,
    SDL_Texture* cellTexture)
{
    SDL_FRect rect{
        10.0f + x * 20.0f,
        120.0f + y * 20.0f,
        20.0f,
        20.0f
    };

    float mouseX, mouseY;
    SDL_MouseButtonFlags buttons =
        SDL_GetMouseState(&mouseX, &mouseY);

    if (isHover(mouseX, mouseY, rect))
    {
        if (buttons & SDL_BUTTON_RMASK)
        {
            flags[x][y] = !flags[x][y];
            if (flags[x][y] && grid[x][y] == -1) {
                currectMines++;
            }
			else if (!flags[x][y] && grid[x][y] == -1) {
				currectMines--;
			}
			if (currectMines == startMines) {
				gameOver = true;
			}
        }
        if (buttons & SDL_BUTTON_LMASK && !flags[x][y])
        {
            opened[x][y] = true;
            if (grid[x][y] == -1) {
                for (int i = 0; i < 24; i++) {
                    for (int j = 0; j < 25; j++) {
						if (grid[i][j] == -1) {
							opened[i][j] = true;
						}
                    }
                }

                gameOver = true;
            }
        }
    }

    SDL_FRect src;

    if (flags[x][y])
        src = { 16, 0, 16, 16 };
    else
        src = { 0, 0, 16, 16 };

    SDL_RenderTexture(
        renderer,
        cellTexture,
        &src,
        &rect
    );
}