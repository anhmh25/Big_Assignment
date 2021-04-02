#ifndef NORMAL__H_
#define NORMAL__H_
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include "background.h"

bool loadMedia( background &gBGTexture, SDL_Renderer* gRenderer);

void logSDLError(std::ostream& os,const std::string& msg, bool fatal);

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer, int screenWidth, int screenHeight, const char* windowTitle);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer );

void waitUntilKeyPressed();

#endif
