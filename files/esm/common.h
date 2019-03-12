#ifndef COMMON_H
#define COMMON_H

#include <QtGlobal>

typedef uint32_t NAME;
typedef uint32_t Color;

inline NAME swapName(NAME name)
{
    return (name >> 24 |
           ((name << 8) & 0x00FF0000) |
           ((name >> 8) & 0x0000FF00) |
           name << 24);
}

#endif // COMMON_H
