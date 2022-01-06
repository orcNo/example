#ifndef __SBUTTON_H
#define __SBUTTON_H

#include "swindow.h"
#include "sobj.h"

struct SDL_Renderer;
class SDL_Rect;

NAMESPACE_SDL_BEGIN

class SRect : public SdlStruct<SDL_Rect> {
public:
    const int SRECT_DEFAULT_XPOS = 0;
    const int SRECT_DEFAULT_YPOS = 0;
    const int SRECT_DEFAULT_W = 100;
    const int SRECT_DEFAULT_H = 40;
public:
    SRect();
    ~SRect();
    //SDL_CPP_OBJECT(SDL_Rect, _rt)
};

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
