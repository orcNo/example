#include "sapp.h"

#include <cstdlib>
#include <memory>

#include <SDL_ttf.h>

#include "utils.h"
#include "swindow.h"

USING_NAMESPACE_SDL

//std::shared_ptr<SApp> SApp::_ins = nullptr;
SApp* SApp::_ins = nullptr;

SApp::SApp() {
    if (_ins) {
        return;
    }

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    TTF_Init();

    _ins = this;
}

//void* SApp::operator new(std::size_t size) {
//    if (!_ins)
//        return malloc(sizeof(SApp));
//    return (void*)_ins;
//}

SApp* SApp::getInstance() {
    return _ins;
}

int SApp::exec() {
    if (!_sw)
        return -1;

    while (!_sw->quilt()) {
        _sw->handleEvent();
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
