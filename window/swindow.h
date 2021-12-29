#ifndef __SWINDOW_H
#define __SWINDOW_H

#include <list>

struct SDL_Renderer;
struct SDL_Window;

class SObj;

#ifndef SDL_CPP_OBJECT
#define SDL_CPP_OBJECT(type, var) \
public: \
    operator type*() { return var; } \
    operator const type*() const { return var; } \
    bool isAveliable() const { return var; } \
private: \
    type *var;
#endif

class SWindow {
    SDL_CPP_OBJECT(SDL_Window, _window)
public:
    SWindow() = default;
    explicit SWindow(SDL_Window *w);
//    explicit SWindow(const SWindow&);

    void draw(SDL_Renderer* r);

private:
    void addChild(SObj *c);

private:
    std::list<SObj*> _children;
};

#endif // __SWINDOW_H
