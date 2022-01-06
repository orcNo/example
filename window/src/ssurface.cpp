#include "ssurface.h"

#include <SDL_image.h>

USING_NAMESPACE_SDL

SSurface::SSurface(std::string path) {
    SDL_RWops *rwop;
    rwop=SDL_RWFromFile(path.c_str(), "rb");
    if (isAveliable())
        destroy();

    _sdl_var = IMG_LoadJPG_RW(rwop);
    if(!_sdl_var) {
        char buf[1024];
        sprintf(buf, "load image error: %s\n", IMG_GetError());
        printf("%s", buf);
        // handle error
    }
}
