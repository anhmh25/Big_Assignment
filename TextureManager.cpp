#include"TextureManager.h"

Texture::Texture() {
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture() {
	free();
}

void Texture::free()
{
	if (texture != NULL)
	{
		texture = NULL;
		width = 0;
		height = 0;
	}
}

bool Texture::loadTexture(const char* filename, SDL_Renderer* renderer) {

	free();
	SDL_Texture* tmpTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(filename);
	if (loadedSurface == nullptr)
	{
		cout << "Unable to load image" << endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		tmpTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (tmpTexture == NULL)
		{
			cout << "Unable to create texture from surface." << endl;
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	texture = tmpTexture;

	return texture != NULL;
}

bool Texture::loadRenderedText(const char* text, TTF_Font* font, SDL_Color textColor, SDL_Renderer* renderer = NULL)
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
	if (textSurface == NULL)
	{
		cout <<"Unable to render text surface!!!"<<endl;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			width = textSurface->w;
			height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return texture != NULL;
}

void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip)
{
	SDL_Rect scrdes = { x, y, width, height };

	if (clip != nullptr)
	{
		scrdes.w = clip->w;
		scrdes.h = clip->h;
	}

	SDL_RenderCopy(renderer, texture, clip, &scrdes);
}



int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}
