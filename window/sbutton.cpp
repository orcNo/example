#include "sbutton.h"

#include <SDL.h>

SRect::SRect() {
    _rt = new SDL_Rect;
    _rt->x = SRECT_DEFAULT_XPOS;
    _rt->y = SRECT_DEFAULT_YPOS;
    _rt->w = SRECT_DEFAULT_W;
    _rt->h = SRECT_DEFAULT_H;
}

SRect::~SRect() {
    if (_rt)
        delete _rt;
    _rt = nullptr;
}

SButton::SButton(SWindow *parent)
    : _parent(parent) {
}


void SButton::draw(SDL_Renderer *r) {
    SDL_RenderDrawRect(r, _rect);
}
