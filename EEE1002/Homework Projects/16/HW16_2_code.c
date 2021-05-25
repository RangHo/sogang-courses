#include <stdio.h>

void stat();

int main()
{
    int i;
    for (i = 1; i <= 3; i++) {
        stat();
    }

    return 0;
}

void stat()
{
    static int x = 0;
    x = x + 1;
    printf("x = %d\n", x);
}