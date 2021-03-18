#include <stdio.h>

int x, y;

void Divide(int*, int*);

int main(void)
{
    int x, y;

    printf("Enter two integers: ");
    scanf("%d %d", &x, &y);

    Divide(&x, &y);
    Divide(&x, &y);

    return 0;
}

void Divide(int* a, int* b)
{
    x = *a;
    y = *b;
    *a = x / y;
    *b = x % y;

    printf("RESULT: %d / %d [Quotient: %d, Remainder: %d]\n", x, y, *a, *b);
}
