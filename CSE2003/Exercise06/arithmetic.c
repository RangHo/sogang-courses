#include <stdio.h>

int x, y;

void Calculate(int*, int*);
void PrintResult(int, int);

int main(void)
{
    printf("Enter two numbers: ");
    scanf("%d %d", &x, &y);

    PrintResult(x, y);

    return 0;
}

void Calculate(int* a, int* b)
{
    x = *a + *b;
    y = *a - *b;

    *a = ((x + y) / 2) * ((x - y) / 2);
    *b = ((x + y) / 2) / ((x - y) / 2);
}

void PrintResult(int a, int b)
{
    Calculate(&a, &b);
    printf("x + y = %d\n", x);
    printf("x - y = %d\n", y);
    printf("x * y = %d\n", a);
    printf("x / y = %d\n", b);
}
