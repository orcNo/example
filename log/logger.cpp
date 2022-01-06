#include "logger.h"

#include <stdarg.h>

FILE *Logger::_logf;// = nullptr;

Logger::Logger() {

}

const Logger& Logger::operator<<(const char* str) const {
    if (!_logf) {
#ifdef WIN32
        auto err = fopen_s(&_logf, "./tmp.log", "wb+");
        if (err) {

        }
#else
#endif
    }
    fprintf(_logf, "%s", str);
    return *this;
}

 void Logger::debug(const char* format, ...) {
#ifdef WIN32
    if (!_logf) {
        auto err = fopen_s(&_logf, "./tmp.log", "A+");
        if (err) {

        }
    }

    va_list vl;
    char buf[1024];

    va_start(vl, format);
    vsprintf_s(buf, format, vl);
    if (_logf)
        fprintf(_logf, "%s", buf);

    va_end(vl);
#endif
}
