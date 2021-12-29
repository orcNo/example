#ifndef __WINDOW_H
#define __WINDOW_H

struct SDL_Window;

class SWindow {
    operator SDL_Window*() { return _window; }
    operator const SDL_Window*() const { return _window; }
    bool isAveliable() const { return _window; }

private:
    SDL_Window *_window;
};

#endif // __WINDOW_H
