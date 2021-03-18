#include <stdio.h>

void divideRemainder(int*, int*);

int main(void)
{
    int dividend, divisor;

    printf("Input two numbers: ");
    scanf("%d %d", &dividend, &divisor);

    divideRemainder(&dividend, &divisor);

    printf("------------------------\n");
    printf("Quotient: [%d] | Remainder: [%d]\n", dividend, divisor);

    return 0;
}

void divideRemainder(int* a, int* b)
{
    int dividend = *a;
    int divisor = *b;

    *a = dividend / divisor;
    *b = dividend % divisor;
}
