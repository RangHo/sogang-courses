#include <stdio.h>

void swap(float*, float*);

int main(void)
{
    float x, y;

    printf("Input two numbers.\n");
    printf("\tx: ");
    scanf("%f", &x);
    printf("\ty: ");
    scanf("%f", &y);

    printf("Before: x [%f] | y [%f]\n", x, y);

    swap(&x, &y);

    printf("After: x [%f] | y [%f]\n", x, y);

    return 0;
}

void swap(float* a, float* b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}
