#ifndef __SWINDOW_H
#define __SWINDOW_H

#include "SDL_events.h"
#include "utils.h"
#include "sobj.h"
#include "ssurface.h"

#include <string>

#define COLOR_BIT 4

NAMESPACE_SDL_BEGIN

class SSurface;
class Scene;
class SApp;

class SWindow : public SObj, public SdlStruct<SDL_Window> {
    PROPERTY(quilt, bool)
    PROPERTY(w, int)
    PROPERTY(h, int)
public:
    explicit SWindow(SApp& app);
    virtual ~SWindow();

public:
    void init();
    void show();
    void handleEvent();
    void destroy() override;

    void setBackground(std::string path);

    bool windowPro(SDL_WindowEvent &e);
private:
    void draw(SDL_Renderer*) override;
//    void draw(SDL_Renderer *r, SDL_Surface *s);

    void drawBackground();

    bool inputPro(SDL_Event &e);
    void updateSurfaceAndTexture();

    void DrawChildren(SDL_Renderer *r);
private:
    void updateWindow();

private:
    std::list<SObj*> _children;
    SDL_Renderer *_render{nullptr};
    //SSurface _surface;
    SDL_Surface *_surface{nullptr};
    SDL_Surface *_bkSurface{nullptr};
    SDL_Texture *_texture{nullptr};
    int _frame;
    Scene *_scene{nullptr};
};

NAMESPACE_SDL_END

#endif //__SWINDOW_H
