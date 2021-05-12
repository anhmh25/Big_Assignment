#pragma once
#include"game.h"

class gameObject {

public:
	gameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
	~gameObject();

	void update();
	void render();

private:
	int xpos, ypos;
	int count = 0;
	SDL_Texture* objectText;
	SDL_Rect scrRec, desRec;
	SDL_Renderer* renderer;
};