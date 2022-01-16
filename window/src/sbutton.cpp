﻿#include "sbutton.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_render.h>
#include <SDL_error.h>

USING_NAMESPACE_SDL

SRect::SRect() {
    _sdl_var = new SDL_Rect;
    _sdl_var->x = SRECT_DEFAULT_XPOS;
    _sdl_var->y = SRECT_DEFAULT_YPOS;
    _sdl_var->w = SRECT_DEFAULT_W;
    _sdl_var->h = SRECT_DEFAULT_H;
}

SRect::~SRect() {
}

SButton::SButton(SWindow *parent)
    : SObj(parent) {
}


void SButton::draw(SDL_Renderer *r) {
    SDL_SetRenderDrawColor(r, 255, 255, 0, 0);
    SDL_RenderDrawRect(r, _rect);

    auto *tx = SDL_GetRenderTarget(r);
    SDL_Color fc;
    SDL_Color bc;
    fc.a = 255;
    fc.r = fc.g = 0;
    fc.b = 0;
    bc.a = 0;
    fc.r = 255;
    bc.g = bc.b = 0;

    std::wstring str = L"打开";
    DLOG("btn text: 中文 %ls.\n", str.c_str());
    auto *font = TTF_OpenFont("E:/Downloads/GB5KM1B.TTF", 18);
    //auto *surface = TTF_RenderUNICODE(font, (const Uint16*)L"打开", fc, bc);//SDL_MapRGBA(SDL_ge))
    //auto *surface = TTF_RenderText_Solid(font, "xxxxxxx", bc);//SDL_MapRGBA(SDL_ge))
    auto *surface = TTF_RenderUNICODE_Blended_Wrapped(font, (const Uint16*)str.c_str(), bc, 300);
    if (!font || !surface) {
        DLOG("render text error: %s\n", SDL_GetError());
        return;
    }
    auto *textTx = SDL_CreateTextureFromSurface(r, surface);
    SDL_RenderCopy(r, textTx, _rect, _rect);
}
