#include <iostream>
#include <string>

#include "sapp.h"
#include "swindow.h"
#include "sbutton.h"


USING_NAMESPACE_SDL

//SDL_Surface* LoadImage(std::string path) {
//    SDL_Surface *image = nullptr;
//    SDL_RWops *rwop;
//    rwop=SDL_RWFromFile(path.c_str(), "rb");
//    image=IMG_LoadJPG_RW(rwop);
//    if(!image) {
//        DLOG("load image error: %s\n", IMG_GetError());
//        // handle error
//    }

//    return image;
//}

int main(int argc, char** argv) {
    SApp app;
//    auto surface = LoadImage("C:\\Users\\longqi\\Desktop\\yuan.jpg");
    SWindow sw(app);
#ifdef _WIN32
    sw.setBackground("C:\\Users\\orcno\\Pictures\\Saved Pictures\\yueyetu.png");
#else
    sw.setBackground("/home/orcno/Pic/Wallpapers/xiaoyuan.jpg");
#endif
    sw.show();

    SButton btn(&sw);

    return app.exec(); 
}
