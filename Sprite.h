#ifndef SPRITE__H_
#define SPRITE__H_
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "background.h"

struct sprite {

    int posX, posY;
    int velX, velY;
    int frame_;

    const int Sprite_WIDTH = 5;
    const int Sprite_HEIGHT = 5;

    static const int Sprite_VEL = 5;
    

    //Initializes the variables
    sprite();

    //Takes key presses and adjusts the Sprite's velocity
    void handleEvent(SDL_Event& e,int &status);

    //Shows the Sprite on the screen
    void render(SDL_Rect* size, background* img, SDL_Renderer* renderer,int i);
};

#endif