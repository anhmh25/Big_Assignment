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
background slash_img[10];

int main(int ardc, char* argv[]) {
    
    initSDL(gWindow, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    if (loadMedia(Texture, gRenderer)) {
        bool quit = false;
        SDL_Event e;
        sprite Sprite;
        int scrollingOffset = 0,  high = 0;
        int status = 0;
        gspriteTexture.jump_frame(jump_img, gRenderer);
        gspriteTexture.run_frame(run_img, gRenderer);
        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                Sprite.handleEvent(e,status);
            }

           
            if (status == 0) {
                for (int i = 0; i < 10; i++) {
                    SDL_Rect sizer = { 0,0,90,105 };
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);
                    for (int j = 0; j < 10; j++) {
                        scrollingOffset--;
                        if (scrollingOffset < -Texture.getWidth())
                        {
                            scrollingOffset = 0;
                        }
                        Texture.render(scrollingOffset, 0, gRenderer);
                        Texture.render(scrollingOffset + Texture.getWidth(), 0, gRenderer);
                    }

                    Sprite.render(&sizer, run_img, gRenderer, i);
                    SDL_Delay(20);
                    SDL_RenderPresent(gRenderer);
                }
            }

            if (status == 1) {
                    SDL_Rect sizer = { 0,high,90,105 };
                    for (int i = 0; i < 10; i++) {
                        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                        SDL_RenderClear(gRenderer);
                        for (int j = 0; j < 10; j++) {
                            scrollingOffset--;
                            if (scrollingOffset < -Texture.getWidth())
                            {
                                scrollingOffset = 0;
                            }
                            Texture.render(scrollingOffset, 0, gRenderer);
                            Texture.render(scrollingOffset + Texture.getWidth(), 0, gRenderer);
                        }

                        Sprite.render(&sizer, jump_img, gRenderer, i);
                        SDL_Delay(20);
                        SDL_RenderPresent(gRenderer);
                        high += 10;
                    }
            }
            status = 0;
        }
        quitSDL(gWindow, gRenderer);
        return 0;
    }
}
