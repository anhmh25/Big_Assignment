#include "Obstacles.h"

Obstacles::Obstacles(int _type)
{
	posX = 0;
	posY = 0;

	width = 0;
	height = 0;

	type = _type;
	if (type == FLY_OBSTACLES)
	{
		posX = rand() % (SCREEN_WIDTH + OBSTACLES_RANGE) + SCREEN_WIDTH;
		posY = rand() % (GHOST_MAX_HEIGHT - GHOST_MIN_HEIGHT) + GHOST_MIN_HEIGHT;
	}
	else if (type == GROUND_OBSTACLES_1)
	{
		posX = rand() % (SCREEN_WIDTH + OBSTACLES_RANGE) + SCREEN_WIDTH;
		posY = 770;
	}
	else if (type == GROUND_OBSTACLES_2)
	{
		posX = rand() % (SCREEN_WIDTH + OBSTACLES_RANGE) + SCREEN_WIDTH;
		posY = 770;
	}

	ObstaclesTexture = NULL;
}

Obstacles::~Obstacles()
{
	posX = 0;
	posY = 0;

	width = 0;
	height = 0;

	type = 0;
	if (ObstaclesTexture != NULL)
	{
		ObstaclesTexture = NULL;
	}
}

void Obstacles::loadFromFile(const char* filename, SDL_Renderer* renderer)
{
	SDL_Texture* tmpTexture = nullptr;

	SDL_Surface* tmpSurface = IMG_Load(filename);
	if (tmpSurface == NULL)
	{
		cout << "Can not load image." << endl;
	}
	else
	{
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

		tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		if (tmpTexture == NULL)
		{
			cout << "Can not create texture from surface." << endl;
		}
		else
		{
			width = 140;
			height = 207;
		}

		SDL_FreeSurface(tmpSurface);
	}

	ObstaclesTexture = tmpTexture;
}

void Obstacles::move(const int& acceleration)
{
	posX += -(OBSTACLES_SPEED + acceleration);
	if (posX + MAX_OBSTACLES_WIDTH < 0)
	{
		posX = rand() % (SCREEN_WIDTH + OBSTACLES_RANGE) + SCREEN_WIDTH;

		if (type == FLY_OBSTACLES)
		{
			posY = rand() % (GHOST_MAX_HEIGHT - GHOST_MIN_HEIGHT ) + GHOST_MIN_HEIGHT;
		}
	}
}

void Obstacles::render(SDL_Renderer* renderer, SDL_Rect* obstacles)
{
	SDL_Rect renderSpace = { posX, posY, width, height };
	if (obstacles != nullptr)
	{
		renderSpace.w = obstacles->w;
		renderSpace.h = obstacles->h;
	}
	SDL_RenderCopy(renderer, ObstaclesTexture, obstacles, &renderSpace);
}

int Obstacles::getType()
{
	if (type == FLY_OBSTACLES)
	{
		return FLY_OBSTACLES;
	}
	else if (type == GROUND_OBSTACLES_1)
	{
		return GROUND_OBSTACLES_1;
	}
	else if (type == GROUND_OBSTACLES_2)
	{
		return GROUND_OBSTACLES_2;
	}
}

int Obstacles::getSpeed(const int& acceleration)
{
	return OBSTACLES_SPEED + acceleration;
}

int Obstacles::getPosX()
{
	return posX;
}

int Obstacles::getPosY()
{
	return posY;
}

int Obstacles::getWidth()
{
	return width;
}

int Obstacles::getHeight()
{
	return height;
}