#include <Windows.h>
#include <debugapi.h>
#include <atlconv.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include "utils.h"

const float D_PI = 3.1415926f;

wchar_t* a2w(const char* a) {
    size_t len = strlen(a) + 1;
    size_t converted = 0;
    wchar_t *w;
    w = (wchar_t*)malloc(len*sizeof(char));
    mbstowcs_s(&converted, w, len, a, _TRUNCATE);

    return w;
}

#ifdef WIN32
#ifndef UNICODE
void winprintf(const char* fmt, ...) {
    char buf[1024];
    va_list aptr;
    int ret;

    va_start(aptr, fmt);
    ret = vsprintf(buf, fmt, aptr);
    assert(ret >= 0);
    va_end(aptr);

    //wchar_t *wbuf = a2w(buf);
    //OutputDebugString(wbuf);
    OutputDebugString(buf);
    //free((void*)wbuf);
}
#else
void winprintf(const wchar_t* fmt, ...) {
    wchar_t buf[1024];
    va_list aptr;
    int ret;

    va_start(aptr, fmt);
    ret = vswprintf(buf, fmt, aptr);
    assert(ret >= 0);
    va_end(aptr);

    //wchar_t *wbuf = a2w(buf);
    //OutputDebugString(wbuf);
    OutputDebugString(buf);
    //free((void*)wbuf);
}
#endif
#endif

//inline float radians(float f) {
//    return f * D_PI / 180.0f;
//}
