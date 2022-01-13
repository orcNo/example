#include "sbutton.h"

#include <SDL.h>

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
}
