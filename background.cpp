#include"background.h"
#include<SDL.h>
#include<SDL_image.h>

background::background()
{
    Texture = NULL;
    mWidth = 0;
    mHeight = 0;
}

background::~background()
{
    free();
}

void background::free()
{
    //Free texture if it exists
    if (Texture != NULL)
    {
        SDL_DestroyTexture(Texture);
        Texture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

bool background::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
    free();

    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    Texture = newTexture;
    return Texture != NULL;
}

void background::render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Rect* des)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if (des != NULL)
    {
        renderQuad.w = des->w;
        renderQuad.h = des->h;
    }
    //Render to screen
    SDL_RenderCopyEx(gRenderer, Texture, clip, &renderQuad, angle, center, flip);
}


void background::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(Texture, red, green, blue);
}

void background::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(Texture, blending);
}

void background::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(Texture, alpha);
}

int background::getWidth()
{
    return mWidth;
}

int background::getHeight()
{
    return mHeight;
}