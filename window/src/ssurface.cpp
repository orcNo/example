#include "ssurface.h"

#include <SDL_image.h>

#include <vector>
#include <algorithm>

USING_NAMESPACE_SDL

typedef SDL_Surface* (*ImageLoadFunc)(SDL_RWops*);
ImageLoadFunc LoadFunc[] = { IMG_LoadICO_RW, IMG_LoadCUR_RW, IMG_LoadBMP_RW, IMG_LoadGIF_RW,
    IMG_LoadJPG_RW, IMG_LoadLBM_RW, IMG_LoadPCX_RW, IMG_LoadPNG_RW, IMG_LoadPNM_RW,
    IMG_LoadSVG_RW, IMG_LoadTGA_RW, IMG_LoadTIF_RW, IMG_LoadXCF_RW, IMG_LoadXPM_RW,
    IMG_LoadXV_RW, IMG_LoadWEBP_RW
};
const std::vector<const char*> ImageFileSurfix = {
    ".ico",
    ".cur",
    ".bmp",
    ".gif",
    ".jpg",
    ".lbm",
    ".pcx",
    ".png",
    ".pnm",
    ".svg",
    ".tga",
    ".tif",
    ".xcf",
    ".xpm",
    ".xv",
    ".webp"
};

SSurface::SSurface(std::string path) {
    SDL_RWops *rwop;
    rwop=SDL_RWFromFile(path.c_str(), "rb");
    if (isAveliable())
        destroy();

    _sdl_var = IMG_LoadJPG_RW(rwop);
    if(!_sdl_var) {
        DLOG("load image error: %s\n", IMG_GetError());
        // handle error
    }
}

ImageSurface::ImageFileFormat ImageSurface::getTypeFromPath(const std::string& str) {
    ImageFileFormat type = ImageFileFormat::IF_UNKONW;
    auto pos = str.find('.');
    if (pos == str.npos) {
        return type;
    }
    auto surfix = str.substr(pos, str.size() - pos);
    std::size_t idx = 0;
    while (idx < ImageFileSurfix.size()) {
        if (0 == strcmp(ImageFileSurfix[idx], surfix.c_str()))
            break;

        ++ idx;
    }
    if (idx != ImageFileSurfix.size())
        return ImageFileFormat(idx);
    return type;
}
