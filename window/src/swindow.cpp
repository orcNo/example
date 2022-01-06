#include "swindow.h"

#include "SDL_error.h"
#include "SDL_pixels.h"
#include "sobj.h"
#include "sapp.h"
#include "ssurface.h"

#include <SDL_cpuinfo.h>
#include <SDL_rect.h>
#include <SDL_surface.h>
#include <SDL_timer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

USING_NAMESPACE_SDL

SWindow::SWindow(SApp& app)
    : SObj()
    , _quilt(false)
    , _render(nullptr)
    , _texture(nullptr)
    , _frame(60) {
    app.setWindow(this);
}

SWindow::~SWindow() {
    destroy();
}

void SWindow::init() {
    _w = 800;
    _h = 400;
    auto wAttr = SDL_WINDOW_RESIZABLE;

    _sdl_var = SDL_CreateWindow("Render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _w, _h, wAttr);
    _render = SDL_CreateRenderer(_sdl_var, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
    //_surface.setVar(SDL_GetWindowSurface(_sdl_var));
    _surface = SDL_GetWindowSurface(_sdl_var);


    updateWindow();
}

void SWindow::show() {
    SDL_ShowWindow(_sdl_var);
}

void SWindow::handleEvent() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        Uint64 preTick = SDL_GetTicks64();
        if (e.type == SDL_QUIT)
            _quilt = true;
        
        switch (e.type) {
            case SDL_WINDOWEVENT: {
                windowPro(e.window);
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                break;
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEWHEEL:
            case SDL_MOUSEMOTION:
                break;
            default:
                break;
            }
        }
        updateWindow();
        auto t = SDL_GetTicks64();
        auto delay = 1000 / _frame - ( t - preTick);
        if (delay > 0)
            SDL_Delay(delay);
    }
}

void SWindow::destroy() {
    if (_bkSurface)
        SDL_FreeSurface(_bkSurface);
    _bkSurface = nullptr;
    if (_surface)
        SDL_FreeSurface(_surface);
    _surface = nullptr;
    if (_texture)
        SDL_DestroyTexture(_texture);
    _texture = nullptr;
    if (_render)
        SDL_DestroyRenderer(_render);
    _render = nullptr;
    if (_sdl_var)
        SDL_DestroyWindow(_sdl_var);
    _sdl_var = nullptr;
}

void SWindow::setBackground(std::string path) {
    //SSurface s(path);
    SDL_RWops *rwop;
    rwop=SDL_RWFromFile(path.c_str(), "rb");

    _bkSurface = IMG_LoadJPG_RW(rwop);
    if(!_bkSurface) {
        char buf[1024];
        sprintf(buf, "load image error: %s\n", IMG_GetError());
        printf("%s", buf);
        // handle error
    }
}

void SWindow::updateWindow() {
    if (!_texture)
        _texture = SDL_CreateTexture(_render, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, _w, _h);
    
    SDL_FillRect(_surface, nullptr, SDL_MapRGBA(_surface->format, 255, 255, 255, 0));
    if (_bkSurface) {
        auto w = _surface->w < _bkSurface->w ? _surface->w : _bkSurface->w;
        auto h = _surface->h < _bkSurface->h ? _surface->h : _bkSurface->h;
        SDL_Rect rt = {
            .x = 0,
            .y = 0,
            .w = w,
            .h = h
        };
        auto ret = SDL_BlitSurface(_bkSurface, nullptr, _surface, nullptr);
        //auto ret = SDL_BlitSurface(_bkSurface, &rt, _surface, &rt);
        if (ret != 0) {
            printf("blit surface error: %s", SDL_GetError());
        }
    }
    SDL_Rect rt = {
        .x = 0,
        .y = 0,
        .w = _w,
        .h = _h
    };
    if (_bkSurface) {
        SDL_UpdateTexture(_texture, nullptr, _bkSurface->pixels, _bkSurface->pitch);
    }
    //SDL_UpdateTexture(_texture, nullptr, _surface->pixels, _surface->pitch);

    SDL_RenderClear(_render);
    SDL_RenderCopy(_render, _texture, nullptr, nullptr);
    SDL_RenderPresent(_render);
}

void SWindow::draw(SDL_Renderer *r, SDL_Surface *s) {
    SDL_Rect rt = {
        .x = 0,
        .y = 0,
        .w = s->w,
        .h = s->h
    };
    //SDL_SetRenderDrawColor(r, 255, 0, 0, 0);
    SDL_Color c = {
        .r = 255,
        .g = 0,
        .b = 0,
        .a = 0
    };
    //SDL_Log("on function draw, surface's w: %d, surface's h: %d", rt.w, rt.h);

    SDL_RenderFillRect(r, &rt);
    SDL_FillRect(s, &rt, SDL_MapRGBA(s->format, 255, 255, 255, 0));
}

bool SWindow::inputPro(SDL_Event &e) {
    return false;
}

bool SWindow::windowPro(SDL_WindowEvent &e) {
    switch (e.type) {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            _w = e.data1;
            _h = e.data2;
            _surface = SDL_GetWindowSurface(_sdl_var);
            break;
        default:
            break;
    }
    return false;
}
