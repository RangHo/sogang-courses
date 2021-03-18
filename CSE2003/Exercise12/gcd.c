#include <stdio.h>

void func_gcd(int, int, int*);

int main(void)
{
    int first, second, result;

    printf("Input first number: ");
    scanf("%d", &first);

    printf("Input second number: ");
    scanf("%d", &second);

    func_gcd(first, second, &result);

    printf("GCD: %d\n", result);

    return 0;
}

void func_gcd(int a, int b, int* gcd)
{
    int dividend, divisor, remainder;
    dividend = a;
    divisor = b;

    for (remainder = -1; remainder != 0;) {
        remainder = dividend % divisor;
        dividend = divisor;
        divisor = remainder;
    }

    *gcd = dividend;
}
