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

NAMESPACE_SDL_END

#endif //__SSURFACE__H

