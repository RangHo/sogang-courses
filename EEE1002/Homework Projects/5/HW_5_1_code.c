#include <stdio.h>

#define N 2147483647
#define A 2

int main()
{
    unsigned long long a = A;

    while (a < N) {
        printf("%llu\n", a);
        a *= 2;

        if (a == 0) {
            break;
        }
    }

    return 0;
}
