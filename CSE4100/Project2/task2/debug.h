#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#include "csapp.h"

#define DEBUG 1

#ifdef DEBUG
#   define debug(...) \
    do { \
        debug_lock(); \
        printf("%s: ", __func__); \
        printf(__VA_ARGS__); \
        debug_unlock(); \
    } while (0)
#else
#   define debug(...)
#endif

void debug_init(void);

void debug_lock(void);

void debug_unlock(void);

#endif /* __DEBUG_H__ */
