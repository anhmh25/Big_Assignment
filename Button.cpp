#include "Button.h"

Button::Button()
{
	position.x = 0;
	position.y = 0;

	Sprite = BUTTON_MOUSE_OUT;
}

Button::Button(int x, int y)
{
	position.x = x;
	position.y = y;

	Sprite = BUTTON_MOUSE_OUT;
}

void Button::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

bool Button::isInside(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;

		SDL_GetMouseState(&x, &y);

		bool inside = true;
		if (x < position.x)
		{
			inside = false;
		}
		else if (x > position.x + BUTTON_WIDTH)
		{
			inside = false; 
		}
		else if (y < position.y)
		{
			inside = false;
		}
		else if (y > position.y + BUTTON_HEIGHT)
		{
			inside = false;
		}
		return inside;
	}
	return false;
}

void Button::render(SDL_Rect* des, SDL_Renderer* renderer, Texture ButtonTexture)
{
	ButtonTexture.render(position.x, position.y, renderer, des);
}