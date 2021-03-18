#include <stdio.h>

int abs(int);
void swap(int*, int*);

int main(void)
{
    int a, b, c;
    printf("Input: ");
    scanf("%d %d %d", &a, &b, &c);

    a = abs(a);
    b = abs(b);
    c = abs(c);

    if (a < b)
        swap(&a, &b);
    if (b < c)
        swap(&b, &c);
    if (a < b)
        swap(&a, &b);

    printf("Result: %d %d %d\n", a, b, c);

    return 0;
}

int abs(int value)
{
    if (value < 0)
        return -value;
    else
        return value;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
