#include "UI.h"

bool UI::isHover(float mouseX, float mouseY, const SDL_FRect& rect)
{
	return mouseX >= rect.x &&
		mouseX < rect.x + rect.w &&
		mouseY >= rect.y &&
		mouseY < rect.y + rect.h;
}

void UI::DrawPanelOld(SDL_Renderer* renderer, float x, float y, float w, float h) {
	SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);
	SDL_FRect panelRect{ x, y, w, h };
	SDL_RenderFillRect(renderer, &panelRect);

	// Верхняя и левая граница
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

	SDL_RenderLine(renderer, x, y, x + w, y);
	SDL_RenderLine(renderer, x, y, x, y + h);

	// Нижняя и правая граница
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderLine(renderer, x, y + h, x + w, y + h);
	SDL_RenderLine(renderer, x + w, y, x + w, y + h);
}

void UI::DrawPanelOldWithTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_FRect panelRect, SDL_FRect scrTextureRect) {
	SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);

	SDL_RenderFillRect(renderer, &panelRect);
	SDL_RenderTexture(renderer, texture, &scrTextureRect, &panelRect);
	// Верхняя и левая граница
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

	SDL_RenderLine(renderer, panelRect.x, panelRect.y, panelRect.x + panelRect.w, panelRect.y);
	SDL_RenderLine(renderer, panelRect.x, panelRect.y, panelRect.x, panelRect.y + panelRect.h);

	// Нижняя и правая граница
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderLine(renderer, panelRect.x, panelRect.y + panelRect.h, panelRect.x + panelRect.w, panelRect.y + panelRect.h);
	SDL_RenderLine(renderer, panelRect.x + panelRect.w, panelRect.y, panelRect.x + panelRect.w, panelRect.y + panelRect.h);
}

void UI::DrawText(int id, SDL_Renderer* renderer, TTF_Font* font, std::string text, float x, float y, SDL_Color color) {
	SDL_Surface* createText [3];
	SDL_Texture* textTexture[3];
	SDL_FRect textRect;

	std::string currentText[3];

	if (currentText[id] != text) {

		SDL_DestroyTexture(textTexture[id]);
		currentText[id] = text;

		createText[id] =
			TTF_RenderText_Solid(font, text.c_str(), 0, color);
		textTexture[id] = SDL_CreateTextureFromSurface(renderer, createText[id]);

		textRect = {
		x,
		y + createText[id]->h / 2.f,
		(float)createText[id]->w,
		(float)createText[id]->h
		};

		SDL_DestroySurface(createText[id]);
	}

	SDL_RenderTexture(renderer, textTexture[id], NULL, &textRect);
	SDL_DestroyTexture(textTexture[id]);
}

bool UI::Button(int id, std::string text, TTF_Font* font, SDL_Color TextColor,
	SDL_Renderer* renderer,
	float x, float y, float w, float h,
	SDL_Color BaseColor, SDL_Color SelectColor, SDL_Color PressColor) {

	SDL_SetRenderDrawColor(renderer, BaseColor.r, BaseColor.g, BaseColor.b, BaseColor.a);
	SDL_FRect buttonRect{ x, y, w, h };

	static SDL_Texture* textures[3]{};
	static std::string oldText[3];
	static bool wasPressed[3]{};
	if (id < 0 || id >= 3) return false;
	if (textures[id] == nullptr || oldText[id] != text)
	{
		SDL_DestroyTexture(textures[id]);

		SDL_Surface* surface =
			TTF_RenderText_Solid(font, text.c_str(), 0, TextColor);

		textures[id] = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_DestroySurface(surface);

		oldText[id] = text;
	}
	SDL_FRect textRect{
		x + (w - textures[id]->w) / 2.0f,
		y + (h - textures[id]->h) / 2.0f,
		(float)textures[id]->w,
		(float)textures[id]->h
	};

	float mouseX, mouseY;
	SDL_MouseButtonFlags buttons =
		SDL_GetMouseState(&mouseX, &mouseY);

	bool pressed = buttons & SDL_BUTTON_LMASK;
	bool clicked = false;

	if (isHover(mouseX, mouseY, buttonRect)) {
		SDL_SetRenderDrawColor(renderer, SelectColor.r, SelectColor.g, SelectColor.b, SelectColor.a);
		if (pressed) {
			SDL_SetRenderDrawColor(renderer, PressColor.r, PressColor.g, PressColor.b, PressColor.a);
			if (!wasPressed[id])
			{
				clicked = true;
			}
		}
	}
	SDL_RenderFillRect(renderer, &buttonRect);
	SDL_RenderTexture(renderer, textures[id], NULL, &textRect);

	// Верхняя и левая граница
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderLine(renderer, x, y, x + w, y);
	SDL_RenderLine(renderer, x, y, x, y + h);

	// Нижняя и правая граница
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

	SDL_RenderLine(renderer, x, y + h, x + w, y + h);
	SDL_RenderLine(renderer, x + w, y, x + w, y + h);

	wasPressed[id] = pressed;
	return clicked;
}