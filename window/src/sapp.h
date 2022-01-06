#include "utils.h"

#include <SDL.h>
#include <SDL_image.h>

//#include <memory>
#include <cstddef>

NAMESPACE_SDL_BEGIN

class SWindow;

class SApp {
public:
    SApp();
    SApp(const SApp&) = delete;

//    void* operator new(std::size_t size);

public:
    static SApp *getInstance();
    int exec();
    
    void setWindow(SWindow* w) { _sw = w; }
private:
    SWindow *_sw{nullptr};
    //static std::shared_ptr<SApp> _ins;
    static SApp* _ins;
};

NAMESPACE_SDL_END
