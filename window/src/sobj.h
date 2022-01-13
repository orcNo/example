#ifndef __SOBJ_H
#define __SOBJ_H

#include "utils.h"

#include <list>

#ifdef WIN32
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <SDL_surface.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#endif

template <typename T>
class SdlStruct {
public:
    virtual ~SdlStruct() { destroy(); }
public:
    inline operator T*() { return _sdl_var; }
    inline operator const T*() const { return _sdl_var; }
    //inline SdlStruct& operator =(T* v) { if (_sdl_var) destroy(); _sdl_var = v; return *this; }
    inline T* get() const { return _sdl_var; }
    inline T* operator ->() { return _sdl_var; }
    inline const T* operator ->() const { return _sdl_var; }
    inline void setVar(T* v) { destroy(); _sdl_var = v; }
    inline bool isAveliable() const { return _sdl_var != nullptr; }

    virtual void destroy() { if(_sdl_var) free(_sdl_var); _sdl_var = nullptr; }

private:
protected:
    T* _sdl_var{nullptr};
};

#ifndef SDL_CPP_OBJECT
#define SDL_CPP_OBJECT(type, var) \
public: \
    inline operator type*() { return var; } \
    inline operator const type*() const { return var; } \
    inline bool isAveliable() const { return var; } \
private: \
    type *var;
#endif

NAMESPACE_SDL_BEGIN

class SObj {
public: 
    explicit SObj(SObj *paren = nullptr);
    virtual ~SObj();

public:
    void setParent(SObj *p);
    std::list<SObj*> children() const { return _vchild; }

    virtual void draw(SDL_Renderer *) = 0;

protected:
    virtual bool update();
    void drawTo(SObj *);

    SDL_Surface* surface() const { return _surface;}

    std::list<SObj*> getDutyObj();

private:
    SDL_Surface *_surface;
    std::list<SObj*> _vchild;
    SObj *_parent;
    bool _changed;
    SDL_Rect _rt;
};

NAMESPACE_SDL_END
#endif //__SOBJ_H
