#ifndef __UTILS__H
#define __UTILS__H

#define SDL sdl
#define NAMESPACE_SDL_BEGIN namespace SDL {
#define NAMESPACE_SDL_END }
#define USING_NAMESPACE_SDL using namespace SDL;

#define PROPERTY(x, type) \
    private: type _##x; \
    public: inline type x() const { return _##x;} \
    public: void set##x(const type& v) { _##x = v;}

extern const float D_PI;
inline float radians(float f) {
    return f * D_PI / 180.0f;
}

#ifdef WIN32
void winprintf(const char* fmt, ...);
#define LOG winprintf
#define DLOG winprintf
#define ELOG winprintf
#else
#define LOG printf
#define DLOG printf
#define ELOG printf
#endif


//TODO: 如是不是linux要打开
#ifndef UNIX
#define rndm 0x100000000LL
#define rndc 0xB16
#define rnda 0x5DEECE66DLL

static unsigned long long seed = 1;

static double drand48(void)
{
    seed = (rnda * seed + rndc) & 0xFFFFFFFFFFFFLL;
    unsigned int x = seed >> 16;
    return  ((double)x / (double)rndm);
}
#endif

//template <typename T>
//bool MIN(T t1, T t2) {
//    return t1 > t2 ? t2 : t1;
//}

#endif
