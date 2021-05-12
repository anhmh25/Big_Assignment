#ifndef OBSTACLES__H_
#define OBSTACLES__H_

#include "TextureManager.h"
using namespace std;

#define GHOST_MAX_HEIGHT 700
#define GHOST_MIN_HEIGHT 500

#define OBSTACLES_RANGE 400
#define MAX_OBSTACLES_WIDTH 300
#define OBSTACLES_SPEED 6
#define FLY_OBSTACLES 0
#define GROUND_OBSTACLES_1 1
#define GROUND_OBSTACLES_2 2
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

class Obstacles
{
public:
	Obstacles(int type = 0);

	~Obstacles();

	void loadFromFile(const char* filename, SDL_Renderer* renderer);

	void move(const int &acceleration);

	void render(SDL_Renderer* renderer, SDL_Rect* obstacles = nullptr);

	int getType();

	int getSpeed(const int& acceleration);

	int getPosX();

	int getPosY();

	int getWidth();

	int getHeight();

	int posX, posY;

private:
	

	int width, height;

	int type;

	SDL_Texture* ObstaclesTexture;
};

#endif
