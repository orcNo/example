#include "window.h"

#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>
#include <iostream>

#include <string>

SDL_Surface* LoadImage(std::string path) {
    SDL_Surface *image;
    image=IMG_Load("sample.png");
    if(!image) {
        printf("IMG_Load: %s\n", IMG_GetError());
        // handle error
    }

    return image;
}

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* w = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    bool run = true;

    while (run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {  // poll until all events are handled!
            // decide what to do with this event.
            if (event.type == SDL_QUIT)
                run = false;
        }

        // update game state, draw the current frame
    }

    SDL_DestroyWindow(w);
    return 0;
}
