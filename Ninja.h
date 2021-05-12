#ifndef NINJA__H_
#define NINJA__H_

#include"TextureManager.h"

const int JUMP = 1;
const int FALL = 0;

class Ninja {

public:
	int VELOCITY =12;

	Ninja();

	int getPosX();
	int getPosY();
	void render(SDL_Rect* des, SDL_Renderer* renderer, Texture NinjaTexture);
	bool Running();
	void HandleEvent(SDL_Event& e, Mix_Chunk* jump);
	void Move();
	

private:

	int posX, posY;
	int status ;

};


#endif
