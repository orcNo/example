#ifndef __SBUTTON_H
#define __SBUTTON_H

//class SWindow;
#include "swindow.h"

struct SDL_Renderer;
class SDL_Rect;

#ifndef SDL_CPP_OBJECT
#define SDL_CPP_OBJECT(type, var) \
public: \
    inline operator type*() { return var; } \
    inline operator const type*() const { return var; } \
    inline bool isAveliable() const { return var; } \
private: \
    type *var;
#endif

const int SRECT_DEFAULT_XPOS = 0;
const int SRECT_DEFAULT_YPOS = 0;
const int SRECT_DEFAULT_W = 100;
const int SRECT_DEFAULT_H = 40;

class SRect {
public:
    SRect();
    ~SRect();
    SDL_CPP_OBJECT(SDL_Rect, _rt)
};

class SObj {
public:
    virtual void draw(SDL_Renderer* ) = 0;

    SWindow *parent() const { return _parent; }

private:
    SWindow *_parent;
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

#endif // __SBUTTON_H
