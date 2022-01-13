#ifndef __SSURFACE__H
#define __SSURFACE__H

#include "SDL_surface.h"
#include "sobj.h"
#include "utils.h"

#include <string>

NAMESPACE_SDL_BEGIN

class SSurface : public SdlStruct<SDL_Surface> {
public:
    SSurface() = default;
    SSurface(std::string path);
    ~SSurface() { destroy(); }

    void destroy() override { if (_sdl_var) SDL_FreeSurface(_sdl_var); _sdl_var = nullptr; }
};

class ImageSurface : public SSurface {
public:
    enum ImageFileFormat {
        IF_ICO = 0,
        IF_CUR,
        IF_BMP,
        IF_GIF,
        IF_JPG,
        IF_LBM,
        IF_PCX,
        IF_PNG,
        IF_PNM,
        IF_SVG,
        IF_TGA,
        IF_TIF,
        IF_XCF,
        IF_XPM,
        IF_XV,
        IF_WEBP,
        IF_UNKONW
    };
public:
    explicit ImageSurface(std::string path);

    static ImageFileFormat getTypeFromPath(const std::string& str);
private:
    ImageFileFormat _imageFormat;
};

NAMESPACE_SDL_END

#endif //__SSURFACE__H

