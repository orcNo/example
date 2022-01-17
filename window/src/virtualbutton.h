#ifndef __VIRTUALBUTTON_H
#define __VIRTUALBUTTON_H

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

class VirtualButton : public SObj {
public:
    explicit VirtualButton(SWindow *parent);
    ~VirtualButton() = default;

    virtual void onClieck() {}

    void draw(SDL_Renderer *) override;

protected:
    virtual bool proEvent(const SDL_Event&e) override;

private:
    bool _force;
    SRect _rect;
//    friend void SWindow::addChild(SObj *c);
};

NAMESPACE_SDL_END

#endif // __VIRTUALBUTTON_H
