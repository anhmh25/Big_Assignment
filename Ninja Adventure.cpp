#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include "public.h"
#include "background.h"
#include "Sprite.h"
using namespace std;

const int SCREEN_WIDTH = 1150;
const int SCREEN_HEIGHT = 600;
const char WINDOW_TITLE[] = "Ninja Adventure";

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

background Texture;
background gspriteTexture;
background run_img[10];
background jump_img[10];
background rock;

int main(int ardc, char* argv[]) {
    
    initSDL(gWindow, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    if (loadMedia(Texture, gRenderer)) {
        bool quit = false;
        SDL_Event e;
        sprite Sprite;
        int scrollingOffset = 0;
        int status = 0;
        gspriteTexture.run_frame(run_img, gRenderer);
        gspriteTexture.jump_frame(jump_img, gRenderer);
        gspriteTexture.rock_frame(rock, gRenderer);
        while (!quit)
        {
            SDL_Rect sizer = { 0,0,90,105 };
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                Sprite.handleEvent(e,&status);
            }
            if (status == 0) {
                for (int i = 0; i < 10; i++) {

                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);
                    for (int j = 0; j < 15; j++) {
                        scrollingOffset--;
                        if (scrollingOffset < -Texture.getWidth())
                        {
                            scrollingOffset = 0;
                        }
                        Texture.render(scrollingOffset, 0, gRenderer);
                        Texture.render(scrollingOffset + rock.getWidth(), 0, gRenderer);
                        Texture.render(scrollingOffset, 0, gRenderer);
                        Texture.render(scrollingOffset + Texture.getWidth(), 0, gRenderer);
                        
                    }

                    Sprite.render(&sizer, run_img, gRenderer, i);
                    SDL_Delay(25);
                    SDL_RenderPresent(gRenderer);

                }
            }
            if (status == 1) {
                for (int j = 0; j < 8; j++) {

                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);
                    for (int i = 0; i < 15; i++) {
                        scrollingOffset--;
                        if (scrollingOffset < -Texture.getWidth())
                        {
                            scrollingOffset = 0;
                        }
                        Texture.render(scrollingOffset, 0, gRenderer);
                        Texture.render(scrollingOffset + Texture.getWidth(), 0, gRenderer);
                    }

                    Sprite.render(&sizer, jump_img, gRenderer, j/2);
                    SDL_Delay(25);
                    SDL_RenderPresent(gRenderer);
                    Sprite.posY -= Sprite.Sprite_VEL;
                }
                for (int j = 16; j < 24; j++) {

                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);
                    for (int i = 0; i < 15; i++) {
                        scrollingOffset--;
                        if (scrollingOffset < -Texture.getWidth())
                        {
                            scrollingOffset = 0;
                        }
                        Texture.render(scrollingOffset, 0, gRenderer);
                        Texture.render(scrollingOffset + Texture.getWidth(), 0, gRenderer);
                        
                    }

                    Sprite.render(&sizer, jump_img, gRenderer, j/4);
                    SDL_Delay(25);
                    SDL_RenderPresent(gRenderer);
                    
                }

                for (int j = 12; j < 20 ; j++) {

                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);
                    for (int i = 0; i < 15; i++) {
                        scrollingOffset--;
                        if (scrollingOffset < -Texture.getWidth())
                        {
                            scrollingOffset = 0;
                        }
                        Texture.render(scrollingOffset, 0, gRenderer);
                        Texture.render(scrollingOffset + Texture.getWidth(), 0, gRenderer);
                    }

                    Sprite.render(&sizer, jump_img, gRenderer, j/2);
                    SDL_Delay(25);
                    SDL_RenderPresent(gRenderer);
                    Sprite.posY += Sprite.Sprite_VEL;
                }
        }
        
            status = 0;
        }
        quitSDL(gWindow, gRenderer);
        return 0;
    }
}
