#include"Ninja.h"

Ninja::Ninja()
{
	posX = 100;
	posY = 730;

	status = 0;
}

bool Ninja::Running()
{
	if (posY == 730)return true;
	return false;
}

void Ninja::HandleEvent(SDL_Event& e, Mix_Chunk* jump)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
		{
			if (Running())
			{
				Mix_PlayChannel(-1, jump, 0);
				status = JUMP;
			}
		}
		}
	}
}

void Ninja::Move()
{
	if (status == JUMP && posY >= 200){
		posY -= VELOCITY;
	}
	if (posY <= 200)
	{
		status = FALL;
	}
	if (status != JUMP && posY < 730){
		posY += VELOCITY;
	}
}

void Ninja::render(SDL_Rect* des, SDL_Renderer* renderer, Texture NinjaTexture)
{
	NinjaTexture.render(posX, posY, renderer, des);
}

int Ninja::getPosX()
{
	return posX;
}

int Ninja::getPosY()
{
	return posY;
}