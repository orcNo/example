#include "swindow.h"
#include "sbutton.h"

SWindow::SWindow(SDL_Window *w)
    : _window(w) {
}

void SWindow::draw(SDL_Renderer* r) {
    for(auto ite : _children) {
        ite->draw(r);
    }
}

void SWindow::addChild(SObj *c) {
     { if(c && c->parent() != this) _children.push_back(c); };
}
