#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

class Logger {
public:
    explicit Logger();

    const Logger& operator<<(const char* str) const;
    static void debug(const char* format, ...);

private:
    static FILE *_logf;
};

#endif // LOGGER_H
