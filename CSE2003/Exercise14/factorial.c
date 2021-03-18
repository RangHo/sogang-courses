#include <stdio.h>

int Factorial(int);

int main(void)
{
    int number;

    scanf("%d", &number);

    printf("%d\n", Factorial(number));

    return 0;
}

int Factorial(int target)
{
    if (target == 0 || target == 1)
        return 1;

    return target * Factorial(target - 1);
}
