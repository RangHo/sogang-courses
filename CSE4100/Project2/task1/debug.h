#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#define DEBUG 1

#ifdef DEBUG
#   define debug(...) \
    do { \
        printf("%s: ", __func__); \
        printf(__VA_ARGS__); \
    } while (0)
#else
#   define debug(...)
#endif

#endif /* __DEBUG_H__ */
