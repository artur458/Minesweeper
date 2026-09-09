#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
class UI
{
public:
	SDL_Event event;
	void DrawPanelOld(SDL_Renderer* renderer, float x, float y, float w, float h);
	void DrawPanelOldWithTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_FRect panelRect, SDL_FRect scrTextureRect);

	void DrawText(int id, SDL_Renderer* renderer, TTF_Font* font, std::string text, float x, float y, SDL_Color color);

	bool Button(int id, std::string text, TTF_Font* font, SDL_Color TextColor,
		SDL_Renderer* renderer,
		float x, float y, float w, float h,
		SDL_Color BaseColor, SDL_Color SelectColor, SDL_Color PressColor);

	bool isHover(float mouseX, float mouseY, const SDL_FRect& rect);
private:
};

