#ifndef __SBUTTON_H
#define __SBUTTON_H

#include "swindow.h"
#include "virtualbutton.h"

struct SDL_Renderer;
class SDL_Rect;

NAMESPACE_SDL_BEGIN

class SButton : public SObj {
public:
    explicit SButton(SWindow *parent);
    ~SButton() = default;

    void draw(SDL_Renderer* ) override;

private:
    SRect _rect;
//    friend void SWindow::addChild(SObj *c);
};

NAMESPACE_SDL_END

#endif // __SBUTTON_H
