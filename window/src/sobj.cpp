#include "sobj.h"

#include "SDL_pixels.h"
#include "SDL_surface.h"

USING_NAMESPACE_SDL

SObj::SObj(SObj* parent)
    : _parent(nullptr)
    , _changed(true) {
    _surface = SDL_CreateRGBSurfaceWithFormat(0, _rt.w, _rt.h, 32, SDL_PIXELFORMAT_RGBA32);
    setParent(parent);
}

SObj::~SObj() {
}

void SObj::setParent(SObj *p) {
    if (_parent == p)
        return;

    if (_parent)
        _parent->_vchild.remove(this);

    _parent = p;
    _parent->_vchild.push_back(this);
}

bool SObj::proEvent(const SDL_Event& e) {
    auto ite = _vchild.begin();
    for(;ite != _vchild.end(); ++ite) {
        if ((*ite)->proEvent(e))
            return true;
    };
}

bool SObj::update() {
    auto dlist = getDutyObj();
    if (!dlist.size())
        return false;

    for (auto ite : dlist) {
        (*ite).drawTo(this);
        (*ite)._changed = false;
    }
    return true;
}
std::list<SObj*> SObj::getDutyObj() {
    std::list<SObj *>dutyList;
    auto ite = _vchild.begin();
    for(;ite != _vchild.end(); ++ite) {
        dutyList.merge((*ite)->getDutyObj());
    }
    
    return dutyList;
}
    
void SObj::drawTo(SObj *) {
}
