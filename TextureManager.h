#ifndef TEXTUREMANAGER__H_
#define TEXTUREMANAGER__H_
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<iostream>
using namespace std;

class Texture {

public:
	Texture();
	~Texture();

	void free();
	bool loadTexture(const char* filename, SDL_Renderer* renderer);
	bool loadRenderedText(const char* text, TTF_Font* font, SDL_Color textColor, SDL_Renderer* renderer);
	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* des = NULL);
	int getWidth();
	int getHeight();
private:
	SDL_Texture* texture;
	int width,height;

};
#endif