#include <stdio.h>

int main(void)
{
    int dividend, divisor;

    printf("Input two integers: ");
    scanf("%d %d", &dividend, &divisor);

    printf("%d / %d is %d with a remainder of %d.\n", dividend, divisor, dividend / divisor,
        dividend % divisor);

    return 0;
}
