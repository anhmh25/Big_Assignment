#ifndef BACKGROUND__H_
#define BACKGROUND__H_
#include <iostream>
#include <SDL.h>
#include <stdio.h>

struct background {
    SDL_Texture* Texture;
    int mWidth;
    int mHeight;
    background();
    ~background();

    void run_frame(background* run_img, SDL_Renderer* gRenderer);
    void jump_frame(background* jump_img, SDL_Renderer* gRenderer);
    void slash_frame(background* slash_img, SDL_Renderer* gRenderer);

    bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

#if defined(SDL_TTF_MAJOR_VERSION)
    //Creates image from font string
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    //Set blending
    void setBlendMode(SDL_BlendMode blending);

    //Set alpha modulation
    void setAlpha(Uint8 alpha);

    //Renders texture at given point
    void render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL,
        double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Rect* des = NULL);

    //Gets image dimensions
    int getWidth();
    int getHeight();
   

};


#endif

