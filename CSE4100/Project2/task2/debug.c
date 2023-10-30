#include "debug.h"

static sem_t debug_padlock;

void debug_init(void)
{
    Sem_init(&debug_padlock, 0, 1);
}

void debug_lock(void)
{
    P(&debug_padlock);
}

void debug_unlock(void)
{
    V(&debug_padlock);
}
