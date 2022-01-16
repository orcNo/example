#include <iostream>
#include <string>

#include "sapp.h"
#include "swindow.h"
#include "sbutton.h"


USING_NAMESPACE_SDL

SDL_Surface* LoadImage(std::string path) {
    SDL_Surface *image = nullptr;
    SDL_RWops *rwop;
    rwop=SDL_RWFromFile(path.c_str(), "rb");
    image=IMG_LoadJPG_RW(rwop);
    if(!image) {
        DLOG("load image error: %s\n", IMG_GetError());
        // handle error
    }

    return image;
}

int main(int argc, char** argv) {
    SApp app;
//    auto surface = LoadImage("C:\\Users\\longqi\\Desktop\\yuan.jpg");
    SWindow sw(app);
#ifdef _WIN32
    sw.setBackground("C:\\Users\\orcno\\Pictures\\Saved Pictures\\yueyetu.png");
#else
    sw.setBackground("/home/orcno/Pic/Wallpapers/xiaoyuan.jpg");
#endif
    sw.show();

    SButton btn(&sw);

    return app.exec(); 
    
    //SButton sb();

    //auto surface = LoadImage("~/Pic/Wallpapers/xiaoyuan.jpg");
    //if (!surface)
    //    return -1;

    //SDL_Window* w = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    //SDL_Renderer *r  = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);

    //int width, height;
    //SDL_GetWindowSize(w, &width, &height);
    //SDL_GetRendererOutputSize(r, &width, &height);
//  //  SDL_Texture* t = SDL_CreateTexture(r,  surface->format->format, SDL_TEXTUREACCESS_TARGET, width, hight);
    //bool run = true;
    //SDL_Texture* t = SDL_CreateTextureFromSurface(r, surface);
    //Uint32 f;
    //int a;
    //SDL_QueryTexture(t, &f, &a, &width, &height);
    //auto pixels = (void*)malloc(sizeof(char)*surface->pitch*surface->h);
    //SDL_ConvertPixels(width, height,
    //                      surface->format->format,
    //                      surface->pixels, surface->pitch,
    //                      f, pixels, surface->pitch);
    //while (run) {
    //    SDL_Event event;
    //    while (SDL_PollEvent(&event)) {  // poll until all events are handled!
    //        // decide what to do with this event.
    //        if (event.type == SDL_QUIT)
    //            run = false;
    //    }
//  //      surface->format->format

    //    SDL_RenderClear(r);
    //    SDL_Rect rt = {
    //        .x = 0,
    //        .y = 0,
    //        .w = width < surface->w ? width : surface->w,
    //        .h = height < surface->h ? height : surface->h
    //    };
    //    int tw, th;

    //    SDL_UpdateTexture(t, nullptr, pixels, surface->pitch);
    //    SDL_RenderCopy(r, t, nullptr, nullptr);
    //    sw.draw(r);
    //    SDL_RenderPresent(r);

    //    // update game state, draw the current frame
    //}

    //SDL_DestroyTexture(t);
    //SDL_DestroyRenderer(r);
    //SDL_DestroyWindow(w);
    
    //return 0;
}
