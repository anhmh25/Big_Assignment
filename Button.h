#ifndef BUTTON__H_
#define BUTTON__H_

#include"TextureManager.h"

const int BUTTON_WIDTH = 304;
const int BUTTON_HEIGHT = 113;

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};

class Button {

public:
	ButtonSprite Sprite;
	Button();
	Button(int x, int y);
	void setPosition(int x, int y);
	bool isInside(SDL_Event* e);
	void render(SDL_Rect* des, SDL_Renderer* renderer, Texture ButtonTexture);

private:
	SDL_Point position;

};
#endif
