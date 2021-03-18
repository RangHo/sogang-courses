#include <stdio.h>

void swap(int*, int*);

int main(void)
{
    int a, b, c;

    printf("Input 3 integers: ");
    scanf("%d %d %d", &a, &b, &c);

    if (a < b)
        swap(&a, &b);
    if (b < c)
        swap(&b, &c);
    if (a < b)
        swap(&a, &b);

    printf("Sorted integers: %d %d %d", a, b, c);

    return 0;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
