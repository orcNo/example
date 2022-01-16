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

#include <cstdio>
#include <algorithm>

USING_NAMESPACE_SDL

int eventWatch(void *data, SDL_Event* ev) {
    if (ev->type != SDL_WINDOWEVENT)
        return 0;
    auto w = (SWindow*)data;
    auto e = ev->window;
    w->windowPro(e);
    return 0;
}

SWindow::SWindow(SApp& app)
    : SObj()
    , _quilt(false)
    , _render(nullptr)
    , _texture(nullptr)
    , _frame(60) {
    app.setWindow(this);

    init();
}

SWindow::~SWindow() {
    destroy();
}

void SWindow::init() {
    auto wAttr = SDL_WINDOW_RESIZABLE;
    _w = 800;
    _h = 400;

    _sdl_var = SDL_CreateWindow("Render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _w, _h, wAttr);
    if (!get())
        DLOG("get window error: %s!\n", SDL_GetError());
    _render = SDL_CreateRenderer(get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
    _surface = SDL_GetWindowSurface(get());
    if (!_surface) {
        DLOG("get window surface error: %s!\n", SDL_GetError());
    } else {
        _w = _surface->w;
        _h = _surface->h;
        _texture = SDL_CreateTexture(_render, _surface->format->format
                , SDL_TEXTUREACCESS_STREAMING, _surface->w, _surface->h);
    }

    updateWindow();
}

void SWindow::show() {
    SDL_ShowWindow(get());
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
        if (delay > 0) {
//            SDL_Delay(delay);
            //DLOG("delay %dms.\n", delay);
        }
    }
}

void SWindow::destroy() {
    if (_bkSurface)
        SDL_FreeSurface(_bkSurface);
    _bkSurface = nullptr;
    //if (_surface) //SDL_GetWindowSurface: Do not free this surface.
    //    SDL_FreeSurface(_surface);
    //_surface = nullptr;
    if (_texture)
        SDL_DestroyTexture(_texture);
    _texture = nullptr;
    if (_render)
        SDL_DestroyRenderer(_render);
    _render = nullptr;
    if (get())
        SDL_DestroyWindow(get());
    _sdl_var = nullptr;
}

void SWindow::setBackground(std::string path) {
    //SSurface s(path);
    //_bkSurface = IMG_LoadJPG_RW(rwop);
    //auto *tmpSurface = IMG_LoadJPG_RW(rwop);
    _bkTexture = IMG_LoadTexture(_render, path.c_str());
    return;

    SDL_RWops *rwop;
    rwop=SDL_RWFromFile(path.c_str(), "rb");
    auto *tmpSurface = IMG_LoadPNG_RW(rwop);
    if(!tmpSurface) {
        DLOG("load image error: %s\n", IMG_GetError());
        // handle error
    }
    _bkSurface = SDL_ConvertSurface(tmpSurface, _surface->format, 0);
    if (!_bkSurface) {
        DLOG("convert surface error: %s\n", IMG_GetError());
    } else {
        DLOG("set bk surface, with w=%d, height=%d\n", _bkSurface->w, _bkSurface->h);
    }
    SDL_FreeSurface(tmpSurface);
}

void SWindow::updateWindow() {
    int w, h;
    SDL_GetWindowSize(*this, &w, &h);
    if (w != _w || h != _h) {
        _w = w;
        _h = h;
        updateSurfaceAndTexture();
    }
    
    SDL_RenderClear(_render);
    draw(_render);
    //SDL_RenderCopy(_render, _texture, nullptr, nullptr);
    SDL_RenderPresent(_render);
}

void SWindow::draw(SDL_Renderer *r) {
#ifdef WIN32
    SDL_Rect rt;
    rt.x = 0;
    rt.y = 0;
    rt.w = _w;
    rt.h = _h;
#else
    SDL_Rect rt = {
        .x = 0,
        .y = 0,
        .w = _w,
        .h = _h
    };
#endif
    SDL_SetRenderDrawColor(r, 255, 0, 0, 0);
    SDL_RenderFillRect(r, &rt);

    drawBackground();
    //SDL_Log("on function draw, surface's w: %d, surface's h: %d", rt.w, rt.h);

    //SDL_FillRect(s, &rt, SDL_MapRGBA(s->format, 255, 255, 255, 0));
    DrawChildren(r);
}

void SWindow::drawBackground() {
#ifdef WIN32
    SDL_Rect rt;
    rt.x = 0;
    rt.y = 0;
    rt.w = _w;
    rt.h = _h;
#else
    SDL_Rect rt = {
        .x = 0,
        .y = 0,
        .w = w,
        .h = h
    };
#endif
    if (_bkTexture) {
        uint32_t f;
        int a, w, h;
        SDL_QueryTexture(_bkTexture, &f, &a, &w, &h);
        rt.w = std::min(rt.w, w);
        rt.h = std::min(rt.h, h);
        SDL_RenderCopy(_render, _bkTexture, &rt, &rt);
        return;
    }

    if (!_bkSurface)
        return;
    auto w = _surface->w < _bkSurface->w ? _surface->w : _bkSurface->w;
    auto h = _surface->h < _bkSurface->h ? _surface->h : _bkSurface->h;
    //DLOG("blit surface with rect, w = %d, h = %d\n", w, h);
    //auto ret = SDL_BlitSurface(_bkSurface, &rt, _surface, &rt);
    ////auto ret = SDL_BlitSurface(_bkSurface, nullptr, _surface, nullptr);
    //if (ret != 0) {
    //    ELOG("blit surface error: %s\n", SDL_GetError());
    //}
    //SDL_UpdateWindowSurface(*this);
    auto *tx = SDL_CreateTexture(_render, _bkSurface->format->format, 0, _w, _h);
    if (0 != SDL_UpdateTexture(tx, nullptr, _bkSurface->pixels, _surface->pitch)) {
        DLOG("update error!");
    }
    SDL_RenderCopy(_render, tx, nullptr, nullptr);
}

bool SWindow::inputPro(SDL_Event &e) {
    return false;
}

void SWindow::updateSurfaceAndTexture() {
    _surface = SDL_GetWindowSurface(*this);
    DLOG("new surface: %lx \n", (intptr_t)_surface);
    if (_texture)
        SDL_DestroyTexture(_texture);
    _texture = SDL_CreateTextureFromSurface(_render, _surface);
}

void SWindow::DrawChildren(SDL_Renderer *r) {
    auto vchild = children();
    auto ite = vchild.begin();
    while (ite != vchild.end()) {
        (*ite)->draw(r);
        ++ite;
    }
}

bool SWindow::windowPro(SDL_WindowEvent &e) {
    switch (e.type) {
        case SDL_WINDOWEVENT_RESIZED:
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            _w = e.data1;
            _h = e.data2;
            updateSurfaceAndTexture();

            break;
        default:
            break;
    }
    return false;
}
