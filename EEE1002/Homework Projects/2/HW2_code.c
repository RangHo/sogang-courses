#include <stdio.h>
#include <stdlib.h>

int mul(int, int);

int main()
{
    int a = 5;
    int b = 10;
    int c = 0;

    c = mul(a, b);
    printf("multiplication of %d and %d is %d", a, b, c);

    return 0;
}

int mul(int x, int y)
{
    int p;
    p = x * y;
    return (p);
}