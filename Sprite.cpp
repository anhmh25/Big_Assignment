#include <iostream>
#include "Sprite.h"
#include <SDL.h>

sprite::sprite()
{
    //Initialize the offsets
    posX = 100;
    posY = 420;

    //Initialize the velocity
    velX = 0;
    velY = 0;

    frame_ = 0;
}

void sprite::handleEvent(SDL_Event& e, int &status)
{
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0){

        switch (e.key.keysym.sym)
        {
        case SDLK_UP: {
            status = 1;
            }
        case SDLK_BACKSPACE: {
            status = 2;
            }
        case SDLK_UP + SDLK_BACKSPACE: {
            status = 3;
            }
        }
    }
    
}

void background::run_frame(background* run_img,SDL_Renderer* gRenderer) {
    run_img[0].loadFromFile("Run__000.png", gRenderer);
    run_img[1].loadFromFile("Run__001.png", gRenderer);
    run_img[2].loadFromFile("Run__002.png", gRenderer);
    run_img[3].loadFromFile("Run__003.png", gRenderer);
    run_img[4].loadFromFile("Run__004.png", gRenderer);
    run_img[5].loadFromFile("Run__005.png", gRenderer);
    run_img[6].loadFromFile("Run__006.png", gRenderer);
    run_img[7].loadFromFile("Run__007.png", gRenderer);
    run_img[8].loadFromFile("Run__008.png", gRenderer);
    run_img[9].loadFromFile("Run__009.png", gRenderer);
}
void background::jump_frame(background* jump_img, SDL_Renderer* gRenderer) {
    jump_img[0].loadFromFile("Jump__000.png", gRenderer);
    jump_img[1].loadFromFile("Jump__001.png", gRenderer);
    jump_img[2].loadFromFile("Jump__002.png", gRenderer);
    jump_img[3].loadFromFile("Jump__003.png", gRenderer);
    jump_img[4].loadFromFile("Jump__004.png", gRenderer);
    jump_img[5].loadFromFile("Jump__005.png", gRenderer);
    jump_img[6].loadFromFile("Jump__006.png", gRenderer);
    jump_img[7].loadFromFile("Jump__007.png", gRenderer);
    jump_img[8].loadFromFile("Jump__008.png", gRenderer);
    jump_img[9].loadFromFile("Jump__009.png", gRenderer);
}
void sprite::render(SDL_Rect* size,background* img, SDL_Renderer* renderer,int i)
{
        img[i].render(posX, posY, renderer, NULL, 0, NULL, SDL_FLIP_NONE, size);
}